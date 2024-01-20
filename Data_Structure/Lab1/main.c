/*******************************************************************************************
 * File Name	: Lab1.c
 * Description	: This file is the skeleton for Lab 1.

 * Instructions	: Complete the state machine as indicated in the comments inside each state.
 *
 * Student Name: Ajay Kumar
 * Student Number: 8831954
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define STACK_SIZE	140
#define BUFFER_SIZE	20


 /**
 * Brief: Structure to hold stack index and stack data
 */
typedef struct
{
	int8_t iIndex;
	char data[STACK_SIZE];

} tSTACK;


int runStateMachine(void);
bool pushIntoStack(tSTACK* pStack, char* bData);
bool popFromStack(tSTACK* pStack);
void printOutStackContents(tSTACK* pStack);
bool isStackEmpty(int8_t stackIndex);
bool isStackFull(int8_t stackIndex);


/**
* Brief: Enum to represent type of command.
*/
typedef enum
{
	COMMAND_EXIT = 0,
	COMMAND_PUSH,
	COMMAND_POP,
	COMMAND_PRINT,

} tCOMMAND;



int main()
{
	while (1)
	{
		runStateMachine();
	}

	return 0;
}


/**
* Brief: A simple state machine that accepts commands from the user via
* the terminal to push and pop data into/from a stack structure.
*/
int runStateMachine(void)
{
	tCOMMAND command = 0;
	static char inputString[BUFFER_SIZE];	// Stores the user's input string
	static tSTACK stack;

	static enum
	{
		START_STATE,
		INITIALIZATION_STATE,
		WAIT_FOR_COMMAND_STATE,
		WAIT_FOR_INPUT_STATE,
		PUSH_TO_STACK_STATE,
		POP_FROM_STACK_STATE,
		PRINT_STACK_CONTENTS_STATE,
		FINISH_STATE

	} STATE = START_STATE;


	switch (STATE)
	{
		case START_STATE:
		{
			printf("Program started!\n");
			STATE = INITIALIZATION_STATE;
			break;
		}

		case INITIALIZATION_STATE:
		{
			// Reset stack data and index then go to wait for command state

			// Write your code here... 
			stack.iIndex = -1;
			STATE = WAIT_FOR_COMMAND_STATE;
			break;
		}

		case WAIT_FOR_COMMAND_STATE:

		{	// User enters the command type from the terminal
			// 1: Go to WAIT_FOR_INPUT_STATE
			// 2: Go to POP_FROM_STACK_STATE
			// 3: Go to PRINT_STACK_CONTENTS_STATE
			// 0: Go to	FINISH_STATE
			// Program should neglect any other input

			// Write your code here...
			int UsrCmd =1;
			printf("Enter 0 to finish \nEnter 1 to PUSH \nEnter 2 to POP\nEnter 3 to PRINT\n");
			scanf_s("%d", &UsrCmd);
			int c;
			while ((c = getchar()) != '\n' && c != EOF) {};
			switch (UsrCmd)
			{
			case COMMAND_EXIT:
			{
				STATE = FINISH_STATE;
				break;
			}
			case COMMAND_PUSH:
			{
				STATE = WAIT_FOR_INPUT_STATE;
				break;
			}
			case COMMAND_POP:
			{
				STATE = POP_FROM_STACK_STATE;
				break;
			}
			case COMMAND_PRINT:
			{
				STATE = PRINT_STACK_CONTENTS_STATE;
				break;
			}
			default:
			{
				STATE = WAIT_FOR_COMMAND_STATE;
				printf("Enter Valid Input\n");
				break;
			}
			}

			break;
		}

		case WAIT_FOR_INPUT_STATE:
		{
			// User enters the input string from terminal
			// then state machine goes to PUSH_TO_STACK_STATE

			// Write your code here...
			printf("Enter string or character to push:");
			fgets(inputString, BUFFER_SIZE, stdin);
			int length = strcspn(inputString, "\n");
			inputString[length] = '\0';
			STATE = PUSH_TO_STACK_STATE;
			break;
		}

		case PUSH_TO_STACK_STATE:
		{
			// Push all data available in input string into the stack
			// Check for overflow condition
			// After all data is pushed, go to WAIT_FOR_COMMAND_STATE

			// Write your code here...
			pushIntoStack(&stack, inputString);
			STATE = WAIT_FOR_COMMAND_STATE;
			break;

		}
		case POP_FROM_STACK_STATE:
		{
			// Pop out the stack contents and display the data popped 
			// Go to WAIT_FOR_COMMAND_STATE

			// Write your code here...
			popFromStack(&stack);
			STATE = WAIT_FOR_COMMAND_STATE;
			break;
		}

		case PRINT_STACK_CONTENTS_STATE:
		{
			// Print out a message indicating stack is empty if the stack has no data.
			// Otherwise display the stack contents without popping out the data.
			printOutStackContents(&stack);
			STATE = WAIT_FOR_COMMAND_STATE;
			break;
		}

		case FINISH_STATE:
		{
			// Display what's inside the stack then exit the program
			// Write your code here...
			printOutStackContents(&stack);
			exit(0);
		}

		default:
		{
			STATE = START_STATE;
			break;
		}
		
	}
}


bool pushIntoStack(tSTACK* pStack, char* bData)

{
	bool fResult = false;

	while (*bData != '\0')
	{
		
		if (isStackFull(pStack->iIndex)!=true)
		{
			
			pStack->data[++(pStack->iIndex)] = *bData++;
			fResult = true;
			//printf("%d",pStack->iIndex);
		}
		else
		{
			printf("Error, stack overflow\n");
			break;
		}

	}
	memset(bData, '\0', sizeof bData);
	return fResult;
}


bool popFromStack(tSTACK* pStack)
{
	bool fResult = false;
	if (isStackEmpty(pStack->iIndex) != true)
	{
		char pData;
		pData = pStack->data[(pStack->iIndex)--];
		printf("POPed element is : %c\n", pData);
		fResult = true;
	}
	return fResult;
}



void printOutStackContents(tSTACK* pStack)
{
	if (isStackEmpty(pStack->iIndex))
	{
		;
	}
	else
	{
		for (int i = 0; i <= pStack->iIndex; i++)
		{
			printf("%c", pStack->data[i]);
		}
		printf("\n");
	}
}


bool isStackEmpty(int8_t stackIndex)
{
	bool fResult = false;
	if (stackIndex < 0)
	{
		printf("stack is empty\n");
		fResult = true;
	}
	return fResult;
}


bool isStackFull(int8_t stackIndex)
{
	bool fResult = false;
	if (stackIndex >= STACK_SIZE )
	{
		fResult = true;
	}
	return fResult;
}


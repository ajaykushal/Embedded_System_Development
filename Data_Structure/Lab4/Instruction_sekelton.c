/*******************************************************************************
* File Name:		Lab4.c
* Description:		Implementation of a hash
*
*  Instructions:
*	- Use the skelton code in this file to implement a hash table.
*	- Implement the following functions:
*		hash_AddDataIntoHashTable()
*		hash_SearchForDataInHashTable()
*		hash_HashingFunction()
*	- After implemeting the above functions, the program should be able to ask the user for input values
*	  to add to the hash table. The program should be able of generating hash values for the inputs and
	  handle collisions. The program will then let the user check for values entered into the hash table and
	  provide its location in the table (if a match was found).

* Student Name:
* Student Number:
******************************************************************************
*/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


uint8_t hash_AddDataIntoHashTable(char* pInputData, uint8_t bufferLength);
uint8_t hash_SearchForDataInHashTable(char* pData, uint8_t bufferLength);
uint8_t hash_HashingFunction(char* pInputBuffer);


#define INPUT_BUFFER_SIZE	200	// Local buffer used for adding data to the hash table
#define HASH_SIZE		10	// Size of hash table to be used (this value is set small for testing purposes)

/*
*  Brief: Data structure used to keep track of hashed data
*/
typedef struct hashStruct {
	char* pBuffer;                      // Pointer to data stored in hash (you will need to malloc space for string to be stored)
	struct hashStruct* pNextHashData;  // Pointer to next item in this hash bucket (or NULL if no more)
}hashStruct_t;

hashStruct_t* hashtable[HASH_SIZE];           // Empty hash table structure (note this is basically an arrary of linked list heads)

int main()
{
	char    inputBuffer[INPUT_BUFFER_SIZE];
	uint8_t hashValue;

	// Initialize the hash table to empty one
	for (int i = 0; i < HASH_SIZE; i++)
	{
		if ((hashtable[i] = (hashStruct_t*)calloc(1, sizeof(hashStruct_t))) == NULL)
		{
			printf("calloc failed!\n");
			return(-1);
		}
	}

	// Add to hash table loop
	while (1)
	{
		printf("enter data to be added to hash table or exit when done\n");

		// Get strings from the console and place in hash until nothing entered
		scanf_s("%s", inputBuffer, INPUT_BUFFER_SIZE);

		// Stop adding data into hash table when "exit" is entered
		if (strcmp(inputBuffer, "exit") == 0)
		{
			break;
		}

		hashValue = hash_AddDataIntoHashTable(inputBuffer, strlen(inputBuffer));
		if (hashValue == HASH_SIZE)
		{
			printf("Error putting into hash table\n");
		}
		else
		{
			printf("Hash value: %u\n", hashValue);
		}

	}

	// Check if data is in hash table
	while (1)
	{
		uint8_t hashIndexNumber = 0;

		printf("Enter data to find, done when complete\n");

		// Get strings from the console and check if in hash table
		scanf_s("%s", inputBuffer, INPUT_BUFFER_SIZE);

		// Stop when "done" is entered
		if (strcmp(inputBuffer, "done") == 0)
		{
			break;
		}

		if ((hashIndexNumber = hash_SearchForDataInHashTable(inputBuffer, strlen(inputBuffer))) == HASH_SIZE)
		{
			printf("%s not found in hash table\n", inputBuffer);
		}
		else
		{
			printf("%s found in hash table at %u\n", inputBuffer, hashIndexNumber);
		}
	}

	return 0;
}

/**
* Description: Function to calculate a hash value to use for storing the data into the hash table
* Parameters:
*   pInputBuffer - a pointer to the buffer to be put into the hash table
* Return: Hash value calculated ( HASH_SIZE on failure)
*/

uint8_t hash_HashingFunction(char* pInputBuffer)
{
	uint8_t calculatedHashValue = 0;

	// Add code to create a hashed value here

	// Make sure if hash value is bigger than the table size, the value wraps
	return calculatedHashValue % HASH_SIZE;
}

/**
* Brief: Function to add a new entry to the hash table
* Parameters:
*   pInputData - Pointer to the data to be added into the hash table
*   bufferLength   - Number of characters in the buffer being put into the hash table
* Return: Hash value used ( HASH_SIZE on failure)
*/
uint8_t hash_AddDataIntoHashTable(char* pInputData, uint8_t bufferLength)
{
	uint8_t hashValue = hash_HashingFunction(pInputData);

	// Check if the value is in the hash
	// Add code to put data into the hash table here

	return hashValue;
}


/**
* Description   : Function to search for data in the hash table
* Parameters:
*   pData  - Pointer to data to search for in the hash table
*   bufferLength - Maxiumum number of characters that can be read
* Return: Hash value used ( return HASH_SIZE value on failure)
*/
uint8_t hash_SearchForDataInHashTable(char* pData, uint8_t bufferLength)
{
	uint8_t hashValue = hash_HashingFunction(pData);

	// Add your code here

	return hashValue;
}

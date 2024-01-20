/*******************************************************************************************
 * File Name	: Lab2.c
 *
 * Description	: This file is the skeleton code for lab 2 (Queues)
 *
 * Instructions	: Complete the following functions:
 *                  queue_Enqueue()
 *                  queue_Dequeue()
 *                  queue_IsFull()
 *                  queue_IsEmpty()
 *                  queue_UpdateDequeuedItems()
 *                  queue_DisplayDequeuedItems()
 *
 * Student Name: AJAY KUMAR
 * Student Number:8831954
 */


#include <stdio.h>
#include<stdint.h>
#include <time.h>
#include <stdbool.h>


#define MAX_SIZE 40     // Maximum size of a queue
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))


typedef enum
{
    HIGH_PRIORITY,
    MED_PRIORITY,
    LOW_PRIORITY,
    PRIORITY_END
} tQUEUE_PRIORITY;


typedef struct
{
    int32_t queueData[MAX_SIZE];
    int8_t rearIndex;
    int8_t frontIndex;
    tQUEUE_PRIORITY ePriority;
    time_t enqueueTime;
    uint8_t enqueueTimeoutPeriod;

} tQUEUE;


void queue_Init(tQUEUE* queueList);
bool queue_Enqueue(int32_t* pQueueData, int8_t* pFrontIndex, int8_t* pRearIndex, int32_t data);
bool queue_Dequeue(int32_t* pQueueData, int8_t* pFrontIndex, int8_t* pRearIndex, int32_t* pData);
bool queue_IsEmpty(int8_t frontIndex);
bool queue_IsFull(int8_t frontIndex, int8_t rearIndex);
void queue_DisplayDequeuedItems(int32_t* pDequeuedItems, uint8_t listLength, int8_t dequeueListIndex);
void queue_UpdateDequeuedItems(int32_t* pDequeuedItems, uint8_t listLength, int8_t* pDequeueListIndex, int32_t dequeuedItem);
void queue_DisplayAllQueues(tQUEUE* pQueueList);
void queue_DisplayQueue(int32_t* pQueueData, int8_t frontIndex, int8_t rearIndex);
void printCurrentTime(void);

/*** Do not change anything in this function ***/
int main(void)
{
    tQUEUE queueList[PRIORITY_END];
    int32_t data[3] = { 0 };
    int32_t dequeuedItems[128] = { 0 };
    int8_t dequeueListIndex = -1;
    time_t startTime;
    time_t currentTime;
    time_t dequeueTime;

    queue_Init(queueList);

    // Reset timers
    time(&startTime);
    time(&currentTime);
    time(&dequeueTime);

    // Enqueue two elements into each queue
    tQUEUE_PRIORITY ePriority;
    for (ePriority = 0; ePriority < PRIORITY_END; ePriority++)
    {
        uint32_t i;
        for (i = 0; i < 2; i++)
        {
            queue_Enqueue(queueList[ePriority].queueData, &queueList[ePriority].frontIndex, &queueList[ePriority].rearIndex, (++data[ePriority] << (8 * ePriority)));
        }
    }

    queue_DisplayAllQueues(queueList);

    // Run program for 30 seconds
    while (difftime(currentTime, startTime) < 30)
    {
        time(&currentTime);     // Capture current time

        /* Scan through list of queues and check if the conditions are met to enqueue for each queue */
        for (ePriority = 0; ePriority < PRIORITY_END; ePriority++)
        {
            /* Checks if the conditions are met to start enqueuing */
            if (difftime(currentTime, queueList[ePriority].enqueueTime) > queueList[ePriority].enqueueTimeoutPeriod)
            {
                queue_Enqueue(queueList[ePriority].queueData, &queueList[ePriority].frontIndex, &queueList[ePriority].rearIndex, (++data[ePriority] << (8 * ePriority)));
                time(&queueList[ePriority].enqueueTime);        // Capture enqueue time
                queue_DisplayAllQueues(queueList);
            }
        }

        // Dequeue every second (priority taken into consideration)
        if (difftime(currentTime, dequeueTime) > 1)
        {
            for (ePriority = 0; ePriority < PRIORITY_END; ePriority++)
            {
                if (queue_IsEmpty(queueList[ePriority].frontIndex) == false)
                {
                    int32_t dequeuedItem;
                    if (queue_Dequeue(queueList[ePriority].queueData, &queueList[ePriority].frontIndex, &queueList[ePriority].rearIndex, &dequeuedItem))
                    {
                        queue_UpdateDequeuedItems(dequeuedItems, ARRAY_LENGTH(dequeuedItems), &dequeueListIndex, dequeuedItem);
                    }
                    break;
                }
            }

            time(&dequeueTime);    // Capture dequeue time
            queue_DisplayAllQueues(queueList);
        }
    }

    queue_DisplayDequeuedItems(dequeuedItems, sizeof(dequeuedItems), dequeueListIndex);
    
    printCurrentTime();//print current command

    return 0;
}


/**
* Brief: This function initializes the list of queues
* Input: pQueueList - Pointer to list of queues
*/
void queue_Init(tQUEUE* pQueueList)
{
    tQUEUE_PRIORITY ePriority;
    for (ePriority = 0; ePriority < PRIORITY_END; ePriority++)
    {
        switch (ePriority)
        {
        case HIGH_PRIORITY:
            pQueueList[ePriority].enqueueTimeoutPeriod = 6;
            break;

        case MED_PRIORITY:
            pQueueList[ePriority].enqueueTimeoutPeriod = 4;
            break;

        case LOW_PRIORITY:
            pQueueList[ePriority].enqueueTimeoutPeriod = 2;
            break;

        default:
            break;
        }

        pQueueList[ePriority].rearIndex = -1;
        pQueueList[ePriority].frontIndex = -1;
        memset(&pQueueList[ePriority].queueData, 0, MAX_SIZE);
        time(&pQueueList[ePriority].enqueueTime);
    }
}


/**
 * Brief: This function enqueues a given data to a specific queue.
 *
 * Input:
 *      pQueueData - Pointer to queue
 *      pFrontIndex - Pointer to front index
 *      pRearIndex - Pointer to rear index
 *      data - Data to be enqueued
 *
 * Return: True if enqueuing was successful
 */
bool queue_Enqueue(int32_t* pQueueData, int8_t* pFrontIndex, int8_t* pRearIndex, int32_t data)
{
    // Check if the queue is full
    if (queue_IsFull(*pFrontIndex, *pRearIndex))
    {
        // If the queue is full, return false
        return false;
    }

    // Increment the rear index to enqueue the data
    *pRearIndex = (*pRearIndex + 1) % MAX_SIZE;
    pQueueData[*pRearIndex] = data;

    // Check if the queue was initially empty
    if (queue_IsEmpty(*pFrontIndex))
    {
        // If the queue was initially empty, set the front index to 0
        *pFrontIndex = 0;
    }

    // Return true to indicate that enqueuing was successful
    return true;
}



/**
 * Brief: This function dequeues an item from queue.
 * Input:
 *       pQueueData - Pointer to queue
 *       pFrontIndex - Pointer to front index
 *       pRearIndex - Pointer to rear index
 * Output:
 *       pData - Pointer to data to be dequeued
 * Return: True if dequeuing was successful
 */
bool queue_Dequeue(int32_t* pQueueData, int8_t* pFrontIndex, int8_t* pRearIndex, int32_t* pData)
{
    // Check if the queue is empty
    if (queue_IsEmpty(*pFrontIndex))
    {
        printf("Queue is empty, dequeue failed\n");
        return false;
    }
    // Check if there is only one element in the queue
    else if (*pFrontIndex == *pRearIndex)
    {
        *pData = pQueueData[*pFrontIndex];  // Retrieve the data from the front of the queue
        *pFrontIndex = -1;  // Set front and rear index to -1 to indicate an empty queue
        *pRearIndex = -1;
        // printf("Dequeue successful else if\n");
        return true;
    }
    // If there are more than one elements in the queue
    else
    {
        *pData = pQueueData[*pFrontIndex];  // Retrieve the data from the front of the queue
        (*pFrontIndex) = (*pFrontIndex + 1) % MAX_SIZE;  // Increment front index and wrap around to the beginning if necessary
        // printf("Dequeue successful\n");
        return true;
    }
}


/**
* Brief: This function is used to check if a certain queue is empty
* Inputs:
*       frontIndex - Front index
* Retrun: True if queue is empty.
*/
bool queue_IsEmpty(int8_t frontIndex)
{
    // Write your code here...
        // Check if front index and rear index are equal
    if (frontIndex == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}


/**
* Brief: This function is used to check if a certain queue is full
* Input:
*       frontIndex - Front index
*       rearIndex  - Rear index
* Retrun: True if queue is full.
*/
bool queue_IsFull(int8_t frontIndex, int8_t rearIndex)
{
    // Write your code here...
    // Check if the next index of the rear index is equal to the front index
    if ((rearIndex + 1) % MAX_SIZE == frontIndex)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * Brief: This function updates the list of dequeued items.
 *
 * Inputs:
 *      pDequeuedItems - Pointer to the list of dequeued items
 *      listLength - Length of the dequeued items list
 *      pDequeueListIndex - Pointer to the index of the last element in the dequeued items list
 *      dequeuedItem - The item that has been dequeued and needs to be added to the dequeued items list
 */
void queue_UpdateDequeuedItems(int32_t* pDequeuedItems, uint8_t listLength, int8_t* pDequeueListIndex, int32_t dequeuedItem)
{
    // Check if the dequeue list is full
    if (*pDequeueListIndex >= (listLength - 1))
    {
        printf("Dequeued items list is full\n");
    }
    else
    {
        // Increment the dequeue list index to add the new dequeued item
        (*pDequeueListIndex)++;

        // Store the dequeued item in the dequeued items list
        pDequeuedItems[*pDequeueListIndex] = dequeuedItem;

        // Print message indicating that the dequeued item has been stored in the dequeued items list
        // printf("Dequeued item stored in list\n");
    }
}



/*
 * Brief: This function displays the dequeued items from all queues
 * Inputs:
 *           pDequeuedItems - Pointer to dequeue items list
 *           bDequeueCounter - Number of items in the dequeued items list
 */
void queue_DisplayDequeuedItems(int32_t* pDequeuedItems, uint8_t listLength, int8_t dequeueListIndex)
{
    // Print a message indicating the start of the dequeued items display
    printf("Dequeued items: ");

    // Loop through each dequeued item and print it
    int i;
    for (i = 0; i <= dequeueListIndex; i++)
    {
        printf("%06X ", pDequeuedItems[i]);
    }

    // Print a newline character to separate the output from any subsequent messages
    printf("\n");
}


/**
* Brief: This function displays the contents of all the queues.
* Input: pQueueList - Pointer to list of queues
*/
void queue_DisplayAllQueues(tQUEUE* pQueueList)
{
    printf("\033[2J");      // Clear screen
    printf("\033[0;0H");    // Reset cursor

    uint32_t i;
    printf("Display all Queue\n");
    for (i = 0; i < PRIORITY_END; i++)
    {
        queue_DisplayQueue(pQueueList[i].queueData, pQueueList[i].frontIndex, pQueueList[i].rearIndex);
    }
}


/**
* Brief: This function displays the contents of a certain queue.
* Inputs:
*       pQueueData - Pointer to queue
*       frontIndex - Front index
*       rearIndex  - Rear index
*/
void queue_DisplayQueue(int32_t* pQueueData, int8_t frontIndex, int8_t rearIndex)
{
    if (queue_IsEmpty(frontIndex))
    {
        printf("empty\n");
    }
    else
    {
        int8_t i;
        //printf("front index : %d and Rear index is : %d\n", frontIndex, rearIndex);
        for (i = frontIndex; i != rearIndex; i = (i + 1) % MAX_SIZE) 
        {
            printf("%06X ", pQueueData[i]);
        }
        printf("%06X\n", pQueueData[i]);
    }
}

/**
 * Brief: Get and print the current time
 */
void printCurrentTime() {
    char currentTimeStr[26];
    time_t currentTime;
    time(&currentTime); // get the current time
    ctime_s(currentTimeStr, sizeof(currentTimeStr), &currentTime);
    printf("Current time = %s", currentTimeStr); // print the current time
}

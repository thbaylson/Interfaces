#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Malloc.h"
#include "queue.h"
#include "arrayQueue.h"

enum constraints {INITIAL_CAPACITY = 10, RESIZE_FACTOR = 2};

/* stuct arrayQueue- Array implementation of the Queue
 * abstract data type.
 * @fields: data: The integer values in the ArrayQueue
 * @fields: capacity: The maximum amount of elements before resizing
 * @fields: size: The number of elements in the ArrayQueue
 */
struct arrayQueue{
    int *data;
    int capacity;
    int size;
};
typedef struct arrayQueue ArrayQueue;

/* arrayQueueEnqueue- This function will add the given int to 
 * the end of the given Queue
 * @params: q: The Queue pointer that needs to be enqueued
 * @params: num: The data to add to the Queue
 */
static void arrayQueueEnqueue(Queue* q, int num){
    /* Set up ArrayQueue data to be manipulated*/
    ArrayQueue* arQ = ((ArrayQueue*)(q->privateData));
    int size = arQ->size;
    int capacity = arQ->capacity;
    
    /* Ensure the size doesn't exceed the capacity*/
    if(size == capacity){
        arQ->data = Realloc(arQ->data, sizeof(int) * (capacity * RESIZE_FACTOR));
        arQ->capacity = capacity * RESIZE_FACTOR;
    }

    /* Find where to enqueue in the array and then enqueue*/
    arQ->data[size] = num;
    arQ->size++;
}

/* arrayQueuePeek- This function will return the first 
 * element in the given Queue
 * @params: q: The Queue pointer to peek at
 * @return: int: The first element of the Queue
 */
static int arrayQueuePeek(Queue* q){
    ArrayQueue* arQ = q->privateData;
    int* loc = arQ->data;
    int num = *loc;
    loc = NULL;
    return num;
}

/* arrayQueueDequeue- This function will remove the first 
 * element from the Queue, and free any memory associated 
 * with the Node containing that first item
 * @params: A pointer to a Queue to dequeue
 */
static void arrayQueueDequeue(Queue* q){
    ArrayQueue* arQ = q->privateData;
    int* loc = arQ->data;
    int size = arQ->size;
    int i;

    /* Because each element is assigned the value of the next, we must only
     * consider up to the (size - 1) element*/
    for(i = 0; i < size - 1; i++){
        *loc = *(loc + 1);
        loc++;
    }
    arQ->size--;
}

/* arrayQueueSize- This function will return the size of the given Queue
 * @params: q: A pointer to the queue for which to find the size of
 * @return: int: The size of the given Queue
 */
static int arrayQueueSize(Queue* q){
    return ((ArrayQueue*)(q->privateData)) -> size;
}

/* arrayQueuePrint- This function will print the contents of the given 
 * Queue to the screen. The output of this method should be: [first, second, thid, ...]
 * @params: q: A pointer to the queue to be printed
 */
static void arrayQueuePrint(Queue* q){
    int size = ((ArrayQueue*)(q->privateData)) -> size;
    int *loc = ((ArrayQueue*)(q->privateData)) -> data;
    int i;

    printf("[");
    for(i = 0; i < size; i++){
        /* This ensures the last printed element doesn't have a hanging comma*/
        if(i == size - 1){
            printf("%d", *loc);
        }
        else{
            printf("%d, ", *loc);
            loc++;
        }
    }
    printf("]\n");
    loc = NULL;
}

/* newArrayQueue- This method will initialize the given Queue object 
 * to a ArrayQueue. This will happen in two steps: (1) dynamically 
 * creating an appropriately initialized ArrayQueue and storing that 
 * in the privateData field of the Queue and (2) initializing each of 
 * the pointers to functions to the corresponding static functions described above.
 * @params: q: A pointer to the queue object to be made into a ArrayQueue
 */
void newArrayQueue(Queue* q){
    /* Initialize an ArrayQueue and set it to the queue field "privateData"
     * The data of the ArrayQueue points to dynamically allocated memory
     * The initial capacity is based on the contraints enumeration*/
    ArrayQueue* arQ = Malloc(sizeof(ArrayQueue));
    arQ->data = Malloc(sizeof(int) * INITIAL_CAPACITY);
    arQ->capacity = INITIAL_CAPACITY;
    arQ->size = 0;
    q->privateData = arQ;

    /* Set pointers of Queue abstraction to ArrayQueue functions*/
    q->enqueue = arrayQueueEnqueue;
    q->dequeue = arrayQueueDequeue;
    q->print = arrayQueuePrint;
    q->peek = arrayQueuePeek;
    q->size = arrayQueueSize;
}

/* deleteArrayQueue- This method will free any dynamically allocated 
 * memory associated w/ the given Queue and set all pointers to NULL
 * @params: q: A pointer to the queue that must be freed
 */
void deleteArrayQueue(Queue* q){
    ArrayQueue* arQ = ((ArrayQueue*)(q->privateData));
    free(arQ->data);
    arQ->size = 0;
    arQ->capacity = 0;
    free(q->privateData);
}

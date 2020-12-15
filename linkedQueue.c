#include <stdio.h>
#include <stdlib.h>

#include "Malloc.h"
#include "queue.h"
#include "linkedQueue.h"

enum constraints {INITIAL_CAPACITY = 10, RESIZE_FACTOR = 2};

/* struct node- A singular point of data in a connected
 * LinkedQueue implementation.
 * @fields: data: The integer value wrapped by a Node
 * @fields: next: The next Node in the LinkedQueue
 */
typedef struct node Node;
struct node{
    int data;
    Node* next;
};

/* struct linkedQueue- Linked implementation of the Queue
 * abstract data type.  
 * @fields: head: A pointer to the first Node
 * @fields: tail: A pointer to the last Node
 * @fields: size: The number of elements in the LinkedQueue
 */
struct linkedQueue{
	Node* head;
	Node* tail;
	int size;
};
typedef struct linkedQueue LinkedQueue;

/* newNode- Assigns an int to a Node and returns a pointer to a Node
 * @params: num: the integer value
 * @params: node: the new Node to be assigned data
 * @return: Node*: A pointer to the newly created Node
 */
static Node* newNode(int num, Node* node){
    node->data = num;
    node->next = Malloc(sizeof(Node));
    return node;
}

/* deleteNode- The function should delete all dynamically allocated 
 * memory associated with that Node
 * @params: node: The Node in the queue to be deleted
 */
static void deleteNode(Node* node){
    free(node);
    node = NULL;
}

/* linkedQueueEnqueue- This function will add the given int to 
 * the end of the given Queue
 * @params: q: The Queue pointer that needs to be enqueued
 * @params: num: The data to add to the Queue
 */
static void linkedQueueEnqueue(Queue* q, int num){
    LinkedQueue* liQ = ((LinkedQueue*)(q->privateData));
    int size = liQ->size;
    int i;

	/* If size is 0 then the head has not been initialized yet*/
    if(size == 0){
        liQ->head = newNode(num, Malloc(sizeof(Node)));
        liQ->tail = liQ->head;
    }
    else{
        Node* currentNode = liQ->head;
        for(i = 0; i < size; i++){
            currentNode = currentNode->next;
        }
        currentNode = newNode(num, currentNode);
		liQ->tail = currentNode;
    }
    liQ->size++;
}

/* linkedQueuePeek- This function will return the first 
 * element in the given Queue
 * @params: q: The Queue pointer to peek at
 * @return: int: The first element of the Queue
 */
static int linkedQueuePeek(Queue* q){
    LinkedQueue* liQ = ((LinkedQueue*)(q->privateData));
    Node* head = liQ->head;
    int num = head->data;
    return num;
}

/* linkedQueueDequeue- This function will remove the first 
 * element from the Queue, and free any memory associated 
 * with the Node containing that first item
 * @params: A pointer to a Queue to dequeue
 */
static void linkedQueueDequeue(Queue* q){
    LinkedQueue* liQ = ((LinkedQueue*)(q->privateData));
    Node* temp = liQ->head;
    liQ->head = (liQ->head)->next;
    liQ->size--;
    deleteNode(temp);
}

/* linkedQueueSize- This function will return the size of the given Queue
 * @params: q: A pointer to the queue for which to find the size of
 * @return: int: The size of the given Queue
 */
static int linkedQueueSize(Queue* q){
    LinkedQueue* liQ = ((LinkedQueue*)(q->privateData));
    int size = liQ->size;
    return size;
}

/* linkedQueuePrint- This function will print the contents of the given 
 * Queue to the screen. The output of this method should be: [first, second, thid, ...]
 * @params: q: A pointer to the queue to be printed
 */
static void linkedQueuePrint(Queue* q){ 
    LinkedQueue* liQ = ((LinkedQueue*)(q->privateData));
    Node* currentNode = liQ->head;
    int size = liQ->size;
    int i;

    printf("[");
    for(i = 0; i < size; i++){
        if(i == size - 1){
            printf("%d", currentNode->data);
        }
        else{
            printf("%d, ", currentNode->data);
        }
        currentNode = currentNode->next;
    }
    printf("]\n");
    currentNode = NULL;
}

/* newLinkedQueue- This method will initialize the given Queue object 
 * to a LinkedQueue. This will happen in two steps: (1) dynamically 
 * creating an appropriately initialized LinkedQueue and storing that 
 * in the privateData field of the Queue and (2) initializing each of 
 * the pointers to functions to the corresponding static functions described above.
 * @params: q: A pointer to the queue object to be made into a LinkedQueue
 */
void newLinkedQueue(Queue* q){
    LinkedQueue* liQ = Malloc(sizeof(LinkedQueue));
    liQ->head = NULL;
    liQ->tail = NULL;
    liQ->size = 0;
    q->privateData = liQ;

    /* Set pointers of Queue abstraction to LinkedQueue functions*/
    q->enqueue = linkedQueueEnqueue;
    q->dequeue = linkedQueueDequeue;
    q->print = linkedQueuePrint;
    q->peek = linkedQueuePeek;
    q->size = linkedQueueSize;
}

/* deleteLinkedQueue- This method will free any dynamically allocated 
 * memory associated w/ the given Queue and set all pointers to NULL
 * @params: q: A pointer to the queue that must be freed
 */
void deleteLinkedQueue(Queue* q){
    LinkedQueue* liQ = ((LinkedQueue*)(q->privateData));
    int currentSize = liQ->size;
    int i;
    for(i = 0; i <= currentSize; i++){
        linkedQueueDequeue(q);
    }
    free(q->privateData);
}

/*
 *
 */
#include <stdio.h>
#include "queue.h"
#include "arrayQueue.h"
#include "linkedQueue.h"

#define ENQUEUE_TEST_LENGTH 15
#define DEQUEUE_TEST_LENGTH 5

/* testQueue- A testing function that tests enqueue, dequeue, print,
 * peek, and size.
 * @params: queue: The Queue to be tested
 */
static void testQueue(Queue* queue){
    int i;
    printf("==========Testing Enqueue==========\n");
    for(i = 0; i < ENQUEUE_TEST_LENGTH; i++){
        queue->enqueue(queue, i*2);
    }
    printf("\nTesting print method, should print:\n");
    printf("[0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28]\n");
    printf("Did print:\n");
    queue->print(queue);
    printf("Size should be: %d; Size is: %d\n", ENQUEUE_TEST_LENGTH, queue->size(queue));

    printf("\n==========Testing Dequeue==========\n");
    for(i = 0; i < DEQUEUE_TEST_LENGTH; i++){
        queue->dequeue(queue);
        printf("\nDequeued Array with Expected First Element: %d\n", queue->peek(queue));
        queue->print(queue);
        printf("Size should be: %d", (ENQUEUE_TEST_LENGTH - 1) - i);
        printf("; Size is: %d\n", queue->size(queue));
    }
}

int main(void){
    Queue array;
    Queue linked;

    printf("\nTesting Array Implementation\n");
    newArrayQueue(&array);
    testQueue(&array);
    deleteArrayQueue(&array);

    printf("==============================================================\n");
    printf("\nTesting Linked Implementation\n");
    newLinkedQueue(&linked);
    testQueue(&linked);
    deleteLinkedQueue(&linked);

    printf("\n============\n= Finished =\n============\n");
    return 0;
}

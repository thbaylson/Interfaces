/*
 * Header file containing the Queue struct
 */

typedef struct queue Queue;
struct queue{
    void *privateData;
    void (*enqueue)(Queue* q, int num);
    void (*dequeue)(Queue* q);
    void (*print)(Queue* q);

    int (*peek)(Queue* q);
    int (*size)(Queue* q);
};

#include <stdlib.h>
#include "tqueue.h"

/* Adds a new element at the end of the list, returns its position */
unsigned long int tqueue_enqueue(TQueue *q, void *data) {
    //TQueueNode* node = (TQueueNode*)(*q);

    if ((*q) == NULL) {
        (*q) = (TQueueNode *) malloc(sizeof(TQueueNode));
        (*q)->data = data;
        (*q)->next = NULL;
        return 0;
    }

    TQueueNode *ptr = (TQueueNode *) (*q);
    TQueueNode *ptrPrev = NULL;
    int i = 0;
    while (ptr) {
        ptrPrev = ptr;
        ptr = ptr->next;
        i++;
    }

    ptr = (TQueueNode *) malloc(sizeof(TQueueNode));
    ptr->data = data;
    ptrPrev->next = ptr;
    return i;
}

/* Removes and returns the element at the beginning of the list, NULL if the
queue is empty */
void *tqueue_pop(TQueue *q) {

}

/* Returns the number of elements in the list */
unsigned long int tqueue_size(TQueue q) {

}

/* Returns a 'view' on the list starting at (a positive) offset distance,
* NULL if the queue is empty */
TQueue tqueue_at_offset(TQueue q, unsigned long int offset) {
    if (q == NULL) {
        return NULL;
    }

    TQueueNode *ptr = (TQueueNode *) q;
    TQueueNode *ptrPrev = NULL;
    for (int i = 0; i <= offset; i++) {
        ptrPrev = ptr;
        if (ptr == NULL)
            ptr = (TQueueNode *) q;
        else
            ptr = ptr->next;
    }

    return (TQueue) (ptrPrev);
}

/* Returns the data on the first node of the given list */
void *tqueue_get_data(TQueue q) {

}
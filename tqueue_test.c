#include <stdio.h>
#include <string.h>
#include "tqueue.c"

void testEnqueue() {
    TQueue q = NULL;

    int a = 1;
    int b = 2;

    tqueue_enqueue(&q, (void *) &a);
    tqueue_enqueue(&q, (void *) &b);

    TQueue q2 = tqueue_at_offset(q, 0);
    void *d = q2->data;
    int *d2 = (int *) d;
    int v = *d2;
    //int v = (int) (*(a->data));

    printf("%d", v);

}
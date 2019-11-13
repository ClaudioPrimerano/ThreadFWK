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
    int *v = (int *) (q2->data);

    printf("%d\n", *v);
    printf("%ld\n", tqueue_size(q));

    void *data = tqueue_pop(&q);
    int *dataD = (int *) data;
    printf("%d\n", *dataD);

    data = tqueue_pop(&q);
    dataD = (int *) data;
    printf("%d\n", *dataD);
}
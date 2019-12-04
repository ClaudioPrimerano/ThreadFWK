//
// Created by claudio on 04/12/19.
//
#include "bthread_private.h"
#include "bthread.h"
#include "tqueue.h"

#define save_context(CONTEXT) sigsetjmp(CONTEXT, 1)
#define restore_context(CONTEXT) siglongjmp(CONTEXT, 1)

__bthread_scheduler_private *bthread_get_scheduler() {
    static __bthread_scheduler_private *instance = NULL;
    if (instance == NULL) {
        instance = (__bthread_scheduler_private *) malloc(sizeof(__bthread_scheduler_private));
        instance->queue = NULL;
        instance->current_item = NULL;
        instance->current_tid = -1;
    }
    return instance;
}; // Private

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine)(void *), void *arg) {
    __bthread_private *newThread = (__bthread_private *) malloc(sizeof(__bthread_private));
    newThread->attr = attr;
    newThread->body = start_routine;
    newThread->arg = arg;
    newThread->stack = NULL;
    int i = tqueue_enqueue(bthread_get_scheduler()->queue, (void *) newThread);
    newThread->tid = i;
    bthread = &i;
    return 1;
};

static int bthread_check_if_zombie(bthread_t bthread, void **retval);

static TQueue bthread_get_queue_at(bthread_t bthread);

int bthread_join(bthread_t bthread, void **retval) {
    volatile __bthread_scheduler_private *scheduler = bthread_get_scheduler();
    scheduler->current_item = scheduler->queue;
    save_context(scheduler->context);
    if (bthread_check_if_zombie(bthread, retval)) return 0;
    __bthread_private *tp;
    do {
        scheduler->current_item = tqueue_at_offset(scheduler->current_item, 1);
        tp = (__bthread_private *) tqueue_get_data(scheduler->current_item);
    } while (tp->state != __BTHREAD_READY);
    if (tp->stack) {
        restore_context(tp->context);
    } else {
        tp->stack = (char *) malloc(sizeof(char) * STACK_SIZE);
        unsigned long target = tp->stack + STACK_SIZE - 1;
#if __APPLE__
        // OSX requires 16 bytes aligned stack
        target -= (target % 16);
#endif
#if __x86_64__
        asm __volatile__("movq %0, %%rsp"::"r"((intptr_t) target));
#else
        asm __volatile__("movl %0, %%esp" :: "r"((intptr_t) target));
#endif
        bthread_exit(tp->body(tp->arg));
    }
}

void bthread_yield();

void bthread_exit(void *retval);

void bthread_cleanup(); // Private

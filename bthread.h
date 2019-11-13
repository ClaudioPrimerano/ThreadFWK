typedef unsigned long int bthread_t;

typedef enum {
    __BTHREAD_READY = 0,
    __BTHREAD_BLOCKED,
    __BTHREAD_SLEEPING,
    __BTHREAD_ZOMBIE
} bthread_state;

typedef struct {
} bthread_attr_t;

typedef void *(*bthread_routine)(void *);
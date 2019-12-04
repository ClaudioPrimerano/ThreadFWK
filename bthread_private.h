typedef struct {
    bthread_t tid;
    bthread_routine body;
    void *arg;
    bthread_state state;
    bthread_attr_t attr;
    char *stack;
    jmp_buf context;
    void *retval;
} __bthread_private;

typedef struct {
    TQueue queue;
    TQueue current_item;
    jmp_buf context;
    bthread_t current_tid;
} __bthread_scheduler_private;

__bthread_scheduler_private *bthread_get_scheduler(); // Private
void bthread_cleanup(); // Private
typedef struct Node_s {
    int data;
    struct Node_s *next;
} Node;

Node *newNode(int v) {
    Node *r = (Node*) calloc(1, sizeof(Node));
    r->data = v;
    return r;
}

typedef struct {
    Node **ppush;
    Node *pop;
    int length;
} Queue;

void pushQueue(Queue *q, int v) {
    Node *o = newNode(v);
    *q->ppush = o;
    q->ppush = &o->next;
    q->length++;
}

void popQueue(Queue *q) {
    Node *o = q->pop;
    q->length--;
    q->pop = o->next;
    free(o);
    if (q->pop == NULL)
        q->ppush = &q->pop;
}

int peekQueue(Queue *q) { return q->pop->data; }
int getQueueLength(Queue *q) { return q->length; }
int isQueueEmpty(Queue *q) { return q->length == 0; }

Queue *createQueue() {
    Queue *q = (Queue*) calloc(1, sizeof(Queue));
    q->ppush = &q->pop;
    return q;
}

void destroyQueue(Queue *q) {
    while (!isQueueEmpty(q))
        popQueue(q);
    free(q);
}

typedef struct {
    Queue *q;
    int size;
} Stack;

/* Create a stack */
void stackCreate(Stack *stack, int maxSize) {
    stack->size = maxSize;
    stack->q = createQueue();
}

/* Push element x onto stack */
void stackPush(Stack *stack, int element) {
    pushQueue(stack->q, element);
}

/* Removes the element on top of the stack */
void stackPop(Stack *stack) {
    int i, skip = getQueueLength(stack->q) - 1;
    for (i = 0; i < skip; ++i) {
        int val = peekQueue(stack->q);
        popQueue(stack->q);
        pushQueue(stack->q, val);
    }
    popQueue(stack->q);
}

/* Get the top element */
int stackTop(Stack *stack) {
    int i, val, skip = getQueueLength(stack->q);
    for (i = 0; i < skip; ++i) {
        val = peekQueue(stack->q);
        popQueue(stack->q);
        pushQueue(stack->q, val);
    }
    return val;
}

/* Return whether the stack is empty */
bool stackEmpty(Stack *stack) {
    return isQueueEmpty(stack->q);
}

/* Destroy the stack */
void stackDestroy(Stack *stack) {
    destroyQueue(stack->q);
}

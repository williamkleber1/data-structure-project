#ifndef fila_h
#define fila_h

typedef struct _node node;
typedef struct _queue queue;

struct _node
{
    int item;
    int priority;
    node *next;
};

struct  _queue
{
    node *first;
    node *last;
    int size;
};

queue* create_queue();

void enqueue(queue *queue, int item);

int dequeue(queue *queue);

int is_empty(queue *queue);

#endif //fila_h

#define MAX_EXPR_SIZE 100

typedef struct {
    int top;
    double data[MAX_EXPR_SIZE];
} Stack;

void init(Stack *s);
int is_empty(Stack *s);
int is_full(Stack *s);
void push(Stack *s, double element);
double pop(Stack *s);
double peek(Stack *s);

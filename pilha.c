#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void init(Stack *s) {
    s->top = -1;
}

int is_empty(Stack *s) {
    return s->top == -1;
}

int is_full(Stack *s) {
    return s->top == MAX_EXPR_SIZE - 1;
}

void push(Stack *s, double element) {
    if (is_full(s)) {
        printf("Erro: pilha cheia!!!\n");
        exit(EXIT_FAILURE);
    }
    s->top++;
    s->data[s->top] = element;
}

double pop(Stack *s) {
    if (is_empty(s)) {
        printf("Erro: pilha vazia!!!\n");
        exit(EXIT_FAILURE);
    }
    double element = s->data[s->top];
    s->top--;
    return element;
}

double peek(Stack *s) {
    if (is_empty(s)) {
        printf("Erro: pilha vazia.\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top];
}

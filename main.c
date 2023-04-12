#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "pilha.h"
#include <locale.h>


#define MAX_EXPR_SIZE 100

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void infix_to_postfix(char infix[], char postfix[]) {
    Stack stack;
    init(&stack);

    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];
        if (isdigit(ch)) {
            postfix[j++] = ch;
            while (isdigit(infix[i+1])) {
                i++;
                postfix[j++] = infix[i];
            }
            postfix[j++] = ' ';
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (!is_empty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            pop(&stack);
        } else if (is_operator(ch)) {
            while (!is_empty(&stack) && precedence(ch) <= precedence(peek(&stack))) {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            push(&stack, ch);
        }
    }

    while (!is_empty(&stack)) {
        postfix[j++] = pop(&stack);
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
}

double evaluate_postfix(char postfix[]) {
    Stack stack;
    init(&stack);

    int i;
    for (i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            double num = ch - '0';
            while (isdigit(postfix[i+1])) {
                i++;
                num = num * 10 + (postfix[i] - '0');
            }
            push(&stack, num);
        } else if (ch == ' ') {
        } else {
            double op2 = pop(&stack);
            double op1 = pop(&stack);
            double result;
            switch (ch) {
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2;
                    break;
                case '*':
                    result = op1 * op2;
                    break;
                case '/':
                    result = op1 / op2;
                    break;
                case '^':
                    result = pow(op1, op2);
                    break;
                default:
                    printf("Erro: operador inválido.\n");
                    exit(EXIT_FAILURE);
            }
            push(&stack, result);
        }
    }

    double result = pop(&stack);
    if (!is_empty(&stack)) {
        printf("Erro: expressão mal formada.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int main(){
	setlocale(LC_ALL, "Portuguese");
    char infix[MAX_EXPR_SIZE];
    char postfix[MAX_EXPR_SIZE];
    printf("Digite a expressão: ");
    fgets(infix, MAX_EXPR_SIZE, stdin);

    infix_to_postfix(infix, postfix);
    printf("Expressão em NPR: %s\n", postfix);

    double result = evaluate_postfix(postfix);
    printf("Resultado: %.2lf\n", result);

return 0;
}

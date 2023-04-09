#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int top;
    int data[MAX_STACK_SIZE];
} Stack;

void initialize(Stack* s) {
    s->top = -1;
}

void push(Stack* s, int value) {
    if (s->top >= MAX_STACK_SIZE - 1) {
        printf("Error: stack full\n");
        exit(EXIT_FAILURE);
    }
    s->data[++s->top] = value;
}

int pop(Stack* s) {
    if (s->top < 0) {
        printf("Error: stack empty\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top--];
}

int evaluate_postfix(char* expr) {
    Stack s;
    int i, op1, op2, result;
    initialize(&s);

    for (i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            push(&s, expr[i] - '0');
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            if (s.top < 1) {
                printf("Error: insufficient operands\n");
                exit(EXIT_FAILURE);
            }
            op2 = pop(&s);
            op1 = pop(&s);
            switch (expr[i]) {
            case '+': result = op1 + op2; break;
            case '-': result = op1 - op2; break;
            case '*': result = op1 * op2; break;
            case '/':
                if (op2 == 0) {
                    printf("Error: division by zero\n");
                    exit(EXIT_FAILURE);
                }
                result = op1 / op2;
                break;
            }
            push(&s, result);
        }
        else {
            printf("Error: invalid character '%c'\n", expr[i]);
            exit(EXIT_FAILURE);
        }
    }
    if (s.top > 0) {
        printf("Error: too many operands\n");
        exit(EXIT_FAILURE);
    }
    return pop(&s);
}

int main() {
    char expr[MAX_STACK_SIZE];
    int result;

    printf("Enter postfix expression: ");
    scanf("%s", expr);

    result = evaluate_postfix(expr);
    printf("Result: %d\n", result);

    return 0;
}

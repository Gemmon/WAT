#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char value;
    struct Node* next;
} Node;

Node* createNode(char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void push(Node** top, char value) {
    Node* newNode = createNode(value);
    newNode->next = *top;
    *top = newNode;
}

char pop(Node** top) {
    if (*top == NULL) {
        fprintf(stderr, "Error: Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    char value = (*top)->value;
    Node* temp = *top;
    *top = (*top)->next;
    free(temp);
    return value;
}

// Check if the character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

// Assign priority to operators
int priority(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return 0;
    }
}

int stackEmpty(Node* top) {
    return top == NULL;
}

void infixToPostfix() {
    Node* stack = NULL;
    char c;

    printf("Podaj wyrazenie: ");
    // Reading characters and checking if they are alphanumeric manually
    while ((c = getchar()) != '\n' && c != EOF) {
        // Check if the character is a letter or a digit
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            printf("%c ", c);
        } else if (c == '(') {
            push(&stack, c);
        } else if (c == ')') {
            while (!stackEmpty(stack) && stack->value != '(') {
                printf("%c ", pop(&stack));
            }
            pop(&stack);
        } else if (isOperator(c)) {
            while (!stackEmpty(stack) && priority(stack->value) >= priority(c)) {
                printf("%c ", pop(&stack));
            }
            push(&stack, c);
        }
    }

    while (!stackEmpty(stack)) {
        printf("%c ", pop(&stack));
    }
    printf("\n");
}

int main() {
    infixToPostfix();

    return 0;
}
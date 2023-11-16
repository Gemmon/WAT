#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(Node** top, char data) {
    Node* newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}


char pop(Node** top) {
    if (*top == NULL) {
        fprintf(stderr, "Error: Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    char data = (*top)->data;
    Node* temp = *top;
    *top = (*top)->next;
    free(temp);
    return data;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getPrecedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

int stackEmpty(Node* top) {
    return top == NULL;
}

void infixToPostfix(char* infix) {
    Node* stack = NULL;
    printf("Postfix expression: ");
    
    while (*infix) {
        if (isalnum(*infix)) {
            printf("%c", *infix);
        } else if (*infix == '(') {
            push(&stack, *infix);
        } else if (*infix == ')') {
            while (!stackEmpty(stack) && stack->data != '(') {
                printf("%c", pop(&stack));
            }
            pop(&stack); // Pop '('
        } else if (isOperator(*infix)) {
            while (!stackEmpty(stack) && getPrecedence(stack->data) >= getPrecedence(*infix)) {
                printf("%c", pop(&stack));
            }
            push(&stack, *infix);
        }
        infix++;
    }

    while (!stackEmpty(stack)) {
        printf("%c", pop(&stack));
    }

    printf("\n");
}


int main() {
    char infix[50];
    printf("Enter infix expression: ");
    scanf(" %[^\n]", infix);

    infixToPostfix(infix);

    return 0;
}

//============================================================================
// Zadanie 4_1  jezyk C
//  Konwersja wyrażeń arytmetycznych z notacji infiksowej na postfiksową
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
//sprawdzenie czy znak to operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}
//nadanie priotyretu
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

void infixNaPostfix(char* infix) {
    Node* stack = NULL;

    while (*infix) {
        if (isalnum(*infix)) {
            printf("%c ", *infix); 
        } else if (*infix == '(') {
            push(&stack, *infix);
        } else if (*infix == ')') {
            while (!stackEmpty(stack) && stack->value != '(') {
                printf("%c ", pop(&stack)); 
            }
            pop(&stack);
        } else if (isOperator(*infix)) {
            while (!stackEmpty(stack) && priority(stack->value) >= priority(*infix)) {
                printf("%c ", pop(&stack));
            }
            push(&stack, *infix);
        }
        infix++;
    }
    while (!stackEmpty(stack)) {
        printf("%c ", pop(&stack)); 
    }
    printf("\n");
}

int main() {
    char infix[50];
    printf("Podaj wyrazenie: ");
    scanf(" %[^\n]", infix);
    printf("Wyrazenie w ONP: ");
    infixNaPostfix(infix);

    return 0;
}
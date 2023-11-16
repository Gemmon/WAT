#include <stdio.h>
#include <stdlib.h>


struct Node;


typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;


void push(Stack* stack, int digit) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        // Obsługa błędu alokacji pamięci
        exit(EXIT_FAILURE);
    }
    new_node->value = digit;
    new_node->next = stack->top;
    stack->top = new_node;
}


int pop(Stack* stack) {
    if (stack->top == NULL) {
        exit(EXIT_FAILURE);
    }

    Node* top_node = stack->top;
    int value = top_node->value;
    stack->top = top_node->next;
    free(top_node);

    return value;
}

// Funkcja wyświetlająca zawartość stosu
void print(Stack* stack) {
    Node* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
}
// Funkcja odwracająca liczbę by można było dodać
void reverse(Stack* stack, Stack* stack_reverse) {
    int digit = 0;
    Node* current = stack->top;
    while (current != NULL) {
        digit = current->value;
        push(stack_reverse, digit);
        current = current->next;
    }
}

// Funkcja wstawiająca liczbę na stos
void insert(Stack* stack, int number) {
    while (number > 0) {
        int digit = number % 10;
        push(stack, digit);
        number /= 10;
    }
}

// Funkcja tworząca trzeci stos z sumą wierzchołków dwóch pierwszych stosów
Stack sum(Stack* stack1, Stack* stack2) {
    Stack result;
    result.top = NULL;
    int carry = 0;

    while(stack1->top != NULL || stack2->top != NULL || carry != 0){
        int sum = carry;

        if(stack1->top != NULL){
            sum += pop(stack1);
        }

        if(stack2->top != NULL){
            sum += pop(stack2);
        }
        push(&result, sum % 10);
        carry = sum / 10;
    }

    return result;
}

// Funkcja zwalniająca  stos
void freeStack(Stack* stack) {
    Node* current = stack->top;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    stack->top = NULL;
}

int main() {
    Stack stack1;
    stack1.top = NULL;
    Stack stack2;
    stack2.top = NULL;
    Stack suma;
    suma.top = NULL;

    Stack stack1r;
    stack1r.top = NULL;
    Stack stack2r;
    stack2r.top = NULL;

    int number1, number2;

    printf("Podaj pierwsza liczbe: ");
    scanf("%d", &number1);

    printf("Podaj druga liczbe: ");
    scanf("%d", &number2);

    insert(&stack1, number1);
    printf("Stos 1: ");
    reverse(&stack1, &stack1r);
    freeStack(&stack1);
    print(&stack1r);

    insert(&stack2, number2);
    printf("\nStos 2: ");
    reverse(&stack2, &stack2r);
    freeStack(&stack2);
    print(&stack2r);

    suma = sum(&stack1r, &stack2r);
    printf("\nSuma stosow: ");
    print(&suma);
    
    freeStack(&stack1r);
    freeStack(&stack2r);
    freeStack(&suma);
    return 0;
}

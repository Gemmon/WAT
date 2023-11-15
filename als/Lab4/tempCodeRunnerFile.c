#include <stdio.h>
#include <stdlib.h>

// Forward declaration of the Node structure
struct Node;

// Define a structure for the stack
typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

// Function to push a digit onto the stack
void push(Stack* stack, int digit) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }
    new_node->value = digit;
    new_node->next = stack->top;
    stack->top = new_node;
}

// Function to pop a digit from the stack
int pop(Stack* stack) {
    if (stack->top == NULL) {
        // Handle underflow (empty stack)
        exit(EXIT_FAILURE);
    }

    Node* top_node = stack->top;
    int value = top_node->value;
    stack->top = top_node->next;
    free(top_node);

    return value;
}

// Function to print the stack
void print_stack(Stack* stack) {
    Node* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
}

void reverse(Stack* stack,Stack* stackr){
    int digit = 0;
    Node* current = stack->top;
    while (current != NULL) {
        digit = current->value;
        push(stackr, digit);
        current = current->next;
    }
}

// Function to insert a number into the stack with the least significant digit at the top
void insert_number(Stack* stack, int number) {
    while (number > 0) {
        int digit = number % 10;
        push(stack, digit);
        number /= 10;
    }
}

// Function to create a third stack with the sum of the tops of the first two stacks
Stack sum_of_stacks(Stack* stack1, Stack* stack2) {
    Stack result_stack;
    result_stack.top = NULL;
    int carry = 0;

    while (stack1->top != NULL || stack2->top != NULL || carry != 0) {
        int sum = carry + pop(stack1) + pop(stack2);

        push(&result_stack, sum % 10);
        carry = sum / 10;
    }

    return result_stack;
}

// Main function for testing
int main() {
    Stack stack1;
    stack1.top = NULL;
    Stack stack2;
    stack2.top = NULL;
    Stack stack_sum;
    stack_sum.top = NULL;


    Stack stack1r;
    stack1r.top = NULL; 
    Stack stack2r;
    stack2r.top = NULL; 
    

    int number1, number2;

    printf("Enter the first number: ");
    scanf("%d", &number1);

    printf("Enter the second number: ");
    scanf("%d", &number2);

    insert_number(&stack1, number1);
    printf("Stack 1: ");
    print_stack(&stack1);
    reverse(&stack1, &stack1r);

    print_stack(&stack1r);


    insert_number(&stack2, number2);
    printf("\nStack 2: ");
    print_stack(&stack2);
    reverse(&stack2, &stack2r);
    print_stack(&stack2r);

    stack_sum = sum_of_stacks(&stack1r, &stack2r);
    printf("\nSum of the tops of the first two stacks: ");
    print_stack(&stack_sum);

    return 0;
}
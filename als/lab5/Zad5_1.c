#include <stdio.h>
#include <stdlib.h>

struct StackNode {
    int krazek;
    struct StackNode* next;
};


void push(struct StackNode** top, int krazek) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->krazek = krazek;
    newNode->next = *top;
    *top = newNode;
}
//Usuwanie krazka z gory
int pop(struct StackNode** top) {
    struct StackNode* temp = *top;
    int krazek = temp->krazek;
    *top = temp->next;
    free(temp);

    return krazek;
}

void drukRuch(int krazek, char A, char C) {
    printf("Przeniesienie krazka %d z %c do %c\n", krazek, A, C);
}

void hanoi(int n, struct StackNode** A, struct StackNode** B, struct StackNode** C, char APeg, char BPeg, char CPeg) {
    if (n > 0) {
        // Przeniesienie krazka n-1 z A do B uzywajac C
        hanoi(n - 1, A, C, B, APeg, CPeg, BPeg);

        // Przeniesienie krazku n z A do C
        int krazek = pop(A);
        push(C, krazek);
        drukRuch(krazek, APeg, CPeg);

        hanoi(n - 1, B, A, C, BPeg, APeg, CPeg);
    }
}

int main() {
    int n;
    printf("Podaj liczbe krazkow: ");
    scanf("%d", &n);

    struct StackNode* A = NULL;
    struct StackNode* B = NULL;
    struct StackNode* C = NULL;
    
    if(n > 0 && n < 11){
    // Nalozenie krazkow na stos A
    for (int i = n; i > 0; i--) {
        push(&A, i);
    }
    

    hanoi(n, &A, &B, &C, 'A', 'B', 'C');

    // Usuniecie pamieci
    while (C != NULL) {
        pop(&C);
    }

    }
    else printf("Za duze n");

    return 0;
}
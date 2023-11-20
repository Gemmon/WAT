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

int pop(struct StackNode** top) {
    struct StackNode* temp = *top;
    int krazek = temp->krazek;
    *top = temp->next;
    free(temp);

    return krazek;
}

void drukRuch(int krazek, char A, char C, FILE* file) {
    printf("Przeniesienie krazka %d z %c do %c\n", krazek, A, C);
    fprintf(file, "Przeniesienie krazka %d z %c do %c\n", krazek, A, C);
}

void hanoi(int n, struct StackNode** A, struct StackNode** B, struct StackNode** C, char APeg, char BPeg, char CPeg, FILE* file) {
    if (n > 0) {
        hanoi(n - 1, A, C, B, APeg, CPeg, BPeg, file);

        int krazek = pop(A);
        push(C, krazek);
        drukRuch(krazek, APeg, CPeg, file);

        hanoi(n - 1, B, A, C, BPeg, APeg, CPeg, file);
    }
}

int main() {
    int n;
    printf("Podaj liczbe krazkow: ");
    scanf("%d", &n);

    struct StackNode* A = NULL;
    struct StackNode* B = NULL;
    struct StackNode* C = NULL;

    if (n > 0 && n < 11) {
        // Open a file for writing
        FILE* file = fopen("hanoi_wynik.txt", "w");
        if (file == NULL) {
            fprintf(stderr, "Nie mozna otworzyc pliku do zapisu.\n");
            return 1; // Exit with an error code
        }

        // Load disks onto stack A
        for (int i = n; i > 0; i--) {
            push(&A, i);
        }

        hanoi(n, &A, &B, &C, 'A', 'B', 'C', file);

        // Close the file
        fclose(file);

        // Clear memory
        while (C != NULL) {
            pop(&C);
        }
    }
    else {
        printf("Za duze n");
    }

    return 0;
}
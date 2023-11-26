#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

struct Node* findMin(struct Node* node) {
    // Znajdowanie najmniejszego elementu w drzewie
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Węzeł do usunięcia znaleziony

        // Przypadek 1: Brak jednego lub obu dzieci
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Przypadek 2: Węzeł ma obu dzieci
        struct Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}


void printGivenLevel(struct Node* root, int level) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->key);
    else if (level > 1) {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}

int height(struct Node* root) {
    if (root == NULL)
        return 0;
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
}

void printLevelOrder(struct Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printGivenLevel(root, i);
        printf("\n");
    }
}

void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
int main() {
    struct Node* root = NULL;
    int choice, key;

    do {
        printf("\n1. Dodaj wezel\n");
        printf("2. Usun wezel\n");
        printf("3. Wyszukaj wezel\n");
        printf("4. Wyświetl drzewo\n");
        printf("5. Usun cale drzewo\n");
        printf("0. Zakoncz\n");

        printf("Wybierz opcje: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Podaj wartosc wezla do dodania: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Podaj wartosc wezla do usuniecia: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 3:
                printf("LVR: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Drzewo:\n");
                printLevelOrder(root);
                break;
            case 5:
                freeTree(root);
                root = NULL;
                printf("Cale drzewo zostało usuniete.\n");
                break;
            case 0:
                break;
            default:
                printf("Nieprawidłowy wybór.\n");
        }
    } while (choice != 0);

    freeTree(root);

    return 0;
}

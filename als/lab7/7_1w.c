//============================================================================
//  Zadanie 7_1  jezyk C
//  Drzewo AVL
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Funkcja do sprawdzenia wysokosci
int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// aktualizowanie wysokosci
void updateHeight(struct Node* node) {
    if (node != NULL) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

// rotacja w prawo
struct Node* rotateRight(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

//rotacja w lewo
struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// odzyskanie balansu drzewa
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// funkcja do dodawania wezlow
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;

    updateHeight(root);

    // poprawienie balansu
    int balance = getBalance(root);

    if (balance > 1) {
        if (key < root->left->key) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }

    if (balance < -1) {
        if (key > root->right->key) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    return root;
}
// wezel minumum
struct Node* findMin(struct Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

struct Node* deleteNode(struct Node* root, int key) {
    // Standard BST delete
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // wezel tylko z max jednym dzieckiem
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // wezel z dwojka dzieci
        struct Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    updateHeight(root);
   
    //naprawienie balansu
    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) >= 0) {
            // Left-Left Case
            return rotateRight(root);
        } else {
            // Left-Right Case
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
        }
    }

    if (balance < -1) {
        if (getBalance(root->right) <= 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
    }
    return root;
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

// usuwanie drzewa
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// LVR
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

//VLR
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// LRV
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->key);
    }
}

//wczytywanie z pliku
void buildRootFromFile(struct Node** root) {
    FILE* file = fopen("we.txt", "r");

    if (file == NULL) {
        printf("Brak otwarcia pliku.\n");
        return;
    }

    int key;
    while (fscanf(file, "%d", &key) == 1) {
        *root = insert(*root, key);
    }

    fclose(file);
    printf("Zapisano.\n");
}

// sciezka do wezla
void findPathToNode(struct Node* root, int key) {
    if (root == NULL) {
        printf("Wezel %d nie znaleziono.\n", key);
        return;
    }

    printf("Sciezka %d: ", key);
    while (root != NULL && root->key != key) {
        printf("%d ", root->key);
        if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }

    if (root != NULL)
        printf("%d\n", root->key);
    else
        printf("(Nie znaleziono)\n");
}

// wizualizacja drzewa
void printTree(struct Node* root, int space) {
    if (root == NULL)
        return;

    space += 5;

    printTree(root->right, space);

    printf("\n");
    int i;
    for (i = 5; i < space; i++)
        printf(" ");
    printf("%d:%d\n", root->key, getBalance(root));

    printTree(root->left, space);
}

int main() {
    struct Node* root = NULL;
    int choice, key;
    int space = 0;

    buildRootFromFile(&root);

    do {
        printf("\n1. Dodaj wezel\n");
        printf("2. Usun wezel\n");
        printf("3. Pokaz drzewo\n");
        printf("4. Usun drzewo\n");
        printf("5. LVR\n");
        printf("6. VLR\n");
        printf("7. LRV\n");
        printf("8. Sciezka\n");
        printf("0. Koniec programu\n");

        printf("Wybierz akcje: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Podaj wartosc: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Podaj wartosc: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 3:
                printf("Drzewo:\n");
                printTree(root, space);
                break;
            case 4:
                freeTree(root);
                root = NULL;
                printf("Drzewo zostalo usuniete.\n");
                break;
            case 5:
                printf("LVR: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("VLR: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 7:
                printf("LRV: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 8:
                printf("Podaj wartosc: ");
                scanf("%d", &key);
                findPathToNode(root, key);
                break;
            case 0:
                break;
            default:
                printf("Blad wyboru.\n");
        }
    } while (choice != 0);

    freeTree(root);

    return 0;
}

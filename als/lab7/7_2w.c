//============================================================================
//  Zadanie 7_2  jezyk C
//  Drzewo RB
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================
#include <stdio.h>
#include <stdlib.h>

//definicja by latwiej pracowac na kolorach
#define RED 0
#define BLACK 1

struct Node {
    int key;
    int color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};
// tworzenie wezla
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->color = RED; // New nodes are always red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// rotacja w lewo
void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// rotacja w prawo
void rightRotate(struct Node** root, struct Node* y) {
    struct Node* x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// naprawa drzewa po dadaniu wezla
void insertFix(struct Node** root, struct Node* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct Node* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            struct Node* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// dodawanie wezla
void insertRB(struct Node** root, int key) {
    struct Node* z = createNode(key);
    struct Node* y = NULL;
    struct Node* x = *root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        *root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    insertFix(root, z);
}

//znajdowanie wezla minimum
struct Node* minimum(struct Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// zamiana wezlow 
void transplant(struct Node** root, struct Node* u, struct Node* v) {
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

// naprawa drzewa po usunieciu wezla
void deleteFix(struct Node** root, struct Node* x) {
    while (x != NULL && x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            struct Node* w = x->parent->right;
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL)
                        w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != NULL)
                    w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            struct Node* w = x->parent->left;
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL)
                        w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != NULL)
                    w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}

// usuwanie wezla
void deleteRB(struct Node** root, int key) {
    struct Node* z = *root;
    struct Node* x, * y;
    while (z != NULL) {
        if (key == z->key)
            break;
        else if (key < z->key)
            z = z->left;
        else
            z = z->right;
    }

    if (z == NULL)
        return;

    y = z;
    int yOriginalColor = y->color;
    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (yOriginalColor == BLACK && x != NULL)
        deleteFix(root, x);

    if (*root != NULL && (*root)->parent != NULL)
        *root = (*root)->parent;
}

// usuwanie drzewa
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}


//wizualizacja drzewa 
void printTree(struct Node* root, int space) {
    if (root == NULL)
        return;

    const int INDENTATION = 5;
    space += INDENTATION;

    printTree(root->right, space);

    int i;
    for (i = INDENTATION; i < space; i++)
        printf(" ");

    char colour = (root->color == BLACK) ? 'B' : 'R';
    printf("%c:%d\n", colour, root->key);

    printTree(root->left, space);
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
        insertRB(root, key);
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

int main() {
    struct Node* root = NULL;
    int choice, key;
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
                printf("Podaj wartosc wezla: ");
                scanf("%d", &key);
                insertRB(&root, key);
                break;
            case 2:
                printf("Podaj wartosc wezla:");
                scanf("%d", &key);
                deleteRB(&root, key);
                break;
            case 3:
                printTree(root, 0);
                printf("\n");
                break;
            case 4:
                freeTree(root);
                printf("\n");
                break;               
            case 5:
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
                printf("Podaj wartosc wezla: ");
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

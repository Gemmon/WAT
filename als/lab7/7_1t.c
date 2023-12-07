#include <stdio.h>
#include <stdlib.h>

// Define colors for Red-Black tree nodes
#define RED 0
#define BLACK 1

struct Node {
    int key;
    int color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->color = RED; // New nodes are always red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Function to perform a left rotation
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

// Function to perform a right rotation
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

// Function to fix violations after inserting a node
void insertFixup(struct Node** root, struct Node* z) {
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

// Function to insert a key into the RB tree
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

    insertFixup(root, z);
}

// Function to find the node with the minimum key in the tree
struct Node* minimum(struct Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to transplant a subtree rooted at node u with a subtree rooted at node v
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

// Function to fix violations after deleting a node
void deleteFixup(struct Node** root, struct Node* x) {
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
                x = *root; // Exit the loop
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
                x = *root; // Exit the loop
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}

// Function to delete a key from the RB tree
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
        return; // Key not found

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
        deleteFixup(root, x);

    if (*root != NULL && (*root)->parent != NULL)
        *root = (*root)->parent;  // Update root if it changed
}


// Function for in-order traversal of the tree
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("(%d, %s) ", root->key, (root->color == RED) ? "RED" : "BLACK");
        inorderTraversal(root->right);
    }
}

// Function to free memory occupied by the tree
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void printTree(struct Node* root, int space) {
    if (root == NULL)
        return;

    const int INDENTATION = 5;

    // Increase the indentation for the next level
    space += INDENTATION;

    // Print the right subtree
    printTree(root->right, space);

    // Print the current node
    int i;
    for (i = INDENTATION; i < space; i++)
        printf(" ");

    char colour = (root->color == BLACK) ? 'B' : 'R';
    printf("%c:%d\n", colour, root->key);

    // Print the left subtree
    printTree(root->left, space);
}



int main() {
    struct Node* root = NULL;
    int choice, key;

    do {
        printf("\n1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. LVR\n");
        printf("0. Exit\n");

        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value of the node to insert: ");
                scanf("%d", &key);
                insertRB(&root, key);
                break;
            case 2:
                printf("Enter the value of the node to delete: ");
                scanf("%d", &key);
                deleteRB(&root, key);
                break;
            case 3:
                printTree(root, 0);
                printf("\n");
                break;
            case 4:
                inorderTraversal(root);
                printf("\n");
                break;
            case 0:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    // Free memory
    freeTree(root);

    return 0;
}

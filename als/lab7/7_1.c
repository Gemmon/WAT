#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height; // Height of the node in the AVL tree
};

// Function prototype for createNode
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1; // Initialize height to 1 for a new node
    return newNode;
}

// Function to get the height of a node
int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to update the height of a node
void updateHeight(struct Node* node) {
    if (node != NULL) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

// Function to perform a right rotation
struct Node* rotateRight(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform a left rotation
struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to get the balance factor of a node
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a key into the AVL tree
struct Node* insert(struct Node* root, int key) {
    // Standard BST insert
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else // Duplicate keys are not allowed in AVL tree
        return root;

    // Update height of the current node
    updateHeight(root);

    // Get the balance factor to check whether the node became unbalanced
    int balance = getBalance(root);

    // Left Heavy
    if (balance > 1) {
        if (key < root->left->key) {
            // Left-Left Case
            return rotateRight(root);
        } else {
            // Left-Right Case
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }

    // Right Heavy
    if (balance < -1) {
        if (key > root->right->key) {
            // Right-Right Case
            return rotateLeft(root);
        } else {
            // Right-Left Case
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    // If the node is already balanced, return the unchanged node
    return root;
}

// Function to find the minimum node in a tree
struct Node* findMin(struct Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to delete a node from the AVL tree
struct Node* deleteNode(struct Node* root, int key) {
    // Standard BST delete
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        struct Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    // Update height of the current node
    updateHeight(root);

    // Get the balance factor to check whether the node became unbalanced
    int balance = getBalance(root);

    // Left Heavy
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

    // Right Heavy
    if (balance < -1) {
        if (getBalance(root->right) <= 0) {
            // Right-Right Case
            return rotateLeft(root);
        } else {
            // Right-Left Case
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
    }

    return root;
}

// Function to calculate the height of a tree
int height(struct Node* root) {
    if (root == NULL)
        return 0;
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
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

// Function for in-order traversal of the tree
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// Function for pre-order traversal of the tree
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function for post-order traversal of the tree
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->key);
    }
}

// Function to build a tree from data in a file
void buildRootFromFile(struct Node** root) {
    FILE* file = fopen("we.txt", "r");

    if (file == NULL) {
        printf("Cannot open the file.\n");
        return;
    }

    int key;
    while (fscanf(file, "%d", &key) == 1) {
        *root = insert(*root, key);
    }

    fclose(file);
    printf("Nodes have been loaded from the file.\n");
}

// Function to find the path to a node in the tree
void findPathToNode(struct Node* root, int key) {
    if (root == NULL) {
        printf("Node %d not found.\n", key);
        return;
    }

    printf("Path to node %d: ", key);
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
        printf("(Node not found)\n");
}

// Function to print the tree with indentation and without arrows
void printTree(struct Node* root, int space) {
    if (root == NULL)
        return;

    space += 5;

    printTree(root->right, space);

    printf("\n");
    int i;
    for (i = 5; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    printTree(root->left, space);
}

int main() {
    struct Node* root = NULL;
    int choice, key;
    int space = 0;

    buildRootFromFile(&root);

    do {
        printf("\n1. Add node\n");
        printf("2. Delete node\n");
        printf("3. Display tree\n");
        printf("4. Delete tree\n");
        printf("5. In-order traversal\n");
        printf("6. Pre-order traversal\n");
        printf("7. Post-order traversal\n");
        printf("8. Find path to node\n");
        printf("0. Exit\n");

        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value of the node to add: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter the value of the node to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 3:
                printf("Tree:\n");
                printTree(root, space);
                break;
            case 4:
                freeTree(root);
                root = NULL;
                printf("The entire tree has been deleted.\n");
                break;
            case 5:
                printf("In-order traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("Pre-order traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 7:
                printf("Post-order traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 8:
                printf("Enter the node to find the path: ");
                scanf("%d", &key);
                findPathToNode(root, key);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    freeTree(root);

    return 0;
}

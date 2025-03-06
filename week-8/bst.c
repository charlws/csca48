#include <stdio.h>
#include <stdlib.h>

typedef struct nodeBST {
    int value;
    struct nodeBST *left;
    struct nodeBST *right;
    int height;
} Node;

Node *createNode(int value) {
    Node *node = NULL;
    node = (Node *)calloc(1, sizeof(Node));
    if (node == NULL) {
        printf("Error reserving memory. Aborted.\n");
        return NULL;
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;

    return node;
}

int getHeight(Node *node){
    if(node == NULL) return -1;
    int leftHeight = node->left != NULL ? node->left->height : -1;
    int rightHeight = node->right != NULL ? node->right->height : -1;
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

void setHeight(Node *node){
    node->height = getHeight(node);
}

Node *rotateLeft(Node *x){
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    setHeight(x);
    setHeight(y);
    return y;
}

Node *rotateRight(Node *y){
    Node *x = y->left;
    y->left = x->right;
    x->right = y;
    setHeight(y);
    setHeight(x);
    return x;
}

// Node *insertNode(Node *root, Node *node){
//     // returns the root
//     if(root == NULL) return node;

//     Node *cur = root, *parent = NULL;
//     while(cur != NULL){
//         parent = cur;
//         if(node->value > cur->value) cur = cur->right;
//         else if(node->value < cur->value) cur = cur->left;
//         else {
//             printf("Duplicate node detected. Aborted.\n");
//             return root;
//         }
//     }

//     if(node->value < parent->value) parent->left = node;
//     else parent->right = node;

//     return root;
// }

Node *insertNode(Node *root, Node *node) {
    if (root == NULL) return node;

    if (root->value == node->value) {
        printf("Duplicate node detected. Aborted.\n");
        return root;
    }

    if (node->value < root->value)
        root->left = insertNode(root->left, node);
    else
        root->right = insertNode(root->right, node);
    
    int hdiff = getHeight(root->left) - getHeight(root->right);
    if(hdiff > 1){
        // left heavy
        if(node->value > root->left->value) // bended chain (need to rotate (the only) child of root first)
            root->left = rotateLeft(root->left);
        root = rotateRight(root);
    } else if(hdiff < -1){
        // right heavy
        if(node->value < root->right->value) // bended chain (need to rotate (the only) child of root first)
            root->right = rotateRight(root->right);
        root = rotateLeft(root);
    }
    setHeight(root);

    return root;
}

Node *searchNode(Node *root, int value, int log, int depth) {
    // returns the node
    if (root == NULL) {
        if (log) printf("NOT FOUND!\n");
        return NULL;
    }

    if (log) printf("%d -> ", root->value);

    if (root->value == value) {
        if (log) printf("FOUND (Depth = %d / Height = %d)!\n", depth, root->height);
        return root;
    }

    if (value < root->value)
        return searchNode(root->left, value, log, depth + 1);
    else
        return searchNode(root->right, value, log, depth + 1);
}

Node *deleteNode(Node *root, int value) {
    if (root == NULL) return NULL;

    if (root->value == value) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            Node *newRoot = root->right;
            free(root);
            return newRoot;
        } else if (root->right == NULL) {
            Node *newRoot = root->left;
            free(root);
            return newRoot;
        } else {
            Node *rightSubtreeMin = root->right;
            // find the smallest value in the right tree
            // (still bigger than everything in left tree)
            while (rightSubtreeMin->left != NULL) rightSubtreeMin = rightSubtreeMin->left;
            // promote this smallest value to root (by copying the value)
            root->value = rightSubtreeMin->value;
            // go into right tree to delete that promoted node
            root->right = deleteNode(root->right, rightSubtreeMin->value);
            setHeight(root);
            return root;
        }
    } else if (value < root->value) {
        root->left = deleteNode(root->left, value);
        setHeight(root);
        return root;
    } else {
        root->right = deleteNode(root->right, value);
        setHeight(root);
        return root;
    }

    // TODO: Add balance here
}

int main() {
    // 1 {value} - insert node
    // 2 {value} - search node
    // 3 {value} - delete node
    Node *root = NULL;
    while (1) {
        int op, value;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d", &value);
            Node *node = createNode(value);
            root = insertNode(root, node);
            printf("Inserted node with value %d at %p\n", value, node);
        } else if (op == 2) {
            scanf("%d", &value);
            Node *node = searchNode(root, value, 1, 0);
            printf("Found node with value %d at %p\n", value, node);
        } else if (op == 3) {
            scanf("%d", &value);
            root = deleteNode(root, value);
            printf("Deleted node with value %d\n", value);
        } else if (op == 0) {
            break;
        }
    }
    return 0;
}
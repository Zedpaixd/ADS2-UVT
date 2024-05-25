#include <stdio.h>
#include <stdlib.h>

// Structura unui nod pentru arbore splay
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Functie pentru a crea un nou nod
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Rotire la dreapta
Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    printf("Rotire la dreapta intre nodurile %d si %d\n", x->key, y->key);
    return y;
}

// Rotire la stanga
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    printf("Rotire la stanga intre nodurile %d si %d\n", x->key, y->key);
    return y;
}

// Functie pentru a da splay la un nod cu cheia data
Node* splay(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    // Cheia se afla in subarborele stang
    if (key < root->key) {
        if (root->left == NULL) return root;

        // Zig-Zig (stanga stanga)
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // Zig-Zag (stanga dreapta)
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    } else { // Cheia se afla in subarborele drept
        if (root->right == NULL) return root;

        // Zag-Zig (dreapta stanga)
        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        // Zag-Zag (dreapta dreapta)
        else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Functie pentru a insera un nod in arbore
Node* insert(Node* root, int key) {
    if (root == NULL) 
        return newNode(key);

    root = splay(root, key);

    if (root->key == key) 
        return root;

    Node* newnode = newNode(key);
    printf("acum inseram\n");
    if (key < root->key) {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    } else {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }

    return newnode;
}

// Functie pentru a sterge un nod din arbore
Node* deleteNode(Node* root, int key) {
    if (root == NULL) 
        return NULL;

    root = splay(root, key);

    if (key != root->key) 
        return root;

    Node* temp;
    if (root->left == NULL) {
        temp = root;
        root = root->right;
    } else {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }

    free(temp);
    return root;
}

// Functie pentru a cauta un nod in arbore
Node* search(Node* root, int key) {
    return splay(root, key);
}

// Functie pentru parcurgerea in ordine (inorder)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Functie pentru parcurgerea in preordine (preorder)
void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// Functie pentru parcurgerea in postordine (postorder)
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

// Functie principala pentru testarea splay tree-ului
int main() {
    Node* root = NULL;

    printf("Inseram valoarea 10\n");
    root = insert(root, 10);
    preorder(root);
    printf("\n");
    printf("Inseram valoarea 20\n");
    root = insert(root, 20);
    preorder(root);
    printf("\n");
    printf("Inseram valoarea 30\n");
    root = insert(root, 30);
    preorder(root);
    printf("\n");
    printf("Inseram valoarea 40\n");
    root = insert(root, 40);
    preorder(root);
    printf("\n");
    printf("Inseram valoarea 50\n");
    root = insert(root, 50);
    preorder(root);
    printf("\n");
    printf("Inseram valoarea 25\n");
    root = insert(root, 25);

    printf("\n\n\n");

    printf("Parcurgerea in preordine a arborelui:\n");
    preorder(root);
    printf("\n");

    printf("Parcurgerea in postordine a arborelui:\n");
    postorder(root);
    printf("\n");

    printf("Parcurgerea in ordine a arborelui:\n");
    inorder(root);
    printf("\n");

    printf("\n\n\n");

    root = search(root, 20);
    printf("Parcurgerea in preordine dupa cautarea lui 20:\n");
    preorder(root);
    printf("\n");

    printf("\n\n\n");

    root = deleteNode(root, 50);
    printf("Parcurgerea in preordine dupa stergerea lui 50:\n");
    preorder(root);
    printf("\n");

    printf("\n\n\n");

    return 0;
}

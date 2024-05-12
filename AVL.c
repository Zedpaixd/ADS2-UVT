#include <stdio.h>
#include <stdlib.h>

// Structura pentru un nod in arborele AVL
struct Node {
    int data;
    struct Node *left, *right;
    int height;
};

// Creearea unui nod nou
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->height = 1; // Inaltimea initiala este 1 (un nod singur are inaltimea 1)
    return newNode;
}

// Functie pentru a obtine inaltimea unui nod
int height(struct Node* node) {
    return (node == NULL) ? 0 : node->height;
}

// Functie pentru a obtine factorul de echilibru al unui nod
int getBalance(struct Node* node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

// Rotirea la dreapta
struct Node* rotateRight(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Efectuam rotirea
    x->right = y;
    y->left = T2;

    // Actualizeam inaltimea
    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));
    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));

    // Returnam noua radacina
    return x;
}

// Rotirea la stanga
struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Efectuam rotirea
    y->left = x;
    x->right = T2;

    // Actualizam inaltimea
    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));
    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));

    // Returnam noua radacina
    return y;
}

// Adauga un nod in arborele AVL
struct Node* addNode(struct Node* node, int data) {
    // Parcurgem arborele si adaugam nodul
    if (node == NULL) return createNode(data);
    if (data < node->data) node->left = addNode(node->left, data);
    else if (data > node->data) node->right = addNode(node->right, data);
    else return node; // Valori duplicate nu sunt permise

    // Actualizeaza inaltimea nodului curent
    node->height = 1 + ((height(node->left) > height(node->right)) ? height(node->left) : height(node->right));

    // Obtine factorul de echilibru al acestui nod
    int balance = getBalance(node);

    // Cazul stanga-stanga
    if (balance > 1 && data < node->left->data)
        return rotateRight(node);

    // Cazul dreapta-dreapta
    if (balance < -1 && data > node->right->data)
        return rotateLeft(node);

    // Cazul stanga-dreapta
    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Cazul dreapta-stanga
    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Gasesim nodul cu valoarea minima
struct Node* findMinNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Sterge un nod din arborele AVL
struct Node* removeNode(struct Node* root, int data) {
    if (root == NULL) return root;

    // Parcurgem arborele pentru a gasi nodul de sters
    if (data < root->data) root->left = removeNode(root->left, data);
    else if (data > root->data) root->right = removeNode(root->right, data);
    else {
        // In cazul daca avem un nod cu un singur copil sau fara copii
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // ... sau un nod cu doi copii
        struct Node* temp = findMinNode(root->right);

        // Copiam continutul succesorului inorder in acest nod
        root->data = temp->data;

        // Stergem succesorul inorder
        root->right = removeNode(root->right, temp->data);
    }

    // Actualizam inaltimea radacinii curente
    root->height = 1 + ((height(root->left) > height(root->right)) ? height(root->left) : height(root->right));

    // Obtinem factorul de echilibru al acestui nod
    int balance = getBalance(root);

    // Cazul stanga-stanga
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    // Cazul stanga-dreapta
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Cazul dreapta-dreapta
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    // Cazul dreapta-stanga
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Cauta un nod in arbore
struct Node* searchNode(struct Node* root, int data) {
    if (root == NULL || root->data == data) return root;
    if (data < root->data) return searchNode(root->left, data);
    return searchNode(root->right, data);
}

// Parcurgerea inorder
void inorderPrint(struct Node* root) {
    if (root != NULL) {
        inorderPrint(root->left);
        printf("%d ", root->data);
        inorderPrint(root->right);
    }
}

// Parcurgerea preorder
void preorderPrint(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderPrint(root->left);
        preorderPrint(root->right);
    }
}

// Parcurgerea postorder
void postorderPrint(struct Node* root) {
    if (root != NULL) {
        postorderPrint(root->left);
        postorderPrint(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n\nOperatii cu Arborele AVL:\n");
        printf("1. Adauga membru\n");
        printf("2. Sterge membru\n");
        printf("3. Cauta membru\n");
        printf("4. Parcurgere inorder\n");
        printf("5. Parcurgere preorder\n");
        printf("6. Parcurgere postorder\n");
        printf("7. Iesire\n");
        printf("Introdu optiunea ta: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Introdu valoarea de adaugat: ");
                scanf("%d", &value);
                root = addNode(root, value);
                break;
            case 2:
                printf("Introdu valoarea de sters: ");
                scanf("%d", &value);
                root = removeNode(root, value);
                break;
            case 3:
                printf("Introdu valoarea de cautat: ");
                scanf("%d", &value);
                if (searchNode(root, value) != NULL) {
                    printf("Valoarea %d este in arbore.\n", value);
                } else {
                    printf("Valoarea %d nu este in arbore.\n", value);
                }
                break;
            case 4:
                printf("Parcurgere inorder: ");
                inorderPrint(root);
                printf("\n");
                break;
            case 5:
                printf("Parcurgere preorder: ");
                preorderPrint(root);
                printf("\n");
                break;
            case 6:
                printf("Parcurgere postorder: ");
                postorderPrint(root);
                printf("\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Optiune invalida!\n");
        }
    }

    return 0;
}

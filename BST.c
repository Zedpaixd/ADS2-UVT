#include <stdio.h>
#include <stdlib.h>

// Structura pentru un nod al arborelui
struct Node {
    int data;
    struct Node *left, *right;
};
/*
                   5
                 /   \ 
               3       7
             /   \    / \
           1      4  6    8
          / \    / \/ \  /  \  
         0   2   N   U   L   L
*/

// Creeaza un nod nou
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Adaugarea unui nod in arbore
struct Node* addNode(struct Node* node, int data) {
    if (node == NULL) return createNode(data);
    if (data < node->data) node->left = addNode(node->left, data);
    else if (data > node->data) node->right = addNode(node->right, data);
    return node;
}

// Gasesirea nodului cu valoarea minima
struct Node* findMinNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Stergerea unui nod din arbore
struct Node* removeNode(struct Node* root, int data) {
    if (root == NULL) return root;   // cazul de baza

    // Parcurge arborele pentru a gasi nodul de sters
    if (data < root->data) 
        root->left = removeNode(root->left, data);

    else if (data > root->data) 
        root->right = removeNode(root->right, data);
    
    else {
        // Nod cu un singur copil sau fara copii
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Nod cu doi copii
        struct Node* temp = findMinNode(root->right);

        // Copiaza continutul succesorului inorder in acest nod
        root->data = temp->data;

        // Sterge succesorul inorder
        root->right = removeNode(root->right, temp->data);
    }
    return root;
}

// Cautarea unui nod in arbore
struct Node* searchNode(struct Node* root, int data) {
    if (root == NULL || root->data == data) return root;
    if (data < root->data) return searchNode(root->left, data);
    return searchNode(root->right, data);
}

// Parcurgere inorder
void inorderPrint(struct Node* root) {
    if (root != NULL) {
        inorderPrint(root->left);
        printf("%d ", root->data);
        inorderPrint(root->right);
    }
}

// Parcurgere preorder
void preorderPrint(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderPrint(root->left);
        preorderPrint(root->right);
    }
}

// Parcurgere postorder
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
        printf("\n\nOperatii cu arborele binar de cautare:\n");
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

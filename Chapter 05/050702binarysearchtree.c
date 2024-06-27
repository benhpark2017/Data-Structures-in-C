/**Solutions to Chapter 5, Section 7, Exercise 2 of Horowitz's Data
 * Structures in C.*/

#include <stdio.h>
#include <stdlib.h>

#define IS_FULL(ptr) (!(ptr))

typedef struct treeNode {
    struct treeNode *left_child;
    int data;
    struct treeNode *right_child;
} node;

typedef struct treeNode *treePtr;

void inorder(treePtr root) {
    if (root) {
        inorder(root->left_child);
        printf("%d ", root->data);
        inorder(root->right_child);
    }
}

void preorder(treePtr root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left_child);
        preorder(root->right_child);
    }
}

void postorder(treePtr root) {
    if (root) {
        postorder(root->left_child);
        postorder(root->right_child);
        printf("%d ", root->data);
    }
}

treePtr recursiveSearch(treePtr root, int key) {
    if (!root) return NULL;
    if (key == root->data) return root;
    if (key < root->data) return recursiveSearch(root->left_child, key);
    return recursiveSearch(root->right_child, key);
}

treePtr modifiedSearch(treePtr root, int key) {
    treePtr result = NULL;
    treePtr ptr = root;

    while (ptr != NULL) {
        result = ptr;
        if (key == ptr->data) {
            printf("Exiting function, same key found.\n");
            return NULL;
        }
        if (key < ptr->data)
            ptr = ptr->left_child;
        else
            ptr = ptr->right_child;
    }
    return result;
}

void insertNode(treePtr *root, int num) {
    treePtr ptr;
    treePtr temp = modifiedSearch(*root, num);

    if (temp || !*root) {
        ptr = (treePtr)malloc(sizeof(struct treeNode));
        if (IS_FULL(ptr)) {
            fprintf(stderr, "The memory is full.\n");
            exit(1);
        }
        ptr->data = num;
        ptr->left_child = ptr->right_child = NULL;

        if (*root) {
            if (num < temp->data)
                temp->left_child = ptr;
            else
                temp->right_child = ptr;
        } else {
            *root = ptr;
        }
    }
}

void deleteNode(treePtr *root, int key) {
    treePtr ptr, parent, temp, child;

    ptr = modifiedSearch(*root, key);
    if (!ptr) {
        printf("Now there is no node found.\n");
        return;
    }

    parent = modifiedSearch(*root, key);

    if (!ptr->left_child) {
        child = ptr->right_child;
    } else if (!ptr->right_child) {
        child = ptr->left_child;
    } else {
        temp = ptr->right_child;
        while (temp->left_child) {
            temp = temp->left_child;
        }
        temp->left_child = ptr->left_child;
        child = ptr->right_child;
    }

    if (!parent) {
        *root = child;
    } else if (parent->left_child == ptr) {
        parent->left_child = child;
    } else {
        parent->right_child = child;
    }

    free(ptr);
}

void freeAll(treePtr ptr) {
    if (ptr != NULL) {
        freeAll(ptr->left_child);
        freeAll(ptr->right_child);
        free(ptr);
    }
}

int main() {
    treePtr root = NULL;
    int select, inputData;

    while (1) {
        printf("Select menu:\n"
               "1. Insert node\n"
               "2. Delete node\n"
               "3. Display tree\n"
               "4. Exit\n"
               "Input Number => ");
        scanf("%d", &select);

        switch (select) {
            case 1:
                printf("Input the insert data: ");
                scanf("%d", &inputData);
                insertNode(&root, inputData);
                break;
            case 2:
                printf("Input the delete data: ");
                scanf("%d", &inputData);
                deleteNode(&root, inputData);
                break;
            case 3:
                printf("\n1. Recursive inorder:\n");
                inorder(root);

                printf("\n2. Recursive preorder:\n");
                preorder(root);

                printf("\n3. Recursive postorder:\n");
                postorder(root);

                printf("\n\n");
                break;
            case 4:
                freeAll(root);
                printf("Freeing all memory, the program will now exit.\n");
                return 0;
            default:
                printf("Error: selection is out of bounds.\n");
                break;
        }
    }

    return 0;
}

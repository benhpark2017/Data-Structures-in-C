/**Solutions to Chapter 5, Section 4, Exercise 2 of Horowitz's
 * Data Structures in C, page 210.
 */

#include <stdio.h> 
#include <stdlib.h> 

//treeNode structure
typedef struct treeNode *tree_pointer; 
    struct treeNode{ 
    char data; 
    tree_pointer left_child, right_child, parent; 
} treeNode;

tree_pointer root, now;

static int l=1, x=1, chk = 1;

//A function that creates a new node
void CreateNode(char data) 
{ 
tree_pointer ptr; 
ptr = (tree_pointer) malloc(sizeof(struct Node)); 


if(root == NULL){ 
ptr->data = data; 
ptr->parent = NULL; 
ptr->right_child = NULL; 
root = ptr; 
now = root; 
} 
else{ 
ptr->data = data; 
ptr->parent = now; 
ptr->left_child = NULL; 
ptr->right_child = NULL; 
if(x == 1){ 
now->left_child = ptr; 
} 
else{ 
now->right_child = ptr; 
l=1; 
} 
} 
now = ptr; 
} 

//노드 위치 찾기 
void SearchNode() 
{ 
l=0; 
if(now==root){ 
chk=0; 
} 
else{ 
now = now->parent; 
if(now==root){ 
chk++; 
if(chk==3 || now->right_child){ 
chk=0; 
} 
} 
else if(now->right_child != NULL){ 
while(now->right_child != NULL){ 
now = now->parent; 
if(now==root){ 
chk++ ; 
if(chk==3 || now->right_child){   
chk=0; 
break 
} 
} 
} 
} 
} 
} 

// 노드 삽입하기 

void NodeInsert() {
    char data, yn;
    while (chk) {
        if (l) {
            printf("%c", now->data);
            printf("의 왼쪽 자식노드가 있습니까(Yes or No)? "); 
            scanf("%s",&yn);
            if(yn == 'y' || yn == 'Y') { 
                printf("%c", now->data); 
                printf("의 왼쪽 Data를 입력하세요=> "); 
                scanf("%s",&data); 
                x = 1;
                CreateNode(data);
            }//end inner if
        }//end outer if
        if(yn == 'n' || yn == 'N') {
            printf("%c", now->data);
            printf("의 오른쪽 형제노드가 있습니까(Yes or No)? "); 
            scanf("%s",&yn);
            if(yn == 'y' || yn == 'Y'){ 
                printf("%c", now->data); 
                printf("의 오른쪽 Data를 입력하세요=> "); 
                scanf("%s",&data); 
                x = 2;
                CreateNode(data); 
            } else {
                SearchNode(); 
            } //end if-else
        } //end outer if
    } //end while
}//end of function

// in-order traversal
void inorder(tree_pointer ptr) {
    if(ptr) {
         inorder(ptr->left_child); 
         printf("%c ", ptr->data); 
         inorder(ptr->right_child); 
    }
}

//Pre-order traversal
void preorder(tree_pointer ptr) { 
    if(ptr) {
        printf("%c ", ptr->data); 
        preorder(ptr->left_child); 
        preorder(ptr->right_child); 
    }
}

// Post-order traversal
void postorder(tree_pointer ptr) {
    if(ptr) {
        postorder(ptr->left_child);
        postorder(ptr->right_child);
        printf("%c ", ptr->data);
    }
}

// Swap_tree() function exchanges the left_child and right_child
void swap_tree(tree_pointer ptr) {
    tree_pointer temp;
    temp = (tree_pointer)malloc(sizeof(Node));
    if (ptr) {
        temp = (ptr->left_child); 
        (ptr->left_child)=(ptr->right_child); 
        (ptr->right_child) = temp; 
    }
}

// main() 함수
int main(){
    char data; 
    printf("Please enter alphabet characters for root\n"); 
    scanf("%c",&data); 

    CreateNode(data); 
    NodeInsert(); 

    printf("In-order traversal: "); 
    inorder(root); 

    printf("\nPre-order traversal: "); 
    preorder(root); 

    printf("\nPost-order traversal: "); 
    postorder(root); 

    printf("\n"); 

    printf("After swap_tree() is called"); 
    swap_tree(root); 

    printf("New in-order traversal: "); 
    inorder(root); 

    printf("\nNew pre-order traversal: "); 
    preorder(root); 

    printf("\nNew post-order traversal: "); 
    postorder(root); 

    printf("\n"); 
}


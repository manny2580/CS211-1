#include <stdio.h>
#include <stdlib.h>

struct Node{
    int value;
    struct Node *right;
    struct Node *left;
};

struct Node *root;

struct Node *insertNode(struct Node *node, int value){

  //create root
  if(node==NULL){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->right = NULL;
    newNode->left = NULL;
    //newNode->parent = NULL;
    printf("inserted\n");
    return newNode;
  }

  if(value==node->value){
    printf("duplicate\n");
    return node;
  }

  else if (value < node->value){
    node->left  = insertNode(node->left, value);
  }
  else if (value > node->value){
    node->right = insertNode(node->right, value);
  }

    return node;

}

 void printBST(struct Node *node){

   if (node == NULL){
     return;
   }

   printBST(node->left);
   printf("%d ", node->value);
   printBST(node->right);
}

void searchBST(struct Node *node, int value){
  if(node==NULL){
    printf("absent\n");
    //newNode->parent = NULL;
  }
  else if(node->value==value){
    printf("present\n");
  }

  else if (value < node->value){
    searchBST(node->left, value);
  }
  else if (value > node->value){
    searchBST(node->right, value);
  }

}

void freeBST(struct Node *node){
  if(node->right!=NULL){
  freeBST(node->right);
}
  if(node->left!=NULL){
  freeBST(node->left);
}
  free(node);
}

struct Node *getInorderSuccessor(struct Node  *node)
{
    struct Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct Node *deleteNode(struct Node *node, int value)
{
    // base case
    if (node == NULL){
      return node;
    }
    if (value < node->value){
        node->left = deleteNode(node->left, value);
    }

    else if (value > node->value){
        node->right = deleteNode(node->right, value);
    }

    else
    {
        // node with only one child or no child
        if (node->left == NULL)
        {
            struct Node *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            struct Node *temp = node->left;
            free(node);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct Node *temp = getInorderSuccessor(node->right);

        // Copy the inorder successor's content to this node
        node->value = temp->value;

        // Delete the inorder successor
        node->right = deleteNode(node->right, temp->value);
    }
    return node;
}

int main(int argc, char *argv[]){

  root = NULL;

  static char buffer[1024];
  while (fgets(buffer, 1024, stdin)){

    char action = buffer[0];
    buffer[0]=' ';
    int input =atoi(buffer);

    //insert
    if(action =='i'){
      root = insertNode(root,input);
    }
    //search
    else if(action =='s'){
      searchBST(root, input);
    }
    //print
    else if(action =='p'){
      printBST(root);
      printf("\n");
    }
    //delete
    else if(action =='d'){
      root = deleteNode(root,input);
    }
  }
  freeBST(root);
}

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
   printf("\n");
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
  freeBST(node->right);
  freeBST(node->left);
  free(node);
}

struct Node *deleteNode(struct Node *node, int value){


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
    }
    //delete
    else if(action =='d'){
      root = deleteNode(root,input);
    }
  }
  freeBST(root);
}

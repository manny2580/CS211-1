#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isInsert(char c);

struct Node{
    int value;
    struct Node *next;
};

int main (int argc, char *argv[]){

  struct Node *head = NULL;


  FILE * file;
  file = fopen (argv[1], "r");

  char *input [30];

  static char buffer[1024];
  while (fgets(buffer, 1024, stdin)){

        printf("%s",buffer);
        bool remove =isInsert(buffer[0]);
        buffer[0]=' ';
        int input =atoi(buffer);
        printf("%d", input);

        if(buffer[0]=='i'){
          //insert
          struct Node *ptr =  head;

          //create head
          if(head==NULL){
            head = (struct Node*)malloc(sizeof(struct Node));
            head->value = input;
            head->next = NULL;
          }
          else{
            struct Node *prev = ptr;
            while(ptr->next!=NULL){
              prev=ptr;
              ptr = ptr->next;
              if(ptr->value<input){
                struct Node *newNode;
                newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode->value = input;
                prev->next = newNode;
                newNode->next = ptr;
              }
            }
          }
      }
        else{
          //delete
        }


      }


}

bool isInsert(char c){
  if(c=='i'){
    return true;
  }
  return false;
}

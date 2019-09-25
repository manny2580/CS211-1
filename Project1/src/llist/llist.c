#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isInsert(char c);

struct Node{
    int value;
    struct Node *next;
};

int main (int argc, char *argv[]){

  struct Node **head_ptr = NULL;
  int length = 0;

  static char buffer[1024];
  while (fgets(buffer, 1024, stdin)){

        printf("%c",buffer[0]);
        bool insert =isInsert(buffer[0]);
        buffer[0]=' ';
        int input =atoi(buffer);
        printf("%d\n", input);

        if(insert){
          //insert
          printf("inserting..\n");
          struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
          newNode->value = input;
          newNode->next = NULL;


          //head is null
          if(head_ptr==NULL){
            printf("creating head..\n");
            (*head_ptr) = newNode;
            //printf("%d\n", head->value);
          }

          //insert before head


          struct Node *head = *head_ptr;

          if(((struct Node *)*head_ptr)->value>input){
            newNode->next = *head_ptr;
            *head_ptr = newNode;
          }

          //insert in middle
          else{
            struct Node **ptr = head_ptr;
            struct Node **prev = NULL;

            while(((struct Node *)*ptr)->next!=NULL){

              if(((struct Node *)*ptr)->value>input){
                ((struct Node *)*prev)->next = newNode;
                newNode->next = *ptr;
                break;
              }
              prev=ptr;
              ptr= &(((struct Node *)ptr)->next);
            }

          }

          //insert at end

          struct Node *ptr = head;

          while(ptr->next!=NULL){
            printf("%d\t", ptr->value);
          }
          printf("\n");

          length++;


      }
        else{
          //delete
        }
      }
}
//assumes chars are only i or d
bool isInsert(char c){
  if(c=='i'){
    return true;
  }
  return false;
}

void push(struct Node** head_ref, int new_data)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    /* 2. put in the data  */
    new_node->value  = new_data;

    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);

    /* 4. move the head to point to the new node */
    (*head_ref)    = new_node;
}

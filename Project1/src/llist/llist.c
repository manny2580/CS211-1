#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isInsert(char c);

struct Node{
    int value;
    struct Node *next;
};


struct Node *insert(struct Node *head, int input){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = input;

    //head is null
    if(head == NULL){
        head = newNode;
        head->next = NULL;
    }
    //insert before head
    else if(head->value > input){
        newNode->next = head;
        return newNode;
    }
    else{
        struct Node *prev;
        struct Node *ptr = head;
        while(ptr != NULL){

            if(ptr->value == input){
                return head;
            }
            else if(ptr->value > input){
                newNode->next = prev->next;
                prev->next = newNode;
                return head;
            }
            prev = ptr;
            ptr = ptr->next;
        }

        newNode-> next = NULL;
        prev->next = newNode;
        ptr = newNode;
        ptr->next = NULL;

    }
    return head;
}

struct Node *delete(struct Node *head, int input){
    struct Node *ptr = head;
    struct Node *prev = head;

    if (ptr == NULL){
        return head;
    }

    if(head->value == input){
        struct Node *newHead = head->next;
        free(head);
        return newHead;
    }
    while(ptr != NULL){
        if(ptr->value == input){
            prev->next = ptr->next;
            free(ptr);
            return head;
        }
        prev = ptr;
        ptr = ptr->next;
    }

    return head;
}

void printList(struct Node *head){

  int length = 0;
  struct Node *ptr = head;
  while(ptr!=NULL){
    length++;
    ptr=ptr->next;
  }
  printf("%d :", length);
  ptr = head;
  while(ptr!=NULL){
    printf(" %d", ptr->value);
    ptr=ptr->next;
  }
  printf("\n");
}

//https://github.com/meesunology/CS211-ComputerArchitecture/blob/master/second/second.c

int main (int argc, char *argv[]){

  struct Node *head=NULL;

  static char buffer[1024];
  while (fgets(buffer, 1024, stdin)){

        bool shouldInsert =isInsert(buffer[0]);
        buffer[0]=' ';
        int input =atoi(buffer);

        if(shouldInsert){
          head = insert(head, input);
      }
        else{
          //delete
          head = delete(head, input);
        }
        printList(head);
      }

      struct Node *ptr = head;
      struct Node *prev = NULL;
      while(ptr!=NULL){
        free(prev);
        prev = ptr;
        ptr = ptr->next;
      }
      free(ptr);
      free(prev);
}
//assumes chars are only i or d. this is really stupid
bool isInsert(char c){
  if(c=='i'){
    return true;
  }
  return false;
}

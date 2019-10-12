#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *rule;
char *currentState;
int numCells;

char newCell(char *neighbors){

  //printf("YEEEE");
  if(strcmp(neighbors, "...")==0){
    return rule[0];
  }
  else if(strcmp(neighbors, "..*")==0){
    return rule[1];
  }
  else if(strcmp(neighbors, ".*.")==0){
    return rule[2];
  }
  else if(strcmp(neighbors, ".**")==0){
    return rule[3];
  }
  else if(strcmp(neighbors, "*..")==0){
    return rule[4];
  }
  else if(strcmp(neighbors, "*.*")==0){
    return rule[5];
  }
  else if(strcmp(neighbors, "**.")==0){
    return rule[6];
  }
  else if(strcmp(neighbors, "***")==0){
    return rule[7];
  }

  return 'A';
}

char *getNextState(){
  char *newState = (char*)malloc(sizeof(char)*(numCells+1));
  newState[numCells]='\0';
  int i =0;
  for(i =0;i<numCells;i++){
    char neighbors[4];
    neighbors[3]='\0';
    if(i==0){
      neighbors[0]=currentState[numCells-1];
      neighbors[1]=currentState[i];
      neighbors[2]=currentState[i+1];
      //printf("neighbors: %s\n",neighbors);
    }
    else if(i==numCells-1){
      neighbors[0]=currentState[i-1];
      neighbors[1]=currentState[i];
      neighbors[2]=currentState[0];
      //printf("neighbors: %s\n",neighbors);
    }
    else{
      neighbors[0] = currentState[i-1];
      neighbors[1] = currentState[i];
      neighbors[2] = currentState[i+1];
    }
    newState[i]= newCell(neighbors);


  }
  //printf("\n");
  free(currentState);
  return newState;
}

int main (int argc, char *argv[]){

  char NUMCELLS[100];
  fgets(NUMCELLS, 100,stdin);
  numCells = atoi(NUMCELLS);

  char NUMITERATIONS[100];
  fgets(NUMITERATIONS, 100,stdin);
  int numIterations = atoi(NUMITERATIONS);



  rule = (char*)malloc(sizeof(char)*(9));
  fgets(rule, 9, stdin);

  getchar();

  char *initialState = (char*)malloc(sizeof(char)*(numCells+1));
  fgets(initialState, numCells+1, stdin);


  currentState = (char*)malloc(sizeof(char)*(numCells+1));
  currentState[numCells]='\0';

    //if there is a 4th argument
    if(initialState[0]!='\n'&&initialState[0]!='\0'){
      //printf("yee");
      int i =0;
      while(initialState[i]!='\n'&&initialState[i]!='\0'){
        if(i==numCells){
          printf("Initial state is longer than numCells.\n");
          return 1;
        }
    //    printf("copying: %c\n",initialState[i]);
        currentState[i]=initialState[i];
        i++;
      }
      free(initialState);
      while(i<numCells){
        currentState[i]='.';
        //  printf("%d %c\t",i, currentState[i]);
           i++;
         }


       }
       else{
             free(initialState);
         int i =0;
         while(i!=numCells){
           currentState[i]='.';
           i++;
         }
         //this is iffy8
         int cellPos = floor(numCells/2);
         //printf("cellPos: %d\n", cellPos);
         currentState[cellPos] = '*';
       }


       printf("%s\n",currentState);
       int iter = 0;

       for(iter = 0;iter<numIterations;iter++){

         currentState = getNextState();
         printf("%s\n",currentState);
       }

       free(currentState);

     //free(rule);

     }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *rule;
char *currentState;
int numCells;

char newCell(char *neighbors){
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
  for(int i =0;i<numCells;i++){
    char neighbors[4];
    neighbors[3]='\0';
    if(i==0){
      neighbors[0]='.';
      neighbors[1]=currentState[i];
      neighbors[2]=currentState[i+1];
    }
    else if(i==numCells-1){
      neighbors[0]=currentState[i-1];
      neighbors[1]=currentState[i];
      neighbors[2]='.';
    }
    else{
      neighbors[0] = currentState[i-1];
      neighbors[1] = currentState[i];
      neighbors[2] = currentState[i+1];
    }
    newState[i]= newCell(neighbors);

    //printf("%s\n",neighbors);
  }
  //printf("\n");
  free(currentState);
  return newState;
}

int main (int argc, char *argv[]){

  for(int i =0;i<argc;i++){
    printf("%s\n",argv[i]);
  }

  //get input
  if(argc<4){
    printf("Incorrect arguments.\n");
    return 0;
  }
  numCells = atoi(argv[1]);
  int numIterations = atoi(argv[2]);
  rule = argv[3];
  //doesnt work

  if(strlen(rule)!=8){
    printf("Improper rule. %d\n", (int)strlen(rule));
    return 0;
  }

  currentState = (char*)malloc(sizeof(char)*(numCells+1));
  currentState[numCells]='\0';

  printf("numCells: %d\tnumIterations: %d\n", numCells, numIterations);
  printf("rule: %s\n",rule );

  if(argc==5){
    char *initialState = argv[4];
    int i =0;
    while(initialState[i]!='\0'){
      if(i==numCells){
        printf("Initial state is longer than numCells.\n");
        return 1;
      }
      currentState[i]=initialState[i];
      i++;
    }
    while(i!=numCells){
      currentState[i]='.';
      i++;
    }
  }
  else{
    int i =0;
    while(i!=numCells){
      currentState[i]='.';
      i++;
    }
    //this is iffy8
    int cellPos = floor((numCells-1)/2);
    printf("cellPos: %d\n", cellPos);
    currentState[cellPos] = '*';
  }
  printf("%s\n",currentState);

  for(int iter = 0;iter<numIterations;iter++){
    currentState = getNextState(currentState, rule);
    printf("%s\n",currentState);
  }

  free(currentState);



}

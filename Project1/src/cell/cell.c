#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *rule;
char *currentState;


char *getNextState(){
  
  return currentState;
}

int main (int argc, char *argv[]){
  //get input
  if(argc<4){
    printf("Incorrect arguments.\n");
    return 0;
  }
  int numCells = atoi(argv[1]);
  int numIterations = atoi(argv[2]);
  rule = argv[3];

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
    int cellPos = floor(numCells/2)-1;
    printf("cellPos: %d\n", cellPos);
    currentState[cellPos] = '*';
  }
  printf("initialState: %s\n",currentState);

  for(int iter = 0;iter<numIterations;iter++){
    printf("%s\n",currentState);
    currentState = getNextState(currentState, rule);
  }

  free(currentState);



}

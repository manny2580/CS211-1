#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

struct Directive{
  int gateType;

  char **inputVariables;
  int inputVariablesSize;
  int * inputVariablesValues;

  char **outputVariables;
  int outputVariablesSize;
  int * outputVariablesValues;

  struct Directive *next;
};

void printMatrix(int **matrix, int rows, int columns){
  for(int i =0;i<rows;i++){
    for(int j=0;j<columns;j++){
      if(j==columns-1){
        printf("%d", matrix[i][j]);
      }
      else{
      printf("%d ", matrix[i][j]);
    }
    }
    printf("\n");
  }
}

void freeMatrix(int ** matrix, int rows, int columns){
  for(int i = 0; i < rows; i++) {
      free(matrix[i]);
  }
  free(matrix);
}

int gateType(char g[17]){

  int r = 0;
  if(strcmp(g,"PASS")==1){

    r= 1;
  }
  if(strcmp(g,"NOT")==1){
    r= 2;
  }
  if(strcmp(g,"ADD")==1){
    r= 3;
  }
  if(strcmp(g,"OR")==1){
    r= 4;
  }
  if(strcmp(g,"NAND")==1){
    r= 5;
  }
  if(strcmp(g,"NOR")==1){
    r= 6;
  }
  if(strcmp(g,"XOR")==1){
    r= 7;
  }
  if(strcmp(g,"DECODER")==1){
    r= 8;
  }
  if(strcmp(g,"MULTIPLEXER")==1){
    r= 9;
  }
  printf("R: %s, %d\n", g,r);
  return r;

}


int main (int argc, char *argv[]){

  int numInputs = 0;
  int numOutputs = 0;

  int inputVariablesSize = 5;
  char inputVariables[inputVariablesSize][17];

  int outputVariablesSize = 5;
  char outputVariables[outputVariablesSize][17];

  //yee

  FILE * circuit;
  circuit = fopen (argv[1], "r");


  //input variables
  fscanf(circuit, "%16s", inputVariables[numInputs]);
  while ((fscanf(circuit, "%16s", inputVariables[numInputs]) == 1) && strcmp(inputVariables[numInputs], "OUTPUT") != 0) {
        //printf("%s|", inputVariables[numInputs]);
        numInputs++;
  }

  //output variables

  while ((fscanf(circuit, " %16s", outputVariables[numOutputs]) == 1) && gateType( outputVariables[numOutputs]) != 0) {
        //printf("___%s|",outputVariables[numOutputs]);
        numOutputs++;
  }

/*
  char x[17];
  while ((fscanf(circuit, " %16s", x) == 1){
    int type = gateType(x);

    while ((fscanf(circuit, " %16s", x) == 1 &&gateType( outputVariables[numOutputs]) != 0)

  }
  */




  //allocate input table
  int numRows = pow(2,numInputs);
  int ** table = (int **)malloc(sizeof(int*) *numRows);
  for(int i = 0; i < numRows; i++) {
    table[i] = (int *)malloc(sizeof(int) *numInputs);
  }

  bool zero = true;
  for(int i =0; i <numInputs;i++){
    int interval = (numRows/2)/(i+1);
      for(int j =0; j<numRows; j++){

        if(j%interval==0){
          zero = !zero;
        }

        if(zero){
          table[j][i] = 0;
        }
        else{
          table[j][i] = 1;
        }
      }
    }
    printMatrix(table, numRows, numInputs);
    freeMatrix(table, numRows,numInputs);
}

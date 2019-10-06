#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *getRow(int size, int rowNum, int **matrix){
  int *row = malloc(sizeof(int*)*size);
  for(int i =0;i<size;i++){
    row[i] =matrix[rowNum][i];
  }
  return row;
}

int *getCol(int size, int colNum, int **matrix){
  int *col = malloc(sizeof(int*)*size);
  for(int i =0;i<size;i++){
    col[i]= matrix[i][colNum];
  }

  return col;
}

int **multiply(int size,int **matrix1, int **matrix2){
  int **answer;
  answer = (int**)malloc(sizeof(int**) *size);

  for(int i = 0; i < size; i++) {
          answer[i] = (int*)malloc(sizeof(int*) *size);
      }

  for(int i =0;i<size;i++){
    for(int j =0;j<size;j++){
      int *row = getRow(size, i, matrix1);
      int *col = getCol(size, j,matrix2);
      int num=0;
      for(int k = 0;k<size;k++){
        num = num+(row[k]*col[k]);
      }
      free(row);
      free(col);
      answer[i][j] = num;
    }
  }

  bool same = true;
  for(int i =0;i<size;i++){
    for(int j =0;j<size;j++){
      if(matrix1[i][j]!=matrix2[i][j]){
        same = false;
      }
    }
  }
  if(!same){
    free(matrix1);
  }

return answer;

}


void printMatrix(int size,int **matrix){
  for(int i =0;i<size;i++){
    for(int j=0;j<size;j++){
      if(j==size-1){
        printf("%d", matrix[i][j]);
      }
      else{
      printf("%d ", matrix[i][j]);
    }
    }
    printf("\n");
  }
}

int main (int argc, char * argv[]){

  if(argc!=2){
    printf("Enter a single arguments.\n");
    return 0;
  }

  FILE *file;
  file = fopen(argv[1], "r");
    if (file == NULL){
        printf("Error opening file.");
        return 1;
    }
    int size;
    fscanf(file, "%d", &size);

    int **inputMatrix;
    inputMatrix = malloc(sizeof(int*) *size);

    for(int i = 0; i < size; i++) {
            inputMatrix[i] = malloc(sizeof(int*) *size);
        }

    for(int i =0; i <size;i++){
      for(int j =0; j<size; j++){

        int current;
        fscanf(file, "%d", &current);
        inputMatrix[i][j]=current;

      }
    }

    int power;
    fscanf(file, "%d", &power);

    /*
    printf("Input Matrix:\n");
    printMatrix(size, (inputMatrix));
    printf("\n");
    */
    //printf("YEEE %d\n", power);

    int **a;
    if(power==0){
      //return identity matrix In
      //printf("YEEERRE");
      for(int i =0;i<size;i++){
        for(int j =0;j<size;j++){
          if(i==j){
            printf("1 ");
          }
          else{
            printf("0 ");
          }
        }
        printf("\n");
      }
      free(inputMatrix);
      return 0;
    }

    else if(power ==1){
      printMatrix(size,inputMatrix);
    }
    else{
    for(int i =1;i<power;i++){
      //power = 2
      if(i==1){
        a = multiply(size, inputMatrix, inputMatrix);
      }
      else{
        a = multiply(size, a, inputMatrix);
      }
    }
    //a = multiply(size, inputMatrix, inputMatrix);
    printMatrix(size, a);
}

    for(int i = 0; i < size; i++) {
        free(a[i]);
        free(inputMatrix[i]);
    }
    free(a);
    free(inputMatrix);

    return 0;
}

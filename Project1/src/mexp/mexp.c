#include <stdio.h>
#include <stdlib.h>

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
answer = malloc(sizeof(int*) *size);

for(int i = 0; i < size; i++) {
        answer[i] = malloc(sizeof(int*) *size);
    }

  for(int i =0;i<size;i++){
    for(int j =0;j<size;j++){
      int *row = getRow(size, i, matrix1);
      int *col = getCol(size, j,matrix2);
      int num=0;
      for(int k = 0;k<size;k++){
        num = num+(row[k]*col[k]);
      }
      answer[i][j] = num;
    }
  }


return answer;
}


void printMatrix(int size,int **matrix){
  for(int i =0;i<size;i++){
    for(int j=0;j<size;j++){
      printf(" %d", matrix[i][j]);
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

    printf("Input Matrix:\n");
    printMatrix(size, (inputMatrix));
    printf("\n");

    int **a;
    a = multiply(size, inputMatrix, inputMatrix);
    printMatrix(size, a);



    for(int i = 0; i < size; i++) {
        free(a[i]);
    }
    free(a);

}

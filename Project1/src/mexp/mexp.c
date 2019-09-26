#include <stdio.h>


void printMatrix(int size,int matrix[size][size]){
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

    int inputMatrix[size][size];

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
    printMatrix(size, inputMatrix);

    

}



/*
int ** matrix;

matrix = malloc(sizeof(int)*num_rows);

for(int i =0;i<num_rows;++i){
  matrix[i]=malloc(sizeof(int)*num_cols);

}

int *matrix;
matrix = malloc(sizeof(int)*num_cols*num_rows);

matrix[i*num_cols+j]
*/

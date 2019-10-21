#include <stdlib.h>
#include <stdio.h>

double ** allocateMatrix(int rows, int columns){
  double ** matrix = (double **)malloc(sizeof(double*) *rows);
  for(int i = 0; i < rows; i++) {
          matrix[i] = (double *)malloc(sizeof(double) *columns);
      }
  return matrix;
}

double ** readMatrixFromFile(FILE * file,int rows,int columns){
  double ** matrix = allocateMatrix(rows, columns);
  for(int i =0; i <rows;i++){
    for(int j =0; j<columns; j++){
      double c;
      fscanf(file, "%lf", &c);
      matrix[i][j] = c;
    }
  }
  return matrix;
}

void printMatrix(double **matrix, int rows, int columns){
  for(int i =0;i<rows;i++){
    for(int j=0;j<columns;j++){
      if(j==columns-1){
        printf("%.1f", matrix[i][j]);
      }
      else{
      printf("%.1f ", matrix[i][j]);
    }
    }
    printf("\n");
  }
}

double ** transposeMatrix(double ** matrix, int rows, int columns){
  double ** transposedMatrix = allocateMatrix(columns, rows);
  for(int i =0; i <rows;i++){
    for(int j =0; j<columns; j++){
      transposedMatrix[j][i] = matrix[i][j];
    }
  }
  return transposedMatrix;
}

double *getRow(int size, int rowNum, double **matrix){
  double *row = malloc(sizeof(double*)*size);
  for(int i =0;i<size;i++){
    row[i] =matrix[rowNum][i];
  }
  return row;
}

double ** setRow(int size, int rowNum, double **matrix, double * newRow){
  for(int i =0;i<size;i++){
    matrix[rowNum][i] =newRow[i];
  }
  return matrix;
}

double *getCol(int size, int colNum, double **matrix){
  double *col = malloc(sizeof(double*)*size);
  //printf("COL: ");
  for(int i = 0;i < size;i++){
    col[i]= matrix[i][colNum];
    //printf("%.1f ", col[i]);
  }
  printf("\n");
  return col;
}

double **multiply(double **matrix1, int rows1,int columns1,
   double **matrix2, int rows2, int columns2){

  double **answer = allocateMatrix(columns1, rows2);

  for(int i =0;i<rows1;i++){
    printf("\n");
    for(int j =0;j<columns2;j++){
      double *col = getRow(columns1, i,matrix1);
      double *row = getCol(rows2, j, matrix2);

      double num=0;
      for(int k = 0;k<rows2;k++){
        num = num+(row[k]*col[k]);
      }
    //  printf("%.1f ",num);
      free(row);
      free(col);
      answer[i][j] = num;
    }

  }
return answer;
}

double * multiplyRowByScalar(int size, double * row, double scalar){
  for(int i =0;i<size;i++){
    row[i] = row[i]*scalar;
  }
  return row;
}

double * addRows(int size, double *row1, double*row2){
  for(int i = 0;i<size;i++){
    row1[i] = row1[i]+row2[i];
  }
  return row1;
}

double ** invert(double **matrix, int size){
  //make augmeted matrix
  double ** identity = allocateMatrix(size, size);
  for(int i =0;i<size;i++){
    for(int j =0;j<size;j++){
      if(i==j){
        //printf("1 ");
        identity[i][j] = 1.0;
      }
      else{
        identity[i][j] = 0.0;
      }
    }
  }


  for(int j =0;j<size;j++){
    for(int i=0;i<size;i++){


      double * currentRow = getRow(size, i,matrix);
      printMatrix(matrix,size,size);
      printf("Looking at: %lf\n", matrix[i][j]);
      //printf("%lf ", matrix[j][i]);
      if(i==j){
        //make element 1
        if(matrix[i][j]==0){
          //current row = some row below w [i][a]!=0 + current row
          int a = i+1;
          while(matrix[a][j]!=0){
            a++;
            if(a==size){
              printf("ERROR");
            }
          }
          double * otherRow = getRow(size, a, matrix);
          /*
          printf("ROW:   ");
          for(int i =0;i<size;i++){
            printf("%lf ", otherRow[i]);
          }
          */
          otherRow = multiplyRowByScalar(size, otherRow, 1/matrix[a][j]);
          otherRow = addRows(size,currentRow, otherRow);
          matrix = setRow(size, i, matrix, otherRow);
          //free(otherRow);
        }
        else{
          currentRow = multiplyRowByScalar(size, currentRow, 1/matrix[i][j]);
          matrix = setRow(size, i, matrix, currentRow);
        }
      }

      else{
        //make element 0
        if(matrix[i][j]!=0){
            //current row = current row - (pivot row * matrix[i][j])
            double * pivotRow = getRow(size, j,matrix);
            printf("ROW:   ");
            for(int i =0;i<size;i++){
              printf("%lf ", pivotRow[i]);
            }
            pivotRow = multiplyRowByScalar(size, pivotRow, -matrix[i][j]);
            printf("ROW:   ");
            for(int i =0;i<size;i++){
              printf("%lf ", pivotRow[i]);
            }
            currentRow = addRows(size,pivotRow, currentRow);
            matrix = setRow(size, i, matrix, currentRow);
            //free(pivotRow);
        }
      }
      printf("\n\n");
    }
  }
  return matrix;
}

void freeMatrix(double ** matrix, int rows, int columns){
  for(int i = 0; i < rows; i++) {
      free(matrix[i]);
  }
  free(matrix);
}

int main (int argc, char * argv[]){
  /*
  if(argc<3){
    printf("incorreectt arguments");
    return 0;
  }
*/

   FILE * trainFile;
   trainFile = fopen (argv[1], "r");

   int numAttributes;
   int numHouses;
   fscanf(trainFile, "%*s %d %d", &numAttributes, &numHouses);

   double ** X = readMatrixFromFile(trainFile, numHouses, numAttributes);
   //int ** Y = readMatrixFromFile(trainFile, 1,numHouses);
   printMatrix(X, numHouses, numAttributes);

   double ** Xtranspose = transposeMatrix(X, numHouses, numAttributes);
   printf("\n\n");
   printMatrix(Xtranspose, numAttributes, numHouses);

   double**  Xmult = multiply(X, numHouses, numAttributes,Xtranspose,numAttributes,numHouses);
  printf("\n\nYEEE:\n\n");
  printMatrix(Xmult, numHouses,numHouses);

  double ** test = invert(Xmult, numHouses);
 printf("\n INVERT:\n");

 printMatrix(test, numHouses,numHouses);


freeMatrix(test, numHouses,numHouses);
  //freeMatrix(Xmult, numHouses,numHouses);
   //double **Xmul = multiply(X,numHouses,numAttributes,X,numHouses,numAttributes);

   //printMatrix(Xmul, numAttributes, numAttributes);
   /*

   printf("\n\n");
   printMatrix(Xtranspose, numAttributes, numHouses);
   //printMatrix(Y, 1, numHouses);
   printf("numAttributes: %d\t numHouses: %d\n", numAttributes, numHouses);
   */
   fclose(trainFile);

   freeMatrix(X, numHouses, numAttributes);
   freeMatrix(Xtranspose,numAttributes,numHouses);

}

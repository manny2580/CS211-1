
int ** matrix;

matrix = malloc(sizeof(int)*num_rows);

for(int i =0;i<num_rows;++i){
  matrix[i]=malloc(sizeof(int)*num_cols);

}

int *matrix;
matrix = malloc(sizeof(int)*num_cols*num_rows);

matrix[i*num_cols+j]

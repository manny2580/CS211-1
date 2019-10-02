#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char * toCharArray(int number){
        int n = log10(number) + 1;
        int i;
      char *numberArray = calloc(n, sizeof(char));
        for ( i = 0; i < n; ++i, number /= 10 ){
            numberArray[i] = (number % 10)+'0';
        }
        return numberArray;
    }

int main (int argc, char *argv[]){

  if(argc!=2){
    printf("Enter a single arguments.\n");
    return 0;
  }

  int argSize = strlen(argv[1]);
  //printf("%d\t", argSize);
  char arg[argSize+1];
  strcpy(arg,argv[1]);
  //printf("%s\n", argv[1]);

  char compress[argSize+1];
  compress [argSize]='\0';

  int i =0;
  int j =0;
  int compressPos = 0;

  while(arg[i]!='\0'){
    //int count = 0;
    while((arg[j]!='\0')&&(arg[j]==arg[i])){

      if(arg[j] >= '0' && arg[j] <= '9'){
        printf("error\n");
        return 0;
      }
      j++;
    }

    int k =j-i;
    //char *num = (char*)&k;
    int numDigits = floor(log10(j-i))+1;

    //printf("%d\n",numDigits );

    if(compressPos+1+numDigits>argSize){
      printf("%s\n",argv[1]);
      return 0;
    }
    compress[compressPos]=arg[i];
    compressPos++;
    char * digitArray = toCharArray(k);
    for(int i =0;i<numDigits;i++){

      compress[compressPos]= digitArray[numDigits-i-1];
      compressPos++;
    }
    free(digitArray);

    //free(num);

    //compressPos=compressPos+numDigits;
/*
    printf("%s\t",compress);
    printf("%d\t",i);
    printf("%d\t",j);
    printf("%d\t", numDigits);
    printf("%d\n", compressPos);
*/
    i=j;
  }
  compress[compressPos]='\0';
  printf("%s\n",compress);
  //printf("%s\n", ;

}

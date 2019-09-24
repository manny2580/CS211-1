#include <stdio.h>
#include <string.h>

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

    if(compressPos+1>argSize){
      //printf("Original string is shorter\n");
      printf("%s\n",argv[1]);
      return 0;
    }

    compress[compressPos]=arg[i];
    int numLetters = j-i;
    compress[compressPos+1]=numLetters+'0';
    compressPos=compressPos+2;
    /*
    printf("%s\t",compress);
    printf("%d\t",i);
    printf("%d\n",j);
    */
    i=j;
  }
  compress[compressPos]='\0';
  printf("Compressed String:\t");
  printf("%s\n",compress);
  //printf("%s\n", ;

}

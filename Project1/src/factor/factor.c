#include <stdio.h>

int atoi(char *arg);
int main(int argc, char *argv[]){
//  printf("yeee");
  if(argc !=2){
    printf("Enter only a single arguements.\n");
        return 0;
  }

  int input =atoi(argv[1]);

  if(input<1){
    printf("Enter a positive interger.\n");
    return 0;
  }

  int count = 2;
  while(input!=1){
    if(input%count==0){

    while(input%count==0){
      input=input/count;

    }
      printf("%d\n", count);

    }
    else{
      count=count+1;
    }
  }

}

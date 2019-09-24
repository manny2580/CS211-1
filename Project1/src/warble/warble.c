#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool isLowerCase(char ch);
bool isLetter(char ch);
int nextLetterPos(int current, char *s);

int main (int argc, char *argv[]){

  int totalLength = 0;
  for ( int i=1; i<argc; i++){
    char *s = argv[i];
    for(int j =0; s[j]!='\0';j++){
      totalLength++;
    }
  }

if((totalLength+argc-1)<1){
  printf("\n");
  return 0;
}

  int currentPos = 0;
    char combinedArgs [totalLength+argc-1];
    for (int i=1; i<argc; i++){
      char *s = argv[i];
      for(int j =0; s[j]!='\0';j++){
        combinedArgs[currentPos]=s[j];
        currentPos++;

      }
        combinedArgs[currentPos]= ' ';
        currentPos++;

    }

    combinedArgs[totalLength+argc-2] = '\0';

       int prev =0;
       int current = 1;
       prev=nextLetterPos(prev, combinedArgs);
       current=nextLetterPos(prev+1,combinedArgs);


      while( combinedArgs[current] != '\0' ) {
        if(isLowerCase(combinedArgs[prev])){
          combinedArgs[current]=toupper(combinedArgs[current]);
        }
        prev=nextLetterPos(prev+1, combinedArgs);
        current=nextLetterPos(prev+1, combinedArgs);
      }

printf("%s\n", combinedArgs);
   }

int nextLetterPos(int current, char *s){

    while(!(isLetter(s[current]))&&( s[current] != '\0')) {
      current++;
    }
  return current;
}

//assumes ch is a letter
bool isLowerCase(char ch){

  if(ch >= 'A' && ch <= 'Z'){
    return false;
  }
  return true;
}

bool isLetter(char ch){
  if((ch >= 'A' && ch <= 'Z')||(ch >= 'a' && ch <= 'z')){
    return true;
}
return false;
}

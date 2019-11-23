#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <ctype.h>
#include <stdbool.h>

/******************************************Structure****************************************************/

typedef struct varLL{
char name[17];
int value;
struct varLL* next;
}varLL;


typedef struct gateLL{
char name[17];
struct varLL* inputs;
struct varLL* outputs;
struct gateLL* next;
}gateLL;

/******************************************Declare Methoad****************************************************/
varLL* create(varLL* temphead,char* name);
void travers(varLL* temphead);
int convert(int dec);
void printma(int** matrix,int row,int col, int input);
gateLL* createGate(gateLL* temphead,char* name,varLL * inputs, varLL * outputs);
void traversg(gateLL* temphead);
void traversnum(varLL* temphead);
int findint(char* name, varLL* head);
int findout(char* name,int n, varLL* head);
int notgate(int input);
int andgate(int input1,int input2);
int orgate(int input1,int input2);
int nandgate(int input1,int input2);
int norgate(int input1,int input2);
int xorgate(int input1,int input2);


int tokenType(char g[17]){

  if(strcmp(g,"PASS")==0){
    return 1;
  }
  if(strcmp(g,"NOT")==0){
    return 1;
  }
  if(strcmp(g,"AND")==0){
    return 1;
  }
  if(strcmp(g,"OR")==0){
    return 1;
  }
  if(strcmp(g,"NAND")==0){
    return 1;
  }
  if(strcmp(g,"NOR")==0){
    return 1;
  }
  if(strcmp(g,"XOR")==0){
    return 1;
  }
  if(strcmp(g,"DECODER")==0){
    return 1;
  }
  if(strcmp(g,"MULTIPLEXER")==0){
    return 1;
  }
  if(strcmp(g,":")==0){
    return 10;
  }
  return 0;
}

char * processVar(varLL * inputHead, varLL * outputHead, char * var){
  varLL * ptr = inputHead;

  bool found = false;
  while(ptr!=NULL){
    if(strcmp(ptr->name, var)==0){
      found = true;
      break;
    }
    ptr=ptr-> next;
  }



  ptr = outputHead;
  while(ptr!=NULL){
    if(strcmp(ptr->name, var)==0){
    found = true;
    }
    ptr=ptr-> next;
  }

  if(!found){
  for(int i = 0; var[i]; i++){
    var[i] = tolower(var[i]);
  }
}
  return var;
}


/******************************************Main function****************************************************/


int main(int argc, char** argv){

int i =0;
int j = 0;
int k =0;



char* name=malloc(17*sizeof(char));
char* x=malloc(17*sizeof(char));

varLL* inputHead=NULL;
varLL* outputHead=NULL;

/*read file*/
  FILE* fl;
  fl=fopen(argv[1],"r");
  if(fl==NULL){
    printf("wrong file name\n");
    return 0;
  }


/*read num of input and store in inputHead LL*/
  //fscanf(fl,"INPUTVAR %d",&input);
  //printf("input is %d\n",input);
  int input = 0;
  fscanf(fl, "%16s", name);
  while ((fscanf(fl, "%16s", name) == 1) && strcmp(name, "OUTPUT") != 0) {
        input++;
        inputHead=create(inputHead,name);
  }


  printf("INPUT VARS: ");
  varLL * ptr = inputHead;
  while(ptr!=NULL){
    printf("%s, ",ptr->name);
    ptr=ptr->next;
  }
  printf("\n");
//fscanf(fl,"\n");



int output = 0;
while ((fscanf(fl, " %16s", name) == 1) && tokenType(name)==0){
      output++;
      outputHead=create(outputHead,name);
}

printf("OUTPUT VARS: ");
ptr = outputHead;
while(ptr!=NULL){
  printf("%s, ",ptr->name);
  ptr=ptr->next;
}
printf("\n");

/*calculate num of row*/
int result=pow(2,input);


int** matrix=malloc(result*sizeof(int*));
for(i=0;i<result;i++){
  matrix[i]=(int*)malloc((input+output)*sizeof(int));
}

bool zero = true;
int interval = (result/2);
for(int i =0; i <input;i++){
    for(int j =0; j<result; j++){

      if(j%interval==0){
        zero = !zero;
      }
      if(zero){
        matrix[j][i] = 1;
      }
      else{
        matrix[j][i] = 0;
      }
    }
    interval/=2;
  }
//printma(matrix,result,(input+output));

/*read gate and store in gate LL*/
gateLL* gate=NULL;

x = name;

varLL *in = NULL;
varLL * out = NULL;
bool isIn = true;

//char * operation[17];

do{

int type = tokenType(x);


  switch(type){
    case 10:
    isIn = false;
    break;

    case 1:
    gate = createGate(gate,x,in,out);
    printf("GATE: %s\n",x);
    in = NULL;
    out = NULL;
    isIn = true;

    break;

    case 0:
    if(isIn==true){
      printf("input: %s \n", x);
      in= create(in,x);
      gate->inputs = in;
    }
    else{
      printf("output: %s \n", x);
      out=create(out,x);
      gate->outputs = out;

  }
  break;
  }


}while(fscanf(fl,"%16s",x)==1);


gateLL * ptr1 = gate;
while(ptr1!=NULL){
  printf("%s\n",ptr1->name );

  varLL * ptr2 = NULL;
  ptr2 =  ptr1->inputs;
  printf("INPUTS: ");

  while(ptr2!=NULL){
    printf("%s ",ptr2->name);
    ptr2 = ptr2->next;
  }
  ptr2 = ptr1-> outputs;
  printf("\nOUTPUTS: ");
  while(ptr2!=NULL){
    printf("%s, ",ptr2->name);
    ptr2 = ptr2->next;
  }
  printf("\n");

  ptr1 = ptr1->next;
}

//traversg(gate);
//char* tempname=malloc(20*sizeof(char));

for(i=0;i<result;i++){
	varLL* pt=inputHead;
	for(j=0;j<input;j++){
		pt->value=matrix[i][j];
		pt=pt->next;
	}
//traversnum(inputHead);
	//travers(inputHead);

gateLL* move=gate;
while(move!=NULL){

	move=move->next;

}
	//traversg(gate);
	//traversnum(inputHead);
	//traversnum(outputHead);
	//traversnum(temphead);

	pt=outputHead;
	for(k=input;k<(input+output);k++){
		matrix[i][k]=pt->value;
		pt=pt->next;
		}
}
	printma(matrix,result,(input+output),input);

return 0;
}


/******************************************add a new varLL after****************************************************/
varLL* create(varLL* temphead,char* name){
  if(temphead==NULL){
    temphead=malloc(sizeof(varLL));
    strcpy(temphead->name,name);
    temphead->next=NULL;
    return temphead;
  }
  varLL* pt=temphead;
  while(pt->next!=NULL){
    pt=pt->next;
  }
varLL* new=malloc(sizeof(varLL));
strcpy(new->name,name);
new->next=NULL;
pt->next=new;
return temphead;

}

/******************************************print out the name of varLL linked list****************************************************/
void travers(varLL* temphead){
  varLL* pt=temphead;
  while(pt!=NULL){
    printf("%s->",pt->name);
    pt=pt->next;
  }
  printf("\n");
  return;
}
/******************************************print out the number of varLL linked list****************************************************/
void traversnum(varLL* temphead){
  varLL* pt=temphead;
  while(pt!=NULL){
    printf("%d->",pt->value);
    pt=pt->next;
  }
    printf("\n");
  return;
}
/******************************************print out the whole matrix****************************************************/
void printma(int** matrix,int row,int col, int input){

int i,j;
for(i=0;i<row;i++){
  for(j=0;j<col;j++){
    if(j-input==0){
      printf("| %d", matrix[i][j]);
    }

    else{
      printf("%d",matrix[i][j]);
    }
    if(j!=col-1){
      printf(" ");
    }
  }
  printf("\n");
}

}

/******************************************Gate functions****************************************************/
int notgate(int input){
	//printf("notgate: %d",input);
  if(input==1){
    return 0;
  }
  if(input==0){
    return 1;
  }
  return 2;
}

int andgate(int input1,int input2){
	//printf("%d and %d\n",input1,input2);
  if(input1==1&&input2==1){
    return 1;
  }

  return 0;
}

int orgate(int input1,int input2){
  if(input1==1||input2==1){
    return 1;
  }

  return 0;
}

int nandgate(int input1,int input2){
  if(input1==0&&input2==0){
    return 1;
  }

  return 0;
}

int passgate(int input){
  return input;
}

int norgate(int input1,int input2){
  if(input1==1||input2==1){
    return 0;
  }

  return 1;
}

int xorgate(int input1,int input2){
	//printf("%d and %d\n",input1,input2);
  if(input1==1&&input2==0){
	 return 1;
	  }else if(input1==0&&input2==1){

    return 1;
		  }else{

  return 0;
}
}
/******************************************add a gate linkedlist after****************************************************/
gateLL* createGate(gateLL* temphead,char* name,varLL * inputs, varLL * outputs){
  if(temphead==NULL){
    temphead=malloc(sizeof(gateLL));
    strcpy(temphead->name,name);
    temphead->inputs = inputs;
    temphead-> outputs = outputs;
    temphead->next=NULL;
    return temphead;
  }
gateLL* pt=temphead;
  while(pt->next!=NULL){
    pt=pt->next;
  }
gateLL* new=malloc(sizeof(gateLL));
strcpy(new->name,name);
temphead->inputs = inputs;
temphead-> outputs = outputs;
new->next=NULL;
pt->next=new;
return temphead;

}
/******************************************print out gate linked list****************************************************/
void traversg(gateLL* temphead){
  gateLL* pt=temphead;
  while(pt!=NULL){
    printf("%s->",pt->name);
    pt=pt->next;
  }
    printf("\n");
  return;
}
/******************************************find the name in input linkedlist and return the value****************************************************/
int findint(char* name, varLL* head){

	varLL* pt=head;
	//printf("%c(%c)->\n",pt->name[strlen(pt->name)-2],name[strlen(name)-2]);
	//printf("%c(%c)->\n",pt->name[strlen(pt->name)-1],name[strlen(name)-1]);
	while(pt!=NULL){
		if(pt->name[strlen(pt->name)-1]==name[strlen(name)-1]){
			//printf("1here\n");
		if(pt->name[strlen(pt->name)-2]==name[strlen(name)-2]){
			//printf("2here\n");
			//printf("value: %d",pt->value);
			return pt->value;
			}
		}
		pt=pt->next;
		}
		return 2;
	};
/******************************************find the name in output linkedlist and return the bl(1:yes 2:not)****************************************************/
int findout(char* name,int n, varLL* head){
	varLL* pt=head;
	while(pt!=NULL){
		//printf("%c(%c)->",pt->name[strlen(pt->name)-2],name[strlen(pt->name)-2]);
		if(pt->name[strlen(pt->name)-1]==name[strlen(name)-1]){
		if(pt->name[strlen(pt->name)-2]==name[strlen(name)-2]){
			//printf("here");
			pt->value=n;
			return 1;
			}
		}
			pt=pt->next;
	}
		return 2;


	};

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

struct Directive{
  int gateType;

  char **inputVariables;
  int inputVariablesSize;

  char **outputVariables;
  int outputVariablesSize;

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

int tokenType(char g[17]){

  if(strcmp(g,"PASS")==0){
    return 1;
  }
  if(strcmp(g,"NOT")==0){
    return 2;
  }
  if(strcmp(g,"AND")==0){
    return 3;
  }
  if(strcmp(g,"OR")==0){
    return 4;
  }
  if(strcmp(g,"NAND")==0){
    return 5;
  }
  if(strcmp(g,"NOR")==0){
    return 6;
  }
  if(strcmp(g,"XOR")==0){
    return 7;
  }
  if(strcmp(g,"DECODER")==0){
    return 8;
  }
  if(strcmp(g,"MULTIPLEXER")==0){
    return 9;
  }

  if(strcmp(g,":")==10){
    return 9;
  }

  return 0;

}


int main (int argc, char *argv[]){

  int numInputs = 0;
  int numOutputs = 0;

  int inputVariablesSize = 100;
  char **inputVariables = malloc(inputVariablesSize*sizeof(char*));
  for(int i =0;i<inputVariablesSize;i++){
    inputVariables[i] = malloc(17*sizeof(char));
  }

  int outputVariablesSize = 100;
  char **outputVariables = malloc(outputVariablesSize*sizeof(char*));
  for(int i =0;i<outputVariablesSize;i++){
    outputVariables[i] = malloc(17*sizeof(char));
  }



int tempVariablesSize = 100;
char tempVariables[tempVariablesSize][17];


  //yee

  FILE * circuit;
  circuit = fopen (argv[1], "r");



  //input variables
  fscanf(circuit, "%16s", inputVariables[numInputs]);
  while ((fscanf(circuit, "%16s", inputVariables[numInputs]) == 1) && strcmp(inputVariables[numInputs], "OUTPUT") != 0) {
        numInputs++;
  }

  //output variables
  while ((fscanf(circuit, " %16s", outputVariables[numOutputs]) == 1) && tokenType(outputVariables[numOutputs])==0){
        numOutputs++;
  }

  printf("Input variables: ");
  for(int i =0;i<numInputs;i++){
    printf("%s, ", inputVariables[i]);
  }

  printf("\nOutput variables: ");
  for(int i =0;i<2;i++){
    printf("%s, ", outputVariables[i]);
  }
  char x[17];
  strcpy(outputVariables[numOutputs],x);
  printf("YEEE%s\n", outputVariables[numOutputs]);
  do{
    printf("%s\n",x);
    struct Directive newDirective;

    newDirective.gateType = tokenType(x);


    int iVS = 100;
    char **iV = malloc(iVS*sizeof(char*));
    for(int i =0;i<iVS;i++){
      iV[i] = malloc(17*sizeof(char));
    }
    int count = 0;

    while (fscanf(circuit, " %16s", iV[count]) == 1 &&tokenType( iV[count]) != 10){
      count++;
    }

    newDirective.inputVariables = iV;
    newDirective.inputVariablesSize = count;

    int oVS = 100;
    char **oV = malloc(iVS*sizeof(char*));
    for(int i =0;i<oVS;i++){
      oV[i] = malloc(17*sizeof(char));
    }
    count = 0;

    while (fscanf(circuit, " %16s", oV[count]) == 1 &&tokenType( oV[count]) != 10){
      count++;
    }
    newDirective.outputVariables = oV;
    newDirective.outputVariablesSize = count;
    printf("%d\n",newDirective.gateType);

  }while (fscanf(circuit, " %16s", x) == 1);



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
    printf("\n");
    printMatrix(table, numRows, numInputs);
    freeMatrix(table, numRows,numInputs);
}
*/

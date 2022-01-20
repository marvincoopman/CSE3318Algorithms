#include <stdio.h>
#include <string.h>
#include <stdlib.h>




/*
Marvin Coopman
1001781933
Lab 3
due 10/28/2021

Create a cost Matrix and order preserving huffman code using dynamic programming

How to run code:
gcc -o temp.out Alg3.c
./temp.out < <testfilename>
The NUMOFSYMBOLS needs to be changed based on the number of symbols being read
*/
#define NUMOFSYMBOLS 15







  struct node{
    int index;
    char bit[NUMOFSYMBOLS];
    struct node* left;
    struct node* right;
  };
  struct node* head = NULL;


  double sumOfPercents(int j, int k, double* symbolsPercentages){ //sum of percentages from j - k inclusively
    double sum = 0;
    for(j; j <= k; j++){
      sum += symbolsPercentages[j];
    }
    return sum;
  }

  struct node* tree(int left,int right,int indent, int trace[NUMOFSYMBOLS][NUMOFSYMBOLS], double costMatrix[NUMOFSYMBOLS][NUMOFSYMBOLS],char bits[] ,char bitValue[]){
  //prints and creates binary tree with the symbols making up its leaves
  struct node* temp = (struct node*)malloc(sizeof(struct node));
  temp->index = -1; //if the node is not a leaf

  char* temp1 = (char*)malloc(NUMOFSYMBOLS*sizeof(char));
  strcpy(temp1,bits);
  strcat(temp1,bitValue);
  strcpy(temp->bit,temp1);
  free(temp1);

  if (left==right) // At a leaf in the optimal tree
  {
    temp->index = left;
    temp->right = NULL;
    temp->left = NULL;
    printf("%*s%d\n",3*indent,"",left);  // Indent and print the index of the matrix
    return temp;
  }

  temp->right = tree(trace[left][right]+1,right,indent+1,trace,costMatrix,temp->bit,"1");   // Print the right subtree for c(left,right)
  printf("%*s%d %d cost %.9f\n",3*indent,"",left,right, costMatrix[left][right]); // Print the root
  temp->left = tree(left,trace[left][right],indent+1,trace,costMatrix,temp->bit,"0");      // Print the left subtree for c(left,right)
  return temp;
  }

  void printPreorderBits(double* expectedBits,double percentages[NUMOFSYMBOLS],struct node* root){
    if(root!=NULL){
      if(root->index != -1){
        printf("%d %s %.9f \n",root->index,root->bit, strlen(root->bit)*percentages[root->index]);
        *expectedBits += strlen(root->bit)*percentages[root->index];
      }

      printPreorderBits(expectedBits,percentages,root->left);
      printPreorderBits(expectedBits,percentages,root->right);

    }
  }

int main(){
  int dummy;
  scanf("%d",&dummy);
  printf("%d\n", NUMOFSYMBOLS);


  double* symbolsPercentages = (double*)malloc(NUMOFSYMBOLS*sizeof(double));
  int p;
  for(p = 0; p < NUMOFSYMBOLS; p++){
    scanf("%lf",&symbolsPercentages[p]);
    printf("%.9f\n", symbolsPercentages[p]);
  }



  double costMatrix[NUMOFSYMBOLS][NUMOFSYMBOLS];
  int trace[NUMOFSYMBOLS][NUMOFSYMBOLS];

  //generate base case
  int q;
  for(q = 0; q < NUMOFSYMBOLS; q++);
  {
    costMatrix[q][q] = 0;
    trace[q][q] = 0;
  }
  double work = 0;


  printf("%.9f", symbolsPercentages[NUMOFSYMBOLS]);
  int i, j, k = 0;
  for(i = 1; i< NUMOFSYMBOLS; i++){
    for(j = 0; j <= NUMOFSYMBOLS-i-1;j++){
      costMatrix[j][j+i] = 9999999; //infintiy

      printf("Compute c[%d][%d]\n",j,j+i);
      for(k = j; k <j+i; k++){
        work = costMatrix[j][k]+costMatrix[k+1][j+i]+ sumOfPercents(j,j+i,symbolsPercentages);
        printf(" k=%d gives cost %.9f=c[%d][%d]+c[%d][%d]+sum(%d,%d) = %.9f+%.9f+%.9f\n",k,work,j,k,k+1,j+i,j,j+i,costMatrix[j][k],costMatrix[k+1][j+i], sumOfPercents(j,j+i,symbolsPercentages));
        if(costMatrix[j][j+i]>work){
          costMatrix[j][j+i] = work;
          trace[j][j+i] = k;
        }
      }
      printf("  c[%d][%d]==%.9f,trace[%d][%d]==%d\n",j,j+i,costMatrix[j][j+i],j,j+i,trace[j][j+i]);
    }
  }
  int ell;
  for(ell = 0; ell < NUMOFSYMBOLS; ell++){
    printf("\t%d\t",ell);
  }
  printf(" \n");

  int i1,i2;

  for(i1 = 0; i1 < NUMOFSYMBOLS; i1++){
    printf("%d ",i1);
    for(i2 = 0; i2 < NUMOFSYMBOLS; i2++){
      if(i1 == i2){
        trace[i1][i1] = 0;
      }
      if(i1>i2){
        printf("\t------\t");
      }else{
        printf(" %.9f %d\t", costMatrix[i1][i2], trace[i1][i2]);
      }
    }

    printf("\n\n");
  }


  char bits[NUMOFSYMBOLS] = ""; //empty string
  head = tree(0,NUMOFSYMBOLS-1,0,trace,costMatrix,bits,"");


  //prob*# of bits
  double* expectedBits = (double*)malloc(sizeof(double)); //expected bits value
  *expectedBits = 0;
  printPreorderBits(expectedBits,symbolsPercentages,head); //prints symbols in preorder and calculates expectedbits
  printf("Expected bits per symbol %.9f", *expectedBits);
  return EXIT_SUCCESS;
}

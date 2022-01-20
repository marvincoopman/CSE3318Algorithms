#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(){
  int sizeA;
  int sizeB;
  int numOfTargets;
  scanf("%d %d %d", &sizeA, &sizeB, &numOfTargets);



  int* a = (int *)malloc((sizeA+2) * sizeof(int));
  int* b = (int *)malloc((sizeB+2) * sizeof(int));
  int* targets = (int *)malloc(numOfTargets * sizeof(int));


  for(int i = 1; i < sizeA+1; i++){
    scanf("%d", &a[i]);
  }
  a[0] = -899999;//endpoints
  a[sizeA+1] = 899999;//endpoints

  for(int i = 1; i < sizeB+1; i++){
    scanf("%d", &b[i]);
  }
  b[0] = -99999;//endpoints
  b[sizeB+1] = 99999;//endpoints

  for(int i = 0; i < numOfTargets; i++){
    scanf("%d", &targets[i]);
  }




  int left,right;
  int i, j;
  int largestSize;
  if(sizeA < sizeB){ //finds the largest sized list
    largestSize = sizeB;
  }else{
    largestSize = sizeB;
  }



  int target;
  for(int ell = 0; ell < numOfTargets; ell++){

    target = targets[ell];

    if(target > largestSize){ //shortcut for binary search ranges
      left = target - largestSize;
    }else{
      left = 0;
    }
    if(target > sizeA){ //shortcut for binary search ranges
      right = sizeA;
    }else{
      right = target;
    }

    while(left <= right){
      i = (left + right)/2;
      if(i > sizeA+1){
        i = sizeA;
      }

      printf("left %d, right %d ", left, right);
      j = target - i;
      if(a[i] <= b[j]){
        printf("i %d j %d a[%d] = %d b[%d] = %d ",i, j, i,a[i], j, b[j]);
        printf("a[%d]=%d\n", i+1,a[i+1]);
      }else{
        printf("i %d j %d b[%d] = %d a[%d] = %d ",i, j, j,b[j], i, a[i]);
        printf("b[%d]=%d\n", j+1,b[j+1]);
      }

        if(i + j == target && a[i] > b[j] && a[i] <= b[j+1]){ //if a
          printf("a[%d]=%d has rank %d\n", i, a[i], target);
          break;
        }else if(i + j == target && a[i] <= b[j] && b[j] < a[i+1]){ //if b
          printf("b[%d]=%d has rank %d\n", j, b[j], target);
          break;
        }else if(a[i + 1] <= b[j]){ //if a too small
          left = i+1;
        }else{ //if a too big
          right = i-1;
        }

      }


  }

}

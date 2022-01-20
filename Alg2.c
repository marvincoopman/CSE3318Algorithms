#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct laundry { //contains key for index and times for washing and drying
  int washTime;
  int dryTime;
  int key;
  bool isWashTimeBetter; //true if washTime <= dryTime ; false if washTime > dryTime
  int bestTime;
};
int laundryChecker (const void* a, const void* b){  //-1 pushes x to the left 1 pushes x to the right; y goes opposite
  struct laundry x = *(const struct laundry*)a;
  struct laundry y = *(const struct laundry*)b;

  int temp = x.bestTime - y.bestTime;

  if(temp >= 0){ //x takes more time
    if(y.isWashTimeBetter){ //check the "better time is dry or wash"
      return 1; //if y best time is wash then push y to the left and x to the right
    }else{
      return -1; //if y best time is dry then push y to the right and x to the left
    }
  }else{ //y takes more time
    if(x.isWashTimeBetter){ //check if best time is wash or dry
      return -1; //if x best time is wash then push x to the left and y to the right
    }else{
      return 1; //if x best time is dry then push x to the right and y to the left
    }
  }
}

int main(){
  int indices; //# of items
  scanf("%d", &indices);

  struct laundry* list;
  list = (struct laundry*)malloc(indices * sizeof(struct laundry));




  int ell = 0;
  for(ell = 0; ell < indices; ell++){
    scanf("%d %d", &list[ell].washTime, &list[ell].dryTime);
    list[ell].key = ell; //original index
    if(list[ell].washTime <= list[ell].dryTime){ //determines if washTime or dryTime is lower
      list[ell].isWashTimeBetter = true;
      list[ell].bestTime = list[ell].washTime;
    }else{
      list[ell].isWashTimeBetter = false;
      list[ell].bestTime = list[ell].dryTime;
    }
  }

  qsort(list, indices, sizeof(struct laundry), laundryChecker);



  //process
  int i;
  int washerUsage = 0;
  int dryerUsage = list[0].washTime;
  int makeSpan = 0;
  for(i = 0; i < indices; i++){
    if(dryerUsage < washerUsage + list[i].washTime){ //if the dryer is open, but no clothes are available to dry
      printf("dryer gap from %d to %d\n",dryerUsage, washerUsage + list[i].washTime);
      dryerUsage += washerUsage + list[i].washTime - dryerUsage; //dryer runs when next wash finishes
    }

    printf("%d %d %d %d %d\n", list[i].key, list[i].washTime, list[i].dryTime, washerUsage, dryerUsage);
    washerUsage += list[i].washTime;
    dryerUsage += list[i].dryTime;
  }
  makeSpan = dryerUsage; //the dryer will always be the final event thus being the makespan
  printf("makespan is : %d", makeSpan);

  return EXIT_SUCCESS;

}

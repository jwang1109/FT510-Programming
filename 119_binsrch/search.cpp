#include<cstdlib>
#include<cstdio>
#include"function.h"

int binarySearchForZero(Function<int,int> * f, int low, int high){
  while(low+1 < high){
    int curr = (low+high)/2;
    double y = f->invoke(curr);
    if(y < 0){
      low = curr;
    }
    else if(y == 0){
      return curr;
    }
    else{
      high = curr;
    }
  }
  return low;
}

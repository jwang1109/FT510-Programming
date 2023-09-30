#include<stdlib.h>
#include<stdio.h>

size_t maxSeq(int * array, size_t n){
  if (n == 0){
    return 0;
  }
  int ans = 1;
  int count = 1;
  for (int i  = 1; i < n; i ++){
    if(array[i] > array[i-1]){
      count ++;
    }
    else{
      count = 1;
    }
    if(count > ans){
      ans = count;
    }
  }
  return ans;
}


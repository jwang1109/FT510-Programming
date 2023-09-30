#include<stdlib.h>
#include<stdio.h>

size_t maxSeq(int * array, size_t n);

int main(void){
  int a0[1] =  {};
  if(maxSeq(a0,0) != 0){return EXIT_FAILURE;}
  

  int a1[1] = {1};
  if(maxSeq(a1,1) != 1){return EXIT_FAILURE;}
  
  int a2[6] = {1,2,4,-5};
  if(maxSeq(a2,4) != 3){return EXIT_FAILURE;}
  
  int a3[4] = {1,2,5,-23};
  if(maxSeq(a3,4) !=3){return EXIT_FAILURE;}
  
  int a4[5] = {0};
  if(maxSeq(a4,1)!=1){return EXIT_FAILURE;}

  int a5[5] = {1,1,1,2,-23};
  if(maxSeq(a5,5)!=2){return EXIT_FAILURE;}
  return EXIT_SUCCESS;
}

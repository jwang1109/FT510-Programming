#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int array_max(int * array,int n){
  int max_index = 0;
  for(int i = 0; i < n; i++){
    if(array[i] > array[max_index]){
      max_index = i;
    }
  }
  return max_index;
}

int breaker(FILE * f){
  int coded_e = 0;
  int key = 0;
  
  int c = 0;
  int counts[26] = {0};
  while((c = fgetc(f))!=EOF){
    if(isalpha(c)){
      c = tolower(c);
      c -= 'a';
      counts[c] += 1;
    }    
  }
  coded_e = array_max(counts,26);
  key = (coded_e - 4 + 26) % 26;
  /*after got the key, compute */

  return key;
}

int main(int argc, char ** argv){
  if(argc!=2){
    fprintf(stderr,"Usage:break inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1],"r");
  if (f==NULL){
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int key = breaker(f);
  if(fclose(f)!=0){
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  fprintf(stdout,"%d\n",key);
  return EXIT_SUCCESS;
}

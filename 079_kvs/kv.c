#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


kvpair_t * readKV(FILE *f){
  char * line = NULL;
  size_t sz = 0;
  if(getline(&line,&sz,f)<=0){
    free(line);
    return NULL;
  }
  //segment and asign a string. This technique worth memorizing
  char * sign = strchr(line,'=');
  if(sign ==NULL){
    fprintf(stderr,"Cant' find sign");
    return NULL;
  }
  kvpair_t * pair = malloc(sizeof(*pair));
  *sign = 0;
  pair->key = line;
  sign ++;
  char * end = strchr(sign,'\n');
  *end = 0;
  pair->value = sign;
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  //1.open file
  FILE * f = fopen(fname,"r");
  if (f ==NULL){
    perror("Fail to open file");
    return NULL;
  }
  //2.intialize the answer
  kvpair_t * pair =NULL;
  kvarray_t * answer = malloc(sizeof(*answer));
  answer->pairs = NULL;
  answer->len = 0;
  //3.read KV and assign it to answer
  while((pair = readKV(f))!=NULL){
    answer->len++;
    answer->pairs = realloc(answer->pairs,answer->len*sizeof(*answer->pairs));
    answer->pairs[answer->len-1]=pair;
  }
  //4.close the file
  fclose(f);
  return answer;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i = 0; i < pairs->len; i++){
    free(pairs->pairs[i]->key);
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  int n = pairs->len;
  for(int i = 0; i< n; i++){
    printf("key = '%s' value = '%s'\n",pairs->pairs[i]->key,pairs->pairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  int n = pairs->len;
    for(int i =0; i<n; i++){
      if(strcmp(pairs->pairs[i]->key,key) ==0){
	return pairs->pairs[i]->value;
      }
    }
    return NULL;
}

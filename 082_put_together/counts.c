#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * ans = malloc(sizeof(*ans));
  ans->strings = NULL;
  ans->len = 0;
  return ans;
}

int checkName(counts_t * c,const char * name){
  // if c already has the string, return 1,else return 0
  int flag = 0;
  for(int i = 0; i < c->len; i++){
    if(name == NULL){
      if(c->strings[i]->string == NULL){
	flag++;
      }
    }
    else if(c->strings[i]->string ==NULL){
      continue;
    }
    else if(strcmp(c->strings[i]->string,name) == 0){
	flag ++;
      }
    }
  return flag;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (checkName(c,name) == 0){
    c->len ++;
    c->strings = realloc(c->strings,(c->len)*sizeof(*c->strings));
    one_count_t * one_count = malloc(sizeof(*one_count));
    if (name == NULL){
      one_count->string = NULL;
    }
    else {
      one_count->string = strdup(name);
    }
    one_count->count = 1;
    c->strings[c->len-1] = one_count;
    return;
  }
  else{
    for(int i = 0; i < c->len; i++){
      if (name == NULL){
	if ((c->strings[i]->string)==NULL){
	  c->strings[i]->count ++;
      }
      }
      else if (c->strings[i]->string ==NULL){
	continue;
      }
      else if (strcmp(c->strings[i]->string,name) == 0){
	c->strings[i]->count ++;
      }
    }
  }
  return;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  int unknown_flag = 0;
  for(int i = 0; i < c->len; i++){
    if(c->strings[i]->string != NULL){
      fprintf(outFile,"%s: %d\n",c->strings[i]->string, c->strings[i]->count);
    }
    else{
      unknown_flag = i;
    }
  }
  if(unknown_flag != 0){
    fprintf(outFile,"<unknown> : %d\n",c->strings[unknown_flag]->count);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(int i = 0; i < c->len; i++){
    free(c->strings[i]->string);
    free(c->strings[i]);
  }
  free(c->strings);
  free(c);
}

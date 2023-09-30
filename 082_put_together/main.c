#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * ans = createCounts();
  FILE * f = fopen(filename,"r");
  if(f==NULL){
    perror("Failure to open file that need to be counted");
    return NULL;
  }
  //WRITE ME
  char * line = NULL;
  size_t sz =0;
  while(getline(&line,&sz,f)>=0){
    char * p = strchr(line,'\n');
    if(p != NULL){
      *p = 0;
    }
    addCount(ans,lookupValue(kvPairs,line));
  }
  free(line);
  fclose(f);
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3){
    fprintf(stderr,"Usage:./counts kv.txt list1a.txt [list1b.txt]");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kvs = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for(int i = 2; i < argc; i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    counts_t * c = countFile(argv[i],kvs);
    //   (call this result c)
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName,"w");
    //print the counts from c into the FILE f
    if( f == NULL){
      perror("Failure to open destination file");
      return EXIT_FAILURE;
    }
    printCounts(c,f);
    //close f
    fclose(f);
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }
  freeKVs(kvs);
 //free the memory for kv
  return EXIT_SUCCESS;
}

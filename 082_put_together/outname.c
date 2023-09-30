#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  //name + .counts 
  char * ans = malloc((strlen(inputName)+8)*sizeof(*ans));
  strcpy(ans, inputName);
  strcat(ans,".counts");
  return ans;
}

#include<stdio.h>
#include<stdlib.h>
void series18(int n ){
  for (int i = 0; i < 3 *n; i ++){
    printf("%d ", - n * n + i * i);
  }
  printf("\n");
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("N not specified\n");
        printf("usage: series18 N\n");
        return 1;
    }
    int n = atoi(argv[1]);
    series18(n);
    return 0;
}

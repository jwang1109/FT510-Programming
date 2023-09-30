#include<stdlib.h>
#include<stdio.h>

void rotate(char mat[10][10]){
  char temp_mat[10][10];
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      temp_mat[j][9-i] = mat[i][j];
    } 
  }
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      mat[i][j] = temp_mat[i][j];
    } 
  }  
}

void printMatrix(char mat[10][10]){
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      printf("%c",mat[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv){
  if (argc !=2 ){
    perror("Usage: rotateMatrix arg");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1],"r");
  if (f == NULL){
    perror("File doesn't exist");
    return EXIT_FAILURE;
  }
  char matrix[10][10];
  char line[12];
  int i = 0;//i = ith row
  while(fgets(line,12,f) != NULL){
    if (line[10] == '\n'){
      for(int j = 0; j < 10; j++){
	matrix[i][j] = line[j];
      }
    }
    else{
      fprintf(stderr,"The line is not ten-character-long");
      return EXIT_FAILURE;
    }
    i++;
  }
  if(i!=10){
    fprintf(stderr,"The matrix doesn't contain exactly 10 rows.");
    return EXIT_FAILURE;
  }
  rotate(matrix);
  printMatrix(matrix);
  if(fclose(f)!=0){
    perror("Failed to close the file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

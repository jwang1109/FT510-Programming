#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<iomanip>
#include"Assets.hpp"
#include<string>

int main(int argc, char ** argv){
  
  //0.command error check.
  if(argc != 2){
    std::cerr << "Usage:input.txt" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  //1.open file.
  std::ifstream f;
  f.open(argv[1]);
  if(!f.is_open()){
    std::cerr << "Failure to open the file" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  //2.read file, calculate and store.
  Portfolio assets(1);
  assets = assets.readFile(f);
  
  //3.calculate correlation matrix.
  std::vector<std::vector<double> > ans;
  ans = assets.corrMat();

  //4.print result
  std::cout << "[";
  for(size_t i = 0; i < ans.size(); i++){
    for(size_t j = 0; j < ans.size();j++){
      std::cout << std::setw(7) << std::fixed << std::setprecision(4) << ans[i][j];
      if(j != ans.size()-1){
	std::cout << ",";
      }
    }
    if(i !=ans.size()-1){
      std::cout << std::endl;
      std::cout << " ";
    }
  }
  std::cout <<"]" << std::endl;
  
  return EXIT_SUCCESS;
}

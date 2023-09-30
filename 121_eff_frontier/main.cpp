#include"Assets.hpp"
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<unistd.h>
#include<set>

int main(int argc, char ** argv){
  //-----0.parsing command line-----
  //command line error check
  if((argc != 3) && (argc!=4)){
    std::cerr << "Usage: -r(optional) universe.csv correlation.csv" << std::endl;
    return EXIT_FAILURE;
  }
  if((argc == 4) && (strcmp(argv[1],"-r"))){
    std::cerr << "Usage: -r(optional) universe.csv correlation.csv" << std::endl;
    return EXIT_FAILURE;
  }
  if((argc == 3) && ((!strcmp(argv[1],"-r") || (!strcmp(argv[2],"-r"))))){
    std::cerr << "Usage: -r(optional) universe.csv correlation.csv" << std::endl;
      return EXIT_FAILURE;
    }
  //parse option "-r"
  char opt;
  bool opt_flag = false;
  while((opt = getopt(argc,argv,"r")) != -1){
    switch(opt){
    case 'r':
      opt_flag = true;
      break;
    default:
      std::cerr << "Usage: -r(optional) universe.csv correlation.csv" << std::endl;
      return EXIT_FAILURE;
    }
   }

  //-----1.open file-----
  int uf_idx = 1;
  int cf_idx = 2;
  if (opt_flag){
    uf_idx += 1;
    cf_idx += 1;
  }
  std::ifstream uf;
  uf.open(argv[uf_idx]);
  if(!uf.is_open()){
    std::cerr << "Failure to open universe file" << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream cf;
  cf.open(argv[cf_idx]);
  if(!cf.is_open()){
    std::cerr << "Failure to open correlation file" << std::endl;
    return EXIT_FAILURE;
  }
  //-----2.read file-----
  Portfolio port;
  port = port.readAll(uf,cf);
  //-----3.optimize ------
  std::cout << "RoR,volatility" << std::endl;
  for(double r = 0.01; r < 0.261; r += 0.01){
    std::cout << std::fixed << std::setprecision(1) << r*100 <<"%," <<  std::setprecision(2) << port.optimize(r,opt_flag)*100 << "%" <<std::endl;
  }
}

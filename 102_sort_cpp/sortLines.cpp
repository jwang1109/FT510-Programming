#include<cstdlib>
#include<cstdio>
#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>

class sorting{
private:
  std::vector<std::string> lines;
public:
  void readfile(std::ifstream & f);
  void readstdin(std::istream & f);
  void display();
};

void sorting::readstdin(std::istream & f){
  std::string line;
  while(std::getline(f,line)){
    lines.push_back(line);
  }
}

void sorting::readfile(std::ifstream & f){
  std::string line;
  while(std::getline(f,line)){
    lines.push_back(line);
  }
}

void sorting::display(){
  std::sort(lines.begin(),lines.end());
  for(size_t i = 0;i < lines.size();i++){
    std::cout << lines[i] << std::endl;
  }
}



int main(int argc, char ** argv){
  if(argc == 1){
    sorting sort;
    sort.readstdin(std::cin);
    sort.display();
  }
  else if(argc > 1){
    for(int i = 1; i < argc; i++){
      sorting sort;
      std::ifstream f;
      f.open(argv[i]);
      if(!f.is_open()){
	std::cerr << "Failure to open file";
	return EXIT_FAILURE;
      }
      sort.readfile(f);
      sort.display();
    }
  }
  else{
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

#include"Assets.hpp"
#include<cassert>
#include<string>
#include<iostream>
#include<limits>

std::vector<std::string> split(std::string s){
  /*Split a string by ",". Used in readFile(); 
    This function is inspired by the way in Docables which are released by Dr. Slankas.*/
  std::vector<std::string> ans;
  std::string delim = ",";
  size_t start = 0;
  size_t end = 0;
  while(end != std::string::npos){
    end = s.find(delim,start);
    ans.push_back(s.substr(start,end-start));
    start = end + delim.size();
  }
  return ans;
}

Portfolio::Portfolio(size_t n):numAssets(n){
  /*Constructor. New a number of n assets attribute.*/
  assets = new Asset [numAssets];
}

Portfolio::~Portfolio(){
  /*Destructor. Clean assets attribute.*/
  delete[] assets;
}


void Portfolio::calculate(){
  
  /*Calculate average RoR and standard deviation.
    Used in readFile(). */
  
  for(size_t i = 0; i < numAssets; i++){
    assets[i].priceExist();
    assets[i].calAvgror();
    assets[i].calSd();
  }
}

double Portfolio::cov(const Asset & a, const Asset & b) const{
  
  /* Calcualte the value of covariance.
   Row number mismatch would reuslt in an exit.
   Used in correlation matrix.*/
  
  if(a.getRor().size() != b.getRor().size()){
    std::cerr << "The rows of RoR mismatch:" << a.getName() << " and " <<b.getName() << std::endl;
    exit(EXIT_FAILURE);
  }
  double ans = 0;
  size_t n = a.getRor().size();
  for(size_t i = 0; i < n; i++){
    ans+=((a.getRor()[i]-a.getAvgror())*(b.getRor()[i]-b.getAvgror()));
  }
  ans /= n;
  return ans;
}

std::vector<std::vector<double> > Portfolio::corrMat() const {
  
  /*Calculate the correation matrix.*/
  
  std::vector<std::vector<double> > ans;
  for(size_t i = 0; i < numAssets; i++){
    std::vector<double> temp_cov_vect;
    for(size_t j = 0; j < numAssets; j++){
      if(assets[i] == assets[j]){
	double value_same = 1;
	temp_cov_vect.push_back(value_same);// explicitly push back 1, otherwise may have number very close to 1
      }
      else{
	double temp_cov = 0;
	temp_cov = cov(assets[i],assets[j])/(assets[i].getSd()*assets[j].getSd());
	temp_cov_vect.push_back(temp_cov);
      }
    }
    ans.push_back(temp_cov_vect);
  }
  return ans;
}

Portfolio Portfolio::readFile(std::ifstream & f){
  
  /*Read file and calculate average RoR and SD at the same time*/
  
  //1. Read the first line to get info from the header.
  std::string header_line;
  std::vector<std::string> header;
  std::getline(f,header_line);
  header = split(header_line);
  
  size_t n_asset = header.size()-1;
  Portfolio assets(n_asset);
  for(size_t i = 0; i < assets.getNum(); i++){
    assets[i].addName(header[i+1]);
    std::cout << header[i+1]<< std::endl;
  }
  
  //2. Read historical price.
  std::string line;
  std::vector<std::string> line_info;
  double * valid_value_array = new double[n_asset];//if a number is blank or null, previous valid value should be used.
  size_t l_count = 0;//if the first line is null, obviously no previous valid value;
  while(getline(f,line)){
    for(size_t i = 0; i < assets.getNum();i++){
      line_info = split(line);
      if((line_info.size()-1)!=assets.getNum()){
	std::cerr << "Blank price data for assets."<<std::endl;
	exit(EXIT_FAILURE);
      }
      if((line_info[i+1] == "null") && (l_count == 0)){
	std::cerr << "No previous valid value is found." << std::endl;
	exit(EXIT_FAILURE);
      }
      
      if(line_info[i+1] == "null"){
	assets[i].addPrice(valid_value_array[i]);
      }
      else{
	assets[i].addPrice(std::stod(line_info[i+1]));
	valid_value_array[i] = std::stod(line_info[i+1]);
      }
    }
    l_count ++;
  }
  delete [] valid_value_array;
  
  assets.calculate();//calculate avgror and sd
  
  return assets;
}

Portfolio & Portfolio::operator=(const Portfolio & rhs){
  
  /* Deep copying assignment*/
  
  if(this != &rhs){
    delete[] assets;
    numAssets = rhs.numAssets;
    assets = new Asset [rhs.numAssets];
    for(size_t i =0; i < rhs.numAssets; i++){
      assets[i] = rhs.assets[i];
    }
  }
  return *this;
}

Asset & Portfolio::operator[](size_t index){
  /*Portfolio indexing, return an asset object.*/
  assert(0<= index && index < numAssets);
  return assets[index];  
}

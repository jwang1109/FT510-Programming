#include"Assets.hpp"
#include<cmath>
#include<iostream>
#include<limits>

void Asset::calAvgror(){
  /*Calculate average RoR. Used in calculate() method in readFile()*/
  double total = 0;
  double former = price[0];
  std::vector<double>::iterator iter = price.begin() + 1;
  while (iter != price.end()){
    ror.push_back((*iter-former)/former);
    total += (*iter-former)/former;
    former = *iter;
    ++ iter;
  }
  avgror = total/ror.size();
}

void Asset::calSd(){
  /* Calclate the standard deviation. Used in calculate() method in readFile() */
  double numerator = 0;
  std::vector<double>::iterator iter = ror.begin();
  while(iter != ror.end()){
    numerator += std::pow(*iter-avgror,2);
    ++ iter;
  }
  sd = std::sqrt((numerator/(ror.size()-1)));
}

bool Asset::priceExist() const{
  /*Check if price exists. Typically deal with the
   case when data lack a column of price.Used in 
   calculate() method in readFile.*/
  if(price.size()==0){
    return false;
  }
    return true;
}

bool Asset::operator==(const Asset & rhs) const{
  if(name != rhs.name){
    return false;
  }
  if(price != rhs.price){
    return false;
  }
  if(ror != rhs.ror){
    return false;
  }
  if(avgror != rhs.avgror){
    return false;
  }
  if(sd != rhs.sd){
    return false;
  }
  return true;
}

Asset & Asset::operator=(const Asset & rhs){
  if(this != &rhs){
    name = rhs.name;
    avgror = rhs.avgror;
    sd = rhs.sd;
    price = rhs.price;
    ror = rhs.ror;
  }
  return *this;
}

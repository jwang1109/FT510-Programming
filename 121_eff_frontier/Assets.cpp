#include"Assets.hpp"
#include<fstream>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<iomanip>
#include<set>

bool math_check_passed(Eigen::MatrixXd A){
  //Check whether correlation mat satisfy math definition.
  for(long i = 0; i < A.rows(); i++){
    for(long j = 0; j < A.cols(); j++){
      if(std::abs(A(i,j))>1){//-1 <= correlation <= 1
	return false;
      }
      if(A(i,j) != A(j,i)){//symmetry
	return false;
      }
      if((i==j) && A(i,j)!=1){//1 on diagnal
	return false;
      }
    }
  }
  return true;
}



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


Portfolio Portfolio::readAll(std::ifstream & uf,std::ifstream & cf){
  /*Read all files and do proper error checking.
    uf is for universe.csv
    cf is for correlation.csv*/
  Portfolio port;
  port.n_assets = 0;
  //1.read universe.csv
  std::string line;
  std::vector<std::string> line_info;
  while(std::getline(uf,line)){
    Asset temp;
    line_info = split(line);
    if(line_info.size() != 3){//testcase
      std::cerr << "Universe file error: Formatting error(should be: name,ror,sd)||Wrong number of columns" << std::endl;
      exit(EXIT_FAILURE);
    }
    temp.setName(line_info[0]);
    try{
    temp.setRor(std::stod(line_info[1]));
    temp.setSd(std::stod(line_info[2]));
    }
    catch(std::exception & e){//testcase
      std::cerr << "Universe data can't be converted to double" << std::endl;
      exit(EXIT_FAILURE);
    }
    port.assets.push_back(temp);
    port.n_assets++;
    }
  if(port.n_assets == 0){//testcase
    std::cerr << "Empty universe file: no asset found." << std::endl;
    exit(EXIT_FAILURE);
  }
  //2.read correlation.csv
  size_t row = 0;
  port.corrMat.resize(port.n_assets,port.n_assets);
  while(std::getline(cf,line)){
    size_t col = 0;
    line_info = split(line);
    if(line_info.size() != port.n_assets){//testcase
      std::cerr << "Correlation file error:Formatting error||Wrong number of columns" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::vector<std::string>::iterator iter = line_info.begin();
    while (iter != line_info.end()){
      try{
	port.corrMat(row,col) = std::stod(*iter);
      }
      catch(std::exception & e){//test case
	std::cerr << "Correlation data can't be converted to double" << std::endl;
	exit(EXIT_FAILURE);
      }
      col++;
      ++iter;
    }
    row++;
    }
  if(row != port.n_assets){//testcase
    std::cerr << "Correlation file error: Empty file||Wrong number of rows" << std::endl;
    exit(EXIT_FAILURE);
  }
  if(!(math_check_passed(port.corrMat))){
    std::cerr << "Correlation math error: Symmetry||1 on Diagnal||-1 <=corrleation <= 1";
    exit(EXIT_FAILURE);
  }
  return port;
}

Eigen::MatrixXd Portfolio::getCovMat(){
  /* Compute the covraiance matrix for optimization
     Used in optimize method.*/
  Eigen::MatrixXd covMat(n_assets,n_assets);
  for(size_t i = 0; i < n_assets; i++){
    for(size_t j = 0; j < n_assets; j++){
      covMat(i,j) = corrMat(i,j) * assets[i].getSd() * assets[j].getSd();
    }
  }
  return covMat;
}

double Portfolio::optimize(double overall_ror,bool opt_flag){
  /* Optimize. Given a certain level of portfolio ror, finding the best weights of assets to minimize the volatility under unrestricted and restricted cases.
     The problem can be converted to a Lagrange function.
     The key point is to solve an equation to find X.
     The X can make the gradients of Langrange function to 0.
     So, I initialize the left side and right side of the equation and solve.*/
  
  //---------1.unrestricted case-----------
  //initialize matrices and vectors
  Eigen::MatrixXd covMat = getCovMat();//covariance matrix
  Eigen::MatrixXd A = Eigen::MatrixXd::Ones(2,n_assets);
  for(size_t i = 0; i < n_assets; i ++){
    A(1,i) = assets[i].getRor();
  }
  Eigen::VectorXd X(n_assets);
  Eigen::Vector2d b(2,1);
  b(0) = 1;
  b(1) = overall_ror;
  //compose the leftside of equation. Left X = Right.
  Eigen::Matrix2d leftZero = Eigen::Matrix2d::Zero(2,2);
  Eigen::MatrixXd Left(n_assets+2,n_assets+2);
  Left << covMat,A.transpose(),A,leftZero;
  //compose the right side of equation. Left X = Right.
  Eigen::VectorXd Right(n_assets+2);
  Eigen::VectorXd rightZero = Eigen::VectorXd::Zero(n_assets);
  Right << rightZero,b;
  X = Left.colPivHouseholderQr().solve(Right);
  /*---------2.Restricted Case-------------
    Repeatedly solving the system by adding a new equation whenever find x is smaller than a -sufficiently small amount.*/
  
  size_t break_flag = 0;//break in case the loop goes forever
  std::set<double> updS;//To avoid repeatedly adding a same equation, a set is used for containing index of updated x.
  while(opt_flag){
    size_t count = 0;    
    for(size_t i = 0; i < n_assets; i++){
      if(X(i) < -0.0000000001){
   	if(updS.find(i)!=updS.end()){//check if a new equation has already been added to the ith x
	  continue;
      	}
	count ++;
      	updS.insert(i);
	//add a new equation to the left side
	Eigen::MatrixXd tempL(Left.rows(),Left.cols());
	tempL = Left;
	Eigen::VectorXd updEqu = Eigen::VectorXd::Zero(Left.rows());//new column to satisfy matrix definition n*n.
	updEqu(i) = 1;//the ith element should be set to 1
	Left.resize(Left.rows()+1,Left.cols()+1);
	Eigen::VectorXd updZero = Eigen::VectorXd::Zero(1);// 1*1 zero vector
	Left << tempL,updEqu,updEqu.transpose(),updZero;
	//update the right side
	Eigen::VectorXd tempR(Right.rows());
	tempR = Right;
	Right.resize(Right.rows()+1);
	Right << tempR,updZero;
      }
    }
    //solve
    X = Left.colPivHouseholderQr().solve(Right);
    
    break_flag++;
    if(count == 0||(break_flag > 99999999)){
      break;
    }
  }

  //------3.Calculate the minimized volatility----------------
  double min_vol = 0;
  for(size_t i = 0; i < n_assets; i++){
    for(size_t j = 0; j < n_assets;j++){
      min_vol += X(i) * X(j) * assets[i].getSd() * assets[j].getSd() * corrMat(i,j);
    }
  }
  min_vol = std::sqrt(min_vol);
  return min_vol;
}

#include<cstdlib>
#include<cstdio>
#include<iostream>
#include"function.h"
#include<cmath>



int binarySearchForZero(Function<int,int>*f, int low, int hihg);

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),
                                                                    f(fn),
								    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
  
};



class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};


void check(Function<int,int>*f
	   ,int low
	   ,int high
	   ,int expected_ans
	   ,const char * mesg){
  int n;
  if(high < low){
    std::cerr << "high < low" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  else if (high > low){
    n = std::log(high-low)/std::log(2)+1;
  }
  else{
    n = 1;
  }
  CountedIntFn * func = new CountedIntFn(n,f,mesg);
  if(expected_ans != binarySearchForZero(func,low,high)){
    std::cerr <<  mesg << std::endl;
    std::exit(EXIT_FAILURE);
  }
  delete func;
}



int main(int argc, char ** argv){
  SinFunction sinf;
  check(&sinf,0,150000,52359,"test case 1");
  check(&sinf, 0, 52358, 52359, "test case 2");
  return EXIT_SUCCESS;
}

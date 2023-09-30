#include"circle.hpp"
#include<cmath>


Circle::Circle(Point init_c, const double init_r):c(init_c),r(init_r){}

void Circle::move(double dx, double dy){
  c.move(dx,dy);
}

double Circle::intersectionArea(const Circle & otherCircle){
  double ans = 0;
  double d = c.distanceFrom(otherCircle.c);
  double r1 = r;
  double r2 = otherCircle.r;

  if(d >= r1 + r2){
    return 0;
  }
  else if(d <= std::fabs(r1-r2)){
    if (r1 > r2){
      return M_PI*pow(r2,2);
    }
    else{
      return M_PI*pow(r1,2);
    }
  }
  else{
    double part1 = r1*r1*(std::acos((d*d+r1*r1-r2*r2)/(2*d*r1)));
    double part2 = r2*r2*(std::acos((d*d+r2*r2-r1*r1)/(2*d*r2)));
    double part3 = -0.5*(std::sqrt((-d+r1+r2)*(d+r1-r2)*(d-r1+r2)*(d+r1+r2)));
    ans = part1+part2+part3;
    return ans;
  }
}

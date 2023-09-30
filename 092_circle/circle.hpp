#include"point.hpp"
class Circle{
private:
  Point c;
  const double r;  
public:
  Circle(Point init_c, const double init_r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

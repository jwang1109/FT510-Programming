#include<fstream>
#include<vector>
#include<string>



class Asset{
private:
  std::string name;//name of the asset
  std::vector<double> price;// price per time step
  std::vector<double> ror;// ror per time step
  double avgror;//average return of rate
  double sd;//standard deviation
public:
  void addPrice(double v){price.push_back(v);};
  void addName(std::string s){name = s;};
  void calAvgror();
  void calSd();
  bool priceExist() const;
  std::string getName() const {return name;};
  std::vector<double> getPrice() const {return price;};
  double getAvgror() const{return avgror;};
  std::vector<double> getRor() const {return ror;};
  double getSd() const {return sd;};
  bool operator==(const Asset & rhs) const;
  Asset & operator=(const Asset & rhs);
};


class Portfolio{
private:
  Asset * assets;//pointer to assets
  size_t numAssets;//number of assets
  double cov (const Asset & a, const Asset & b) const;// calculate cov, used by corrMat() method
  void calculate();//calculate Asset avgror,sd....used by readFile() method
public:
  Portfolio(size_t n);
  ~Portfolio();
  Portfolio readFile(std::ifstream & f);
  std::vector<std::vector<double> > corrMat() const;
  Asset & operator[](size_t index);
  size_t getNum() const {return numAssets;};
  Portfolio & operator=(const Portfolio & p);
};

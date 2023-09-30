#include<vector>
#include<string>
#include<Eigen/Dense>

class Asset{
private:
  std::string name;//name of the asset
  double ror;//average ror
  double sd;//standard deviation
public:
  void setName(std::string nm){name = nm;};
  void setSd(double s){sd = s;};
  void setRor(double r){ror = r;};
  double getRor() const {return ror;};
  double getSd() const {return sd;};
};

class Portfolio{
private:
  std::vector<Asset> assets;// A vector of assets, which is a portofolio.
  size_t n_assets;//The number of assets. Explicitly define this would be ultra helpful.
  Eigen::MatrixXd corrMat;// Corrleation matrix of the assets.
public:
  Portfolio readAll(std::ifstream & uf, std::ifstream & cf);//Read all files.
  Eigen::MatrixXd getCovMat();//Compute the covariance matrix.
  double optimize(double overall_ror,bool opt_flag);//Optimize to find the efficient frontier.
};

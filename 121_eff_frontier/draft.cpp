
bool is_sufficient_small(Eigen::MatrixXd grad, double small){
  for(long i  = 0; i < grad.rows(); i++){
    if(std::abs(grad(i,0)) > small){
      return false;
    }
  }
  return true;
}

double Portfolio::unresOptimize(){
  /* Unrestricted case.
     Solve an equation to find the optmized weight. */
  Eigen::MatrixXd covMat = getCovMat();
  Eigen::MatrixXd A = Eigen::MatrixXd::Ones(2,n_assets);
  Eigen::VectorXd Xt(n_assets);//arbitrarilly initialize the X for conducting gradient method
  Eigen::VectorXd Xt1(n_assets);
  Eigen::VectorXd Lt = Eigen::VectorXd::Zero(2);
  Eigen::VectorXd Lt1(2);
  Eigen::Vector2d b(2,1);
  Eigen::VectorXd step_vector1(n_assets);
  Eigen::VectorXd step_vector2(2);
  for(size_t i = 0; i < n_assets; i++){
    Xt(i) = (double)1/(double)n_assets;
    A(1,i) = assets[i].getRor();
  }
  b(0) = 1;
  b(1) = 0.01;
  std::cout << A << std::endl;

  /*test!
  Eigen::MatrixXd temp(n_assets,n_assets);
  temp = covMat*Xt+A.transpose()*Lt;
  Eigen::MatrixXd temp1(2,1);
  temp1 =A.transpose() * Lt;
  Eigen::MatrixXd temp3(n_assets,1);
  temp3 = 0.01*(temp+temp1);
  std::cout << temp3 << std::endl;
  test !*/
  
  size_t count = 0;
  Eigen::MatrixXd grad_x = covMat * Xt + A.transpose() * Lt;
  Eigen::MatrixXd grad_l = A * Xt -b;
  std::cout << covMat << std::endl;
  while(!(is_sufficient_small(grad_x,0.00001))){
    if(count >= 10000000){
      break;
    }
    Xt1 = Xt - 0.000001 * grad_x;
    Lt1 = Lt + 0.000001 * grad_l;
    if(count >= 9999990){
      std::cout << grad_x << std::endl;
    }
    Xt = Xt1;
    Lt = Lt1;
    grad_x = covMat * Xt + A.transpose() * Lt;
    grad_l = A * Xt -b;
    count ++;
  }
  std::cout << count << std::endl;
  std::cout << Xt1 << std::endl;
  std::cout << "The Lt:"<<std::endl;
  std::cout << Lt << std::endl;
  std::cout << "The covariance matrix: " <<std::endl;
  std::cout << covMat << std::endl;

  //calculate sigma
  double min_vol = 0;
  for(size_t i = 0; i < n_assets; i++){
    for(size_t j = 0; j < n_assets;j++){
      min_vol += Xt(i) * Xt(j) * assets[i].getSd() * assets[j].getSd() * corrMat(i,j);
    }
  }
  min_vol = std::sqrt(min_vol);
  std::cout << min_vol << std::endl;
  return min_vol;
}

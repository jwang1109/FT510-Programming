#include<stdlib.h>
#include<stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double compute_balance(double balance,retire_info retire){
  balance += balance * retire.rate_of_return + retire.contribution;
  return balance;
}


void retirement (int startAge,
		 double initial,
		 retire_info working,
		 retire_info retired
		 ){
  double balance = initial;
  for(int i = 0; i < working.months; i ++){
    printf("Age %3d month %2d you have $%.2f\n",((startAge+i)/12),((startAge+i)%12),balance);
    balance = compute_balance(balance, working);
  }
  startAge += working.months;
  for(int j = 0; j < retired.months; j ++){
    printf("Age %3d month %2d you have $%.2f\n",((startAge+j)/12),((startAge+j)%12),balance);
    balance = compute_balance(balance, retired);
  }  
}


int main(void){;
  retire_info working_info;
  working_info.months = 489;
  working_info.contribution  = 1000;
  working_info.rate_of_return = 0.045/12;
  retire_info retired_info;
  retired_info.months = 384;
  retired_info.contribution = -4000;
  retired_info.rate_of_return = 0.01/12;
  retirement(327,21345,working_info,retired_info);
  return 1;
}





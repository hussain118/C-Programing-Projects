#include<stdio.h>  q1
double calculateRepayment(double loan, int interestRate, int years, int currentYear)
{
   
    if (loan <= 0 || years == 0)
        return 0;     

  
    double interest = loan * (interestRate / 100.0);
    loan += interest;

  
    double installment = 36720.86;

  
    loan -= installment;
   

    printf("Year %d Remaining loan = %.2f\n", currentYear, loan);

   
    return installment + calculateRepayment(loan, interestRate, years - 1, currentYear + 1);
}
int main(){
 double loan=100000; 
  int interestRate= 5; 
  int years=3; 
 int currentYear=1;   
 int total=calculateRepayment(loan, interestRate, years, currentYear);
    printf("total repayment %d", total);
    return 0;

}





q2
void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets){
if (fuel==0 || planet==totalPlanets)
{
    return;
}
if (fuel<(consumption))
{
    printf("you cannot complete journey lack of fuel");
    return;
}

consumption=5;
recharge=0;
solarBonus =0;


if (planet==2 || planet==5|| planet==7)
{
    recharge=2;
    
}
if (planet==4 || planet ==8)
{
    solarBonus=3;
}
int fuelused=(consumption-solarBonus-recharge);
fuel-=fuelused;

printf("\nplanet %d fuel remaining %d\n", planet,fuel);
calculateFuel(fuel,consumption,recharge,solarBonus,planet+1,totalPlanets);

}

int main(){
    int fuel=70; 
    int consumption=5 ;
    int recharge=0; 
    int solarBonus=0; 
    int planet=1;
    int totalPlanets=8;
    calculateFuel(fuel,consumption,recharge,solarBonus,planet, totalPlanets);
    return 0;
}


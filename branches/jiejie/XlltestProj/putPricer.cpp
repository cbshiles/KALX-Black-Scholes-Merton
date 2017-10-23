
//Jie Li
// source file for putPricer, for C++ only, later to be used in Excel add-in
//% This function calculates the price of a put option assuming the following:
//% s0  is today's stock price
//% sigma is the volatility
//% k is the put strike price
//% t is the option maturity date
//% r = 0
//% a and b are parameters in the distribution, see below
//% phiTilda is the modified standardized normal distribution with the following pdf:
//% phi(a)*exp( -a*(x-a) ), phi(x), and phi(b)*exp( -b*(x-b) ) on -inf to a, a to b, and b to inf, respectively
//% a < 0, 0 < b
//% Xt = log St and Xt ~ N(m, v), m is mean and v is variance
//% m = log s0 - .5 * sigma*a*t
//% v = sigma*a*t
//% normalize Xt to z through substitution z = (Xt - m)/sqrt(v)
//% with z ~ N(0,1)
//% the integral[log(k), -inf] (k - exp(x)) p(x) dx where p(x) is the pdf of Xt
//% is transformed to the integral[L, -inf] (k - exp(sqrt(v)*z + m)) phiTilda(z) dz

#include "../normal.h"
#include "putPricer.h"
using namespace std;

double putPricer(double s0, double sigma,double k,double t,double a,double b);


double putPricer(double s0, double sigma,double k,double t,double a,double b){

	
    double m = log(s0) - .5 * sigma*sigma*t;
    double v = sigma*sigma*t;                      // v is the variance of the Xt distribution
    double sqrt_v = sqrt(v);
    double phi_a = normal_pdf(a);
    double phi_b = normal_pdf(b);

	double lamda = 1/( phi_a/-a + normal_cdf<ooura>(b) - normal_cdf<ooura>(a) + phi_b/b );  // lamda is the scaling factor to make the modified standard normal distribution integrate to one
	cout << "\n\t lamda, the scaling function is " << lamda <<endl;

    double L = (log(k) - m)/sqrt_v;           // L is normalized right limit of integration (k normalized to log k to L)


    if (L <= a)
        return (lamda*phi_a* (  k*exp(-a*(L-a))/-a - exp( (sqrt_v -a)*L +m+a*a )/( sqrt_v -a) ));
    else if (L <= b)
        return (lamda*phi_a* (  k/-a - exp( (sqrt_v -a)*a +m+a*a )/( sqrt_v -a) ) + k*( normal_cdf<ooura>(L) - normal_cdf<ooura>(a) )  - exp(m+v/2)*( normal_cdf<ooura>(L-sqrt_v) - normal_cdf<ooura>(a-sqrt_v) ));
    else {
        double A = phi_a* (  k/-a - exp( (sqrt_v -a)*a +m+a*a )/( sqrt_v -a) );
        double B = k*( normal_cdf<ooura>(b) - normal_cdf<ooura>(a) )  - exp(m+v/2)*( normal_cdf<ooura>(b-sqrt_v) - normal_cdf<ooura>(a-sqrt_v) );
        double C = phi_b* (  k*(exp(-b*(L-b)) -1)/-b - (exp( (sqrt_v -b)*L +m+b*b )  - exp(b*sqrt_v + m ) )/( sqrt_v -b) );
        return (lamda*(A+B+C));
    }
 }

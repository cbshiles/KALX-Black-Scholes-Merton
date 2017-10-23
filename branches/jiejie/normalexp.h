// normalexp.h - normal in the middle, exponential at both ends
#pragma once
#include "normal.h"

#pragma warning(push)
#pragma warning(disable: 4100) // unreferrence formal parameter

// Area under g(x) = f(a) exp(alpha (x - a), x < a; f(x), a < x < b; f(b) exp(-beta (x - b)), x > b,
// where f is that standard normal density function
// assumptions: a<0<b and a = -alpha and b = beta
inline
double normalexp_den(double a, double alpha, double b, double beta)
{
	double ans = -1.0;
	ans = -normal_pdf(a)/a + normal_cdf<ooura>(b) - normal_cdf<ooura>(a) + normal_pdf(b)/b;
	return ans;
}
// h(x) = g(x)/normalexp_den
// assumptions: assumption of a<0<b and a = -alpha and b = beta
inline 
double normalexp_pdf(double x, double a, double alpha, double b, double beta)
{
	double ans = -1.0;
	if (x < a)
		ans = normal_pdf(a)*exp( -a*(x-a) )/normalexp_den(a,alpha,b,beta);
	else if (x < b)
		ans = normal_pdf(x)/normalexp_den(a,alpha,b,beta);
	else
		ans = normal_pdf(b)*exp( -b*(x-b) )/normalexp_den(a,alpha,b,beta);
	return ans;
}

// cumulative distribution function of h
// assumptions: assumption of a<0<b and a = -alpha and b = beta and a < sigma (so that sigma -a > 0)
inline 
double normalexp_cdf(double x, double a, double alpha, double b, double beta)
{
	double ans = -1.0;
	if (x < a)
		ans = -normal_pdf(a)*exp( -a*(x-a) )/( a*normalexp_den(a,alpha,b,beta) );
	else if (x < b)
		ans = (-normal_pdf(a)/a + normal_cdf<ooura>(x) - normal_cdf<ooura>(a) )/normalexp_den(a,alpha,b,beta);
	else
		ans = (-normal_pdf(a)/a + normal_cdf<ooura>(b) - normal_cdf<ooura>(a) - normal_pdf(b)*exp( -b*(x-b) )/b + normal_pdf(b)/b)/normalexp_den(a,alpha,b,beta);
	return ans;
}

// integral to x of exp(sigma x)h(x) dx
// assumptions: assumption of a<0<b and a = -alpha and b = beta
inline
double normalexp_exp(double x, double sigma, double a, double alpha, double b, double beta)
{
	double ans = -1.0;
	if (x < a)
		ans = normal_pdf(a)*exp( (sigma - a)*x + a*a )/(normalexp_den(a,alpha,b,beta) * (sigma - a));
	else if (x < b) {
		ans = normal_pdf(a)*exp(a*sigma)/(sigma-a) + exp(.5*sigma*sigma)*(normal_cdf<ooura>(x-sigma) - normal_cdf<ooura>(a-sigma));
		ans = ans/normalexp_den(a,alpha,b,beta);
	}
	else {
		ans = normal_pdf(a)/(sigma-a);
		ans = ans + exp(.5*sigma*sigma)*(normal_cdf<ooura>(b-sigma) - normal_cdf<ooura>(a-sigma));
		ans = ans + normal_pdf(b)*(exp((sigma-b)*x + b*b)  - exp(sigma*b))/(sigma-b);
		ans = ans/normalexp_den(a,alpha,b,beta);
	}
	return ans;
}

// If F = f exp(ct + sigma sqrt(t) X), E[max{k - S}, F] = ? normalexp_cdf - ? normalexp_exp
// Choose c so thate E[S] = f.

#pragma warning(pop)
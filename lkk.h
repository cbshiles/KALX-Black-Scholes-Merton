// lkk.h - Levy-Khintchine/Kolomorov process
/*****************************************************************************

	 G(x) = a exp(x/alpha), x < 0; sigma^2 - b exp(-x/beta), x > 0
	 G'(x) = a/alpha exp(x/alpha), x < 0; b/beta exp(-x/beta), x > 0; (sigma^2 - a - b) delta(0)

	 exp[- int_R K_u(x) dG(x)] 
			= exp(-iau) (1 + i alpha u)^a/alpha(1 + i alpha u)
			* exp[-(sigma^2 - a - b)u^2/2]
			* exp(ibu) (1 - i beta u)^b/beta(1 - i u beta),
	 
	 where K_u(x) = (exp(iux) - 1 - iux)/x^2.

	 Note kappa(s) = -as/alpha + a/alpha(1 + alpha s)log(1 + alpha s)
					 -(sigma^2 - a - a)s^2/2
				     +bs/beta + b/beta(1 - beta s)log(1 - beta s)
	 
	 Assume a = alpha, b = beta.
	 We have Re (1 + iau)^(1 + iau) = exp(-au arctan au) sqrt(1 + a^2 u^2) cos[artcan au + au/2 log(1 + a^2 u^2)]
	 ~= exp(-(1 - 1/sqrt(2))a^2 u^2) cos(2^(1/4) au).

	 Note exp(gamma x)1(x < x) -> 1(x < x) as gamma -> 0 has Fourier transform
	 int_R exp(-iux) exp(gamma x)1(x < x) = exp(gamma - iu)x/(gamma - iu) -> exp(-iua)/-iu as gamma -> 0.

	 P(X < x) = int_R E[exp(iuX)] exp(-iuc)/-iu du/2pi,
	 P(X = x) = int_R E[exp(iuX)] exp(-iuc) du/2pi.
		 = int_R exp(-iau) exp(-(1 - 1/sqrt(2))a^2 u^2) cos(2^(1/4) au)
			 * exp[-(sigma^2 - a - b)u^2/2]
			 * exp(ibu) exp(-(1 - 1/sqrt(2))b^2 u^2) cos(2^(1/4) bu)
			 * exp(-icu) du/2pi.

*****************************************************************************/
#pragma once
#ifndef ensure
#include <cassert>
#define ensure(x) assert(x)
#endif
#include <cmath>


namespace lkk {

	inline double kappa(double sigma, double a, double alpha, double b, double beta)
	{
		ensure (1 + alpha > 0);
		ensure (1 - beta  > 0);

		return (alpha == 0 ? 0 : -a/alpha + a/alpha*(1 + alpha)*log(1 + alpha))
			   - (sigma*sigma - a - b)/2
			   + (beta == 0 ? 0 : b/beta + b/beta*(1 - beta)*log(1 - beta));
	}

	// always assume s = 1 so this acts more like a standard normal???
	template<class Ty, class Tx, class Ts, class Ta, class Tb>
	inline Ty pdf(Tx x, Ts s, Ta a, Tb b)
	{
		return
0.1*(exp((2*((1 + M_SQRT2)*a*a + (1 + M_SQRT2)*b*b - 2*a*(b - x) - 
           2*b*x + x*x))/
       (a + (-2 + M_SQRT2)*a*a + b + (-2 + M_SQRT2)*b*b - s*s))*
     (exp(((-3 + 2*pow(2,0.25) - 3*M_SQRT2)*a*a + 
           (-3 + 2*pow(2,0.25) - 3*M_SQRT2)*b*b - 
           2*(-3 + pow(2,0.25))*b*x - 3*x*x - 
           2*a*((-3 + 2*pow(2,0.25) + M_SQRT2)*b - (-3 + pow(2,0.25))*x))/
         (2.*(a + (-2 + M_SQRT2)*a*a + b + (-2 + M_SQRT2)*b*b - 
             s*s))) + exp(
        ((-3 + 2*pow(2,0.25) - 3*M_SQRT2)*a*a - 
           (3 + 2*pow(2,0.25) + 3*M_SQRT2)*b*b + 
           2*(3 + pow(2,0.25))*b*x - 3*x*x + 
           2*a*((3 + M_SQRT2)*b + (-3 + pow(2,0.25))*x))/
         (2.*(a + (-2 + M_SQRT2)*a*a + b + (-2 + M_SQRT2)*b*b - 
             s*s))) + exp(
        ((-3 - 2*pow(2,0.25) - 3*M_SQRT2)*a*a + 
           (-3 + 2*pow(2,0.25) - 3*M_SQRT2)*b*b - 
           2*(-3 + pow(2,0.25))*b*x - 3*x*x + 
           2*a*((3 + M_SQRT2)*b - (3 + pow(2,0.25))*x))/
         (2.*(a + (-2 + M_SQRT2)*a*a + b + (-2 + M_SQRT2)*b*b - 
             s*s))) + exp(
        -((3 + 2*pow(2,0.25) + 3*M_SQRT2)*a*a + 
            (3 + 2*pow(2,0.25) + 3*M_SQRT2)*b*b - 
            2*(3 + pow(2,0.25))*b*x + 3*x*x + 
            2*a*((-3 - 2*pow(2,0.25) + M_SQRT2)*b + (3 + pow(2,0.25))*x))/
         (2.*(a + (-2 + M_SQRT2)*a*a + b + (-2 + M_SQRT2)*b*b - 
             s*s))))*pow(M_PI,1.5))/
   (4.*M_SQRT2*sqrt(-a - (-2 + M_SQRT2)*a*a - b - (-2 + M_SQRT2)*b*b + 
       s*s))		;
	}

	template<class Ty, class Tx, class Ts, class Ta, class Tb>
	inline Ty cdf(Tx x, Ts s, Ta a, Tb b)
	{
		Ty x_(x), y(0);
		Ty fx = pdf<double,double,double,double,double>(x_, s, a, b);

		Tx dx = 1e-3;
		while (fx > 1e-11) {
			x_ -= dx;
			Ty fx_ = pdf<double,double,double,double,double>(x_, s, a, b);
			y += (fx_ + fx)*dx/2;

			fx = fx_;
		}
		
		return y;
	}
	template<class Ty, class Tf, class Ts, class Tk, class Tt>
	inline Ty put(Tf f, Ts s, double a, double b, Tk k, Tt t)
	{
		double kap = kappa(s, a, a, b, b);

		Ty x_(log(k/f) + kap), y(0);
		Ty df = pdf<double,double,double,double,double>(x_, s, a, b);
		Ty fx = (k - f*exp(-kap + x_))*df;

		double dx = 1e-3;
		while (df > 1e-11) {
			x_ -= dx;
			df = pdf<double,double,double,double,double>(x_, s, a, b);
			Ty fx_ = (k - f*exp(-kap + x_))*df;
			y += (fx_ + fx)*dx/2;

			fx = fx_;
		}
		
		return y;
	}
} // namespace lkk
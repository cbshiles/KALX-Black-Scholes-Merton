// jr.h - Jarrow Rudd 1982
// "Approximate option valuation for arbitrary stochastic processes", Journal of Financial Economics 10:347-369.
// Uncomment the following line to use features for Excel2007 and above.
//#define EXCEL12
#include <vector>
#include "xll/utility/ensure.h"
#include "black.h"
#include "../fmsdual/dual.h"

namespace jr {

	// first four cumulants: mean, mu2, mu3, mu4 - 3 mu2^2
	template<class T>
	inline std::vector<T> kappa(T s, T r, T t, T sigma)
	{
		std::vector<T> k(4);
		T q2(exp(sigma*sigma*t) - 1);

		k[0] = s*exp(r*t); // kappa_1 = alpha_1
		k[1] = k[0]*k[0]*q2;
		k[2] = k[0]*k[0]*k[0]*(3*q2*q2 + q2*q2*q2);
		k[3] = k[0]*k[0]*k[0]*k[0]*(16*pow(q2,3) + 15*pow(q2,4) + 6*pow(q2,5) + pow(q2,6));

		return k;
	}

	// a(S_t) = exp[-{log S_t - (log alpha_1 - sigma^2 t/2)}^2/2sigma^2 t]/S_t sigma sqrt(2pi t)
	template<class S, class T>
	inline S a(S s, T s0, T r, T t, T sigma)
	{
		T alpha_1 = s0*exp(r*t);
		T e1 = log(alpha_1) - sigma*sigma*t/2;
		S e2 = log(s) - e1;

		return exp(-e2*e2/(2*sigma*sigma*t))/(s*sigma*sqrt(2*M_PI*t));
	}

	inline double value(double s0, double r, double t, double sigma, double k, double dk2, double dk3, double dk4)
	{
		double R(exp(r*t)); // realized return

		if (k < 0)
			return jr::value(s0, r, t, sigma, -k, dk2, dk3, dk4) - s0 + (-k)/R;

		double c = black::value(s0*R, sigma, k, t)/R;

		dual::number<double,3> A, K(k,1);
		A = a(K, s0, r, t, sigma);

		double dc = (A[0]*dk2/2 - A[1]*dk3/6 + 2*A[2]*(dk4 + 3*dk2*dk2)/12)/R;

		return (c + dc)/R;
	}

} // namespace jr
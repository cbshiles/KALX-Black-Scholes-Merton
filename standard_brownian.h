// standard_brownian.h - Standard  Brownian motion.
#pragma once
#include "options.h"
#include "../fmsdual/normal.h"

namespace option {

template<class R = double, class T = double>
struct standard_brownian : public base_distribution<R,T> { // B_t
	standard_brownian(const T& t)
		: base_distribution<R,T>(t)
	{ }
	~standard_brownian()
	{ }

	// probability density function
	template<class U>
	U pdf(const U& x) const
	{
		return t_ ? normal_pdf(x/sqrt(t_)) : 0.; // really delta function at 0
	}

	// cumulative distribution function
	template<class U>
	U cdf(const U& x) const
	{
		return t_ ? normal_cdf(x/sqrt(t_)) : 1*(x >= 0.) ;
	}

	// kappa(s, t) = log E[exp(s X_t)]
	template<class U>
	U cumulant(const U& s) const
	{
		return t_*s*s/2.;
	}

	// cumulant distribution function
	// log E[exp(sB_t) 1(B_t <= x)] = s^2t/2 + log P(X_t + st <= z)
	template<class U, class V>
	R cudf(const U& s, const V& z) const
	{
		return cumulant(s) + log(cdf(z - s*t_));
	}

	// exp(-kappa(s) + F.kappa(s, z))
	template<class U, class V>
	R N(const U& s, const V& z) const
	{
		return cdf(z - s*t_);
	}
};

} // namespace option
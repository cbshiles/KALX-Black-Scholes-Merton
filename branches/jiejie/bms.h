// bms.h - Black-Merton-Scholes pricing for standard options
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include <cmath>
#include <functional>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/tools/roots.hpp>

using boost::math::detail::check_positive_x;
using boost::math::tools::bracket_and_solve_root;

template<class T = double, class Policy = boost::math::policies::policy<>>
class black {
public:
	// Not so efficient calculations for greeks.
	struct black_data {
		T k;
		T t;
		mutable T srt_; // sigma*sqrt(t)
		mutable T d1_;
		mutable T d2_;
		mutable T Nd1_;
		mutable T Nd2_;
		mutable T nd1_;
		black_data(T strike, T expiration)
			: k(strike), t(expiration), srt_(0), d1_(0), d2_(0), Nd1_(0), Nd2_(0), nd1_(0)
		{ 

		}
		T srt(T volatility) const
		{
			return volatility*sqrt(t);
		}
		T d1(T forward, T volatility) const
		{
			srt_ = srt(volatility);

			d1_ = log(forward/k)/srt_ + srt_/2;
			d2_ = d1_ - srt_;

			return d1_;
		}
		T d2(T forward, T volatility) const
		{
			d1_ = d1(forward, volatility);

			return d2_;
		}
		T Nd1(T forward, T volatility) const
		{
			Nd1_ = cdf(boost::math::normal_distribution<T>(), d1(forward, volatility));

			return Nd1_;
		}
		T Nd2(T forward, T volatility) const
		{
			Nd2_ = cdf(boost::math::normal_distribution<T>(), d2(forward, volatility));

			return Nd2_;
		}
		T nd1(T forward, T volatility) const
		{
			nd1_ = pdf(boost::math::normal_distribution<T>(), d1(forward, volatility));

			return nd1_;
		}
	};

	struct option : public black::black_data { 
		option(T strike, T expiration)
			: black::black_data(strike, expiration)
		{ }
	};
	struct binary : public black::black_data { 
		binary(T strike, T expiration)
			: black::black_data(strike, expiration)
		{ }
	};

	static const int call = 1;
	static const int put = -1;

	// option or binary greeks
	// cp > 0 for calls, cp < 0 for puts
	// the values pointed to by the greeks get incremented
	// cp can be different than 1 or -1 to calculate weighted portfolios
	template<class O>
	static T greeks(const O& o, T cp, T forward, T volatility,
		T* delta = 0, T* gamma = 0, T* vega = 0, T* theta = 0);

	// European call or put option.
	template<>
	static T greeks<option>(const option& o, T cp, T f, T sigma, T* df, T* ddf, T* ds, T* dt)
	{
		// boundary cases
		if (f == 0 || sigma == 0 || o.t == 0) {
			if (df) *df += (cp*f > cp*o.k);
			if (ddf) *ddf += 0; // really delta function at k

			return cp*f > cp*o.k ? cp*(f - o.k) : 0;
		}
		if (o.k == 0) {
			if (df) *df += 1;

			return f;
		}

		T result;
		if (!check_positive_x(__FUNCTION__ "%1%", f, &result, Policy()))
			return result;
		if (!check_positive_x(__FUNCTION__ "%1%", sigma, &result, Policy()))
			return result;
		if (!check_positive_x(__FUNCTION__ "%1%", o.t, &result, Policy()))
			return result;

		if (df)
			*df += cp*o.Nd1(f, sigma);

		if (ddf)
			*ddf += o.nd1(f, sigma)/(f*o.srt(sigma));

		if (ds)
			*ds += f*o.srt(sigma)*o.nd1(f, sigma)/sigma;

		if (dt)
			*dt += -f*o.srt(sigma)*o.nd1(f, sigma)/(2*o.t);

		return cp*(f*o.Nd1(f, sigma) - o.k*o.Nd2(f, sigma));
	}

	template<class O>
	static T value(const O& o, T cp, T forward, T volatility);

	// European call or put option.
	template<>
	static T value<option>(const option& o, T cp, T f, T sigma)
	{
		return greeks(o, cp, f, sigma);
	}

	// European binary call or put.
	//template<>
	//static T greeks<binary>(const option& o, T cp, T f, T sigma, T* df, T* ddf, T* ds, T* dt)

	// European call or put implied volatility
	template<class O, class Tol>
	static T implied(const O& o, T cp, T forward, T price, T guess, T factor, Tol tol, boost::uintmax_t& max_iter)
	{
		std::pair<T,T> v;

		v = bracket_and_solve_root([&](T sigma) { return black<T>::value(o, cp, forward, sigma) - price; },
				guess, factor, true, tol, max_iter, Policy());

		return mid(v);
	}
private:
	static T mid(const std::pair<T,T>& p)
	{
		return (p.first + p.second)/2;
	}
};
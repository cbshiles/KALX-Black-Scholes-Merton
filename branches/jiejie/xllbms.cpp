// xllbms.cpp - Excel functions for Black-Merton-Scholes pricing.
#include "bms.h"
#include "xllbms.h"

using namespace xll;

static AddInX xai_black_greeks2(
	FunctionX(XLL_FPX, _T("?xll_black_greeks2"), _T("BLACK.GREEKS2"))
	.Arg(XLL_DOUBLEX, _T("forward"), IS_FORWARD)
	.Arg(XLL_DOUBLEX, _T("volatility"), IS_VOLATILITY)
	.Arg(XLL_DOUBLEX, _T("strike"),	IS_STRIKE)
	.Arg(XLL_DOUBLEX, _T("expiration"), IS_EXPIRATION)
	.Arg(XLL_DOUBLEX, _T("callput"), _T("is the call or put indicator. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns a one column array of the value, delta, gamma, vega, and theta of a Black call or put option"))
	.Documentation(
		_T("The <codeInline>callput</codeInline> argument can take values other than 1 or -1. ")
		_T("It is a multiplier that can be used for weighted portfolios of options. ")
		,
		xml::xlink(_T("BLACK.IMPLIED"))
	)
);
xfp* WINAPI
xll_black_greeks2(double f, double sigma, double k, double t, double cp)
{
#pragma XLLEXPORT
	static FPX v(5, 1);

	try {
		v = 0;
		v[0] = black<>::greeks(black<>::option(k, t), cp, f, sigma, &v[1], &v[2], &v[3], &v[4]);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return v.get();
}

#ifdef _DEBUG
#include <random>

using namespace std;

#pragma warning(disable: 4305 4244)

template<typename T>
void
test_bms_args(T& cp, T& f, T& sigma, T& k, T& t)
{
	static subtract_with_carry_01<T, 24, 10, 24> eng;

	uniform_real<T> cpd(0, 1);
	uniform_real<T> fd(90, 110);
	uniform_real<T> sigmad(0.01, 0.5);
	uniform_real<T> kd(90, 100);
	uniform_real<T> td(0.1, 2);

	cp = cpd(eng) > 0.5 ? 1 : -1;
	f = fd(eng);
	sigma = sigmad(eng);
	k = kd(eng);
	t = td(eng);
}

template<typename T>
void
xll_test_bms_greeks(T eps)
{
	T h = sqrt(std::numeric_limits<T>::epsilon());
	T tmp1, tmp2;
	T cp, f, sigma, k, t;
	T u, _u, u_, delta, gamma, vega, theta;

	delta = gamma = vega = theta = 0;
	test_bms_args(cp, f, sigma, k, t);

	T ddf_(0), _ddf(0);
	u  = black<T>::greeks(black<T>::option(k, t), cp, f, sigma, &delta, &gamma, &vega, &theta);
	u_ = black<T>::greeks(black<T>::option(k, t), cp, f*(1 + h), sigma, 0, &ddf_);
	_u = black<T>::greeks(black<T>::option(k, t), cp, f*(1 - h), sigma, 0, &_ddf);
	tmp1 = (u_ - _u)/(2*f*h);
	tmp1 = delta - (u_ - _u)/(2*f*h);
	tmp2 = 2*__max(__max(ddf_, _ddf), gamma)*f*f*h*h;
//	ensure (fabs(delta - (u_ - _u)/(2*f*h)) < 2*gamma*h*h);
//	ensure (fabs(gamma - (u_ - 2*u + _u)/(h*h)) < 

	u_ = black<T>::greeks(black<T>::option(k, t), cp, f, sigma*(1 + h));
	_u = black<T>::greeks(black<T>::option(k, t), cp, f, sigma*(1 - h));
	tmp1 = vega - (u_ - _u)/(2*sigma*h);
	tmp2 = tmp1/(2*sigma*sigma*h*h);
//	ensure (fabs(vega - (u_ - _u)/(2*sigma*h)) < 2*vega*h*h); 

	u_ = black<T>::greeks(black<T>::option(k, t*(1 + h)), cp, f, sigma);
	tmp1 = theta + (u_ - u)/(t*h);
	tmp2 = tmp1/(2*t*h);
//	ensure (fabs(theta + (u_ - u)/h) < -2*theta*h); 

	uintmax_t maxiter = 100;
	u = black<T>::implied<>(black<T>::option(k, t), cp, f, u, 0.1, 2, [&](T a, T b) { return b - a < eps; }, maxiter);
	ensure (fabs(u - sigma) < eps);
}

int
xll_test_bms(void)
{
	try {
		xll_test_bms_greeks<float>(1e-6f);
		xll_test_bms_greeks<double>(1e-12);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<Open> xao_test_bms(xll_test_bms);

#endif // _DEBUG
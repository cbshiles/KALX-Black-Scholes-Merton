// jr.cpp - Jarrow Rudd option pricing.
#include <cmath>
#include "jr.h"
#include "xll/xll.h"

#define CATEGORY "CCM"

using namespace xll;

typedef traits<XLOPERX>::xfp xfp;

#ifdef _DEBUG
static AddIn xai_jr_a(
	Function(XLL_FP, "?xll_jr_a", "JR.A")
	.Arg(XLL_DOUBLE, "S", "is S.")
	.Arg(XLL_DOUBLE, "S0", "is S0.")
	.Arg(XLL_DOUBLE, "R", "is R.")
	.Arg(XLL_DOUBLE, "T", "is T.")
	.Arg(XLL_DOUBLE, "Sigma", "is sigma. ")
	.Category(CATEGORY)
	.FunctionHelp("Jarrow-Ross a() function. ")
);
xfp* WINAPI xll_jr_a(double s, double s0, double r, double t, double sigma)
{
#pragma XLLEXPORT
	static xll::FP v(3,1);

	dual::number<double,3> S(s, 1);
	dual::number<double,3> V;

	V = jr::a(S, s0, r, t, sigma);
	double v0 = jr::a(s, s0, r, t, sigma);
	double dv;
	dv = V[0] - v0;

	v[0] = V[0];
	v[1] = V[1];
	v[2] = V[2];

	return v.get();
}

#endif // _DEBUG

static AddIn xai_jr_option(
	Function(XLL_DOUBLE, "?xll_jr_value", "JR.VALUE")
	.Arg(XLL_DOUBLE, "Spot", "is the spot price.", 100)
	.Arg(XLL_DOUBLE, "Rate", "is the continuously compounded spot rate.", 0.01)
	.Arg(XLL_DOUBLE, "Time", "is the time in years to expiration.", 0.25)
	.Arg(XLL_DOUBLE, "Sigma", "is the volatility.", 0.2)
	.Arg(XLL_DOUBLE, "Strike", "is the option strike.", 100)
	.Arg(XLL_DOUBLE, "_Kappa2", "is the perturbation in volatility.", 0)
	.Arg(XLL_DOUBLE, "_Kappa3", "is the perturbation in skewness.", 0)
	.Arg(XLL_DOUBLE, "_Kappa4", "is the perturbation in kurtosis. ", 0)
	.Category(CATEGORY)
	.FunctionHelp("Jarrow-Ross option valuation. ")
);
double WINAPI xll_jr_value(double s, double r, double t, double sigma, double k, double dk2, double dk3, double dk4)
{
#pragma XLLEXPORT
	double v(std::numeric_limits<double>::quiet_NaN());

	try {
		v = jr::value(s, r, t, sigma, k, dk2, dk3, dk4);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return v;
}

#ifdef _DEBUG

#include "cumulant.h"

void test_polynomial_bell(void)
{
	double B[] = {1, 1, 2, 5, 15, 52, 203};
	std::vector<double> x(7,1);

	for (int k = 6; k >= 0; --k)
		ensure (B[k] == polynomial::Bell(k, &x[0]));
}

int test_jr()
{
	try {
		test_polynomial_bell();

		double s(100), k(100), r(0), t(.25), sigma(.2);
		double dk2(.01), dk3(.01), dk4(.01);

		std::vector<double> kap(4);
		kap = jr::kappa<double>(s, r, t, sigma);

		double v;
		v = jr::value(s, r, t, sigma, k, dk2, dk3, dk4);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<Open> xao(test_jr);

#endif // _DEBUG
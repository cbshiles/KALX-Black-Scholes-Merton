// xllnormalexp.cpp - Normal in the center, exponential on both ends.
// Copyright (c) 2006-2009 KALX, LLC. All rights reserved. No warranty is made.
#include "xllbms.h"
#include "normalexp.h"

using namespace xll;


static AddInX xai_normalexp_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_normalexp_pdf"), _T("NORMALEXP.PDF"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is the point at which the probability density function is to be evaluated."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is a negative number below which the density function is exponential."))
	.Arg(XLL_DOUBLEX, _T("alpha"),	_T("is a postive number for the exponential decay."))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is a positive number above which the density function is exponential."))
	.Arg(XLL_DOUBLEX, _T("beta"), _T("is a positive number for the exponential decay. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the probability density function of a normal distribution with exponential tails."))
	.Documentation(
		_T("The density function is proportional to <math>g(x) = f(a) e<superscript>" ENT_alpha "(x - a)</superscript></math>, ")
		_T("<math>x &lt; a</math>; <math>f(x)</math>, <math>a &lt; x &lt; b</math>; <math>f(a) e<superscript>" ENT_minus ENT_beta)
		_T("(x - b)</superscript></math>, <math>x &gt; b</math> where <math>f</math> is the standard normal density function, ")
		_T("<math>a &lt; 0 &lt; b</math> and both " ENT_alpha " and " ENT_beta " are positive. ")
	)
);
double WINAPI
xll_normalexp_pdf(double x, double a, double alpha, double b, double beta)
{
#pragma XLLEXPORT
	double f;

	try {
		ensure (a < 0);
		ensure (alpha > 0);
		ensure (b > 0);
		ensure (beta > 0);

		f = normalexp_pdf(x, a, alpha, b, beta);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return f;
}

/// adding begins

static AddInX xai_normalexp_cdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_normalexp_cdf"), _T("NORMALEXP.CDF"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is the point at which the cumulative density function is to be evaluated."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is a negative number below which the density function is exponential."))
	.Arg(XLL_DOUBLEX, _T("alpha"),	_T("is a postive number for the exponential decay."))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is a positive number above which the density function is exponential."))
	.Arg(XLL_DOUBLEX, _T("beta"), _T("is a positive number for the exponential decay. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the cumulative density function of a normal distribution with exponential tails."))
	.Documentation(
		_T("The density function is proportional to <math>g(x) = f(a) e<superscript>" ENT_alpha "(x - a)</superscript></math>, ")
		_T("<math>x &lt; a</math>; <math>f(x)</math>, <math>a &lt; x &lt; b</math>; <math>f(a) e<superscript>" ENT_minus ENT_beta)
		_T("(x - b)</superscript></math>, <math>x &gt; b</math> where <math>f</math> is the standard normal density function, ")
		_T("<math>a &lt; 0 &lt; b</math> and both " ENT_alpha " and " ENT_beta " are positive. ")
	)
);
double WINAPI
xll_normalexp_cdf(double x, double a, double alpha, double b, double beta)
{
#pragma XLLEXPORT
	double f;

	try {
		ensure (a < 0);
		ensure (alpha > 0);
		ensure (b > 0);
		ensure (beta > 0);

		f = normalexp_cdf(x, a, alpha, b, beta);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return f;
}


/// adding ends
 
 #ifdef _DEBUG

int
test_normalexp(void)
{
	try {
		int i = 0;
		ensure (i == 0);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<OpenAfter> xao_black(test_normalexp);

#endif // _DEGBUG

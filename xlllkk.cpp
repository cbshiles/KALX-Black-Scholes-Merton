// xlllkk.cpp - Levy-Khintchine/Kolomogorov process
#include "xll/xll.h"
#include "lkk.h"

using namespace xll;

typedef traits<XLOPERX>::xfp xfp;
typedef traits<XLOPERX>::xword xword;

static AddInX xai_lkk_pdf(
	FunctionX(XLL_FPX, _T("?xll_lkk_pdf"), _T("LKK.PDF"))
	.Arg(XLL_FPX, _T("x"), _T("are the values at which to sample the distribution. "))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the volatility. "))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the low tail. "))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the high tail. "))
	.Category(_T("LKK"))
	.FunctionHelp(_T("Returns the probability density function of the Levy-Khintchine/Kolomogorov distribution."))
);
xfp* WINAPI
xll_lkk_pdf(xfp* px, double s, double a, double b)
{
#pragma XLLEXPORT
	for (xword i = 0; i < size(*px); ++i)
		px->array[i] = lkk::pdf<double,double,double,double,double>(px->array[i], s, a, b);

	return px;
}

static AddInX xai_lkk_cdf(
	FunctionX(XLL_FPX, _T("?xll_lkk_cdf"), _T("LKK.CDF"))
	.Arg(XLL_FPX, _T("x"), _T("are the values at which to sample the distribution. "))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the volatility. "))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the low tail. "))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the high tail. "))
	.Category(_T("LKK"))
	.FunctionHelp(_T("Returns the cumulative probability distribution of the Levy-Khintchine/Kolomogorov distribution."))
);
xfp* WINAPI
xll_lkk_cdf(xfp* px, double s, double a, double b)
{
#pragma XLLEXPORT
	try {
		ensure (s*s - a - b > 0);

		for (xword i = 0; i < size(*px); ++i)
			px->array[i] = lkk::cdf<double,double,double,double,double>(px->array[i], s, a, b);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return px;
}

static AddInX xai_lkk_put(
	FunctionX(XLL_DOUBLEX, _T("?xll_lkk_put"), _T("LKK.PUT"))
	.Arg(XLL_DOUBLEX, _T("f"), _T("forward. "))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("volatility. "))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the low tail. "))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the high tail. "))
	.Arg(XLL_DOUBLEX, _T("k"), _T("strike. "))
	.Arg(XLL_DOUBLEX, _T("t"), _T("expiration. "))
	.Category(_T("LKK"))
	.FunctionHelp(_T("Returns the cumulative probability distribution of the Levy-Khintchine/Kolomogorov distribution."))
);
double WINAPI
xll_lkk_put(double f, double s, double a, double b, double k, double t)
{
#pragma XLLEXPORT
	double v;

	try {
		ensure (s*s - a - b > 0);

			v = lkk::put<double,double,double,double,double>(f, s, a, b, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return v;
}

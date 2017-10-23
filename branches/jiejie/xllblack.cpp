// black.cpp - Fischer Black model that uses forwards and no rates.
// Copyright (c) 2006-2009 KALX, LLC. All rights reserved. No warranty is made.
#include "xllbms.h"
#include "black.h"

using namespace black;
using namespace xll;

#ifndef EXCEL12
static AddInX xai_black_doc(
	ArgsX(CATEGORY)
	.Documentation(xml::File(_T("../Code/xllbms/bms.xml")))
);
#endif

static AddInX xai_black_greeks(
	FunctionX(XLL_FPX, _T("?xll_black_greeks"), _T("BLACK.GREEKS"))
	.Arg(XLL_DOUBLEX, _T("forward"), IS_FORWARD)
	.Arg(XLL_DOUBLEX, _T("volatility"), IS_VOLATILITY)
	.Arg(XLL_DOUBLEX, _T("strike"),	IS_STRIKE)
	.Arg(XLL_DOUBLEX, _T("expiration"), IS_EXPIRATION _T(". "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns a one column array of the value, delta, gamma, vega, and theta of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
		,
		xml::xlink(_T("BLACK.IMPLIED"))
	)
);
xfp* WINAPI
xll_black_greeks(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	static FPX v(5, 1);

	try {
		v = 0;
		v[0] = black::black(f, sigma, k, t, &v[1], &v[2], &v[3], &v[4]);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return v.get();
}
static AddInX xai_black_value(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_value"), _T("BLACK.VALUE"))
	.Arg(XLL_DOUBLEX, _T("forward"), IS_FORWARD)
	.Arg(XLL_DOUBLEX, _T("volatility"), IS_VOLATILITY)
	.Arg(XLL_DOUBLEX, _T("strike"),	IS_STRIKE)
	.Arg(XLL_DOUBLEX, _T("expiration"), IS_EXPIRATION _T(". "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the value of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
		,
		xml::xlink(_T("BLACK.IMPLIED"))
	)
);
double WINAPI
xll_black_value(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double x;

	try {
		x = black::black(f, sigma, k, t, 0, 0, 0, 0);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return std::numeric_limits<double>::quiet_NaN();
	}

	return x;
}
static AddInX xai_black_delta(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_delta"), _T("BLACK.DELTA"))
	.Arg(XLL_DOUBLEX, _T("forward"), IS_FORWARD)
	.Arg(XLL_DOUBLEX, _T("volatility"), IS_VOLATILITY)
	.Arg(XLL_DOUBLEX, _T("strike"),	IS_STRIKE)
	.Arg(XLL_DOUBLEX, _T("expiration"), IS_EXPIRATION _T(". "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the delta of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
		,
		xml::xlink(_T("BLACK.IMPLIED"))
	)
);
double WINAPI
xll_black_delta(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double x(0);

	try {
		black::black(f, sigma, k, t, &x, 0, 0, 0);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return std::numeric_limits<double>::quiet_NaN();
	}

	return x;
}
static AddInX xai_black_gamma(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_gamma"), _T("BLACK.GAMMA"))
	.Arg(XLL_DOUBLEX, _T("forward"), IS_FORWARD)
	.Arg(XLL_DOUBLEX, _T("volatility"), IS_VOLATILITY)
	.Arg(XLL_DOUBLEX, _T("strike"),	IS_STRIKE)
	.Arg(XLL_DOUBLEX, _T("expiration"), IS_EXPIRATION _T(". "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the gamma of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
		,
		xml::xlink(_T("BLACK.IMPLIED"))
	)
);
double WINAPI
xll_black_gamma(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double x(0);

	try {
		black::black(f, sigma, k, t, 0, &x, 0, 0);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return std::numeric_limits<double>::quiet_NaN();
	}

	return x;
}
static AddInX xai_black_vega(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_vega"), _T("BLACK.VEGA"))
	.Arg(XLL_DOUBLEX, _T("forward"), IS_FORWARD)
	.Arg(XLL_DOUBLEX, _T("volatility"), IS_VOLATILITY)
	.Arg(XLL_DOUBLEX, _T("strike"),	IS_STRIKE)
	.Arg(XLL_DOUBLEX, _T("expiration"), IS_EXPIRATION _T(". "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the vega of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
		,
		xml::xlink(_T("BLACK.IMPLIED"))
	)
);
double WINAPI
xll_black_vega(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double x(0);

	try {
		black::black(f, sigma, k, t, 0, 0, &x, 0);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return std::numeric_limits<double>::quiet_NaN();
	}

	return x;
}
static AddInX xai_black_theta(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_theta"), _T("BLACK.THETA"))
	.Arg(XLL_DOUBLEX, _T("forward"), IS_FORWARD)
	.Arg(XLL_DOUBLEX, _T("volatility"), IS_VOLATILITY)
	.Arg(XLL_DOUBLEX, _T("strike"),	IS_STRIKE)
	.Arg(XLL_DOUBLEX, _T("expiration"), IS_EXPIRATION _T(". "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the theta of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
		,
		xml::xlink(_T("BLACK.IMPLIED"))
	)
);
double WINAPI
xll_black_theta(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double x(0);

	try {
		black::black(f, sigma, k, t, 0, 0, 0, &x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return std::numeric_limits<double>::quiet_NaN();
	}

	return x;
}

static AddInX xai_black_implied(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_implied"), _T("BLACK.IMPLIED"))
	.Arg(XLL_DOUBLEX, _T("forward"), IS_FORWARD)
	.Arg(XLL_DOUBLEX, _T("price"), IS_PRICE)
	.Arg(XLL_DOUBLEX, _T("strike"), IS_STRIKE)
	.Arg(XLL_DOUBLEX, _T("expiration"), IS_EXPIRATION _T(". "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the implied volatility of a Black call or put option"))
	.Documentation(
		_T("The implied volatilty is that which returns <codeInline>price</codeInline> ")
		_T("from <codeInline>BLACK.VALUE</codeInline>. ")
		,
		xml::xlink(_T("BLACK.VALUE"))
	)
);
double WINAPI
xll_black_implied(double f, double p, double k, double t)
{
#pragma XLLEXPORT
	double value;

	try {
		value = black::implied(f, p, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		value = std::numeric_limits<double>::quiet_NaN();
	}

	return value;
}

#ifdef _DEBUG

int
test_black(void)
{
	try {
		OPERX x;
		x = ExcelX(xlfEvaluate, OPERX(_T("BLACK.GREEKS(100, .2, 100, .25)")));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<OpenAfter> xao_black(test_black);

#endif // _DEGBUG

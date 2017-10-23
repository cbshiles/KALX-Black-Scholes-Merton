// black.cpp - Fischer Black model that uses forwards and no rates.
// Copyright (c) 2006-2009 KALX, LLC. All rights reserved. No warranty is made.
#include "../xll8/xll/xll.h"
#include "../fmsgjr/black.h"

#define CATEGORY _T("XLL")
#define PREFIX //CATEGORY _T(".")

#define IS_FORWARD _T("is the forward value of the underlying.")
#define IS_VOLATILITY _T("is the volatility of the underlying.")
#define IS_STRIKE _T("is the strike of the underlying option.")
#define IS_EXPIRATION _T("is the time in years to option expiration.")
#define IS_VALUE _T("is the option value.")

using namespace fms;
using namespace xll;

typedef traits<XLOPERX>::xfp xfp;
/*
#ifdef _DEBUG
static AddInX xai_black_doc(
	ArgsX(CATEGORY)
	.Documentation(xml::File(_T("./Code/xllbms/bms.xml")))
);
#endif
*/
static AddInX xai_black_binary(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_binary"), PREFIX _T("BLACK.BINARY"))
	.Num(_T("Forward"), IS_FORWARD, 100)
	.Num(_T("Volatility"), IS_VOLATILITY, .2)
	.Num(_T("Strike"),	IS_STRIKE, 100)
	.Num(_T("Expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the binary of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
/*		,
		xml::xlink(_T("BLACK.IMPLIED"))
*/	)
);
double WINAPI xll_black_binary(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double x(std::numeric_limits<double>::quiet_NaN());

	try {
		x = black::binary(f, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}


static AddInX xai_black_value(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_value"), PREFIX _T("BLACK.VALUE"))
	.Num(_T("Forward"), IS_FORWARD, 100)
	.Num(_T("Volatility"), IS_VOLATILITY, .2)
	.Num(_T("Strike"),	IS_STRIKE, 100)
	.Num(_T("Expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the value of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
/*		,
		xml::xlink(_T("BLACK.IMPLIED"))
*/	)
);
double WINAPI xll_black_value(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double x(std::numeric_limits<double>::quiet_NaN());

	try {
		x = black::value(f, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_black_greeks(
	FunctionX(XLL_FPX, _T("?xll_black_greeks"), PREFIX _T("BLACK.GREEKS"))
	.Num(_T("Forward"), IS_FORWARD, 100)
	.Num(_T("Volatility"), IS_VOLATILITY, .2)
	.Num(_T("Strike"),	IS_STRIKE, 100.)
	.Num(_T("Expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns a one column array of the value, delta, gamma, vega, and theta of a Black call or put option"))
	.Documentation(R"(
		If you prefer a call/put flag of )" ENT_plusmn R"(1 use <codeInline>flag*strike</codeInline> as the
		<codeInline>strike</codeInline> argument to this function.
	)"
/*		,
		xml::xlink(_T("BLACK.IMPLIED"))
*/	)
);
xfp* WINAPI xll_black_greeks(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	static FPX v(5, 1);

	try {
		v = 0;
		v[0] = black::greeks(f, sigma, k, t, &v[1], &v[2], &v[3], &v[4]);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		v = std::numeric_limits<double>::quiet_NaN();
	}

	return v.get();
}

static AddInX xai_black_delta(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_delta"), PREFIX _T("BLACK.DELTA"))
	.Num(_T("Forward"), IS_FORWARD, 100)
	.Num(_T("Volatility"), IS_VOLATILITY, .2)
	.Num(_T("Strike"),	IS_STRIKE, 100)
	.Num(_T("Expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the delta of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
/*		,
		xml::xlink(_T("BLACK.IMPLIED"))
*/	)
);
double WINAPI xll_black_delta(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double x(std::numeric_limits<double>::quiet_NaN());

	try {
		black::greeks(f, sigma, k, t, &x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_black_gamma(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_gamma"), PREFIX _T("BLACK.GAMMA"))
	.Num(_T("Forward"), IS_FORWARD, 100)
	.Num(_T("Volatility"), IS_VOLATILITY, .2)
	.Num(_T("Strike"),	IS_STRIKE, 100)
	.Num(_T("Expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the gamma of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
/*		,
		xml::xlink(_T("BLACK.IMPLIED"))
*/	)
);
double WINAPI xll_black_gamma(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double x(std::numeric_limits<double>::quiet_NaN());

	try {
		black::greeks<double>(f, sigma, k, t, 0, &x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_black_vega(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_vega"), PREFIX _T("BLACK.VEGA"))
	.Num(_T("Forward"), IS_FORWARD, 100)
	.Num(_T("Volatility"), IS_VOLATILITY, .2)
	.Num(_T("Strike"),	IS_STRIKE, 100)
	.Num(_T("Expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the vega of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
/*		,
		xml::xlink(_T("BLACK.IMPLIED"))
*/	)
);
double WINAPI xll_black_vega(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double x(std::numeric_limits<double>::quiet_NaN());

	try {
		black::greeks<double>(f, sigma, k, t, 0, 0, &x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_black_theta(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_theta"), PREFIX _T("BLACK.THETA"))
	.Num(_T("Forward"), IS_FORWARD, 100)
	.Num(_T("Volatility"), IS_VOLATILITY, .2)
	.Num(_T("Strike"),	IS_STRIKE, 100)
	.Num(_T("Expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the theta of a Black call or put option"))
	.Documentation(
		_T("If you prefer a call/put flag of ") ENT_plusmn _T("1 use <codeInline>flag*strike</codeInline> as the ")
		_T("<codeInline>strike</codeInline> argument to this function. ")
/*		,
		xml::xlink(_T("BLACK.IMPLIED.VOLATILITY"))
*/	)
);
double WINAPI xll_black_theta(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double x(std::numeric_limits<double>::quiet_NaN());

	try {
		black::greeks<double>(f, sigma, k, t, 0, 0, 0, &x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_corrado_miller_implied_volatility(
	FunctionX(XLL_DOUBLEX, _T("?xll_corrado_miller_implied_volatility"), PREFIX _T("CM.IMPLIED.VOLATILITY"))
	.Num(_T("Forward"), IS_FORWARD, 100)
	.Num(_T("Value"), IS_VALUE, 4)
	.Num(_T("Strike"), IS_STRIKE, 100)
	.Num(_T("Expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the Corrado-Miller implied volatility of a Black call or put option"))
	.Documentation(
		_T("The implied volatilty is that which returns <codeInline>value</codeInline> ")
		_T("from <codeInline>BLACK.VALUE</codeInline>. ")
/*		,
		xml::xlink(_T("BLACK.VALUE"))
*/	)
);
double WINAPI
xll_corrado_miller_implied_volatility(double f, double p, double k, double t)
{
#pragma XLLEXPORT
	double vol(std::numeric_limits<double>::quiet_NaN());

	try {
		vol = black::corrado_miller_implied_volatility(f, p, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return vol;
}

static AddInX xai_black_implied_volatility(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_implied_volatility"), PREFIX _T("BLACK.IMPLIED.VOLATILITY"))
	.Num(_T("Forward"), IS_FORWARD, 100)
	.Num(_T("Value"), IS_VALUE, 4)
	.Num(_T("Strike"), IS_STRIKE, 100)
	.Num(_T("Expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the implied volatility of a Black call or put option"))
	.Documentation(
		_T("The implied volatilty is that which returns <codeInline>value</codeInline> ")
		_T("from <codeInline>BLACK.VALUE</codeInline>. ")
/*		,
		xml::xlink(_T("BLACK.VALUE"))
*/	)
);
double WINAPI
xll_black_implied_volatility(double f, double p, double k, double t)
{
#pragma XLLEXPORT
	double vol(std::numeric_limits<double>::quiet_NaN());

	try {
		vol = black::implied_volatility(f, p, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return vol;
}

#if 0
static AddInX xai_black_implied_forward(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_implied_forward"), _T("BLACK.IMPLIED.FORWARD"))
	.Num(_T("value"), IS_VALUE, 4)
	.Num(_T("volatility"), IS_VOLATILITY, .2)
	.Num(_T("strike"), IS_STRIKE, 100)
	.Num(_T("expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the implied forward of a Black call or put option."))
	.Documentation(
		"The implied forward is that which returns <codeInline>value</codeInline> "
		"from <codeInline>BLACK.VALUE</codeInline>. "
/*		,
		xml::xlink(_T("BLACK.VALUE"))
*/	)
);
double WINAPI
xll_black_implied_forward(double v, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double f(std::numeric_limits<double>::quiet_NaN());

	try {
		f = black::implied_forward(v, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return f;
}

#ifdef _DEBUG

#include "option.h"

void test_model(void)
{
	option::black<> m;

	ensure (m.kappa(.25, 0.2) == .2*.2*.25/2);


}

int
test_black(void)
{
	try {
		OPERX x;
		x = Excel<XLOPERX>(xlfEvaluate, OPERX(_T("BLACK.GREEKS(100, .2, 100, .25)")));

		test_model();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<OpenAfter> xao_black(test_black);

#endif // _DEGBUG
#endif

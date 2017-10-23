// function.cpp - Rename this file and replace this description.
#include "header.h"
#include "putPricer.h"

using namespace xll;


static AddInX xai_function(
	FunctionX(XLL_LPOPERX, _T("?xll_function"), _T("XLL.FUNCTION"))
	.Arg(XLL_DOUBLEX, _T("Forward"), _T("is is the forward price."))
	.Arg(XLL_DOUBLEX, _T("Sigma"), _T("is the volatility."))
	.Arg(XLL_DOUBLEX, _T("Strike"), _T("is the strike of the put option."))
	.Arg(XLL_DOUBLEX, _T("Expiration"), _T("is the time in years to expiration."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the low exponential parameter."))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the low exponential parameter. "))
//	.Arg(...) // add more args here
	.Category(CATEGORY)
	.FunctionHelp(_T("This function calculates the price of a put option."))
	.Documentation(_T("The model assumes the following: risk-free rate r is zero and ..."))
);
LPOPERX WINAPI
xll_function(double s0, double sigma, double k, double t, double a, double b)
{
#pragma XLLEXPORT
	static OPERX xResult;

	// function body goes here
	// xResult = y*exp(x); 
	//	xResult = putPricer(1,0.1, 1.1, .5,-2,2.5); 

	xResult = putPricer(s0,sigma, k, t,a,b);

	return &xResult;
}
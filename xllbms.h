// xllbms.h - Black-Merton-Scholes constant volatility model
#pragma once
// uncomment to build for Excel 2007 and later
//#define EXCEL12
#include "xll/xll.h"

#ifndef CATEGORY
#define CATEGORY _T("BMS")
#endif

typedef xll::traits<XLOPERX>::xcstr xcstr;
typedef xll::traits<XLOPERX>::xfp xfp;
typedef xll::traits<XLOPERX>::xword xword;

#define IS_FORWARD    _T("is the forward value of the underlying instrument at option expiration")
#define IS_VOLATILITY _T("is the square root of the annualized variance of the log of the underlying")
#define IS_STRIKE     _T("is the strike of the call or the negative of the strike of the put")
#define IS_EXPIRATION _T("is the time in years to option expiration")
#define IS_VALUE      _T("is the value of the call or put option")


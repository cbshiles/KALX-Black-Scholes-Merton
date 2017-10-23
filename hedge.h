// hedge.h - hedging using futures
#pragma once
#include <tuple>
#include "xll/utility/srng.h"
#include "normal.h"

namespace hedge {

	// inf {t > 0 : min B_t > lo, max B_t < hi }, hi?
	inline std::tuple<double,bool> hitting_time(double lo, double hi)
	{
		static utility::srng rng; // should use global variable

		ensure (lo < 0);
		ensure (hi > 0);

		double x;

		x = lo/normal_inv<ooura>((1 - rng.real())/2);
		double Tlo = x*x;

		x = hi/normal_inv<ooura>((1 - rng.real())/2);
		double Thi = x*x;

		return std::make_tuple(min(Tlo, Thi), Thi < Tlo); // !!! not correct
	}

	// time limit order executes, hi?
	inline std::tuple<double, bool> next_hit(double spot, double lo, double hi)
	{
		std::tuple<double,bool> db = hitting_time(0,0);
		double d = std::get<0>(db);
		bool b = std::get<1>(db);

		return hitting_time(lo - spot, hi - spot);
	}

	struct order {
		double level;
		double amount;
	};



	// hedging standard Brownian motion
	class futures {
	public:
		// 
		futures
		{ }
	};

} // namespace hedge
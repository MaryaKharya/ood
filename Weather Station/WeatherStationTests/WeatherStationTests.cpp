#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include <set>
#include "../Weather Station/Observer.h"
#include "../Weather Station/WeatherData.h"
#include "../../catch2/catch.hpp"

SCENARIO("Priority test")
{
	std::ostringstream out;
	CWeatherData wd;
	CDisplayTest display1(1, out);
	CDisplayTest display2(2, out);
	CStatsDisplayTest display3(3, out);
	wd.RegisterObserver(display1, 7);
	wd.RegisterObserver(display2, -2);
	wd.RegisterObserver(display3, 4);
	wd.SetMeasurements(3, 0.7, 760);
	CHECK(out.str() == "132");
}
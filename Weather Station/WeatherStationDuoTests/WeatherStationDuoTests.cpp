#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include <set>
#include "../WeatherStationDuo/Observer.h"
#include "../WeatherStationDuo/WeatherData.h"
#include "../../catch2/catch.hpp"

SCENARIO("WeatherStationDuo test")
{
	std::ostringstream out;
	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	CWeatherData wdIn;
	CWeatherData wdOut;
	CDisplay display1(wdIn);
	wdIn.RegisterObserver(display1, 1);
	wdOut.RegisterObserver(display1, 1);
	wdOut.SetMeasurements(3, 0.7, 760);
	wdIn.SetMeasurements(4, 0.8, 761);
	std::cout.rdbuf(coutbuf);
	CHECK(out.str() == "Outdoor station:\nCurrent Temp 3\nCurrent Hum 0.7\nCurrent Pressure 760\n----------------\nIndoor station:\nCurrent Temp 4\nCurrent Hum 0.8\nCurrent Pressure 761\n----------------\n");
}
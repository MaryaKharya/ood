#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 7);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 9);

	wd.SetMeasurements(3, 0.7, 760, 12, 90);
	wd.SetMeasurements(4, 0.8, 761, 14, 180);

	wd.SetMeasurements(10, 0.8, 761, 6, 45);
	wd.SetMeasurements(-10, 0.8, 761, 20, 0);
	return 0;
}
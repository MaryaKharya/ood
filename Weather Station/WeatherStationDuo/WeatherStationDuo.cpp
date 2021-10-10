#include "WeatherData.h"

int main()
{
	CWeatherData wdIn;
	CWeatherData wdOut;

	CDisplay display(wdIn, wdOut);
	wdIn.RegisterObserver(display, 1);
	wdOut.RegisterObserver(display, 2);

	CStatsDisplay statsDisplay(wdIn, wdOut);
	wdIn.RegisterObserver(statsDisplay, 9);
	wdOut.RegisterObserver(statsDisplay, 9);

	wdIn.SetMeasurements(3, 0.7, 760);
	wdOut.SetMeasurements(4, 0.8, 761);
	return 0;
}
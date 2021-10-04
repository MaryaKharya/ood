#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windDirection = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplayOneParameter
{
public:
	void UpdateData(double data)
	{
		if (m_min > data)
		{
			m_min = data;
		}
		if (m_max < data)
		{
			m_max = data;
		}
		m_acc += data;
		++m_countAcc;

		std::cout << "Max: " << m_max << std::endl;
		std::cout << "Min: " << m_min << std::endl;
		std::cout << "Average: " << (m_acc / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;

};

class CStatsDisplayWindDirection
{
public:
	void UpdateData(double windDirection, double windSpeed)
	{
		m_sinSum += windSpeed * sin(windDirection * M_PI / 180);
		m_cosSum += windSpeed * cos(windDirection * M_PI / 180);
		++m_countAcc;
		double accDirection = 180 / M_PI * (atan2(m_sinSum / m_countAcc, m_cosSum / m_countAcc));
		if (windDirection < 0)
		{
			windDirection += 360;
		}
		std::cout << "Average: " << accDirection << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	double m_sinSum = 0;
	double m_cosSum = 0;
	unsigned m_countAcc = 0;

};



class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Temperature stats:\n";
		m_temperature.UpdateData(data.temperature);
		std::cout << "Humidity stats:\n";
		m_humidity.UpdateData(data.humidity);
		std::cout << "Pressure stats:\n";
		m_pressure.UpdateData(data.pressure);
		std::cout << "Wind Speed stats:\n";
		m_windSpeed.UpdateData(data.windSpeed);
		std::cout << "Wind Direction stats:\n";
		m_windDirection.UpdateData(data.windDirection, data.windSpeed);
	}
	CStatsDisplayOneParameter m_temperature;
	CStatsDisplayOneParameter m_humidity;
	CStatsDisplayOneParameter m_pressure;
	CStatsDisplayOneParameter m_windSpeed;
	CStatsDisplayWindDirection m_windDirection;
};


class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	double GetTemperature()const
	{
		return m_temperature;
	}
	double GetHumidity()const
	{
		return m_humidity;
	}
	double GetPressure()const
	{
		return m_pressure;
	}
	double GetWindSpeed()const
	{
		return m_windSpeed;
	}
	double GetWindDirection()const
	{
		return m_windDirection;
	}
	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0.0;
	double m_windDirection = 0.0;
};

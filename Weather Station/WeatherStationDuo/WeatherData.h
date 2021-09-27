#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	CDisplay(const IObservable<SWeatherInfo>& in)
		:m_in(in)
	{}
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override
	{
		if (&observable == &m_in)
		{
			std::cout << "Indoor station:" << std::endl;
		}
		else
		{
			std::cout << "Outdoor station:" << std::endl;
		}
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
	const IObservable<SWeatherInfo>& m_in;
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


class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(IObservable<SWeatherInfo> const& in)
		:m_in(in)
	{}
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override
	{
		if (&observable == &m_in)
		{
			std::cout << "Indoor station:" << std::endl;
		}
		else
		{
			std::cout << "Outdoor station:" << std::endl;
		}
		std::cout << "Temperature stats:\n";
		m_temperature.UpdateData(data.temperature);
		std::cout << "Humidity stats:\n";
		m_humidity.UpdateData(data.humidity);
		std::cout << "Pressure stats:\n";
		m_pressure.UpdateData(data.pressure);
	}
	CStatsDisplayOneParameter m_temperature;
	CStatsDisplayOneParameter m_humidity;
	CStatsDisplayOneParameter m_pressure;
	IObservable<SWeatherInfo> const& m_in;
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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

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

class CDisplayTest : public IObserver<SWeatherInfo>
{
public:
	CDisplayTest(int observer, std::ostream& out)
		:m_observer(observer)
		, m_out(out)
	{}
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
		m_out << m_observer;
	}
	int m_observer;
	std::ostream& m_out;
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

class CStatsDisplayTest : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplayTest(int observer, std::ostream& out)
		:m_observer(observer)
		, m_out(out)
	{}
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Temperature stats:\n";
		m_temperature.UpdateData(data.temperature);
		std::cout << "Humidity stats:\n";
		m_humidity.UpdateData(data.humidity);
		std::cout << "Pressure stats:\n";
		m_pressure.UpdateData(data.pressure);
		m_out << m_observer;
	}
	CStatsDisplayOneParameter m_temperature;
	CStatsDisplayOneParameter m_humidity;
	CStatsDisplayOneParameter m_pressure;
	int m_observer;
	std::ostream& m_out;
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
	}
	CStatsDisplayOneParameter m_temperature;
	CStatsDisplayOneParameter m_humidity;
	CStatsDisplayOneParameter m_pressure;
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
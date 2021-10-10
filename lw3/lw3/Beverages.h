
#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description)
	{}
	double GetCost() const override
	{
		return 60;
	}
};

enum class CoffeePortionType
{
	Standard,
	Double
};
// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeePortionType portion = CoffeePortionType::Standard)
		:CCoffee("Cappuccino " + std::string(portion == CoffeePortionType::Double ? "Double" : "Standard"))
		, m_portion(portion)
	{}

	double GetCost() const override
	{
		return m_portion == CoffeePortionType::Double ? 120 : 80;
	}
	CoffeePortionType m_portion;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeePortionType portion = CoffeePortionType::Standard)
		:CCoffee("Latte " + std::string(portion == CoffeePortionType::Double ? "Double" : "Standard"))
		, m_portion(portion)
	{

	}

	double GetCost() const override
	{
		return m_portion == CoffeePortionType::Double ? 130 : 90;
	}

private:
	CoffeePortionType m_portion;
};

// Чай
enum class TeaType
{
	Black,
	Green,
	Oolong,
	Mate
};

class CTea : public CBeverage
{
public:
	CTea(TeaType type = TeaType::Black)
		: CBeverage("Tea " + GetTeaType(type))
		, m_type(type)
	{
	}

	double GetCost() const override
	{
		return 30;
	}

private:
	TeaType m_type;
	std::string GetTeaType(TeaType type)
	{
		switch (type)
		{
		case TeaType::Black:
			return "black";
		case TeaType::Green:
			return "Green";
		case TeaType::Oolong:
			return "Oolong";
		case TeaType::Mate:
			return "Mate";
		}
	};
};

// Молочный коктейль
enum class MilkshakePortionType
{
	Small,
	Medium,
	Large,
};

class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortionType portion = MilkshakePortionType::Small)
		:CBeverage("Milkshake " + GetPortionType(portion))
		, m_portion(portion)
	{}

	double GetCost() const override
	{
		switch (m_portion)
		{
		case MilkshakePortionType::Small:
			return 50;
		case MilkshakePortionType::Medium:
			return 60;
		case MilkshakePortionType::Large:
			return 80;
		}
	}
private:
	MilkshakePortionType m_portion;
	std::string GetPortionType(MilkshakePortionType portion)
	{
		switch (portion)
		{
		case MilkshakePortionType::Small:
			return "Small";
		case MilkshakePortionType::Medium:
			return "Medium";
		case MilkshakePortionType::Large:
			return "Large";
		}
	};
};
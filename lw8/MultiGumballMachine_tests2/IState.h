#pragma once
#include <iostream>

struct IState
{
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual void FillMachine(unsigned const gumballs) = 0;
	virtual std::string ToString()const = 0;
	virtual ~IState() = default;
};
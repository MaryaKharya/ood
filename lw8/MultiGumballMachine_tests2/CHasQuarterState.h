#pragma once
#include "IState.h"
#include "IGumballMachine.h"

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		if (m_gumballMachine.GetQuarterCount() == 5)
		{
			std::cout << "You can't insert another quarter\n";
		}
		else
		{
			m_gumballMachine.AddQuarter();
			std::cout << "You inserted a quarter\n";
		}
	}
	void EjectQuarter() override
	{
		std::cout << "Quarters returned\n";
		m_gumballMachine.ReleaseAllQuarter();
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		m_gumballMachine.ReleaseQuarter();
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}
	void FillMachine(unsigned const gumballs) override
	{
		if (gumballs != 0)
		{
			std::cout << "gumballs added";
			m_gumballMachine.AddGumballs(gumballs);
		}
	}
private:
	IGumballMachine& m_gumballMachine;
};

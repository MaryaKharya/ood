#pragma once
#include "IState.h"
#include "IGumballMachine.h"

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Quarters returned\n";
		m_gumballMachine.ReleaseAllQuarter();
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "sold out";
	}
	void FillMachine(unsigned const gumballs) override
	{
		if (gumballs != 0)
		{
			std::cout << "gumballs added";
			m_gumballMachine.AddGumballs(gumballs);
			if (m_gumballMachine.GetQuarterCount() == 0)
			{
				m_gumballMachine.SetNoQuarterState();
			}
			else
			{
				m_gumballMachine.SetHasQuarterState();
			}
		}
	}
private:
	IGumballMachine& m_gumballMachine;
};

#pragma once
#include "IState.h"
#include "IGumballMachine.h"

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}
	void InsertQuarter() override
	{
		std::cout << "We're already giving you a gumball\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Sorry you already turned the crank\n";
	}
	void TurnCrank() override
	{
		std::cout << "Turning twice doesn't get you another gumball\n";
	}
	void Dispense() override
	{
		m_gumballMachine.ReleaseQuarter();
		m_gumballMachine.ReleaseBall();

		if (m_gumballMachine.GetQuarterCount() == 0)
		{
			m_gumballMachine.SetNoQuarterState();
		}
		else
		{
			m_gumballMachine.SetHasQuarterState();
		}

		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
	}
	std::string ToString() const override
	{
		return "delivering a gumball";
	}
private:
	IGumballMachine& m_gumballMachine;
};

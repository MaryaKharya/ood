#pragma once
#include "IState.h"
#include "IGumballMachine.h"
#include "boost/format.hpp"
#include "CHasQuarterState.h"
#include "CHasAllQuartersState.h"
#include "CNoQuarterState.h"
#include "CSoldOutState.h"
#include "CSoldState.h"

class CGumballMachine : private IGumballMachine
{
public:
	CGumballMachine(unsigned numBalls)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_count(numBalls)
	{
		if (m_count > 0)
		{
			m_state = &m_noQuarterState;
		}
	}
	void EjectQuarter()
	{
		m_state->EjectQuarter();
	}
	void InsertQuarter()
	{
		m_state->InsertQuarter();
	}
	void TurnCrank()
	{
		m_state->TurnCrank();
		m_state->Dispense();
	}
	void FillMachine(unsigned const gumballs)
	{
		m_state->FillMachine(gumballs);
	}

	std::string ToString()const
	{
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inserted quarters: %1%
Inventory: %2% gumball%3%
Machine is %4%
)");
		return (fmt % m_quarter % m_count % (m_count != 1 ? "s" : "") % m_state->ToString()).str();
	}
private:
	unsigned GetBallCount() const override
	{
		return m_count;
	}
	unsigned GetQuarterCount() const override
	{
		return m_quarter;
	}
	virtual void ReleaseBall() override
	{
		if (m_count != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_count;
		}
	}
	virtual void AddQuarter() override
	{
		++m_quarter;
	}

	void AddGumballs(unsigned const gumballs) override
	{
		m_count += gumballs;
	}

	virtual void ReleaseQuarter() override
	{
		if (m_quarter != 0)
		{
			--m_quarter;
		}
	}

	virtual void ReleaseAllQuarter() override
	{
		if (m_quarter != 0)
		{
			m_quarter = 0;
		}
	}

	void SetSoldOutState() override
	{
		m_state = &m_soldOutState;
	}
	void SetNoQuarterState() override
	{
		m_state = &m_noQuarterState;
	}
	void SetSoldState() override
	{
		m_state = &m_soldState;
	}
	void SetHasQuarterState() override
	{
		m_state = &m_hasQuarterState;
	}
private:
	unsigned m_count = 0;
	unsigned m_quarter = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState* m_state;

};
#pragma once
#include <iostream>

struct IGumballMachine
{
	virtual void ReleaseBall() = 0;
	virtual void ReleaseQuarter() = 0;
	virtual void ReleaseAllQuarter() = 0;
	virtual void AddQuarter() = 0;
	virtual void AddGumballs(unsigned const gumballs) = 0;
	virtual unsigned GetBallCount()const = 0;
	virtual unsigned GetQuarterCount()const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};

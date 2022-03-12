#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include <set>
#include "../lw8/CGumballMachine.h"
#include "boost/format.hpp"
#include "../../catch2/catch.hpp"

SCENARIO("Gumball Machine is empty")
{
	CGumballMachine gumballMachine(0);
	WHEN("there is no action")
	{
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 0 gumballs\nMachine is sold out\n");
	}
	WHEN("eject quarter")
	{
		gumballMachine.EjectQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 0 gumballs\nMachine is sold out\n");
	}
	WHEN("insert quarter")
	{
		gumballMachine.InsertQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 0 gumballs\nMachine is sold out\n");
	}
	WHEN("turn crank")
	{
		gumballMachine.TurnCrank();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 0 gumballs\nMachine is sold out\n");
	}
}


SCENARIO("Gumball Machine has gumball, but quarter is not inserted")
{
	CGumballMachine gumballMachine(1);
	WHEN("there is no action")
	{
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 1 gumball\nMachine is waiting for quarter\n");
	}
	WHEN("eject quarter")
	{
		gumballMachine.EjectQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 1 gumball\nMachine is waiting for quarter\n");
	}
	WHEN("insert quarter")
	{
		gumballMachine.InsertQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 1 gumball\nMachine is waiting for turn of crank\n");

	}
	WHEN("turn crank")
	{
		gumballMachine.TurnCrank();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 1 gumball\nMachine is waiting for quarter\n");

	}
}

SCENARIO("Gumball Machine has 1 gumball and quarter is inserted")
{
	CGumballMachine gumballMachine(1);
	gumballMachine.InsertQuarter();
	WHEN("there is no action")
	{
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 1 gumball\nMachine is waiting for turn of crank\n");
	}
	WHEN("eject quarter")
	{
		gumballMachine.EjectQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 1 gumball\nMachine is waiting for quarter\n");
	}
	WHEN("insert quarter")
	{
		gumballMachine.InsertQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 1 gumball\nMachine is waiting for turn of crank\n");

	}
	WHEN("turn crank")
	{
		gumballMachine.TurnCrank();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 0 gumballs\nMachine is sold out\n");
	}
}

SCENARIO("Gumball Machine has some gumballs and quarter is inserted")
{
	CGumballMachine gumballMachine(3);
	gumballMachine.InsertQuarter();
	WHEN("turn crank")
	{
		gumballMachine.TurnCrank();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: 2 gumballs\nMachine is waiting for quarter\n");
	}
}

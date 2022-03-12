#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include <set>
#include "CGumballMachine.h"
#include "boost/format.hpp"
#include "../../catch2/catch.hpp"

SCENARIO("Gumball Machine is empty")
{
	CGumballMachine gumballMachine(0);
	WHEN("there is no action")
	{
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 0 gumballs\nMachine is sold out\n");
	}
	WHEN("eject quarter")
	{
		gumballMachine.EjectQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 0 gumballs\nMachine is sold out\n");
	}
	WHEN("insert quarter")
	{
		gumballMachine.InsertQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 0 gumballs\nMachine is sold out\n");
	}
	WHEN("turn crank")
	{
		gumballMachine.TurnCrank();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 0 gumballs\nMachine is sold out\n");
	}
	WHEN("fill machine with 0 gumballs")
	{
		gumballMachine.FillMachine(0);
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 0 gumballs\nMachine is sold out\n");
	}
	WHEN("fill machine with some gumballs")
	{
		gumballMachine.FillMachine(2);
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 2 gumballs\nMachine is waiting for quarter\n");
	}
}

SCENARIO("Gumball Machine has gumball, but quarter is not inserted")
{
	CGumballMachine gumballMachine(1);
	WHEN("there is no action")
	{
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 1 gumball\nMachine is waiting for quarter\n");
	}
	WHEN("eject quarter")
	{
		gumballMachine.EjectQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 1 gumball\nMachine is waiting for quarter\n");
	}
	WHEN("insert quarter")
	{
		gumballMachine.InsertQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 1\nInventory: 1 gumball\nMachine is waiting for turn of crank\n");

	}
	WHEN("turn crank")
	{
		gumballMachine.TurnCrank();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 1 gumball\nMachine is waiting for quarter\n");
	}
	WHEN("fill machine with 0 gumballs")
	{
		gumballMachine.FillMachine(0);
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 1 gumball\nMachine is waiting for quarter\n");
	}
	WHEN("fill machine with some gumballs")
	{
		gumballMachine.FillMachine(2);
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 3 gumballs\nMachine is waiting for quarter\n");
	}
}

SCENARIO("Gumball Machine has 1 gumball and quarter is inserted")
{
	CGumballMachine gumballMachine(1);
	gumballMachine.InsertQuarter();
	WHEN("there is no action")
	{
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 1\nInventory: 1 gumball\nMachine is waiting for turn of crank\n");
	}
	WHEN("eject quarter")
	{
		gumballMachine.EjectQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 1 gumball\nMachine is waiting for quarter\n");
	}
	WHEN("insert quarter")
	{
		gumballMachine.InsertQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 2\nInventory: 1 gumball\nMachine is waiting for turn of crank\n");

	}
	WHEN("turn crank")
	{
		gumballMachine.TurnCrank();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 0 gumballs\nMachine is sold out\n");
	}
	WHEN("fill machine with 0 gumballs")
	{
		gumballMachine.FillMachine(0);
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 1\nInventory: 1 gumball\nMachine is waiting for turn of crank\n");
	}
	WHEN("fill machine with some gumballs")
	{
		gumballMachine.FillMachine(2);
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 1\nInventory: 3 gumballs\nMachine is waiting for turn of crank\n");
	}
}

SCENARIO("Gumball Machine has some gumballs and quarter is inserted")
{
	CGumballMachine gumballMachine(3);
	gumballMachine.InsertQuarter();
	WHEN("turn crank")
	{
		gumballMachine.TurnCrank();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 2 gumballs\nMachine is waiting for quarter\n");
	}
}

SCENARIO("Insert some quarter")
{
	CGumballMachine gumballMachine(3);
	gumballMachine.InsertQuarter();
	gumballMachine.InsertQuarter();
	gumballMachine.InsertQuarter();
	gumballMachine.InsertQuarter();
	gumballMachine.InsertQuarter();
	WHEN("there is no action")
	{
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 5\nInventory: 3 gumballs\nMachine is waiting for turn of crank\n");
	}
	WHEN("insert quarter")
	{
		gumballMachine.InsertQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 5\nInventory: 3 gumballs\nMachine is waiting for turn of crank\n");
	}
	WHEN("eject quarter")
	{
		gumballMachine.EjectQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 3 gumballs\nMachine is waiting for quarter\n");
	}
	WHEN("turn crank")
	{
		gumballMachine.TurnCrank();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 4\nInventory: 2 gumballs\nMachine is waiting for turn of crank\n");
	}
	WHEN("turn crank and insert quarter")
	{
		gumballMachine.TurnCrank();
		gumballMachine.TurnCrank();
		gumballMachine.InsertQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 4\nInventory: 1 gumball\nMachine is waiting for turn of crank\n");
	}

	WHEN("eject quarter if Gumball Machine is empty")
	{
		gumballMachine.TurnCrank();
		gumballMachine.TurnCrank();
		gumballMachine.TurnCrank();
		gumballMachine.TurnCrank();
		gumballMachine.EjectQuarter();
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 0\nInventory: 0 gumballs\nMachine is sold out\n");
	}
	WHEN("fill empty machine with some gumballs with quarters")
	{
		gumballMachine.TurnCrank();
		gumballMachine.TurnCrank();
		gumballMachine.TurnCrank();
		gumballMachine.FillMachine(2);
		CHECK(gumballMachine.ToString() == "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInserted quarters: 2\nInventory: 2 gumballs\nMachine is waiting for turn of crank\n");
	}
}
#include "CMenu.h" 
#include "CGumballMachine.h"

int main()
{
	CMenu menu;
	CGumballMachine gumballMachine(3);

	menu.AddItem("info", "Info", [&] { std::cout << gumballMachine.ToString(); });
	menu.AddItem("insertQuarter", "Insert quarter", [&] { gumballMachine.InsertQuarter(); });
	menu.AddItem("ejectQuarter", "Eject quarter", [&] { gumballMachine.EjectQuarter(); });
	menu.AddItem("turnCrank", "Turn crank", [&] { gumballMachine.TurnCrank(); });
	menu.Run();
}

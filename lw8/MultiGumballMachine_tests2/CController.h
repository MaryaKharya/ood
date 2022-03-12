#pragma once
#include <functional>
#include <fstream>
#include <string>
#include "CMenu.h"
#include "CGumballMachine.h"

using namespace std;
using namespace std::placeholders;

class CEditor
{
public:
	CEditor(std::istream& fileIn, std::ostream& fileOut, CGumballMachine& gumballMachine)  //-V730
		:m_fileIn(fileIn)
		, m_fileOut(fileOut)
		, m_gumballMachine(gumballMachine)
	{
		m_menu.AddItem("info", "Info", [this] { m_fileOut << m_gumballMachine.ToString(); });
		m_menu.AddItem("insertQuarter", "Insert quarter", [this]{ m_gumballMachine.InsertQuarter(); });
		m_menu.AddItem("ejectQuarter", "Eject quarter", [this] { m_gumballMachine.EjectQuarter(); });
		m_menu.AddItem("turnCrank", "Turnin crank", [this]{ m_gumballMachine.TurnCrank(); });
		m_menu.AddItem("fillMachine", "Fill machine <number of balls>", [this]() { m_gumballMachine.FillMachine(); });
	}

	void Start();

private:
	// ”казатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::* MenuHandler)(istream& in);

	void AddMenuItem(const string& shortcut, const string& description, MenuHandler handler);

	// TODO: скипнуть первый пробел элегантнее
	void SetTitle(istream& in);

	void InsertParagraph(istream& in);

	void List(istream&);

	void Undo(istream&);

	void Redo(istream&);

	CMenu m_menu;
	std::istream& m_fileIn;
	std::ostream& m_fileOut;
	CGumballMachine m_gumballMachine;
};
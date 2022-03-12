#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace naive
{
	class CGumballMachine
	{
	public:
		enum class State
		{
			SoldOut,		// ������ �����������
			NoQuarter,		// ��� �������
			HasQuarter,		// ���� �������
			Sold,			// ������� ������
		};

		CGumballMachine(unsigned count)
			: m_count(count)
			, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		{
		}

		void InsertQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				cout << "You can't insert a quarter, the machine is sold out\n";
				break;
			case State::NoQuarter:
				cout << "You inserted a quarter\n";
				m_countQuarter++;
				m_state = State::HasQuarter;
				break;
			case State::HasQuarter:
				if (m_countQuarter != 5)
				{
					cout << "You inserted a quarter\n";
					m_countQuarter++;
				}
				else
				{
					cout << "You can't insert another quarter\n";
				}
				break;
			case State::Sold:
				cout << "Please wait, we're already giving you a gumball\n";
				break;
			}
		}

		void EjectQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::HasQuarter:
				cout << "Quarter returned\n";
				m_countQuarter = 0;
				m_state = State::NoQuarter;
				break;
			case State::NoQuarter:
				cout << "You haven't inserted a quarter\n";
				break;
			case State::Sold:
				cout << "Sorry you already turned the crank\n";
				break;
			case State::SoldOut:
				cout << "You can't eject, you haven't inserted a quarter yet\n";
				m_countQuarter = 0;
				break;
			}
		}

		void TurnCrank()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				cout << "You turned but there's no gumballs\n";
				break;
			case State::NoQuarter:
				cout << "You turned but there's no quarter\n";
				break;
			case State::HasQuarter:
				cout << "You turned...\n";
				m_countQuarter--;
				m_state = State::Sold;
				Dispense();
				break;
			case State::Sold:
				cout << "Turning twice doesn't get you another gumball\n";
				break;
			}
		}

		void Refill(unsigned numBalls)
		{
			m_count = numBalls;
			m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
		}

		std::string ToString()const
		{
			std::string state =
				(m_state == State::SoldOut) ? "sold out" :
				(m_state == State::NoQuarter) ? "waiting for quarter" :
				(m_state == State::HasQuarter) ? "waiting for turn of crank"
				: "delivering a gumball";
			auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 
Inserted quarters: %4%
Inventory: %1% gumball%2%
Machine is %3%
)");
			return (fmt % m_count % (m_count != 1 ? "s" : "") % state % m_countQuarter).str();
		}

	private:
		void Dispense()
		{
			using namespace std;
			switch (m_state)
			{
			case State::Sold:
				cout << "A gumball comes rolling out the slot\n";
				--m_count;
				if (m_countQuarter == 0)
				{
					m_state = State::NoQuarter;
				}
				else
				{
					m_state = State::HasQuarter;
				}
				if (m_count == 0)
				{
					cout << "Oops, out of gumballs\n";
					m_state = State::SoldOut;
				}
				break;
			case State::NoQuarter:
				cout << "You need to pay first\n";
				break;
			case State::SoldOut:
			case State::HasQuarter:
				cout << "No gumball dispensed\n";
				break;
			}
		}

		unsigned m_count;	// ���������� �������
		unsigned m_countQuarter = 0;
		State m_state = State::SoldOut;
	};
}
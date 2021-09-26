#include <cassert>
#include <iostream>
#include <functional>
#include <memory>
#include <vector>

using namespace std;
using IFlyBehavior = function<void()>;
using IQuackBehavior = function<void()>;
using IDanceBehavior = function<void()>;

void FlyBehavior()
{
	int x = 0;
	auto l = [x]() mutable
	{
		++x;
		cout << "I'm flying with wings!! " << x << endl;
		//return x;
	};
	l();
}

void FlyNoWay()
{
};

void QuackBehavior()
{
	cout << "Quack Quack!!!" << endl;
}

void SqueakBehavior()
{
	cout << "Squeek!!!" << endl;
}

void MuteQuackBehavior()
{
};

void DanceMinuetBehavior()
{
	std::cout << "I'm dancing minuet!\n";
};

void DanceWaltzBehavior()
{
	std::cout << "I'm dancing waltz!\n";
};

void DanceNoWay()
{
};

class Duck
{
public:
	Duck(IFlyBehavior&& flyBehavior,
		IQuackBehavior&& quackBehavior,
		IDanceBehavior&& danceBehavior)
		: m_quackBehavior(move(quackBehavior))
		, m_danceBehavior(move(danceBehavior))
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(move(flyBehavior));
	}
	void Quack() const
	{
		if (m_quackBehavior)
		{
			m_quackBehavior();
		}
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		if (m_flyBehavior)
		{
			m_flyBehavior();
		}
	}
	void Dance() const
	{
		if (m_danceBehavior)
		{
			m_danceBehavior();
		}
	}
	void SetFlyBehavior(IFlyBehavior&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = move(flyBehavior);
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	IFlyBehavior m_flyBehavior;
	IQuackBehavior m_quackBehavior;
	IDanceBehavior m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyBehavior, QuackBehavior, DanceMinuetBehavior)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyBehavior, QuackBehavior, DanceWaltzBehavior)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay, MuteQuackBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, SqueakBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyBehavior(FlyNoWay);
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyBehavior(FlyBehavior);
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

}
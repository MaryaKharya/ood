#include <cassert>
#include <iostream>
#include <functional>
#include <memory>
#include <vector>

using namespace std;
using IFlyBehavior = function<void()>;
using IQuackBehavior = function<void()>;
using IDanceBehavior = function<void()>;


void Fly()
{
	cout << "I'm flying with wings!!" << endl;
}

void FlyNoWay()
{
};

void Quack()
{
	cout << "Quack Quack!!!" << endl;
}

void Squeak()
{
	cout << "Squeek!!!" << endl;
}

void MuteQuack()
{
};

void DanceMinuet()
{
	std::cout << "I'm dancing minuet!\n";
};

void DanceWaltz()
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
	void oQuack() const
	{
		m_quackBehavior();
	}
	void oSwim()
	{
		cout << "I'm swimming" << endl;
	}
	void oFly()
	{
		m_flyBehavior();
	}
	void Dance() const
	{
		m_danceBehavior();
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
		: Duck(Fly, Quack, DanceMinuet)
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
		: Duck(Fly, Quack, DanceWaltz)
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
		: Duck(FlyNoWay, MuteQuack, DanceNoWay)
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
		: Duck(FlyNoWay, Squeak, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, Quack, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.oQuack();
	duck.oFly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(Fly);
	PlayWithDuck(modelDuck);
}
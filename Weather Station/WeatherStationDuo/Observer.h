#pragma once

#include <set>
#include <map>
#include <functional>

template <typename T>
class IObservable;

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, IObservable<T> const& observable) = 0;
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		m_observers.emplace(abs(priority), &observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto it = m_observers.rbegin(); it != m_observers.rend(); it++)
		{
			it->second->Update(data, *this);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto it = m_observers.rbegin(); it != m_observers.rend(); it++)
		{
			if (it->second == &observer)
			{
				m_observers.erase(it->first);
				break;
			}
		}
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	std::multimap<int, ObserverType*> m_observers;
};


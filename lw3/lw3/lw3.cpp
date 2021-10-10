#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;



int main()
{
	auto tea = make_unique<CTea>(TeaType::Black);
	std::cout << tea->GetDescription() << " " << tea->GetCost() << "\n";
	// добавляем корицы
	auto cinnamon = make_unique<CCinnamon>(move(tea));
	// добавляем пару долек лимона
	auto lemon = make_unique<CLemon>(move(cinnamon), 2);
	// добавляем пару кубиков льда
	auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
	// добавляем 2 грамма шоколадной крошки
	auto beverage = make_unique<CChocolateCrumbs>(move(iceCubes), 2);
	std::cout << beverage->GetDescription() << " " << beverage->GetCost() << "\n";
}
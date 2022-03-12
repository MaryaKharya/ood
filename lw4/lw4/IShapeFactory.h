#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class CShape;

struct IShapeFactory
{
	virtual std::unique_ptr<CShape> CreateShape(const std::string& description) = 0;

	virtual ~IShapeFactory() = default;
};
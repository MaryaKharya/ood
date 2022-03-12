#include "CShapeFactory.h"
#include <sstream>

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string& description)
{
	std::istringstream stream(description);
	std::string name;
	stream >> name;
	if (name == "ellipse")
	{
		return CreateEllipse(stream);
	}
	else if (name == "triangle")
	{
		return CreateTriangle(stream);
	}
	else if (name == "rectangle")
	{
		return CreateRectangle(stream);
	}
	else if (name == "polygon")
	{
		return CreateRegularPolygon(stream);
	}
	else
	{
		throw std::invalid_argument("there is no such figure");
	}
}

std::unique_ptr<CRectangle> CShapeFactory::CreateRectangle(std::istringstream& stream) const
{
	float x, y, width, height;
	std::string color;
	stream >> x >> y >> width >> height >> color;
	if (stream.fail())
	{
		throw std::invalid_argument("incorrect input");
	}

	CRectangle rectangle(GetColor(color), { x, y }, { x + width, y + height});
	return std::make_unique<CRectangle>(rectangle);
}

std::unique_ptr<CEllipse> CShapeFactory::CreateEllipse(std::istringstream& stream) const
{
	float x, y, radiusX, radiusY;
	std::string color;
	stream >> x >> y >> radiusX >> radiusY >> color;
	if (stream.fail())
	{
		throw std::invalid_argument("incorrect input");
	}
	CEllipse ellipse(GetColor(color), { x, y }, radiusX, radiusY);
	return std::make_unique<CEllipse>(ellipse);
}

std::unique_ptr<CTriangle> CShapeFactory::CreateTriangle(std::istringstream& stream) const
{
	float x1, y1, x2, y2, x3, y3;
	std::string color;
	stream >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> color;
	if (stream.fail())
	{
		throw std::invalid_argument("incorrect input");
	}
	CTriangle triangle(GetColor(color), { x1, y1 }, { x2, y2 }, { x3, y3 });
	return std::make_unique<CTriangle>(triangle);
}

std::unique_ptr<CRegularPolygon> CShapeFactory::CreateRegularPolygon(std::istringstream& stream) const
{
	float vertexCount, x, y, radius;
	std::string color;
	stream >> vertexCount >> x >> y >> radius >> color;
	if (stream.fail())
	{
		throw std::invalid_argument("incorrect input");
	}
	CRegularPolygon regularPolygon(GetColor(color), vertexCount, {x, y}, radius);
	return std::make_unique<CRegularPolygon>(regularPolygon);
}

Color CShapeFactory::GetColor(std::string const& color) const
{
	if (color == "green")
	{
		return Color::Green;
	}
	else if (color == "red")
	{
		return Color::Red;
	}
	else if (color == "blue")
	{
		return Color::Blue;
	}
	else if (color == "yellow")
	{
		return Color::Yellow;
	}
	else if (color == "pink")
	{
		return Color::Pink;
	}
	else if (color == "black")
	{
		return Color::Black;
	}
	else
	{
		throw std::invalid_argument("Invalid color");
	}
}
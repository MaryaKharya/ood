#pragma once
#include "CPoint.h"
#include "ICanvas.h"
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>
#undef min
#undef max
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);
	void SetColor(const Color& color) override;
	void DrawLine(const CPoint & from, const CPoint & to) override;
	void DrawEllipse(float radiusX, float radiusY, const CPoint& center) override;
	void DrawRegularPolygon(float radius, const CPoint& center, float vertexCount) override;
private:
	sf::Color m_color;
	sf::RenderWindow& m_window;
};
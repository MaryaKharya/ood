#include <iostream>
#include "CCanvas.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>

CCanvas::CCanvas(sf::RenderWindow& window)
	:m_window(window)
{
}

void CCanvas::SetColor(const Color& color)
{
	switch (color)
	{
	case Color::Green:
		m_color = sf::Color::Green;
		break;
	case Color::Red:
		m_color = sf::Color::Red;
		break;
	case Color::Blue:
		m_color = sf::Color::Blue;
		break;
	case Color::Yellow:
		m_color = sf::Color::Yellow;
		break;
	case Color::Pink:
		m_color = sf::Color(255, 20, 148);
		break;
	case Color::Black:
		m_color = sf::Color::Black;
		break;
	}
}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(from.x, from.y);
	line[0].color = m_color;
	line[1].position = sf::Vector2f(to.x, to.y);
	line[1].color = m_color;
	m_window.draw(line);
}

void CCanvas::DrawEllipse(float radiusX, float radiusY, const CPoint& center)
{
	sf::CircleShape circle(radiusX);
	circle.setPosition(center.x - radiusX, center.y - radiusY);
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(m_color);
	circle.scale(1, radiusY / radiusX);
	m_window.draw(circle);
}
void CCanvas::DrawRegularPolygon(float radius, const CPoint& center, float vertexCount)
{
	sf::CircleShape circle(radius, static_cast<size_t>(vertexCount));
	circle.setPosition(center.x - radius, center.y - radius);
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(m_color);
	m_window.draw(circle);
}
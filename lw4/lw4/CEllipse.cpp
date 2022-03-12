#include <iostream>
#include "CEllipse.h"
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#define M_PI (3.141592653589793)

CEllipse::CEllipse(const Color& color, const CPoint& center, float radiusX, float radiusY)
	: CShape(color)
	, m_center(center)
	, m_radiusX(radiusX)
	, m_radiusY(radiusY)
{
}

void CEllipse::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawEllipse(m_radiusX, m_radiusY, m_center);
}

float CEllipse::GetHorizontalRadius() const
{
	return m_radiusX;
}

float CEllipse::GetVerticalRadius() const
{
	return m_radiusY;
}

CPoint CEllipse::GetCenter() const
{
	return m_center;
}
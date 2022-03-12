#include <iostream>
#include "CRegularPolygon.h"
#include <string>
#include <iomanip>

CRegularPolygon::CRegularPolygon(const Color& color, float vertexCount, const CPoint& center, float radius)
	: CShape(color)
	, m_vertexCount(vertexCount)
	, m_center(center)
	, m_radius(radius)
{
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawRegularPolygon(m_radius, m_center, m_vertexCount);
}

float CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

CPoint CRegularPolygon::GetCenter() const
{
	return m_center;
}

float CRegularPolygon::GetRadius() const
{
	return m_radius;
}
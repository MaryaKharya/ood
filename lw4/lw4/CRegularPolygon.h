#pragma once
#include <string>
#include "Shape.h"
#include "CPoint.h"
#include "EColor.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(const Color& color, float vertexCount, const CPoint& center, float radius);
	float GetVertexCount() const;
	CPoint GetCenter() const;
	float GetRadius() const;
	void Draw(ICanvas& canvas) const;

private:
	float m_vertexCount;
	CPoint m_center;
	float m_radius;
};

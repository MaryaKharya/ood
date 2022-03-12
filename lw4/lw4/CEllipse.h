#pragma once
#include <string>
#include "Shape.h"
#include "CPoint.h"
#include "EColor.h"

class CEllipse : public CShape
{
public:
	CEllipse(const Color& color, const CPoint& center, float radiusX, float radiusY);
	float GetHorizontalRadius() const;
	float GetVerticalRadius() const;
	CPoint GetCenter() const;
	void Draw(ICanvas& canvas) const;

private:
	CPoint m_center;
	float m_radiusX;
	float m_radiusY;
};
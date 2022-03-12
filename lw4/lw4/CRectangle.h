#pragma once
#include <string>
#include "Shape.h"
#include "CPoint.h"
#include "EColor.h"

class CRectangle : public CShape
{
public:
	CRectangle(const Color& color, const CPoint& leftTop, const CPoint& rightBottom);
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	void Draw(ICanvas& canvas) const;

private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
};
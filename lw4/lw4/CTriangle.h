#pragma once
#include <string>
#include "Shape.h"
#include "CPoint.h"
#include "EColor.h"

class CTriangle: public CShape
{
public:
	CTriangle(const Color& color, const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3);
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	void Draw(ICanvas& canvas) const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};

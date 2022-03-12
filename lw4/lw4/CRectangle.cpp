#include <iostream>
#include "CRectangle.h"
#include <string>
#include <iomanip>

CRectangle::CRectangle(const Color& color, const CPoint& leftTop, const CPoint& rightBottom)
	: CShape(color)
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{
}

void CRectangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_leftTop, { m_rightBottom.x, m_leftTop.y });
	canvas.DrawLine({ m_rightBottom.x, m_leftTop.y }, m_rightBottom);
	canvas.DrawLine(m_rightBottom, {m_leftTop.x, m_rightBottom.y});
	canvas.DrawLine({ m_leftTop.x, m_rightBottom.y }, m_leftTop);
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

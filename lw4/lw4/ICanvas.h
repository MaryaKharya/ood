#pragma once
#include "CPoint.h"
#include "EColor.h"
#include <string>
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void SetColor(const Color& color) = 0;
	virtual void DrawLine(const CPoint& from, const CPoint& to) = 0;
	virtual void DrawEllipse(float radiusX, float radiusY, const CPoint& center) = 0;
	virtual void DrawRegularPolygon(float radius,  const CPoint& center, float vertexCount) = 0;
};
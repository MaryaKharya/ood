#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include <set>
#include "../AdapterClass/app.h"
#include "boost/format.hpp"
#include "../../catch2/catch.hpp"

SCENARIO("Graphic lib tests")
{
	graphics_lib::CCanvas canvas;
	std::ostringstream out;
	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	WHEN("Move to some coordinates")
	{
		canvas.MoveTo(10, 14);
		std::cout.rdbuf(coutbuf);
		CHECK(out.str() == "MoveTo (10, 14)\n");
	}
	WHEN("Line to some coordinates")
	{
		canvas.LineTo(-8, 0);
		std::cout.rdbuf(coutbuf);
		CHECK(out.str() == "LineTo (-8, 0)\n");
	}
	WHEN("Set some color")
	{
		canvas.SetColor(0x34582c);
		std::cout.rdbuf(coutbuf);
		CHECK(out.str() == "SetColor (#34582c)\n");
	}
}

SCENARIO("Shape lib triangle test")
{
	graphics_lib::CCanvas canvas;
	shape_drawing_lib::CCanvasPainter painter(canvas);
	shape_drawing_lib::CTriangle triangle({ 1, 5 }, { 2, 0 }, { -3, 20 }, 0xffff45);
	std::ostringstream out;
	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	painter.Draw(triangle);
	std::cout.rdbuf(coutbuf);
	CHECK(out.str() == "SetColor (#ffff45)\nMoveTo (1, 5)\nLineTo (2, 0)\nLineTo (-3, 20)\nLineTo (1, 5)\n");
}

SCENARIO("Shape lib rectangle test")
{
	graphics_lib::CCanvas canvas;
	shape_drawing_lib::CCanvasPainter painter(canvas);
	shape_drawing_lib::CRectangle rectangle({ 90, 460 }, 5, 8, 0xf67645);
	std::ostringstream out;
	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	painter.Draw(rectangle);
	std::cout.rdbuf(coutbuf);
	CHECK(out.str() == "SetColor (#f67645)\nMoveTo (90, 460)\nLineTo (95, 460)\nLineTo (95, 468)\nLineTo (90, 468)\nLineTo (90, 460)\n");
}

SCENARIO("Modern lib tests")
{
	std::ostringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	WHEN("Begin draw")
	{
		CHECK_NOTHROW(renderer.BeginDraw());
		CHECK(out.str() == "<draw>\n");
	}
	WHEN("Eegin draw double")
	{
		renderer.BeginDraw();
		CHECK_THROWS_AS(renderer.BeginDraw(), logic_error);
		CHECK(out.str() == "<draw>\n");
	}
	WHEN("End draw if begin draw")
	{
		renderer.BeginDraw();
		CHECK_NOTHROW(renderer.EndDraw());
		CHECK(out.str() == "<draw>\n</draw>\n");
	}
	WHEN("End draw if don't begin draw")
	{
		CHECK_THROWS_AS(renderer.EndDraw(), logic_error);
	}

	WHEN("Draw line after begin draw")
	{
		renderer.BeginDraw();
		CHECK_NOTHROW(renderer.DrawLine({ 9, 5 }, { 8, -89 }, { 0.677f, 0.343f, 0.00000f, 1.0f }));
		CHECK(out.str() == "<draw>\n  <line fromX=\"9\" fromY=\"5\" toX=\"8\" toY=\"-89\"/>\n    <color r=\"0.68\" g=\"0.34\" b=\"0.00\" a=\"1.00\"/>\n  </line>\n");
	}

	WHEN("Draw line if don't begin draw")
	{
		CHECK_THROWS_AS(renderer.DrawLine({ 9, 5 }, { 8, -89 }, { 0.677f, 0.343f, 0.00000f, 1.0f }), logic_error);
	}
	WHEN("Draw line after end draw")
	{
		renderer.BeginDraw();
		renderer.EndDraw();
		CHECK_THROWS_AS(renderer.DrawLine({ 9, 5 }, { 8, -89 }, { 0.677f, 0.343f, 0.00000f, 1.0f }), logic_error);
	}
}

SCENARIO("Adapter class tests")
{
	std::ostringstream out;
	app::ModernGraphicsAdapter adapter(out);
	WHEN("Move to")
	{
		adapter.MoveTo(4, 7);
		modern_graphics_lib::CPoint point = adapter.GetPoint();
		CHECK(point.x == 4);
		CHECK(point.y == 7);
	}
	WHEN("Set color")
	{
		adapter.SetColor(0xffffff);
		modern_graphics_lib::CRGBAColor color = adapter.GetColor();
		CHECK(color.r - 1.00f < 0.01);
		CHECK(color.g - 1.00f < 0.01);
		CHECK(color.b - 1.00f < 0.01);
		CHECK(color.a == 1.00f);
	}

	WHEN("Line to")
	{
		adapter.BeginDraw();
		adapter.LineTo(-7, 9);
		adapter.EndDraw();
		CHECK(out.str() == "<draw>\n  <line fromX=\"0\" fromY=\"0\" toX=\"-7\" toY=\"9\"/>\n    <color r=\"0.00\" g=\"0.00\" b=\"0.00\" a=\"1.00\"/>\n  </line>\n</draw>\n");
	}
}

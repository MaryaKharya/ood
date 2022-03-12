#pragma once
#include "shape_drawing_lib.h"
#include "modern_graphic_lib.h"
namespace app
{
	class ModernGraphicsAdapter : public graphics_lib::ICanvas, public modern_graphics_lib::CModernGraphicsRenderer
	{
	public:
		ModernGraphicsAdapter(std::ostream& strm)
			: modern_graphics_lib::CModernGraphicsRenderer(strm)
		{
		}

		void MoveTo(int x, int y) override
		{
			m_point = { x, y };
		}

		void LineTo(int x, int y) override
		{
			DrawLine(m_point, { x, y }, m_color);
			m_point = { x, y };
		}

		void SetColor(uint32_t rgbColor) override
		{
			m_color.r = ((rgbColor >> 16) & 0xff) / 255.0f;
			m_color.g = ((rgbColor >> 8) & 0xff) / 255.0f;
			m_color.b = (rgbColor & 0xff) / 255.0f;
		}

		//для тестов
		modern_graphics_lib::CPoint GetPoint()
		{
			return m_point;
		}

		modern_graphics_lib::CRGBAColor GetColor()
		{
			return m_color;
		}

	private:
		modern_graphics_lib::CPoint m_point = { 0, 0 };
		modern_graphics_lib::CRGBAColor m_color = { 0.0, 0.0, 0.0, 1.0 };
	};

	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xff2323);
		CRectangle rectangle({ 30, 40 }, 18, 24);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
		try
		{
			ModernGraphicsAdapter canvas(cout);
			canvas.BeginDraw();
			shape_drawing_lib::CCanvasPainter canvasPainter(canvas);

			PaintPicture(canvasPainter);
			canvas.EndDraw();
		}
		catch (logic_error e)
		{
			cout << e.what() << "\n";
		}
		// TODO: при помощи существующей функции PaintPicture() нарисовать
		// картину на renderer
		// Подсказка: используйте паттерн "Адаптер"
	}

}

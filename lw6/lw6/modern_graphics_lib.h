#pragma once
#include "graphic_lib.h"
#include <fstream>
#include "boost/format.hpp"
// ѕространство имен современной графической библиотеки (недоступно дл€ изменени€)
namespace modern_graphics_lib
{
    class CPoint
    {
    public:
        CPoint(int x, int y) 
            :x(x), 
            y(y) 
        {
        }

        int x;
        int y;
    };

    class CRGBAColor
    {
    public:
        CRGBAColor(float r, float g, float b, float a) 
            :r(r)
            , g(g)
            , b(b)
            , a(a)
        {
        }
        float r, g, b, a;
    };


    //  ласс дл€ современного рисовани€ графики
    class CModernGraphicsRenderer
    {
    public:
        CModernGraphicsRenderer(ostream& strm) 
            : m_out(strm)
        {
        }

        ~CModernGraphicsRenderer()
        {
            if (m_drawing) // «авершаем рисование, если оно было начато
            {
                EndDraw();
            }
        }

        // Ётот метод должен быть вызван в начале рисовани€
        void BeginDraw()
        {
            if (m_drawing)
            {
                throw logic_error("Drawing has already begun");
            }
            m_out << "<draw>" << endl;
            m_drawing = true;
        }

        // ¬ыполн€ет рисование линии
        void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
        {
            if (!m_drawing)
            {
                throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
            }			
            m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"/>)") % start.x % start.y % end.x % end.y << std::endl;
            m_out << boost::format(R"(    <color r="%1$.2f" g="%2$.2f" b="%3$.2f" a="%4$.2f"/>)") % color.r % color.g % color.b % color.a << std::endl;
            m_out << "  </line>\n";
        }

        // Ётот метод должен быть вызван в конце рисовани€
        void EndDraw()
        {
            if (!m_drawing)
            {
                throw logic_error("Drawing has not been started");
            }
            m_out << "</draw>" << endl;
            m_drawing = false;
        }
    private:
        ostream& m_out;
        bool m_drawing = false;
    };
}

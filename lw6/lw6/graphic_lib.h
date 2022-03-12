#pragma once
#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

namespace graphics_lib
{
    // ����� ��� ���������
    class ICanvas
    {
    public:
        // ������ "����" � ����� x, y
        virtual void MoveTo(int x, int y) = 0;
        // ������ ����� � ������� �������, ���������� ���� � ����� x,y
        virtual void SetColor(uint32_t rgbColor) = 0;
        virtual void LineTo(int x, int y) = 0;
        virtual ~ICanvas() = default;
    };

    // ���������� ������ ��� ���������
    class CCanvas : public ICanvas
    {
    public:
        void MoveTo(int x, int y) override
        {
            cout << "MoveTo (" << x << ", " << y << ")" << endl;
        }
        void LineTo(int x, int y) override
        {
            cout << "LineTo (" << x << ", " << y << ")" << endl;
        }

        void SetColor(uint32_t rgbColor) override
        {
            cout << "SetColor (#" << std::setfill('0') << std::setw(6) << std::hex << rgbColor << ")" << std::dec << "\n" ;
        }
    };
}

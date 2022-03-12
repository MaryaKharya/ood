#include "Designer.h"
#include "CShapeFactory.h"
#include "CPainter.h"
#include "CCanvas.h"
#include <fstream>
#include <iostream>
#include <string>

int main()
{
	CShapeFactory factory;
	CDesigner designer(factory);
	std::ifstream shapes("Shapes.txt");
	CPictureDraft draft = designer.CreateDraft(shapes);
	std::string str;

	sf::RenderWindow window(sf::VideoMode(1300, 1000), "SFML window");
	CCanvas canvas(window);
	CPainter painter;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear(sf::Color(0xffffffff));
		painter.DrawPicture(draft, canvas);
		window.display();
	}

	return 0;
}

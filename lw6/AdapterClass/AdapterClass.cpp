#include <iostream>
#include "app.h"

using namespace std;

int main()
{
	cout << "Should we use new API (y)?\n";
	string userInput;
	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}

	return 0;
}

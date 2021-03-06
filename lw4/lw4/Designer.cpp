#include "Designer.h"
#include "PictureDraft.h"
#include "IShapeFactory.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

CDesigner::CDesigner(IShapeFactory& factory)
	:m_factory(factory)
{
}


CDesigner::~CDesigner()
{
}

CPictureDraft CDesigner::CreateDraft(std::istream& inputData)
{
	CPictureDraft draft;
	std::string line;
	while (std::getline(inputData, line))
	{
		try
		{
			draft.AddShape(m_factory.CreateShape(line));
		}
		catch (exception e)
		{
			std::cout << e.what() << "\n";
		}
	}
	return draft;
}
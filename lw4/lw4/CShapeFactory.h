#include <vector>
#include "CPoint.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CRegularPolygon.h"
#include "CRectangle.h"
#include "IShapeFactory.h"

class CShapeFactory: public IShapeFactory
{
public:
	std::unique_ptr<CShape> CreateShape(const std::string& description) override;
private:
	std::unique_ptr<CRegularPolygon> CreateRegularPolygon(std::istringstream& stream) const;
	std::unique_ptr<CTriangle> CreateTriangle(std::istringstream& stream) const;
	std::unique_ptr<CRectangle> CreateRectangle(std::istringstream& stream) const;
	std::unique_ptr<CEllipse> CreateEllipse(std::istringstream& stream) const;
	Color GetColor(std::string const& color) const;
};

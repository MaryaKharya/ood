#pragma once
#include "PictureDraft.h"
#include "ICanvas.h"

class CPainter
{
public:
	void DrawPicture(const CPictureDraft& pictureDraft, ICanvas& canvas)
	{
		for (size_t index = 0; index < pictureDraft.GetShapesCount(); index++)
		{
			pictureDraft.GetShape(index).Draw(canvas);
		}
	}
};
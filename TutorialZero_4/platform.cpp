#include "platform.h"

void Platform::on_draw(const Camera& camera) const
{
	putimage_alpha(camera, renderPos.x, renderPos.y, img);

	if (is_debug)
	{
		setlinecolor(RGB(255, 0, 0));
		putline(camera, (int)shape.left, (int)shape.y, (int)shape.right, (int)shape.y);
	}
}
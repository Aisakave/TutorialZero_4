#include "util.h"
#pragma comment(lib, "MSIMG32.LIB") // AlphaBlend

void flip_image(IMAGE* src, IMAGE* dst)
{
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx_src = y * w + x;
			int idx_dst = y * w + (w - x - 1);
			dst_buffer[idx_dst] = src_buffer[idx_src];
		}
	}
}

void putimage_alpha(int dst_x, int dst_y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();

	AlphaBlend(GetImageHDC(nullptr), dst_x, dst_y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255, AC_SRC_ALPHA });

}

void putimage_alpha(const Camera& camera, int dst_x, int dst_y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	const Vector2& pos_camera = camera.get_postion();
	AlphaBlend(GetImageHDC(nullptr), (int)(dst_x - pos_camera.x), (int)(dst_y - pos_camera.y), w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255, AC_SRC_ALPHA });

}

//在(dst_x, dst_y) 处 显示 (src_x, src_y), w, h 的 图
void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y) {

	int w = width > 0 ? width : img->getwidth();
	int h = height > 0 ? height : img->getheight();

	//将(src_x, src_y), w, h 的图像 复制到 (dst_x, dst_y)处
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

void putline(const Camera& camera, int x1, int y1, int x2, int y2)
{
	const Vector2& pos_camera = camera.get_postion();
	line((int)(x1 - pos_camera.x), (int)(y1 - pos_camera.y), (int)(x2 - pos_camera.x), (int)(y2 - pos_camera.y));
}

void sketchImage(IMAGE* src, IMAGE* dst) {

	auto W = src->getwidth(), H = src->getheight();
	Resize(dst, W, H);

	auto srcBuffer = GetImageBuffer(src);
	auto dstBuffer = GetImageBuffer(dst);

	for (int h = 0; h < H;h++)
		for (int w = 0; w < W; w++) {

			auto idx = h * W + w;

			dstBuffer[idx] = BGR(RGB(255, 255, 255)) | (srcBuffer[idx] & 0xFF000000);
		}

}

/*
AlphaBlend:	Windows GDI+ API，用于图像混合。
	GetImageHDC(nullptr), x, y, w, h:
		GetImageHDC(nullptr):获取屏幕
		x, y, w, h:	屏幕的位置,作为目标区域。(左上角坐标为x,y，宽为w，高为h)
	GetImageHDC(img), 0, 0, w, h:
		GetImageHDC(img):获取图像
		0, 0, w, h:	整个图像，作为源区域。

	{ AC_SRC_OVER,0,255, AC_SRC_ALPHA }: 将源图像以透明的方式覆盖到目标图像上，透明度由源图像的Alpha通道控制。
		AC_SRC_OVER:	源图像覆盖目标图像
		0,255:			参数，此处无作用
		AC_SRC_ALPHA:	指定源图像的Alpha通道覆盖
			图像的Alpha通道: 是图像的透明度通道，存储着每个像素的透明度信息
*/

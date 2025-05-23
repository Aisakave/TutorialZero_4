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

//��(dst_x, dst_y) �� ��ʾ (src_x, src_y), w, h �� ͼ
void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y) {

	int w = width > 0 ? width : img->getwidth();
	int h = height > 0 ? height : img->getheight();

	//��(src_x, src_y), w, h ��ͼ�� ���Ƶ� (dst_x, dst_y)��
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
AlphaBlend:	Windows GDI+ API������ͼ���ϡ�
	GetImageHDC(nullptr), x, y, w, h:
		GetImageHDC(nullptr):��ȡ��Ļ
		x, y, w, h:	��Ļ��λ��,��ΪĿ������(���Ͻ�����Ϊx,y����Ϊw����Ϊh)
	GetImageHDC(img), 0, 0, w, h:
		GetImageHDC(img):��ȡͼ��
		0, 0, w, h:	����ͼ����ΪԴ����

	{ AC_SRC_OVER,0,255, AC_SRC_ALPHA }: ��Դͼ����͸���ķ�ʽ���ǵ�Ŀ��ͼ���ϣ�͸������Դͼ���Alphaͨ�����ơ�
		AC_SRC_OVER:	Դͼ�񸲸�Ŀ��ͼ��
		0,255:			�������˴�������
		AC_SRC_ALPHA:	ָ��Դͼ���Alphaͨ������
			ͼ���Alphaͨ��: ��ͼ���͸����ͨ�����洢��ÿ�����ص�͸������Ϣ
*/

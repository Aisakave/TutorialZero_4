#pragma once
#include <graphics.h>
#include "camera.h"

void flip_image(IMAGE* src, IMAGE* dst); // ��תͼ�����ҶԳ�
void putimage_alpha(int x, int y, IMAGE* img); // ͼ�����(͸����)
void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img); // ͼ�����(͸����)
void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y); // �ü�����λ�õ�ͼ����ʾ��(dst_x, dst_y) �� ��ʾ (src_x, src_y), w, h �� ͼ
void putline(const Camera& camera, int x1, int y1, int x2, int y2);
void sketchImage(IMAGE* src, IMAGE* dst);
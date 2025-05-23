#pragma once
#include <graphics.h>
#include "camera.h"

void flip_image(IMAGE* src, IMAGE* dst); // 翻转图像左右对称
void putimage_alpha(int x, int y, IMAGE* img); // 图像绘制(透明度)
void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img); // 图像绘制(透明度)
void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y); // 裁剪任意位置的图并显示在(dst_x, dst_y) 处 显示 (src_x, src_y), w, h 的 图
void putline(const Camera& camera, int x1, int y1, int x2, int y2);
void sketchImage(IMAGE* src, IMAGE* dst);
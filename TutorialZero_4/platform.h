#pragma once
#include <graphics.h>
#include "camera.h"
#include "util.h"

extern bool is_debug;

class Platform {
public:
	Platform() = default;
	~Platform() = default;
public:
	// 碰撞箱为一条直线
	struct CollisionShape 
	{
		float y;			// 线的竖直坐标位置
		float left, right;	// 线的左右端点
	};

public:
	// 渲染数据
	IMAGE* img = nullptr;
	POINT renderPos = { 0 };

	// 碰撞数据
	CollisionShape shape;	// 平台碰撞箱
public:

	void on_draw(const Camera& camera) const;
};

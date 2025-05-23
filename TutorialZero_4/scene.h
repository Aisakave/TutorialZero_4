#pragma once
#include <graphics.h>
#include "camera.h"

/*
场景
	菜单
	角色选择
	游戏
*/

class Scene
{
public:
	Scene() = default;
	~Scene() = default;
public:

	virtual void on_enter() = 0; // 进入
	virtual void on_updata(int delta) = 0; // 更新
	virtual void on_draw(const Camera& camera) = 0; // 渲染
	virtual void on_input(const ExMessage& msg) = 0; // 输入
	virtual void on_exit() = 0; // 退出

private:

};
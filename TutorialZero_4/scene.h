#pragma once
#include <graphics.h>
#include "camera.h"

/*
����
	�˵�
	��ɫѡ��
	��Ϸ
*/

class Scene
{
public:
	Scene() = default;
	~Scene() = default;
public:

	virtual void on_enter() = 0; // ����
	virtual void on_updata(int delta) = 0; // ����
	virtual void on_draw(const Camera& camera) = 0; // ��Ⱦ
	virtual void on_input(const ExMessage& msg) = 0; // ����
	virtual void on_exit() = 0; // �˳�

private:

};
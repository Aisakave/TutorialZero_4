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
	// ��ײ��Ϊһ��ֱ��
	struct CollisionShape 
	{
		float y;			// �ߵ���ֱ����λ��
		float left, right;	// �ߵ����Ҷ˵�
	};

public:
	// ��Ⱦ����
	IMAGE* img = nullptr;
	POINT renderPos = { 0 };

	// ��ײ����
	CollisionShape shape;	// ƽ̨��ײ��
public:

	void on_draw(const Camera& camera) const;
};

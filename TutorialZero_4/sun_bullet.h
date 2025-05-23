#pragma once
#include "bullet.h"
#include "animation.h"
#include "camera.h"

extern Atlas atlasSun;
extern Atlas atlasSunExplode;
extern Camera main_camera;

class SunBullet : public Bullet {
public:
	void on_updata(int delta);
	void on_draw(const Camera& camera) const;

public:
	SunBullet();
public:
	void onCollide();

private:
	// �˶�
	const float gravity = 1e-3f;

	// ��Ⱦ
	Animation animationIdle;				// Ĭ�϶���
	Animation animationExplode;				// ��ը����
	Vector2 explodeon_drawOffset;			// ��ը������ƫ��
};

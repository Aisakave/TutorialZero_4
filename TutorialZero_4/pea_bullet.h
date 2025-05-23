#pragma once
#include "bullet.h"
#include "animation.h"
#include "util.h"

extern IMAGE imgPea;
extern Atlas atlasPeaBreak;

class PeaBullet :public Bullet {
public:
	PeaBullet();

public:

	// ��ײ
	void onCollide();			// ������ײ

public:
	void on_updata(int delta);
	void on_draw(const Camera& camera) const;


private:

	//��Ⱦ
	Animation animationBreak;			// ���鶯��

};

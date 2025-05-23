#pragma once
#include "bullet.h"
#include "animation.h"
#include "camera.h"

extern Atlas atlasSunEx;
extern Atlas atlasSunExExplode;
extern Camera main_camera;

class SunBulletEx : public Bullet {
public:
	void on_updata(int delta);
	void on_draw(const Camera& camera) const;
public:
	SunBulletEx();
public:
	//Åö×²
	void onCollide();
	bool checkIsCollision(const Vector2& position, const Vector2& size) override;
private:

	//äÖÈ¾
	Animation animationIdle;				// Ä¬ÈÏ¶¯»­
	Animation animationExplode;				// ±¬Õ¨¶¯»­
	Vector2 explodeon_drawOffset;			// ±¬Õ¨¶¯»­µÄÆ«ÒÆ
};

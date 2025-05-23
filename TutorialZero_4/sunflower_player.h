#pragma once
#include "player.h"
#include "sun_bullet.h"
#include "sun_bullet_ex.h"
#include <iostream>

extern Atlas atlasSunFlowerIdleLeft;
extern Atlas atlasSunFlowerIdleRight;
extern Atlas atlasSunFlowerRunLeft;
extern Atlas atlasSunFlowerRunRight;

extern Atlas atlasSunFlowerAttackExLeft;
extern Atlas atlasSunFlowerAttackExRight;
extern Atlas atlasSunText;

extern Atlas atlasSunFlowerDieLeft;
extern Atlas atlasSunFlowerDieRight;

extern Player* player_1;
extern Player* player_2;

class SunflowerPlayer : public Player
{
public:
	SunflowerPlayer(bool isFacingRight = true);
	~SunflowerPlayer() = default;

	void on_updata(int delta);
	void on_draw(const Camera& camera) override;

public:
	//¹¥»÷
	void on_attack() override;
	void on_attack_ex() override;

private:

	// ×Óµ¯ËÙ¶È
	const Vector2 velocitySun{ 0.25, -0.5 };
	const float speedSunEx = 0.15;

	// äÖÈ¾
	Animation animationSunText;
	bool isSunTextVisible = false;

};


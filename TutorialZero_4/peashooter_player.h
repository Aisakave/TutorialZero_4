#pragma once
#include "player.h"
#include "pea_bullet.h"
#include <iostream>

extern Atlas atlasPeaShooterIdleLeft;
extern Atlas atlasPeaShooterIdleRight;
extern Atlas atlasPeaShooterRunLeft;
extern Atlas atlasPeaShooterRunRight;

extern Atlas atlasPeaShooterAttackExLeft;
extern Atlas atlasPeaShooterAttackExRight;

extern Atlas atlasPeaShooterDieLeft;
extern Atlas atlasPeaShooterDieRight;

extern Camera main_camera;

class PeashooterPlayer : public Player
{
public:
	PeashooterPlayer(bool isFacingRight = true);
	~PeashooterPlayer() = default;

	void on_updata(int delta);
public:
	//攻击
	void on_attack() override;
	void on_attack_ex() override;

private:
	void spawnPeaBullet(float speed);

private:
	//攻击
	const float speedPea = 0.75f;
	const float speedPeaEx = 1.5f;
	const int attackExDuration = 2500;		// 特殊攻击时长

	Timer timerAttackEx;					// 角色特殊攻击
	Timer timerSpawnPeaEx;					// 子弹特殊发射

};


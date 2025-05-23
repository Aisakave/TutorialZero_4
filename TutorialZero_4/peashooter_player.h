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
	//����
	void on_attack() override;
	void on_attack_ex() override;

private:
	void spawnPeaBullet(float speed);

private:
	//����
	const float speedPea = 0.75f;
	const float speedPeaEx = 1.5f;
	const int attackExDuration = 2500;		// ���⹥��ʱ��

	Timer timerAttackEx;					// ��ɫ���⹥��
	Timer timerSpawnPeaEx;					// �ӵ����ⷢ��

};


#include "peashooter_player.h"

PeashooterPlayer::PeashooterPlayer(bool isFacingRight) :Player(isFacingRight)
{
	// 初始化动画
	animationIdleLeft.set_atlas(&atlasPeaShooterIdleLeft);
	animationIdleRight.set_atlas(&atlasPeaShooterIdleRight);
	animationRunLeft.set_atlas(&atlasPeaShooterRunLeft);
	animationRunRight.set_atlas(&atlasPeaShooterRunRight);
	animationAttackExLeft.set_atlas(&atlasPeaShooterAttackExLeft);
	animationAttackExRight.set_atlas(&atlasPeaShooterAttackExRight);

	animationDieLeft.set_atlas(&atlasPeaShooterDieLeft);
	animationDieRight.set_atlas(&atlasPeaShooterDieRight);

	animationIdleLeft.set_interval(75);
	animationIdleRight.set_interval(75);
	animationRunLeft.set_interval(75);
	animationRunRight.set_interval(75);
	animationAttackExLeft.set_interval(75);
	animationAttackExRight.set_interval(75);

	animationDieLeft.set_interval(150);
	animationDieRight.set_interval(150);

	animationDieLeft.set_loop(false);
	animationDieRight.set_loop(false);

	size.x = 96, size.y = 96;

	// 设置定时器
	timerAttackEx.set_callback([&] { isAttackingEx = false; });
	timerAttackEx.set_wait_time(attackExDuration);
	timerAttackEx.set_one_shot(true);

	timerSpawnPeaEx.set_callback([&] { spawnPeaBullet(speedPeaEx); });
	timerSpawnPeaEx.set_wait_time(100);

	// 普攻cd
	attack_cd = 100;

}

void PeashooterPlayer::on_updata(int delta)
{
	Player::on_updata(delta);

	if (isAttackingEx) 
	{
		main_camera.shake(5, 100);

		timerAttackEx.on_updata(delta);
		timerSpawnPeaEx.on_updata(delta);
	}
}

void PeashooterPlayer::on_attack() 
{
	spawnPeaBullet(speedPea);

	switch (rand() % 2) 
	{
	case 0:
		mciSendString(_T("play peaShoot1 from 0"), nullptr, 0, nullptr);
		break;
	case 1:
		mciSendString(_T("play peaShoot2 from 0"), nullptr, 0, nullptr);
		break;
	default:
		break;
	}

}
void PeashooterPlayer::on_attack_ex()
{
	isAttackingEx = true;
	timerAttackEx.restart();

	isFacingRight ? animationAttackExRight.reset() : animationAttackExLeft.reset();

	mciSendString(_T("play peaShootEx from 0"), nullptr, 0, nullptr);

}

void PeashooterPlayer::spawnPeaBullet(float speed)
{
	Bullet* bullet = new PeaBullet();
	Vector2 bulletPosition, bulletVelocity;
	auto bulletSize = bullet->getSize();
	// 设置子弹位置为豌豆头部
	bulletPosition.x = isFacingRight ? position.x + size.x - bulletSize.x / 2 :
		position.x - bulletSize.x / 2;

	bulletPosition.y = position.y;

	// 设置子弹速度
	bulletVelocity.x = isFacingRight ? speed : -speed;
	bulletVelocity.y = 0;

	bullet->setPosition(bulletPosition.x, bulletPosition.y);
	bullet->setVelocity(bulletVelocity.x, bulletVelocity.y);

	// 设置子弹的碰撞目标
	bullet->setCollideTarget( id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

	// 设置子弹回调
	bullet->setCallback([&] {mp += 25; });

	bullet_list.push_back(bullet);

}


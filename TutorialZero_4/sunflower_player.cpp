#include "sunflower_player.h"

SunflowerPlayer::SunflowerPlayer(bool isFacingRight) :Player(isFacingRight)
{
	// 初始化动画
	animationIdleLeft.set_atlas(&atlasSunFlowerIdleLeft);
	animationIdleRight.set_atlas(&atlasSunFlowerIdleRight);
	animationRunLeft.set_atlas(&atlasSunFlowerRunLeft);
	animationRunRight.set_atlas(&atlasSunFlowerRunRight);

	animationAttackExLeft.set_atlas(&atlasSunFlowerAttackExLeft);
	animationAttackExRight.set_atlas(&atlasSunFlowerAttackExRight);
	animationSunText.set_atlas(&atlasSunText);

	animationDieLeft.set_atlas(&atlasSunFlowerDieLeft);
	animationDieRight.set_atlas(&atlasSunFlowerDieRight);


	animationIdleLeft.set_interval(75);
	animationIdleRight.set_interval(75);
	animationRunLeft.set_interval(75);
	animationRunRight.set_interval(75);
	
	animationAttackExLeft.set_interval(100);
	animationAttackExRight.set_interval(100);
	animationSunText.set_interval(100);

	animationDieLeft.set_interval(150);
	animationDieRight.set_interval(150);

	animationAttackExLeft.set_loop(false);
	animationAttackExRight.set_loop(false);
	animationSunText.set_loop(false);

	animationDieLeft.set_loop(false);
	animationDieRight.set_loop(false);

	// 设置动画回调
	animationAttackExLeft.set_callback(
		[&] 
		{
			isAttackingEx = false;
			isSunTextVisible = false;
		}
	);

	animationAttackExRight.set_callback(
		[&] 
		{
			isAttackingEx = false;
			isSunTextVisible = false;
		}
	);

	size.x = 96, size.y = 96;

	attack_cd = 250;
	
}

void SunflowerPlayer::on_updata(int delta)
{
	Player::on_updata(delta);

	if (isSunTextVisible)
		animationSunText.on_updata(delta);
}

void SunflowerPlayer::on_draw(const Camera& camera)
{
	Player::on_draw(camera);

	if (isSunTextVisible) {

		Vector2 textPosition;

		auto frame = animationSunText.get_frame();

		textPosition.x = position.x - (size.x - frame->getwidth()) / 2;
		textPosition.y = position.y - frame->getheight();

		animationSunText.on_draw(camera, textPosition.x, textPosition.y);
	}

}

void SunflowerPlayer::on_attack()
{
	auto bullet = new SunBullet;

	Vector2 bulletPosition;

	auto bulletSize = bullet->getSize();

	// 设置子弹位置为向日葵头部
	bulletPosition.x = position.x + (size.x - bulletSize.x) / 2;
	bulletPosition.y = position.y;

	// 设置子弹速度
	bullet->setPosition(bulletPosition.x, bulletPosition.y);
	bullet->setVelocity(isFacingRight ? velocitySun.x : -velocitySun.x, velocitySun.y);

	// 设置子弹的碰撞目标
	bullet->setCollideTarget(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

	// 设置子弹回调
	bullet->setCallback([&] {mp += 35; });

	bullet_list.push_back(bullet);
}

void SunflowerPlayer::on_attack_ex() 
{
	isAttackingEx = true;
	isSunTextVisible = true;

	animationSunText.reset();

	isFacingRight ? animationAttackExRight.reset() : animationAttackExLeft.reset();

	Bullet* bullet = new SunBulletEx();
	Player* targetPlayer = (id == PlayerID::P1 ? player_2 : player_1);

	Vector2 bulletPosition, bulletVelocity;

	const Vector2& bulletSize = bullet->getSize();
	const Vector2& targetSize = targetPlayer->getSize();
	const Vector2& targetPosition = targetPlayer->getPosition();

	// 子弹位于玩家头顶中心
	bulletPosition.x = targetPosition.x + (targetSize.x - bulletSize.x) / 2;
	bulletPosition.y = -size.y;
	bulletVelocity.x = 0;
	bulletVelocity.y = speedSunEx;

	bullet->setPosition(bulletPosition.x, bulletPosition.y);
	bullet->setVelocity(bulletVelocity.x, bulletVelocity.y);

	// 设置子弹的碰撞目标
	bullet->setCollideTarget(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

	// 设置子弹回调
	bullet->setCallback([&] {mp += 50; });

	bullet_list.push_back(bullet);

	mciSendString(_T("play sunText from 0"), nullptr, 0, nullptr);
}

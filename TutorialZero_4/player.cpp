#include "player.h"

Player::Player(bool isFacingRight) : isFacingRight(isFacingRight)
{
	current_animation = isFacingRight ? &animationIdleRight : &animationIdleLeft;

	timer_attack_cd.set_wait_time(attack_cd);
	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_callback(
		[&]
		{
			can_attack = true;
		}
	);

	// �޵ж�ʱ��
	timerInvulnerable.set_wait_time(750);
	timerInvulnerable.set_one_shot(true);
	timerInvulnerable.set_callback
	(
		[&] 
		{
			isInvulnerable = false;
		}
	);

	// �޵ж����л�
	timerInvulnerableBlink.set_wait_time(75);
	timerInvulnerableBlink.set_callback
	(
		[&]
		{
			isShowSketchFram = !isShowSketchFram;
		}
	);

	// ���ӷ���
	timerRunEffectGeneration.set_wait_time(75);
	timerRunEffectGeneration.set_callback([&] {

		Vector2 particlePosition;
		auto frame = atlasRunEffect.get_image(0);

		// ����λ�����ˮƽ����
		particlePosition.x = position.x + (size.x - frame->getwidth()) / 2;
		// ��ҽŵ�
		particlePosition.y = position.y + size.y - frame->getheight();

		particles.emplace_back(particlePosition, &atlasRunEffect, 45);

		});

	timerDieEffectGeneration.set_wait_time(35);
	timerDieEffectGeneration.set_callback([&] {

		Vector2 particlePosition;
		auto frame = atlasRunEffect.get_image(0);

		// ����λ�����ˮƽ����
		particlePosition.x = position.x + (size.x - frame->getwidth()) / 2;
		// ��ҽŵ�
		particlePosition.y = position.y + size.y - frame->getheight();

		particles.emplace_back(particlePosition, &atlasRunEffect, 150);

		});

	// ��Ծ�����
	animationJumpEffect.set_atlas(&atlasJumpEffect);
	animationJumpEffect.set_interval(25);
	animationJumpEffect.set_loop(false);
	animationJumpEffect.set_callback(
		[&] 
		{
			isJumpEffectVisible = false;
		}
	);

	animationLandEffect.set_atlas(&atlasLandEffect);
	animationLandEffect.set_interval(50);
	animationLandEffect.set_loop(false);
	animationLandEffect.set_callback(
		[&]
		{
			isLandEffectVisible = false;
		}
	);

	timerCursorVisibility.set_wait_time(99999999);
	timerCursorVisibility.set_one_shot(true);
	timerCursorVisibility.set_callback
	(
		[&]
		{
			isCursorVisible = false;
		}
	);

}

void Player::setId(const PlayerID& id) 
{
	this->id = id;
}

void Player::setPos(float x, float y)
{
	position.x = x, position.y = y;
}

const Vector2& Player::getPosition() const {

	return position;
}

const Vector2& Player::getSize() const {

	return size;
}

void Player::on_run(float distance)
{
	if (isAttackingEx) return;

	position.x += distance;
	timerRunEffectGeneration.resume();
}

void Player::on_jump()
{
	if (velocity.y != 0 || isAttackingEx) return;
	velocity.y += jump_velocity;

	// ��Ծ
	isJumpEffectVisible = true;
	animationJumpEffect.reset();
	auto frame = animationJumpEffect.get_frame();
	// jumpλ���������
	positionJumpEffect.x = position.x + (size.x - frame->getwidth()) / 2;
	positionJumpEffect.y = position.y + size.x - frame->getheight();

}

void Player::on_land() 
{

	// ���
	isLandEffectVisible = true;
	animationLandEffect.reset();
	auto frame = animationLandEffect.get_frame();
	// jumpλ���������
	positionLandEffect.x = position.x + (size.x - frame->getwidth()) / 2;
	positionLandEffect.y = position.y + size.x - frame->getheight();
}

void Player::makeInvulnerable()
{
	isInvulnerable = true;
	timerInvulnerable.restart();
}

void Player::on_updata(int delta)
{
	// ���ݰ����Ƿ��ƶ��жϳ���
	int direction = isRightKeyDown - isLeftKeyDown;
	if (direction != 0)
	{
		if(!isAttackingEx)
			isFacingRight = direction > 0;
		current_animation = isFacingRight ? &animationRunRight : &animationRunLeft;
		float distance = direction * run_velocity * delta;
		on_run(distance);
	}
	else
	{
		current_animation = isFacingRight ? &animationIdleRight : &animationIdleLeft;
		timerRunEffectGeneration.pause();
	}

	if(isAttackingEx)
		current_animation = isFacingRight ? &animationAttackExRight : &animationAttackExLeft;

	// ��������
	if (hp <= 0)
		current_animation = lastHurtDirection.x < 0 ? &animationDieLeft : &animationDieRight;

	// ���¶���
	current_animation->on_updata(delta);
	animationJumpEffect.on_updata(delta);
	animationLandEffect.on_updata(delta);

	// ���¶�ʱ��
	timer_attack_cd.on_updata(delta);
	timerInvulnerable.on_updata(delta);
	timerInvulnerableBlink.on_updata(delta);

	// ���¹�궨ʱ��
	timerCursorVisibility.on_updata(delta);

	// ��������
	timerRunEffectGeneration.on_updata(delta);
	if (hp <= 0)
		timerDieEffectGeneration.on_updata(delta);

	//��������
	particles.erase(std::remove_if(particles.begin(), particles.end(), 
		[](const Particle& particle) 
		{
			return !particle.checkIsValid();
		}), particles.end());

	for (auto& particle : particles)
		particle.on_updata(delta);

	// ��Ӱ
	if (isShowSketchFram)
		sketchImage(current_animation->get_frame(), &imgSketch);

	// ����ģ�� �� ��ײ���
	move_and_collide(delta);
}

void Player::setHp(int val)
{
	hp = val;
}

void Player::setMp(int val) 
{
	mp = val;
}

const int Player::getHp() const 
{
	return hp;
}

const int Player::getMp() const
{
	return mp;
}

void Player::move_and_collide(int delta) 
{
	float last_velocity_y = velocity.y;

	velocity.y += gravity * delta;
	position += velocity * (float)delta;

	if (hp <= 0) return;

	// �����ƽ̨
	if (velocity.y > 0)
	{
		for (const Platform& platform : platform_list)
		{
			const Platform::CollisionShape& shape = platform.shape;
			bool is_collide_x = max(position.x + size.x, shape.right) - min(position.x, shape.left) <= shape.right - shape.left + size.x;
			bool is_collide_y = shape.y >= position.y && shape.y <= position.y + size.y;

			// ����������������
			if (is_collide_x && is_collide_y)
			{
				// �ж���һ֡����Ƿ���ƽ̨֮��
				float delta_pos_y = velocity.y * delta;
				float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;

				if (last_tick_foot_pos_y <= shape.y)
				{
					position.y = shape.y - size.y;
					// ƽ̨���ٶ�Ϊ0
					velocity.y = 0;

					// ���
					if (last_velocity_y != 0)
						on_land();

					break;
				}

			}

		}
	}

	// ������ӵ�
	if (!isInvulnerable)
	{
		for (Bullet* bullet : bullet_list)
		{
			if (!bullet->getValid() || bullet->getCollideTarget() != id) continue;

			if (bullet->checkIsCollision(position, size))
			{
				makeInvulnerable();
				bullet->onCollide();
				bullet->setValid(false);
				hp -= bullet->getDamage();

				// ��ҵ��ӵ�������
				lastHurtDirection = bullet->getPosition() - position;

				if (hp <= 0)
				{
					velocity.x = lastHurtDirection.x < 0 ? 0.35 : -0.35;
					velocity.y = -1.0;
				}
			
			}
		}
	}

}

void Player::on_draw(const Camera& camera)
{
	if (isJumpEffectVisible)
		animationJumpEffect.on_draw(camera, positionJumpEffect.x, positionJumpEffect.y);

	if (isLandEffectVisible)
		animationLandEffect.on_draw(camera, positionLandEffect.x, positionLandEffect.y);

	// ��������Ⱦ��������
	for (const Particle& particle : particles)
		particle.on_draw();


	if (hp > 0 && isInvulnerable && isShowSketchFram)
		putimage_alpha(camera, (int)position.x, (int)position.y, &imgSketch);
	else
		current_animation->on_draw(camera, (int)position.x, (int)position.y);

	if (isCursorVisible) {

		switch (id) {
		case PlayerID::P1:
			//���ͷ������
			putimage_alpha(camera, (int)(position.x + (size.x - img1PCursor.getwidth()) / 2), (int)(position.y - img1PCursor.getheight()),
				&img1PCursor);
			break;
		case PlayerID::P2:
			putimage_alpha(camera, (int)(position.x + (size.x - img2PCursor.getwidth()) / 2), (int)(position.y - img2PCursor.getheight()),
				&img2PCursor);
			break;
		default:
			break;
		}

	}

	if (is_debug) {

		setlinecolor(RGB(0, 125, 255));

		rectangle(position.x, position.y, position.x + size.x, position.y + size.y);
	}
}

void Player::on_input(const ExMessage& msg)
{
	switch (msg.message) {
	case WM_KEYDOWN:

		switch (id) {
		case PlayerID::P1:
			switch (msg.vkcode) {
				// 'A'
			case 0x41:
				isLeftKeyDown = true;
				break;
				// 'D'
			case 0x44:
				isRightKeyDown = true;
				break;
				// 'W'
			case 0x57:
				on_jump();
				break;
				// 'J'
			case 0x4a:
				if (can_attack) {
					on_attack();
					can_attack = !can_attack;
					timer_attack_cd.restart();
				}
				break;
				// 'K'
			case 0x4b:
				if (mp >= 100) {
					on_attack_ex();
					mp = 0;
				}
				break;
			default:
				break;
			}
			break;
		case PlayerID::P2:
			switch (msg.vkcode) {
				// <
			case VK_LEFT:
				isLeftKeyDown = true;
				break;
				// >
			case VK_RIGHT:
				isRightKeyDown = true;
				break;
				// '��'
			case VK_UP:
				on_jump();
				break;
				// '1'
			case 0x61:
				if (can_attack) {
					on_attack();
					can_attack = !can_attack;
					timer_attack_cd.restart();
				}
				break;
				// '2'
			case 0x62:
				if (mp >= 100) {
					on_attack_ex();
					mp = 0;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		break;
	case WM_KEYUP:

		switch (id) {
		case PlayerID::P1:
			switch (msg.vkcode) {
				//'A'
			case 0x41:
				isLeftKeyDown = false;
				break;
				//'D'
			case 0x44:
				isRightKeyDown = false;
				break;
			default:
				break;
			}
			break;
		case PlayerID::P2:
			switch (msg.vkcode) {
				//<
			case VK_LEFT:
				isLeftKeyDown = false;
				break;
				//>
			case VK_RIGHT:
				isRightKeyDown = false;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		break;
	default:
		break;
	}

}


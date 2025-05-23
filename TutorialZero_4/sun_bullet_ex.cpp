#include "sun_bullet_ex.h"

void SunBulletEx::on_updata(int delta)
{

	if (isValid)
		position += velocity * delta;


	if (!isValid)
		animationExplode.on_updata(delta);
	else
		animationIdle.on_updata(delta);

	if (checkIsExceedScreen())
		isCanRemove = true;
}

void SunBulletEx::on_draw(const Camera& camera) const
{

	if (isValid)
		animationIdle.on_draw(camera, position.x, position.y);
	else
		animationExplode.on_draw(camera, position.x + explodeon_drawOffset.x, position.y + explodeon_drawOffset.y);

	Bullet::on_draw(camera);
}

SunBulletEx::SunBulletEx() 
{

	size.x = 288, size.y = 288;

	damage = 20;

	animationIdle.set_atlas(&atlasSunEx);
	animationIdle.set_interval(50);

	animationExplode.set_atlas(&atlasSunExExplode);
	animationExplode.set_interval(50);
	animationExplode.set_loop(false);
	animationExplode.set_callback(
		[&] ()
		{
			isCanRemove = true;
		}
	);

	auto frameIdle = animationIdle.get_frame();
	auto frameExplode = animationExplode.get_frame();

	//±¬Õ¨¶¯»­Æ«ÒÆ
	explodeon_drawOffset.x = (frameIdle->getwidth() - frameExplode->getwidth()) / 2.0;
	explodeon_drawOffset.y = (frameIdle->getheight() - frameExplode->getheight()) / 2.0;
}

void SunBulletEx::onCollide() 
{

	Bullet::onCollide();

	main_camera.shake(20, 350);

	mciSendString(_T("play sunExplodeEx from 0"), nullptr, 0, nullptr);
}

bool SunBulletEx::checkIsCollision(const Vector2& position, const Vector2& size) 
{

	auto xLeft = this->position.x;
	auto xRight = this->position.x + this->size.x;

	auto yTop = this->position.y;
	auto yDown = this->position.y + this->size.y;

	bool isCollideX = max(xRight, position.x + size.x) - min(xLeft, position.x) <= this->size.x + size.x;
	bool isCollideY = max(yDown, position.y + size.y) - min(yTop, position.y) <= this->size.y + size.y;

	return isCollideX && isCollideY;
}


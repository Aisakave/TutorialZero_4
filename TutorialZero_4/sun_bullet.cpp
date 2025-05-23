#include "sun_bullet.h"

void SunBullet::on_updata(int delta) 
{

	if (isValid) 
	{
		velocity.y += gravity * delta;
		position += velocity * (float)delta;
	}

	if (!isValid)
		animationExplode.on_updata(delta);
	else
		animationIdle.on_updata(delta);

	if (checkIsExceedScreen())
		isCanRemove = true;
}

void SunBullet::on_draw(const Camera& camera) const
{
	if (isValid)
		animationIdle.on_draw(camera, (int)position.x, (int)position.y);
	else
	{ 
		animationExplode.on_draw(camera, 
			(int)(position.x + explodeon_drawOffset.x),
			(int)(position.y + explodeon_drawOffset.y));
	}

	Bullet::on_draw(camera);
}

SunBullet::SunBullet()
{

	size.x = 96, size.y = 96;

	damage = 20;

	animationIdle.set_atlas(&atlasSun);
	animationIdle.set_interval(50);

	animationExplode.set_atlas(&atlasSunExplode);
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

	// ±¬Õ¨¶¯»­Æ«ÒÆ
	explodeon_drawOffset.x = (frameIdle->getwidth() - frameExplode->getwidth()) / 2.0f;
	explodeon_drawOffset.y = (frameIdle->getheight() - frameExplode->getheight()) / 2.0f;
}

void SunBullet::onCollide() 
{

	Bullet::onCollide();

	main_camera.shake(5, 250);

	mciSendString(_T("play sunExplode from 0"), nullptr, 0, nullptr);
}


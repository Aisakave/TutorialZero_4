#include "pea_bullet.h"


PeaBullet::PeaBullet() {

	size.x = 64, size.y = 64;

	damage = 15;

	animationBreak.set_atlas(&atlasPeaBreak);
	animationBreak.set_interval(100);
	animationBreak.set_loop(false);
	animationBreak.set_callback(
		[&] ()
		{
			isCanRemove = true;
		}
	);

}

// 重写父类方法，但依旧需要执行父类逻辑
void PeaBullet::onCollide() {

	Bullet::onCollide();
	// 随机播放音乐

	switch (rand() % 3) {
	case 0:
		mciSendString(_T("play peaBreak1 from 0"), nullptr, 0, nullptr);
		break;
	case 1:
		mciSendString(_T("play peaBreak1 from 0"), nullptr, 0, nullptr);
		break;
	case 2:
		mciSendString(_T("play peaBreak1 from 2"), nullptr, 0, nullptr);
		break;
	default:
		break;
	}

}

void PeaBullet::on_updata(int delta) {

	position += velocity * (float)delta;

	if (!isValid)
		animationBreak.on_updata(delta);

	if (checkIsExceedScreen())
		isCanRemove = true;

}

void PeaBullet::on_draw(const Camera& camera)const {

	if (isValid)
		putimage_alpha(camera, (int)position.x, (int)position.y, &imgPea);
	else
		animationBreak.on_draw(camera, (int)position.x, (int)position.y);
	Bullet::on_draw(camera);
}


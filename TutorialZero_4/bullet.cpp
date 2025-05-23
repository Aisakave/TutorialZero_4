#include "bullet.h"

void Bullet::setDamage(int val) 
{
    damage = val;
}

int Bullet::getDamage() const 
{
    return damage;
}

void Bullet::setPosition(float x, float y)
{
    position.x = x, position.y = y;
}

const Vector2& Bullet::getPosition() const 
{
    return position;
}

const Vector2& Bullet::getSize() const 
{
    return size;
}

void Bullet::setVelocity(float x, float y)
{

    velocity.x = x, velocity.y = y;
}

void Bullet::setCollideTarget(const PlayerID& id) 
{
    targetID = id;
}

const PlayerID& Bullet::getCollideTarget() const 
{
    return targetID;
}

void Bullet::setValid(bool flag) 
{
    isValid = flag;
}

bool Bullet::getValid() const 
{
    return isValid;
}

bool Bullet::checkCanRemove() const
{

    return isCanRemove;
}

bool Bullet::checkIsCollision(const Vector2& position, const Vector2& size) 
{
    // 计算子弹的中心位置
    auto x = this->position.x + this->size.x / 2; 
    auto y = this->position.y + this->size.y / 2;

    //判断子弹的中心位置坐标
    return x >= position.x && x <= position.x + size.x && y >= position.y && y <= position.y + size.y;

}

void Bullet::onCollide()
{
    if (callback)
        callback();
}

void Bullet::setCallback(const std::function<void()>& callback_) 
{

    this->callback = callback_;
}

bool Bullet::checkIsExceedScreen()
{

    int w = getwidth(), h = getheight();

    auto x = this->position.x + size.x;
    auto y = this->position.y + size.y;

    return x <= 0 || x >= w || y <= 0 || y >= h;

}

void Bullet::on_updata(int delta) 
{

}

void Bullet::on_draw(const Camera& camera) const
{
    if (is_debug) {
        setfillcolor(RGB(255, 255, 255));
        setlinecolor(RGB(255, 255, 255));

        rectangle((int)position.x, (int)position.y, (int)(position.x + size.x), (int)(position.y + size.y));
        // 在图片的中心画圆
        solidcircle(int(position.x + size.x / 2), (int)(position.y + size.y / 2), 5);
    }
   
}


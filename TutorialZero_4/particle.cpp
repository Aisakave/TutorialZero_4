#include "particle.h"

void Particle::setPosition(const Vector2& position) 
{
	this->position = position;
}

void Particle::setAtlas(Atlas* atlas) 
{
	this->atlas = atlas;
}

void Particle::setLifeSpan(int lifeSpan)
{
	this->lifeSpan = lifeSpan;
}

bool Particle::checkIsValid() const 
{
	return isValid;
}

void Particle::on_updata(int delta)
{

	timer += delta;

	if (timer >= lifeSpan)
	{

		timer = 0;
		index++;

		// 粒子在播完动画后消失
		if (index == atlas->get_size())
		{

			index = atlas->get_size() - 1;

			isValid = false;

		}
	}
}

void Particle::on_draw() const 
{

	putimage_alpha(position.x, position.y, atlas->get_image(index));
}


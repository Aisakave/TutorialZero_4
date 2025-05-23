#pragma once
#include "vector2.h"
#include <functional>
#include "player_id.h"
#include "camera.h"
#include "graphics.h"

extern bool is_debug;

class Bullet 
{

public:
	// �˺�
	void setDamage(int val);
	int getDamage() const;
	// λ��
	void setPosition(float x, float y);
	const Vector2& getPosition() const;
	const Vector2& getSize() const;
	// �ٶ�
	void setVelocity(float x, float y);

	// ��ײ
	void setCollideTarget(const PlayerID& id);
	const PlayerID& getCollideTarget() const;

	void setValid(bool flag);
	bool getValid() const;
	bool checkCanRemove() const;

	virtual bool checkIsCollision(const Vector2& position, const Vector2& size);	// �����ײ
	virtual void onCollide();														// ������ײ

	// �ص�
	void setCallback(const std::function<void()>& callbcak_);

protected:
	// ��Ļ
	bool checkIsExceedScreen();


public:
	virtual void on_updata(int delta);
	virtual void on_draw(const Camera& camera) const;

protected:

	// �ӵ��ƶ�
	Vector2 position;		// λ��
	Vector2 size;			// �ߴ�
	Vector2 velocity;		// �ٶ�

	// �˺�
	int damage = 10;

	// �ӵ�״̬
	bool isValid = true;
	bool isCanRemove = false;

	// �ص����������������
	std::function<void()> callback;

	// Ŀ�����
	PlayerID targetID = PlayerID::P1;

};

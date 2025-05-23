#pragma once
#include "camera.h"
#include "vector2.h"
#include "bullet.h"
#include "platform.h"
#include "particle.h"
#include "animation.h"
#include "player_id.h"
#include <graphics.h>

extern IMAGE img1PCursor;
extern IMAGE img2PCursor;

extern Atlas atlasRunEffect;
extern Atlas atlasJumpEffect;
extern Atlas atlasLandEffect;

extern bool is_debug;
extern std::vector<Platform> platform_list;
extern std::vector<Bullet*> bullet_list;

class Player
{
public:
	Player(bool isFacingRight = true);
	~Player() = default;
	
	virtual void on_updata(int delta);
	virtual void on_draw(const Camera& camera);
	virtual void on_input(const ExMessage& msg);

	void setId(const PlayerID& id);
	void setPos(float x, float y);
public:
	const Vector2& getPosition() const;
	const Vector2& getSize() const;

public:
	// ����
	virtual void on_attack() = 0;
	virtual void on_attack_ex() = 0;
protected:
	// �޵�
	void makeInvulnerable();
public:
	void setHp(int val);
	void setMp(int val);
	const int getHp() const;
	const int getMp() const;

protected:
	virtual void on_run(float distance);		// ����
	virtual void on_jump();						// ��Ծ
	virtual void on_land();						// ���

protected:
	const float run_velocity = 0.55f;           // �ܶ��ٶ�
	const float jump_velocity = -0.85;			// ��Ծ�ٶ�
	const float gravity = 1.6e-3f;				// �������ٶ�
protected:
	void move_and_collide(int delta);			// ��������ײ

protected:
	// �ƶ���Ϣ
	Vector2 position;                           // ��ɫλ��
	Vector2 size;							    // ��ײ�ߴ�
	Vector2 velocity;							// ����ٶ�
	bool isFacingRight = true;					// ��ǰ����Ƿ����Ҳ� ���ݰ����ж�

	// HP MP
	int hp = 100, mp = 0;
	// ����
	int attack_cd = 500;						// ��ͨ������ȴʱ��
	bool can_attack = true;						// �Ƿ�����ͷ���ͨ����
	Timer timer_attack_cd;						// ��ͨ������ȴ��ʱ��
	bool isAttackingEx = false;

	// �޵�
	IMAGE imgSketch;

	bool isInvulnerable = false;
	bool isShowSketchFram = false;				// ��ǰ֡�Ƿ�Ӧ����ʾ��Ӱ

	Timer timerInvulnerable;					// ����޵�
	Timer timerInvulnerableBlink;				// ��˸�л�
	
	// ������Ч
	std::vector<Particle> particles;

	Timer timerRunEffectGeneration;				// ����ܶ����ӷ�����
	Timer timerDieEffectGeneration;				// ����������ӷ�����

	// ��ʼ�����
	bool isCursorVisible = true;
	Timer timerCursorVisibility;

	// ����
	Vector2 lastHurtDirection;					// ����ʱ���ܻ�����

	// ������Ϣ
	bool isLeftKeyDown = false;					// �����ƶ������Ƿ���
	bool isRightKeyDown = false;				// �����ƶ������Ƿ���



	// ��Ⱦ����
	Animation animationIdleLeft;
	Animation animationIdleRight;
	Animation animationRunLeft;
	Animation animationRunRight;
	Animation animationAttackExLeft;
	Animation animationAttackExRight;

	Animation animationJumpEffect;				// ��Ծ����
	Animation animationLandEffect;				// ���

	Animation animationDieLeft;					// ����
	Animation animationDieRight;

	bool isJumpEffectVisible = false;			// ��Ծ�ɼ�
	bool isLandEffectVisible = false;			// ��ؿɼ�

	Vector2 positionJumpEffect;
	Vector2 positionLandEffect;

	Animation* current_animation = nullptr;		// ��ǰ���ڲ��ŵĶ���

	PlayerID id = PlayerID::P1;					// ������ ID
};


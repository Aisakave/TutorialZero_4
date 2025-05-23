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
	// 攻击
	virtual void on_attack() = 0;
	virtual void on_attack_ex() = 0;
protected:
	// 无敌
	void makeInvulnerable();
public:
	void setHp(int val);
	void setMp(int val);
	const int getHp() const;
	const int getMp() const;

protected:
	virtual void on_run(float distance);		// 奔跑
	virtual void on_jump();						// 跳跃
	virtual void on_land();						// 落地

protected:
	const float run_velocity = 0.55f;           // 跑动速度
	const float jump_velocity = -0.85;			// 跳跃速度
	const float gravity = 1.6e-3f;				// 重力加速度
protected:
	void move_and_collide(int delta);			// 重力和碰撞

protected:
	// 移动信息
	Vector2 position;                           // 角色位置
	Vector2 size;							    // 碰撞尺寸
	Vector2 velocity;							// 玩家速度
	bool isFacingRight = true;					// 当前玩家是否朝向右侧 根据按键判断

	// HP MP
	int hp = 100, mp = 0;
	// 攻击
	int attack_cd = 500;						// 普通攻击冷却时间
	bool can_attack = true;						// 是否可以释放普通攻击
	Timer timer_attack_cd;						// 普通攻击冷却定时器
	bool isAttackingEx = false;

	// 无敌
	IMAGE imgSketch;

	bool isInvulnerable = false;
	bool isShowSketchFram = false;				// 当前帧是否应该显示剪影

	Timer timerInvulnerable;					// 玩家无敌
	Timer timerInvulnerableBlink;				// 闪烁切换
	
	// 粒子特效
	std::vector<Particle> particles;

	Timer timerRunEffectGeneration;				// 玩家跑动粒子发射器
	Timer timerDieEffectGeneration;				// 玩家死亡粒子发射器

	// 初始化光标
	bool isCursorVisible = true;
	Timer timerCursorVisibility;

	// 死亡
	Vector2 lastHurtDirection;					// 死亡时的受击方向

	// 按键信息
	bool isLeftKeyDown = false;					// 向左移动按键是否按下
	bool isRightKeyDown = false;				// 向右移动按键是否按下



	// 渲染数据
	Animation animationIdleLeft;
	Animation animationIdleRight;
	Animation animationRunLeft;
	Animation animationRunRight;
	Animation animationAttackExLeft;
	Animation animationAttackExRight;

	Animation animationJumpEffect;				// 跳跃动画
	Animation animationLandEffect;				// 落地

	Animation animationDieLeft;					// 死亡
	Animation animationDieRight;

	bool isJumpEffectVisible = false;			// 跳跃可见
	bool isLandEffectVisible = false;			// 落地可见

	Vector2 positionJumpEffect;
	Vector2 positionLandEffect;

	Animation* current_animation = nullptr;		// 当前正在播放的动画

	PlayerID id = PlayerID::P1;					// 玩家序号 ID
};


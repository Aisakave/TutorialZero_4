#pragma once
#include "timer.h"
#include "vector2.h"

class Camera 
{
public:
	Camera();
	~Camera() = default;
public:
	void reset();
	void on_updata(int runTimeMs);				//让摄像机执行时间
	void shake(float strength, int duration);
public:
	const Vector2& get_postion() const;


private:
	Vector2 position; // 摄像机位置
	Timer timer_shake; // 摄像机抖动定时器
	bool is_shaking; // 摄像机是否在抖动
	float shaking_strength; // 摄像机抖动幅度
};

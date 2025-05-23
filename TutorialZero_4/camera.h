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
	void on_updata(int runTimeMs);				//�������ִ��ʱ��
	void shake(float strength, int duration);
public:
	const Vector2& get_postion() const;


private:
	Vector2 position; // �����λ��
	Timer timer_shake; // �����������ʱ��
	bool is_shaking; // ������Ƿ��ڶ���
	float shaking_strength; // �������������
};

#pragma once
#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;
public:
	void restart();
	void set_wait_time(int val);
	void set_one_shot(bool flag);
	void set_callback(const std::function<void()>& callback_);
public:
	void setTimer(int timerMs, bool isOneShot, const std::function<void()>& cb);
public:
	void pause();
	void resume();							//�ָ�����

public:
	void on_updata(int runTimeMs);				//�ö�ʱ������runTimeMs


private:
	int pass_time = 0; // �ѹ�ʱ��
	int wait_time = 0; // �ȴ�ʱ��
	bool paused = false; // �Ƿ���ͣ
	bool shotted = false; // �Ƿ񴥷�
	bool one_shot = false; // ���δ���
	std::function<void()> callback;
};


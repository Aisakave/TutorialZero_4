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
	void resume();							//恢复运行

public:
	void on_updata(int runTimeMs);				//让定时器运行runTimeMs


private:
	int pass_time = 0; // 已过时间
	int wait_time = 0; // 等待时间
	bool paused = false; // 是否暂停
	bool shotted = false; // 是否触发
	bool one_shot = false; // 单次触发
	std::function<void()> callback;
};


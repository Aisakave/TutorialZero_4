#include "timer.h"

void Timer::restart()
{
	pass_time = 0;
	shotted = false;
}

void Timer::set_wait_time(int val)
{
	wait_time = val;
}

void Timer::set_one_shot(bool flag)
{
	one_shot = flag;
}

void Timer::set_callback(const std::function<void()>& callback_)
{
	this->callback = callback_;
}

void Timer::pause()
{
	paused = true;
}

void Timer::resume()
{
	paused = false;
}

void Timer::on_updata(int runTimeMs)
{
	if (paused)
		return;

	pass_time += runTimeMs;
	if (pass_time >= wait_time)
	{
		if ((!one_shot || (one_shot && !shotted)) && callback)
			callback();

		shotted = true;
		pass_time = 0;
	}
}
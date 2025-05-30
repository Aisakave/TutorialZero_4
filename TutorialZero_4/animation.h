#pragma once
#include "atlas.h"
#include "util.h"
#include "camera.h"
#include <graphics.h>
#include <functional>

class Animation
{
public:
	Animation() = default;
	~Animation() = default;

public:
	void reset();

	void set_atlas(Atlas* new_atlas);

	void set_loop(bool flag);

	void set_interval(int ms);

	int get_idx_frame();

	IMAGE* get_frame();

	bool check_finished();

	void on_updata(int delta);

	void on_draw(const Camera& camera, int x, int y) const;

	void set_callback(std::function<void()> callback_);

private:
	int timer = 0; // ��ʱ��
	int interval = 0; // ֡���
	int idx_frame = 0; // ֡����
	bool is_loop = true;
	Atlas* atlas = nullptr;
	std::function<void()> callback;

};


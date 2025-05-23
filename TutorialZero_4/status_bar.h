#pragma once

#include "util.h"

class StatusBar
{
public:
	void setAvatar(IMAGE* img);
	void setPosition(int x, int y);

	void setHp(int val);
	void setMp(int val);

	void on_draw();

private:
	const int width = 275;			// ×´Ì¬Ìõ¿í¶È

private:
	int hp = 0;
	int mp = 0;
	POINT position = { 0 };
	IMAGE* imgAvatar = nullptr;
};


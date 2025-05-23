#pragma once
#include "scene.h"

extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* selector_scene;

class SceneManager
{
public:
	enum class SceneType{ Menu, Game, Selector };
public:
	SceneManager() = default;
	~SceneManager() = default;

	void set_current_scene(Scene* scene);

	void switch_to(SceneType type);

	void on_updata(int delta);

	void on_draw(const Camera& camera);

	void on_input(const ExMessage& msg);

private:
	Scene* current_scene = nullptr;
};


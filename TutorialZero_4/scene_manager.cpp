#include "scene_manager.h"

void SceneManager::set_current_scene(Scene* scene)
{
	current_scene = scene;
	current_scene->on_enter();
}

void SceneManager::switch_to(SceneType type)
{
	current_scene->on_exit();
	switch (type)
	{
	case SceneType::Menu:
		current_scene = menu_scene;
		break;
	case SceneType::Game:
		current_scene = game_scene;
		break;
	case SceneType::Selector:
		current_scene = selector_scene;
	default:
		break;
	}
	current_scene->on_enter();
}

void SceneManager::on_updata(int delta)
{
	current_scene->on_updata(delta);
}

void SceneManager::on_draw(const Camera& camera)
{
	current_scene->on_draw(camera);
}

void SceneManager::on_input(const ExMessage& msg)
{
	current_scene->on_input(msg);
}
#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "atlas.h"

extern SceneManager scene_manager;
extern Atlas atlasPeaShooterRunRight;
extern IMAGE imgMenuBackground;

class MenuScene : public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	void on_enter();
	void on_updata(int delta);
	void on_draw(const Camera& camera);
	void on_input(const ExMessage& msg);
	void on_exit();
	 
private:

};
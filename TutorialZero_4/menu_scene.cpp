#include "menu_scene.h"
#include <iostream>

void MenuScene::on_enter() 
{
	mciSendString(_T("play bgmMenu repeat from 0"), nullptr, 0, nullptr);

}

void MenuScene::on_input(const ExMessage& msg) 
{
	if (msg.message == WM_KEYUP)
	{
		mciSendString(_T("play uiConfirm from 0"), nullptr, 0, nullptr);
		scene_manager.switch_to(SceneManager::SceneType::Selector);
	}
}

void MenuScene::on_updata(int delta)
{

}

void MenuScene::on_draw(const Camera& camera)
{
	putimage(0, 0, &imgMenuBackground);
}

void MenuScene::on_exit() 
{

}

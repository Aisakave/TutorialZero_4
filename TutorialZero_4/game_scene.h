#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "util.h"
#include "status_bar.h"
#include "player.h"
#include "platform.h"
#include <vector>

extern IMAGE imgSky;									//天空
extern IMAGE imgHills;									//山脉
extern IMAGE imgLargePlatform;							//平台
extern IMAGE imgSmallPlatform;

extern IMAGE img1PWinner;
extern IMAGE img2PWinner;
extern IMAGE imgWinnerBar;

extern Camera main_camera;
extern SceneManager scene_manager;
extern std::vector<Platform> platform_list;
extern Player* player_1;
extern Player* player_2;

extern IMAGE* imgPlayer1Avatar;
extern IMAGE* imgPlayer2Avatar;

class GameScene : public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter(); // 进入
	void on_updata(int delta); // 更新
	void on_draw(const Camera& camera); // 渲染
	void on_input(const ExMessage& msg); // 输入
	void on_exit(); // 退出

private:
	// 天空和山脉 世界坐标
	POINT posImgSky = { 0 };
	POINT posImgHills = { 0 };

	// 状态栏
	StatusBar statusBar1P, statusBar2P;

	bool isGameOver = false;
	// 结算动画
	POINT posImgWinnerBar = { 0 };
	POINT posImgWinnerText = { 0 };

	int posXImgWinnerBarDst = 0;
	int posXImgWinnerTextDst = 0;

	Timer timerWinnerSlideIn, timerWinnerSlideOut;

	float speedWinnerBar = 3.0;
	float speedWinnerText = 1.5;

	bool isSlideOutStarted = false;
	
};


#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "animation.h"
#include "player_id.h"
#include "sunflower_player.h"
#include "peashooter_player.h"

//VS艺术字
extern IMAGE imgVS;
//玩家
extern IMAGE img1P;
extern IMAGE img2P;
//键位描述
extern IMAGE img1PDesc;
extern IMAGE img2PDesc;
//背景
extern IMAGE imgSelectorBackground;
//提示信息
extern IMAGE imgSelectorTip;
//墓碑
extern IMAGE imgGraveStoneLeft;
extern IMAGE imgGraveStoneRight;

//1P button
extern IMAGE img1PSelectorButtonIdleLeft;
extern IMAGE img1PSelectorButtonIdleRight;
extern IMAGE img1PSelectorButtonDownLeft;
extern IMAGE img1PSelectorButtonDownRight;
//2P button
extern IMAGE img2PSelectorButtonIdleLeft;
extern IMAGE img2PSelectorButtonIdleRight;
extern IMAGE img2PSelectorButtonDownLeft;
extern IMAGE img2PSelectorButtonDownRight;
//background
extern IMAGE imgPeaShooterSelectorBackgroundLeft;
extern IMAGE imgPeaShooterSelectorBackgroundRight;
extern IMAGE imgSunFlowerSelectorBackgroundLeft;
extern IMAGE imgSunFlowerSelectorBackgroundRight;

extern Atlas atlasPeaShooterIdleRight;
extern Atlas atlasSunFlowerIdleRight;

extern IMAGE imgPeaShooterAvatar;
extern IMAGE imgSunFlowerAvatar;

extern Player* player_1;
extern Player* player_2;
extern SceneManager scene_manager;

extern IMAGE* imgPlayer1Avatar;	
extern IMAGE* imgPlayer2Avatar;

class SelectorScene : public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	void on_enter();
	void on_updata(int delta);
	void on_draw(const Camera& camera);
	void on_input(const ExMessage& msg);
	void on_exit();

private:
	enum class PlayerType {Peashooter = 0, Sunflower, Invalid };
private:
	POINT posImgVS = { 0 };							//VS艺术字 位置
	POINT posImgTip = { 0 };						//提示信息 位置
	POINT posImg1P = { 0 };							//1P 位置
	POINT posImg2P = { 0 };							//2P 位置

	POINT posImg1PDesc = { 0 };						//1P键位描述 位置
	POINT posImg2PDesc = { 0 };						//2P键位描述 位置
	POINT posImg1PName = { 0 };						//1P姓名 位置
	POINT posImg2PName = { 0 };						//2P姓名 位置

	POINT posAnimation1P = { 0 };					//1P角色动画 位置
	POINT posAnimation2P = { 0 };					//2P角色动画 位置

	POINT posImg1PGravestone = { 0 };				//1P墓碑 位置
	POINT posImg2PGravestone = { 0 };				//2P墓碑 位置

	POINT pos1PSelectorButtonLeft = { 0 };			//1P向左切换按钮 位置
	POINT pos1PSelectorButtonRight = { 0 };			//1P向右切换按钮 位置
	POINT pos2PSelectorButtonLeft = { 0 };			//2P向左切换按钮 位置
	POINT pos2PSelectorButtonRight = { 0 };			//2P向右切换按钮 位置

	Animation animationPeaShooter;
	Animation animationSunFlower;

	PlayerType player_type_1 = PlayerType::Peashooter;	
	PlayerType player_type_2 = PlayerType::Sunflower;

	LPCTSTR str_peashooter_name = _T("婉逗射手"); 
	LPCTSTR str_sunflower_name = _T("龙日葵");

	int selectorBackgroundScrollX = 0; // 背景板滚动距离

	bool isButton1PDownLeft = false; // 1P 向左切换按钮是否按下
	bool isButton1PDownRight = false;
	bool isButton2PDownLeft = false; // 2P 向左切换按钮是否按下
	bool isButton2PDownRight = false;

private:
	void outtextxy_shaded(int x, int y, LPCTSTR str)
	{
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}
};


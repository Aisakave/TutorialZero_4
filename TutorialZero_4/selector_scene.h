#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "animation.h"
#include "player_id.h"
#include "sunflower_player.h"
#include "peashooter_player.h"

//VS������
extern IMAGE imgVS;
//���
extern IMAGE img1P;
extern IMAGE img2P;
//��λ����
extern IMAGE img1PDesc;
extern IMAGE img2PDesc;
//����
extern IMAGE imgSelectorBackground;
//��ʾ��Ϣ
extern IMAGE imgSelectorTip;
//Ĺ��
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
	POINT posImgVS = { 0 };							//VS������ λ��
	POINT posImgTip = { 0 };						//��ʾ��Ϣ λ��
	POINT posImg1P = { 0 };							//1P λ��
	POINT posImg2P = { 0 };							//2P λ��

	POINT posImg1PDesc = { 0 };						//1P��λ���� λ��
	POINT posImg2PDesc = { 0 };						//2P��λ���� λ��
	POINT posImg1PName = { 0 };						//1P���� λ��
	POINT posImg2PName = { 0 };						//2P���� λ��

	POINT posAnimation1P = { 0 };					//1P��ɫ���� λ��
	POINT posAnimation2P = { 0 };					//2P��ɫ���� λ��

	POINT posImg1PGravestone = { 0 };				//1PĹ�� λ��
	POINT posImg2PGravestone = { 0 };				//2PĹ�� λ��

	POINT pos1PSelectorButtonLeft = { 0 };			//1P�����л���ť λ��
	POINT pos1PSelectorButtonRight = { 0 };			//1P�����л���ť λ��
	POINT pos2PSelectorButtonLeft = { 0 };			//2P�����л���ť λ��
	POINT pos2PSelectorButtonRight = { 0 };			//2P�����л���ť λ��

	Animation animationPeaShooter;
	Animation animationSunFlower;

	PlayerType player_type_1 = PlayerType::Peashooter;	
	PlayerType player_type_2 = PlayerType::Sunflower;

	LPCTSTR str_peashooter_name = _T("������"); 
	LPCTSTR str_sunflower_name = _T("���տ�");

	int selectorBackgroundScrollX = 0; // �������������

	bool isButton1PDownLeft = false; // 1P �����л���ť�Ƿ���
	bool isButton1PDownRight = false;
	bool isButton2PDownLeft = false; // 2P �����л���ť�Ƿ���
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


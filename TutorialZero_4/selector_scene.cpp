#include "selector_scene.h"
#include <iostream>

void SelectorScene::on_enter()
{
	animationPeaShooter.set_atlas(&atlasPeaShooterIdleRight);
	animationSunFlower.set_atlas(&atlasSunFlowerIdleRight);
	animationPeaShooter.set_interval(100);
	animationSunFlower.set_interval(100);

	static const int OFFSET_X = 50;

	//getwidth:窗口width
		//图片窗口居中 = (窗口 - 图片) / 2
	posImgVS.x = (getwidth() - imgVS.getwidth()) / 2;
	posImgVS.y = (getheight() - imgVS.getheight()) / 2;
	posImgTip.x = (getwidth() - imgSelectorTip.getwidth()) / 2;
	posImgTip.y = getheight() - 125;
	posImg1P.x = (getwidth() / 2 - img1P.getwidth()) / 2 - OFFSET_X;
	posImg1P.y = 35;
	posImg2P.x = getwidth() / 2 + (getwidth() / 2 - img2P.getwidth()) / 2 + OFFSET_X;
	posImg2P.y = posImg1P.y;
	posImg1PDesc.x = (getwidth() / 2 - img1PDesc.getwidth()) / 2 - OFFSET_X;
	posImg1PDesc.y = getheight() - 150;
	posImg2PDesc.x = getwidth() / 2 + (getwidth() / 2 - img2PDesc.getwidth()) / 2 + OFFSET_X;
	posImg2PDesc.y = posImg1PDesc.y;
	posImg1PGravestone.x = (getwidth() / 2 - imgGraveStoneRight.getwidth()) / 2 - OFFSET_X;
	posImg1PGravestone.y = posImg1P.y + img1P.getheight() + 35;
	posImg2PGravestone.x = getwidth() / 2 + (getwidth() / 2 - imgGraveStoneLeft.getwidth()) / 2 + OFFSET_X;
	posImg2PGravestone.y = posImg1PGravestone.y;
	posAnimation1P.x = (getwidth() / 2 - atlasPeaShooterIdleRight.get_image(0)->getwidth()) / 2 - OFFSET_X;
	posAnimation1P.y = posImg1PGravestone.y + 80;
	posAnimation2P.x = getwidth() / 2 + (getwidth() / 2 - atlasPeaShooterIdleRight.get_image(0)->getwidth()) / 2 + OFFSET_X;
	posAnimation2P.y = posAnimation1P.y;
	posImg1PName.y = posAnimation1P.y + 155;
	posImg2PName.y = posImg1PName.y;
	pos1PSelectorButtonLeft.x = posImg1PGravestone.x - img1PSelectorButtonIdleLeft.getwidth();
	pos1PSelectorButtonLeft.y = posImg1PGravestone.y + (imgGraveStoneRight.getheight() - img1PSelectorButtonIdleLeft.getheight()) / 2;
	pos1PSelectorButtonRight.x = posImg1PGravestone.x + imgGraveStoneRight.getwidth();
	pos1PSelectorButtonRight.y = pos1PSelectorButtonLeft.y;
	pos2PSelectorButtonLeft.x = posImg2PGravestone.x - img2PSelectorButtonIdleLeft.getwidth();
	pos2PSelectorButtonLeft.y = pos1PSelectorButtonLeft.y;
	pos2PSelectorButtonRight.x = posImg2PGravestone.x + imgGraveStoneLeft.getwidth();
	pos2PSelectorButtonRight.y = pos1PSelectorButtonLeft.y;
}

void SelectorScene::on_input(const ExMessage& msg)
{
	switch (msg.message) 
	{
	case WM_KEYDOWN:
		switch (msg.vkcode) 
		{
			//A
		case 0x41:

			isButton1PDownLeft = true;
			break;
			//D
		case 0x44:
			isButton1PDownRight = true;
			break;
			// '<-'
		case VK_LEFT:
			isButton2PDownLeft = true;
			break;
			// '->'
		case VK_RIGHT:
			isButton2PDownRight = true;
			break;
		}
		break;
	case WM_KEYUP:
		switch (msg.vkcode) 
		{
			//A
		case 0x41:
			isButton1PDownLeft = false;
			//使玩家 在 [peaShooter, inlvalid)切换
				//Enum 类 默认是由0开始的int变量
			player_type_1 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_1 - 1) % (int)PlayerType::Invalid);
			mciSendString(_T("play uiSwitch from 0"), NULL, 0, NULL);
			break;
			//D
		case 0x44:
			isButton1PDownRight = false;
			player_type_1 = PlayerType(((int)player_type_1 + 1) % (int)PlayerType::Invalid);
			mciSendString(_T("play uiSwitch from 0"), NULL, 0, NULL);
			break;
		case VK_LEFT:
			isButton2PDownLeft = false;
			player_type_2 = PlayerType(((int)player_type_2 - 1 + (int)PlayerType::Invalid)  % (int)PlayerType::Invalid);
			mciSendString(_T("play uiSwitch from 0"), NULL, 0, NULL);
			break;
		case VK_RIGHT:
			isButton2PDownRight = false;
			player_type_2 = PlayerType(((int)player_type_2 + 1) % (int)PlayerType::Invalid);
			mciSendString(_T("play uiSwitch from 0"), NULL, 0, NULL);
			break;
		case VK_RETURN:
			scene_manager.switch_to(SceneManager::SceneType::Game);
			mciSendString(_T("play uiSwitch from 0"), NULL, 0, NULL);
			break;
		}
		break;
	default:
		break;
	}
}

void SelectorScene::on_updata(int delta)
{
	//动画更新 delta
	animationPeaShooter.on_updata(delta);
	animationSunFlower.on_updata(delta);

	//背景线
	selectorBackgroundScrollX += 5;
	if (selectorBackgroundScrollX >= imgPeaShooterSelectorBackgroundLeft.getwidth())
		selectorBackgroundScrollX = 0;
}

void SelectorScene::on_draw(const Camera& camera)
{
	IMAGE* img1PselectorBackground = nullptr;
	IMAGE* img2PselectorBackground = nullptr;

	switch (player_type_2) {
	case PlayerType::Peashooter:
		img1PselectorBackground = &imgPeaShooterSelectorBackgroundRight;
		break;
	case PlayerType::Sunflower:
		img1PselectorBackground = &imgSunFlowerSelectorBackgroundRight;
		break;
	default:
		img1PselectorBackground = &imgPeaShooterSelectorBackgroundRight;
		break;
	}

	switch (player_type_1) {
	case  PlayerType::Peashooter:
		img2PselectorBackground = &imgPeaShooterSelectorBackgroundLeft;
		break;
	case PlayerType::Sunflower:
		img2PselectorBackground = &imgSunFlowerSelectorBackgroundLeft;
		break;
	default:
		img2PselectorBackground = &imgPeaShooterSelectorBackgroundLeft;
		break;
	}

	putimage(0, 0, &imgSelectorBackground);

	// 渲染滚动背景
	putimage_alpha(selectorBackgroundScrollX - img1PselectorBackground->getwidth(), 0, img1PselectorBackground);
	putimage_alpha(selectorBackgroundScrollX, 0,
		img1PselectorBackground->getwidth() - selectorBackgroundScrollX, 0, img1PselectorBackground, 0, 0);
	putimage_alpha(getwidth() - img2PselectorBackground->getwidth(), 0, img2PselectorBackground->getwidth() -
		selectorBackgroundScrollX, 0, img2PselectorBackground, selectorBackgroundScrollX, 0);
	putimage_alpha(getwidth() - selectorBackgroundScrollX, 0, img2PselectorBackground);


	putimage_alpha(posImgVS.x, posImgVS.y, &imgVS);

	putimage_alpha(posImg1P.x, posImg1P.y, &img1P);
	putimage_alpha(posImg2P.x, posImg2P.y, &img2P);

	// 动画在墓碑之上——需要先渲染墓碑
	putimage_alpha(posImg1PGravestone.x, posImg1PGravestone.y, &imgGraveStoneRight);
	putimage_alpha(posImg2PGravestone.x, posImg2PGravestone.y, &imgGraveStoneLeft);

	switch (player_type_1)
	{
	case SelectorScene::PlayerType::Peashooter:
		animationPeaShooter.on_draw(camera, posAnimation1P.x, posAnimation1P.y);
		posImg1PName.x = posImg1PGravestone.x + (imgGraveStoneRight.getwidth() - textwidth(str_peashooter_name)) / 2;
		outtextxy_shaded(posImg1PName.x, posImg1PName.y, str_peashooter_name);
		break;
	case SelectorScene::PlayerType::Sunflower:
		animationSunFlower.on_draw(camera, posAnimation1P.x, posAnimation1P.y);
		posImg1PName.x = posImg1PGravestone.x + (imgGraveStoneRight.getwidth() - textwidth(str_sunflower_name)) / 2;
		outtextxy_shaded(posImg1PName.x, posImg1PName.y, str_sunflower_name);
		break;
	}


	switch (player_type_2)
	{
	case SelectorScene::PlayerType::Peashooter:
		animationPeaShooter.on_draw(camera, posAnimation2P.x, posAnimation2P.y);
		posImg2PName.x = posImg2PGravestone.x + (imgGraveStoneLeft.getwidth() - textwidth(str_peashooter_name)) / 2;
		outtextxy_shaded(posImg2PName.x, posImg2PName.y, str_peashooter_name);
		break;
	case SelectorScene::PlayerType::Sunflower:
		animationSunFlower.on_draw(camera, posAnimation2P.x, posAnimation2P.y);
		posImg2PName.x = posImg2PGravestone.x + (imgGraveStoneLeft.getwidth() - textwidth(str_sunflower_name)) / 2;
		outtextxy_shaded(posImg2PName.x, posImg2PName.y, str_sunflower_name);
		break;
	}


	// 按钮
	putimage_alpha(pos1PSelectorButtonLeft.x, pos1PSelectorButtonLeft.y,
		isButton1PDownLeft ? &img1PSelectorButtonDownLeft : &img1PSelectorButtonIdleLeft);
	putimage_alpha(pos1PSelectorButtonRight.x, pos1PSelectorButtonRight.y,
		isButton1PDownRight ? &img1PSelectorButtonDownRight : &img1PSelectorButtonIdleRight);

	putimage_alpha(pos2PSelectorButtonLeft.x, pos2PSelectorButtonLeft.y,
		isButton2PDownLeft ? &img2PSelectorButtonDownLeft : &img2PSelectorButtonIdleLeft);
	putimage_alpha(pos2PSelectorButtonRight.x, pos2PSelectorButtonRight.y,
		isButton2PDownRight ? &img2PSelectorButtonDownRight : &img2PSelectorButtonIdleRight);

	// 辅助信息
	putimage_alpha(posImg1PDesc.x, posImg1PDesc.y, &img1PDesc);
	putimage_alpha(posImg2PDesc.x, posImg2PDesc.y, &img2PDesc);
	putimage_alpha(posImgTip.x, posImgTip.y, &imgSelectorTip);

}

void SelectorScene::on_exit()
{
	switch (player_type_1)
	{
	case PlayerType::Peashooter:
		player_1 = new PeashooterPlayer();
		imgPlayer1Avatar = &imgPeaShooterAvatar;
		break;
	case PlayerType::Sunflower:
		player_1 = new SunflowerPlayer();
		imgPlayer1Avatar = &imgSunFlowerAvatar;
		break;
	}
	player_1->setId(PlayerID::P1);

	switch (player_type_2)
	{
	case PlayerType::Peashooter:
		player_2 = new PeashooterPlayer(false);
		imgPlayer2Avatar = &imgPeaShooterAvatar;
		break;
	case PlayerType::Sunflower:
		player_2 = new SunflowerPlayer(false);
		imgPlayer2Avatar = &imgSunFlowerAvatar;
		break;
	}
	player_2->setId(PlayerID::P2);

	mciSendString(_T("stop bgmMenu"), nullptr, 0, nullptr);
}

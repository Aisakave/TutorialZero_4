#include "game_scene.h"
#include <iostream>

void GameScene::on_enter() 
{
	// 结算初始化
	isGameOver = false, isSlideOutStarted = false;
	posImgWinnerBar.x = -imgWinnerBar.getwidth();
	posImgWinnerBar.y = (getheight() - imgWinnerBar.getheight()) / 2;
	posXImgWinnerBarDst = (getwidth() - imgWinnerBar.getwidth()) / 2;

	posImgWinnerText.x = posImgWinnerBar.x;
	posImgWinnerText.y = (getheight() - img1PWinner.getheight()) / 2;
	posXImgWinnerTextDst = (getwidth() - img1PWinner.getwidth()) / 2;

	timerWinnerSlideIn.restart();
	timerWinnerSlideIn.set_one_shot(true);
	timerWinnerSlideIn.set_wait_time(2500);
	timerWinnerSlideIn.set_callback
	(
		[&] 
		{
			isSlideOutStarted = true;
		}
	);

	timerWinnerSlideOut.restart();
	timerWinnerSlideOut.set_one_shot(true);
	timerWinnerSlideOut.set_wait_time(1000);
	timerWinnerSlideOut.set_callback
	(
		[&] 
		{
			scene_manager.switch_to(SceneManager::SceneType::Menu);
		}
	);

	// 设置状态条头像
	statusBar1P.setAvatar(imgPlayer1Avatar);
	statusBar2P.setAvatar(imgPlayer2Avatar);

	statusBar1P.setPosition(235, 625);
	statusBar2P.setPosition(675, 625);

	player_1->setPos(200, 50);
	player_2->setPos(975, 50);

	int xWindow = getwidth(), yWindow = getheight();

	// 窗口居中
	posImgSky.x = (xWindow - imgSky.getwidth()) / 2,
	posImgSky.y = (yWindow - imgSky.getheight()) / 2;
	posImgHills.x = (xWindow - imgHills.getwidth()) / 2,
	posImgHills.y = (yWindow - imgHills.getheight()) / 2;

	// 初始化平台
	platform_list.resize(4);
	Platform& large_platform = platform_list[0];
	large_platform.img = &imgLargePlatform;
	large_platform.renderPos.x = 122, large_platform.renderPos.y = 455;

	// 碰撞箱 一般 位于 渲染图内部偏上
	large_platform.shape.left = large_platform.renderPos.x + 30,
	large_platform.shape.right = large_platform.renderPos.x + large_platform.img->getwidth() - 30,
	large_platform.shape.y = large_platform.renderPos.y + 60;

	//small1
	auto& smallPlatform1 = platform_list[1];

	smallPlatform1.img = &imgSmallPlatform;
	smallPlatform1.renderPos.x = 175, smallPlatform1.renderPos.y = 360;

	smallPlatform1.shape.left = smallPlatform1.renderPos.x + 40,
	smallPlatform1.shape.right = smallPlatform1.renderPos.x + smallPlatform1.img->getwidth() - 40,
	smallPlatform1.shape.y = smallPlatform1.renderPos.y + smallPlatform1.img->getheight() / 2;

	//small2
	auto& smallPlatform2 = platform_list[2];

	smallPlatform2.img = &imgSmallPlatform;
	smallPlatform2.renderPos.x = 855, smallPlatform2.renderPos.y = 360;

	smallPlatform2.shape.left = smallPlatform2.renderPos.x + 40,
	smallPlatform2.shape.right = smallPlatform2.renderPos.x + smallPlatform2.img->getwidth() - 40,
	smallPlatform2.shape.y = smallPlatform2.renderPos.y + smallPlatform2.img->getheight() / 2;

	//small3
	auto& smallPlatform3 = platform_list[3];

	smallPlatform3.img = &imgSmallPlatform;
	smallPlatform3.renderPos.x = 515, smallPlatform3.renderPos.y = 225;

	smallPlatform3.shape.left = smallPlatform3.renderPos.x + 40,
	smallPlatform3.shape.right = smallPlatform3.renderPos.x + smallPlatform3.img->getwidth() - 40,
	smallPlatform3.shape.y = smallPlatform3.renderPos.y + smallPlatform3.img->getheight() / 2;

	mciSendString(_T("play bgmGame repeat from 0"), nullptr, 0, nullptr);
}

void GameScene::on_input(const ExMessage& msg) 
{
	player_1->on_input(msg);
	player_2->on_input(msg);

	switch (msg.message)
	{
	case WM_KEYUP:
		// 'Q'
		if (msg.vkcode == 0x51)
			is_debug = !is_debug;
		break;
	default:
		break;
	}
}

void GameScene::on_updata(int delta) 
{
	player_1->on_updata(delta);
	player_2->on_updata(delta);
	main_camera.on_updata(delta);
	//std::remove_if 不会真的删掉元素
	//	它只是：

	//	遍历容器；

	//	把不需要删除的元素前移；

	//	最后返回一个“新结尾”的迭代器（可以理解为“有效部分”的结尾）。
	//auto new_end = std::remove_if(vec.begin(), vec.end(), predicate);
	//此时，[vec.begin(), new_end) 是保留的元素，[new_end, vec.end()) 是“逻辑上要删除的元素”，但还留在内存里。
	/*vec.erase(new_end, vec.end());.erase() 才是真正地删掉那段内容*/

	bullet_list.erase(std::remove_if(bullet_list.begin(), bullet_list.end(),
		[](const Bullet* bullet) 
		{
			bool deletable = bullet->checkCanRemove();
			if (deletable)	delete bullet;
			// 是否删除指针
			return deletable;
		}),
		bullet_list.end());

	for (Bullet* bullet : bullet_list)
		bullet->on_updata(delta);

	// 判断玩家是否掉下
	const auto& positionPlayer1 = player_1->getPosition();
	const auto& positionPlayer2 = player_2->getPosition();

	if (positionPlayer1.y >= getheight())
		player_1->setHp(0);
	if (positionPlayer2.y >= getheight())
		player_2->setHp(0);

	if (player_1->getHp() <= 0 || player_2->getHp() <= 0) 
	{
		if (!isGameOver) 
		{

			mciSendString(_T("stop bgmGame"), nullptr, 0, nullptr);
			mciSendString(_T("play uiWin from 0"), nullptr, 0, nullptr);

		}
		isGameOver = true;
	}


	// 更新状态栏
	statusBar1P.setHp(player_1->getHp());
	statusBar1P.setMp(player_1->getMp());

	statusBar2P.setHp(player_2->getHp());
	statusBar2P.setMp(player_2->getMp());

	// 结算
	if (isGameOver)
	{

		posImgWinnerBar.x += (int)(speedWinnerBar * delta);
		posImgWinnerText.x += (int)(speedWinnerText * delta);

		if (!isSlideOutStarted)
		{

			timerWinnerSlideIn.on_updata(delta);

			if (posImgWinnerBar.x > posXImgWinnerBarDst)
				posImgWinnerBar.x = posXImgWinnerBarDst;

			if (posImgWinnerText.x > posXImgWinnerTextDst)
				posImgWinnerText.x = posXImgWinnerTextDst;
		}
		else
			timerWinnerSlideOut.on_updata(delta);

	}
}

void GameScene::on_draw(const Camera& camera)
{
	putimage_alpha(camera, posImgSky.x, posImgSky.y, &imgSky);
	putimage_alpha(camera, posImgHills.x, posImgHills.y, &imgHills);

	for (const Platform& platform : platform_list)
		platform.on_draw(camera);

	if (is_debug)
	{
		settextcolor(RGB(255, 0, 0));
		outtextxy(15, 15, _T("已开启调试模式, 按 'Q' 键关闭"));
	}

	player_1->on_draw(camera);
	player_2->on_draw(camera);

	for (const Bullet* bullet : bullet_list)
	{
		bullet->on_draw(camera);
	}

	if (isGameOver)
	{

		putimage_alpha(posImgWinnerBar.x, posImgWinnerBar.y, &imgWinnerBar);
		putimage_alpha(posImgWinnerText.x, posImgWinnerText.y, player_1->getHp() > 0 ? &img1PWinner : &img2PWinner);
	}
	else 
	{
		statusBar1P.on_draw();
		statusBar2P.on_draw();
	}

}

void GameScene::on_exit()
{
	delete player_1;
	delete player_2;

	player_1 = nullptr, player_2 = nullptr;
	
	is_debug = false;

	bullet_list.clear();
	main_camera.reset();
}

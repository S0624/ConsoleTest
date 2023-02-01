#include "GameoverScene.h"
#include"../InputState.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"../DrawFunctions.h"
#include<DXLib.h>

void GameoverScene::FadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (--fadeTimer_ == 0) {
		updateFunc_ = &GameoverScene::NormalUpdate;
	}
}

void GameoverScene::NormalUpdate(const InputState& input)
{
	if (input.IsTrigger(InputType::next))
	{
		updateFunc_ = &GameoverScene::FadeOutUpdate;
		fadeColor_ = 0x000000;
	}
}

void GameoverScene::FadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (++fadeTimer_ == fade_interval) {
		manager_.ChangeScene(new TitleScene(manager_));
		return;
	}
}

GameoverScene:: GameoverScene(SceneManager& manager) :Scene(manager),
updateFunc_(&GameoverScene::FadeInUpdate)
{
	gameoverH_ = my::MyLoadGraph(L"../Data/img/cat3.png");
}

void
GameoverScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void
GameoverScene::Draw()
{
	DrawRotaGraph(320, 240, 1.0f,0.0f, gameoverH_, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, 640, 480, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawString(300, 200, L"GameOverScene", 0xffff);
}
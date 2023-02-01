#include "TitleScene.h"
#include"../InputState.h"
#include"SceneManager.h"
#include"GameplayingScene.h"
#include"OptionScene.h"
#include"../DrawFunctions.h"
#include<DxLib.h>

void TitleScene::FadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (--fadeTimer_ == 0) {
		updateFunc_ = &TitleScene::NormalUpdate;
		fadeValue_ = 0;
	}
}

void TitleScene::NormalUpdate(const InputState& input)
{
	//「次へ」ボタンが押されたら次へ
	if (input.IsTrigger(InputType::next))
	{
		updateFunc_ = &TitleScene::FadeOutUpdate;
	}
	if (input.IsTrigger(InputType::prev))
	{
		manager_.ChangeScene(new OptionScene(manager_));
		return;
	}
}

void TitleScene::FadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (++fadeTimer_ == fade_interval) {
		manager_.ChangeScene(new GameplayingScene(manager_));
		return;
	}
		
}

TitleScene::TitleScene(SceneManager& manager)
	: Scene(manager), updateFunc_(&TitleScene::FadeInUpdate)
{
	titleH_ = my::MyLoadGraph(L"../Data/img/cat2.png");
	GradH_ = my::MyLoadGraph(L"../Data/img/Gra2.png");
}
TitleScene::~TitleScene()
{
	DeleteGraph(titleH_);
}
void
TitleScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void
TitleScene::Draw()
{
	//普通の描画
	DrawRotaGraph(320, 240, 1.0f, 0.0f, titleH_, true);
	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_MULA, fadeValue_);
	//DrawBox(0, 0, 540, 480, 0x00000, true);
	//画面全体を真っ黒に塗りつぶす
	DrawGraph(0, 200,GradH_, true);
	//変更したら元に戻す
	DrawBox(0, 0, 640, 480, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawString(300, 200, L"TitleScene", 0xfffff);
}
#include "GameplayingScene.h"
#include"../InputState.h"
#include"GameoverScene.h"
#include"TitleScene.h"
#include"PauseScene.h"
#include"SceneManager.h"
#include"../Game/ChargeShot.h"
#include"../DrawFunctions.h"
#include"../Game/Player.h"
#include"../Game/Shot.h"
#include<DXLib.h>

constexpr int rapid_fire_interval = 10;
constexpr int max_charge_frame = 80;
constexpr int gauge_x = 10;
constexpr int gauge_y = 480 - 36;


void GameplayingScene::FadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (--fadeTimer_ == 0) {
		updateFunc_ = &GameplayingScene::NormalUpdate;
		rapidFireCount = 0;
	}
}

void GameplayingScene::NormalUpdate(const InputState& input)
{
	scroll_ = scroll_ + 1;
	player_->Update(input);
	//連射
	//if (input.IsPressed(InputType::shot))
	//{
	//	
	//	if (rapidFireCount == 0)
	//	{
	//		for (auto& shot : shots_)
	//		{
	//			if (!shot->IsEnabled())
	//			{
	//				shot->Fire(player_->GetPosition());
	//				//shot->Fire(player_->GetPosition() + Vector2(26.0f,0.0f));
	//				break;
	//			}
	//		}
	//	}
	//	
	//	rapidFireCount = (rapidFireCount + 1) % rapid_fire_interval;
	//}


	if (input.IsPressed(InputType::shot))
	{
		//前のフレームが押されてなかった
		if (input.IsTrigger(InputType::shot))
		{
			for (auto& shot : shots_)
			{
				if (!shot->IsEnabled())
				{
					shot->Fire(player_->GetPosition());
					break;
				}
			}
		}
		else
		{
			++chargePower_;
		}
	}
	else
	{
		if (chargePower_ >= max_charge_frame)
		{
			chargeShot_->Fire(player_->GetPosition());
		}
		chargePower_ = 0;
	}


	//全弾の状態を更新
	for (auto& shot : shots_)
	{
		if (shot->IsEnabled())
		{
			shot->Update();
		}
	}
	if (chargeShot_->IsEnabled())
	{
		chargeShot_->Update();
	}
	

	vy += 0.1f;
	py += vy;
	if (py >= 400)
	{
		vy = -8.0;
	}
	if (input.IsTrigger(InputType::next))
	{
		updateFunc_ = &GameplayingScene::FadeOutUpdate;
		fadeColor_ = 0xff0000;
	}
	if (input.IsTrigger(InputType::prev))
	{
		manager_.ChangeScene(new TitleScene(manager_));
		return;
	}
	if (input.IsTrigger(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}
}

void GameplayingScene::FadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (++fadeTimer_ == fade_interval) {
		manager_.ChangeScene(new GameoverScene(manager_));
		return;
	}
}

GameplayingScene:: GameplayingScene(SceneManager& manager) :Scene(manager),
updateFunc_(&GameplayingScene::FadeInUpdate)
{
	gameplayH_ = my::MyLoadGraph(L"../Data/img/cat1.png");
	px = 320;
	py = 400;
	vx = 0;
	vy = 0;


	//ハンドルをせってい
	bgImgs_[0].handle = my::MyLoadGraph(L"../Data/img/game/bg-back.png");
	bgImgs_[1].handle = my::MyLoadGraph(L"../Data/img/game/bg-planet.png");
	bgImgs_[2].handle = my::MyLoadGraph(L"../Data/img/game/bg-stars.png");
	
	//スクロールスピード
	bgImgs_[0].scrollSpeed = 0.5f;
	bgImgs_[1].scrollSpeed = 0.75f;
	bgImgs_[2].scrollSpeed = 1.0f;

	bgImgs_[2].isTurnV = true;

	GetGraphSize(bgImgs_[0].handle, &bgW_, &bgH_);

	gaugeImg_ = my::MyLoadGraph(L"../Data/img/game/gauge.png");
	chargedgaugeImg_ = my::MyLoadGraph(L"../Data/img/game/chargedgauge.png");

	player_ = std::make_shared<Player>();
	chargeShot_ = std::make_shared<ChargeShot>();

	
	//弾の生成
	int shotH = my::MyLoadGraph(L"../Data/img/game/shot.png");
	for (auto& shot : shots_)
	{
		shot = std::make_shared<Shot>(shotH);
	}
	/*playerHandle_ = my::MyLoadGraph(L"../Data/img/game/player.png");*/
}

void
GameplayingScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void
GameplayingScene::Draw()
{
	constexpr float bg_scale = 3.0f;
	//基準のスクロール
	for (auto& bg : bgImgs_)
	{
		int scroll = static_cast<int>(scroll_ * bg.scrollSpeed) %
			static_cast<int>(bgW_ * bg_scale * (bg.isTurnV? 2.0f:1.0f));

		//背景1
		DrawRotaGraph(bgW_ * 0.5 * bg_scale - scroll,
			bgH_ * 0.5 * bg_scale,
			3.0f, 0.0f, bg.handle, true,
			false, false);

		if (!bg.isTurnV)
		{
			DrawRotaGraph(bgW_ * (1 + 0.5) * bg_scale - scroll,
				bgH_ * 0.5 * bg_scale,
				3.0f, 0.0f, bg.handle, true,
				false,false);
			//if (scroll_ == 0 && bg.isTurnV)
			//{
			//	bg.currentTurnV = !bg.isTurnV;
			//}
		}
	}
	//	DrawRotaGraph(320, 240, 1.0f, 0.0f, gameplayH_, true);
	//プレイヤーの描画
	player_->Draw();

	//通常弾の描画
	for (auto& shot : shots_)
	{
		if (shot->IsEnabled())
		{
			shot->Draw();
		}
	}

	if (chargeShot_->IsEnabled())
	{
		chargeShot_->Draw();
	}
	
	//ゲージ
	DrawExtendGraph(gauge_x, gauge_y,
		gauge_x + std::min(chargePower_ * 2,max_charge_frame * 2),
		gauge_y + 10,
		chargePower_>= max_charge_frame? chargedgaugeImg_ : gaugeImg_,
		true);
	//枠
	DrawBox(gauge_x, gauge_y,
		gauge_x + max_charge_frame * 2, gauge_y + 10,
		0xffffff, false);
	
	//DrawCircle(px, py, 20, 0xaaffaa, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, 640, 480, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawString(300, 200, L"GamePlayingScene", 0xffff);
}
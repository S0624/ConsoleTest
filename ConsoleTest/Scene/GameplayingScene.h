#pragma once
#include "Scene.h"
#include<memory>	//「スマートポインタ」を使うためのinclude
#include<array>		//配列用  

//プロトタイプ宣言
class Player;		//プレイヤークラス
class Shot;			//自機の弾
class ChargeShot;			//波動砲
/// <summary>
/// ゲーム中シーン
/// </summary>

class GameplayingScene :public Scene
{
private:
	float px = 0, py = 0;
	float vx = 0, vy = 0;

	static constexpr int fade_interval = 60;
	int gameplayH_ = -1;		//タイトル画像
	int fadeTimer_ = fade_interval; //フェードタイマー
	int fadeValue_ = 255; //黒矩形とのブレンド具合

	unsigned int fadeColor_ = 0x000000;//フェードの色（kuro）

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(GameplayingScene::*)(const InputState& input);
	UpdateFunc_t updateFunc_ = nullptr;

	int playerHandle_;
	int gaugeImg_;
	int chargedgaugeImg_;

	//プレイヤー
	std::shared_ptr < Player> player_;

	//弾
	std::array<std::shared_ptr <Shot>,32> shots_;
	int rapidFireCount = 0;

	//チャージ
	std::shared_ptr <ChargeShot> chargeShot_;
	int chargePower_ = 0;

	struct BackImg
	{
		int handle;				//画像のハンドル
		float scrollSpeed;		//スクロールのスピード（多重スクロール用）
		bool isTurnV = false;	//上下反転ありか
		bool currentTurnV = false;	//現在の画像は上下反転するか
	};

	//背景
	std::array<BackImg, 3>bgImgs_;
	//現在のスクロール
	int scroll_ = 0;
	//現在の幅
	int bgW_ = 0;
	//現在の高さ
	int bgH_ = 0;

public:
	GameplayingScene(SceneManager& manager);
	~GameplayingScene(){}
	void Update(const InputState& input);
	void Draw();
};


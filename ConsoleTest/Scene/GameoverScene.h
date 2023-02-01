#pragma once
#include "Scene.h"
/// <summary>
/// ゲームオーバーシーン
/// </summary>
class GameoverScene :public Scene
{
private:
	int gameoverH_ = -1;		//タイトル画像

	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval; //フェードタイマー
	int fadeValue_ = 255; //黒矩形とのブレンド具合

	unsigned int fadeColor_ = 0xff0000;//フェードの色（kuro）

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(GameoverScene::*)(const InputState& input);
	UpdateFunc_t updateFunc_ = nullptr;
public:
	GameoverScene(SceneManager& manager);
	~GameoverScene() {}
	void Update(const InputState& input);
	void Draw();
};


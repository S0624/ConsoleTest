#pragma once
#include "Scene.h"
//#include"InputState.h"

class InputState;
//タイトルシーン
class TitleScene : public Scene
{
private:
	static constexpr int fade_interval = 60;
	int titleH_ = -1;		//タイトル画像
	int GradH_ = -1;		//タイトル画像
	int fadeTimer_ = fade_interval; //フェードタイマー
	int fadeValue_ = 255; //黒矩形とのブレンド具合

	//フェードインの時のUpdeta関数
	void FadeInUpdate(const InputState& input);
	//通常状態のUpdate関数
	void NormalUpdate(const InputState& input);
	//フェードうアウトの時のUpdate関数
	void FadeOutUpdate(const InputState& input);
	//Update用メンバ関数ポインタ
	void (TitleScene::* updateFunc_)(const InputState& input);
public:
	TitleScene(SceneManager& manager);
	~TitleScene();

	void Update(const InputState& input);
	void Draw();
};


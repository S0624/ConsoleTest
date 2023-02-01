#pragma once
#include "Scene.h"
/// <summary>
/// �Q�[���I�[�o�[�V�[��
/// </summary>
class GameoverScene :public Scene
{
private:
	int gameoverH_ = -1;		//�^�C�g���摜

	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval; //�t�F�[�h�^�C�}�[
	int fadeValue_ = 255; //����`�Ƃ̃u�����h�

	unsigned int fadeColor_ = 0xff0000;//�t�F�[�h�̐F�ikuro�j

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


#pragma once
#include "Scene.h"
#include<memory>	//�u�X�}�[�g�|�C���^�v���g�����߂�include
#include<array>		//�z��p  

//�v���g�^�C�v�錾
class Player;		//�v���C���[�N���X
class Shot;			//���@�̒e
class ChargeShot;			//�g���C
/// <summary>
/// �Q�[�����V�[��
/// </summary>

class GameplayingScene :public Scene
{
private:
	float px = 0, py = 0;
	float vx = 0, vy = 0;

	static constexpr int fade_interval = 60;
	int gameplayH_ = -1;		//�^�C�g���摜
	int fadeTimer_ = fade_interval; //�t�F�[�h�^�C�}�[
	int fadeValue_ = 255; //����`�Ƃ̃u�����h�

	unsigned int fadeColor_ = 0x000000;//�t�F�[�h�̐F�ikuro�j

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(GameplayingScene::*)(const InputState& input);
	UpdateFunc_t updateFunc_ = nullptr;

	int playerHandle_;
	int gaugeImg_;
	int chargedgaugeImg_;

	//�v���C���[
	std::shared_ptr < Player> player_;

	//�e
	std::array<std::shared_ptr <Shot>,32> shots_;
	int rapidFireCount = 0;

	//�`���[�W
	std::shared_ptr <ChargeShot> chargeShot_;
	int chargePower_ = 0;

	struct BackImg
	{
		int handle;				//�摜�̃n���h��
		float scrollSpeed;		//�X�N���[���̃X�s�[�h�i���d�X�N���[���p�j
		bool isTurnV = false;	//�㉺���]���肩
		bool currentTurnV = false;	//���݂̉摜�͏㉺���]���邩
	};

	//�w�i
	std::array<BackImg, 3>bgImgs_;
	//���݂̃X�N���[��
	int scroll_ = 0;
	//���݂̕�
	int bgW_ = 0;
	//���݂̍���
	int bgH_ = 0;

public:
	GameplayingScene(SceneManager& manager);
	~GameplayingScene(){}
	void Update(const InputState& input);
	void Draw();
};


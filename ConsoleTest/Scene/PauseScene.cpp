#include "PauseScene.h"
#include"DxLib.h"
#include"../InputState.h"
#include"SceneManager.h"
#include"TitleScene.h"
#include"KeyConfigScene.h"
PauseScene::PauseScene(SceneManager& manager):Scene(manager)
{

}

PauseScene::~PauseScene()
{
}

void PauseScene::Update(const InputState& input)
{
	if (input.IsTrigger(InputType::pause))
	{
		manager_.PopScene();
		return;
	}
	if (input.IsTrigger(InputType::keyconf))
	{
		manager_.PushScene(new KeyConfigScene(manager_,input));
	}
}

void PauseScene::Draw()
{

	constexpr int pw_width = 400;		//�|�[�Y�g�̕�
	constexpr int pw_height = 300;		//�|�[�Y�g�̍���
	constexpr int pw_start_x = (640 - pw_width) / 2;
	constexpr int pw_start_y = (480 - pw_height) / 2;
	
	SetDrawBlendMode(DX_BLENDMODE_MULA, 135);		//�����������Ƃ�MALA
	//SetDrawBlendMode(DX_BLENDMODE_ADD, 128);		//�����������Ƃ���ADD
	//�|�[�Y�E�B���h�E�Z���t�@��			//�|�[�Y�����b�Z�[�W
	DrawBox(pw_start_x, pw_start_y,
		pw_start_x + pw_width, pw_start_y + pw_height,					
			0x00000, true);
	
	//���ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//�ʏ�`��ɖ߂�
	
	//�|�[�Y�����b�Z�[�W
	DrawString(pw_start_x + 50, pw_start_y + 50, L"Pausing...", 0x0ffff);

	//�|�[�Y�E�C���h�E�g��
	DrawBox(pw_start_x, pw_start_y,
		pw_start_x + pw_width, pw_start_y + pw_height,
		0xffffff, false);
}

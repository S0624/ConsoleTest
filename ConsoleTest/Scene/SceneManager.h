#pragma once

#include<deque>

//�v���g�^�C�v�錾
class Scene;		//�V�[�����N���X
class InputState;	//���̓X�e�[�g

//�V�[���Ď��N���X
class SceneManager
{
private:
	//�u�����s���v�̃V�[����؂�ւ��Ă��������̂�
	//�Q�Ƃł͂Ȃ��|�C���^�Ƃ��Đ錾
	std::deque<Scene*> scenes_;
	//Scene* scene_ = nullptr;

public:
	/// <summary>
	/// �V�[���̐؂�ւ����s��
	/// </summary>
	/// <param name="scene">�؂�ւ��������̃V�[���̃A�h���X</param>
	void ChangeScene(Scene* scene);
	/// <summary>
	/// �V�[������ɐς�
	/// Update�Ŏ��s�����̂͏�ɐς܂ꂽ�V�[���̂�
	/// </summary>
	/// <param name="scene"></param>
	void PushScene(Scene* scene);

	/// <summary>
	/// ��ԏ�̃V�[�����폜����
	/// Update�Ŏ��s�����̂͏�ɐς܂ꂽ�V�[���̂�
	/// </summary>
	/// <param name="scene"></param>
	void PopScene();
	
	/// <summary>
	/// �e�V�[����Update���i�X�V�j�s��
	/// </summary>
	/// <param name="input"></param>
	void Update(const InputState& input);
	/// <summary>
	/// �e�V�[���̕`��
	/// </summary>
	void Draw();
};


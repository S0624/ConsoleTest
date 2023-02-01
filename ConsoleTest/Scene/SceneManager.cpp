#include "SceneManager.h"
#include"Scene.h"

void
SceneManager::ChangeScene(Scene* scene)
{
	//�V�[���X�^�b�N����ł͂Ȃ�������
	if (!scenes_.empty())
	{
		delete scenes_.front();	//top�͂Ă��؂�̗v�f��Ԃ��Ă���
		scenes_.pop_front();			//����遨���ʂ͂O�ɂȂ�
	}
	scenes_.push_front(scene);		//�������
}

void SceneManager::PushScene(Scene* scene)
{
	scenes_.push_front(scene);	//�������
}

void SceneManager::PopScene()
{
	if (scenes_.size() > 1)
	{
		//�|�b�v�̌��ʁA�V�[�����[���ɂȂ�Ȃ��悤�ɂ���
		delete scenes_.front();
		scenes_.pop_front();
	}
}

void
SceneManager::Update(const InputState& input)
{
	scenes_.front()->Update(input);
}

void 
SceneManager::Draw()
{
	for (int i = scenes_.size() - 1; i >= 0; --i)
	{
		scenes_[i]->Draw();
	}
	//DrawString(300, 200, L"TitleScene", 0xffffff);
}
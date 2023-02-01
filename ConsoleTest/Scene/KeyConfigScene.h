#pragma once
#include "Scene.h"

class InputState;
class SeceneManager;

/// <summary>
/// �L�[�R���t�B�O�V�[��
/// </summary>

class KeyConfigScene : public Scene
{
private:
    const InputState& inputState_;
    //���͈ꎞ�e�[�u��
    ////�������������e���ꎞ�I�ɓ����Ă���
    //InputState::InputMap_t temporayInputMapTable_;
    int currentInputIndex_;      //���ݑI�𒆂̃C���f�b�N�X
    bool isEditing = false;     //���ݓ���̓��͕͂ҏW���ł�

public:
    KeyConfigScene(SceneManager& manager,const InputState& input);
    ~KeyConfigScene();

    void Update(const InputState& input);
    void Draw();
};
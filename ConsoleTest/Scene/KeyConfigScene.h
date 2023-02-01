#pragma once
#include "Scene.h"

class InputState;
class SeceneManager;

/// <summary>
/// キーコンフィグシーン
/// </summary>

class KeyConfigScene : public Scene
{
private:
    const InputState& inputState_;
    //入力一時テーブル
    ////書き換えた内容が一時的に入っている
    //InputState::InputMap_t temporayInputMapTable_;
    int currentInputIndex_;      //現在選択中のインデックス
    bool isEditing = false;     //現在特定の入力は編集中です

public:
    KeyConfigScene(SceneManager& manager,const InputState& input);
    ~KeyConfigScene();

    void Update(const InputState& input);
    void Draw();
};
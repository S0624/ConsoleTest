#include "OptionScene.h"
#include"../InputState.h"
#include"SceneManager.h"
#include"TitleScene.h"
#include<DXLib.h>

void 
OptionScene::Update(const InputState & input)
{
	if (input.IsTrigger(InputType::prev))
	{
		manager_.ChangeScene(new TitleScene(manager_));
		return;
	}
}
void
OptionScene::Draw()
{
	DrawString(300, 200, L"OptionScene", 0xffff);
}

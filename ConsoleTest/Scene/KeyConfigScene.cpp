#include "KeyConfigScene.h"
#include"../InputState.h"
#include"SceneManager.h"
#include<DxLib.h>

KeyConfigScene::KeyConfigScene(SceneManager& manager, const InputState& input) :
	inputState_(input), Scene(manager),currentInputIndex_(0)
{

}

KeyConfigScene::~KeyConfigScene()
{
	inputState_.SaveKeyInfo();
}

void KeyConfigScene::Update(const InputState& input)
{
	auto& configInput = const_cast<InputState&>(input);

	if (!isEditing)			//フラグの通りじゃなかったら処理を受け付けない
	{
		if (input.IsTrigger(InputType::keyconf))
		{
			configInput.RollbackChangedInputInfo();
			manager_.PopScene();					//もう一度押されたら閉じる
			return;
		}
		if (input.IsTrigger(InputType::change))
		{
			
			configInput.RewriteInpurInfo(InputType::prev, InputCategory::keybd, KEY_INPUT_ESCAPE);
			configInput.RewriteInpurInfo(InputType::prev, InputCategory::pad, PAD_INPUT_X);
			configInput.RewriteInpurInfo(InputType::prev, InputCategory::mouse, MOUSE_INPUT_RIGHT);

			OutputDebugStringA("キーが書き換えられました。\n");
		}

		const int nameCount = input.inputNameTable_.size() + 2;
		{
			if (input.IsTrigger(InputType::up))
			{
				currentInputIndex_ = ((currentInputIndex_ - 1) + nameCount) % nameCount;
			}
			else if (input.IsTrigger(InputType::down))
			{
				currentInputIndex_ = (currentInputIndex_ + 1) % nameCount;
			}
		}
	}

	//この時はもう、確定しますを選択している
	if (currentInputIndex_ == input.inputNameTable_.size())
	{
		if (input.IsTrigger(InputType::next))
		{
			configInput.CommitChangedInputInfo();
		}
	}
	if (currentInputIndex_ == input.inputNameTable_.size() + 1)
	{
		if (input.IsTrigger(InputType::next))
		{
			configInput.ResetInputInfo();
			return;
		}
	}

	//nextボタンでエディット中かそうじゃないかを
	//決定する	
	if (input.IsTrigger(InputType::next))
	{
		isEditing = !isEditing;			//trueとfalseを切り替える
		return;
	}

	if (isEditing)
	{
		char keystate[256];
		GetHitKeyStateAll(keystate);
		auto padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		auto mouseState = GetMouseInput();
		
		int idx = 0;
		InputType currentType = InputType::max;
		for (const auto& name : inputState_.inputMapTable_)
		{
			if (currentInputIndex_ == idx)
			{
				currentType = name.first;
				break;
			}
			++idx;
		}


		for (int i = 0; i < 256; ++i)
		{
			if (keystate[i])
			{
				configInput.RewriteInpurInfo(currentType, InputCategory::keybd, i);
				break;
			}
		}
		if (padState != 0)
		{
			configInput.RewriteInpurInfo(currentType, InputCategory::pad, padState);

		}
		if (mouseState != 0)
		{
			configInput.RewriteInpurInfo(currentType, InputCategory::mouse, mouseState);

		}
	}
}

void KeyConfigScene::Draw()
{
	constexpr int pw_width = 400;		//キーコンフィグ枠の幅
	constexpr int pw_height = 300;		//キーコンフィグ枠の高さ
	constexpr int pw_start_x = (640 - pw_width) / 2 + 50;		//キーコンフィグ枠左
	constexpr int pw_start_y = (480 - pw_height) / 2 + 50;		//キーコンフィグ枠上

	//キーコンフィグウインドウ背景
	DrawBox(pw_start_x, pw_start_y,
		pw_start_x + pw_width, pw_start_y + pw_height,
		0x008800, true);

	//キーコンフィグ中メッセージ
	DrawString(pw_start_x + 5 , pw_start_y + 5, L"keyconfig...", 0xffffaa);

	auto y = pw_start_y + 30;
	int idx = 0;
	bool isInputTypeSelected = false;

	for (const auto& name : inputState_.inputNameTable_)
	{
		int offset = 0;
		unsigned int color = 0xfffffff;

		//各キーの表示
		if (currentInputIndex_ == idx)
		{
			offset = 10;
			if (isEditing)
			{
				color = 0xff0000;
			}
			isInputTypeSelected = true;
			DrawString(pw_start_x + 10, y, L"▶", 0xff0000);
		}
		int x = pw_start_x + 20 + offset;
		DrawString(x, y, name.second.c_str(), color);

		auto type = name.first;
		auto it = inputState_.tempMapTable_.find(type);
		x += 64;
		DrawString(x, y, L": ", color);
		x += 10;
		for (const auto& elem : it->second)
		{
			if (elem.cat == InputCategory::keybd)
			{
				DrawFormatString(x, y, color, L"key = %d", elem.id);
			}
			else if (elem.cat == InputCategory::pad)
			{
				DrawFormatString(x, y, color, L"pad = %d", elem.id);
			}
			else if (elem.cat == InputCategory::mouse)
			{
				DrawFormatString(x, y, color, L"mouse = %d", elem.id);
			}

			x += 100;
		}

		y += 18;
		++idx;
	}
	y += 20;
	if (!isInputTypeSelected)
	{
		int yoffset = 0;
		if (currentInputIndex_ == inputState_.inputNameTable_.size() + 1)
		{
			yoffset = 20;
		}
		DrawString(pw_start_x + 90, y + yoffset, L"▶", 0xff0000);
	}
	//各キーの表示
	DrawString(pw_start_x + 100, y, L"　確定します　", 0xffffff);
	

	y += 20;
	DrawString(pw_start_x + 100, y, L"　キーリセット　", 0xffffff);

	//キーコンフィグウインドウ枠線
	DrawBox(pw_start_x, pw_start_y,
		pw_start_x + pw_width, pw_start_y + pw_height,
		0xffffff, false);
}

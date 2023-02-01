#include "InputState.h"
#include<DxLib.h>
#include<cassert>

InputState::InputState()
{
	//次へ
	defaultMapTable_[InputType::next] = { {InputCategory::keybd,KEY_INPUT_RETURN},
										{InputCategory::pad,PAD_INPUT_R},		//スタートボタン
										//{InputCategory::pad,PAD_INPUT_1},		//スタートボタン
										{InputCategory::mouse,MOUSE_INPUT_LEFT} };

	//前へ
	defaultMapTable_[InputType::prev] = { {InputCategory::keybd,KEY_INPUT_SPACE},
										{InputCategory::pad,PAD_INPUT_B}};
										//{InputCategory::pad,PAD_INPUT_2}};

	//ポーズ
	defaultMapTable_[InputType::pause] = { {InputCategory::keybd,KEY_INPUT_P},
									{InputCategory::pad,PAD_INPUT_L} };			//セレクト
									//{InputCategory::pad,PAD_INPUT_3} };			//セレクト
	
	//キーコンフィグ
	defaultMapTable_[InputType::keyconf] = { {InputCategory::keybd,KEY_INPUT_K},
									{InputCategory::pad,PAD_INPUT_Y} };			//左ショルダー
									//{InputCategory::pad,PAD_INPUT_4} };			//左ショルダー

	//変更
	defaultMapTable_[InputType::change] = { {InputCategory::keybd,KEY_INPUT_C},
									{InputCategory::pad,PAD_INPUT_Z} };			//右ショルダー
								//{InputCategory::pad,PAD_INPUT_4} };			//右ショルダー

	//上
	defaultMapTable_[InputType::up] = { {InputCategory::keybd,KEY_INPUT_UP},
									{InputCategory::pad,PAD_INPUT_UP} };			//上ショルダー
								//{InputCategory::pad,PAD_INPUT_4} };			//上ショルダー

	//下
	defaultMapTable_[InputType::down] = { {InputCategory::keybd,KEY_INPUT_DOWN},
									{InputCategory::pad,PAD_INPUT_DOWN} };			//下ショルダー
								//{InputCategory::pad,PAD_INPUT_4} };			//下ショルダー
	//左
	defaultMapTable_[InputType::left] = { {InputCategory::keybd,KEY_INPUT_LEFT},
									{InputCategory::pad,PAD_INPUT_LEFT} };			//下ショルダー
								//{InputCategory::pad,PAD_INPUT_4} };			//下ショルダー

	//右
	defaultMapTable_[InputType::right] = { {InputCategory::keybd,KEY_INPUT_RIGHT},
									{InputCategory::pad,PAD_INPUT_RIGHT} };			//上ショルダー
								//{InputCategory::pad,PAD_INPUT_4} };			//上ショルダー

	defaultMapTable_[InputType::shot] = { {InputCategory::keybd,KEY_INPUT_Z},
									{InputCategory::pad,PAD_INPUT_C} };			//上ショルダー
								//{InputCategory::pad,PAD_INPUT_4} };			//上ショルダー
	
	inputMapTable_ = defaultMapTable_;
	LoadKeyInfo();

	//位置にマップテーブルにコピー
	tempMapTable_ = inputMapTable_;

	//入力タイプの名前のテーブルを作る
	inputNameTable_[InputType::next] = L"next";
	inputNameTable_[InputType::prev] = L"prev";
	inputNameTable_[InputType::pause] = L"pause";
	inputNameTable_[InputType::keyconf] = L"keyconf";
	inputNameTable_[InputType::change] = L"change";
	inputNameTable_[InputType::shot] = L"shot";

	currentInput_.resize(static_cast<int>(InputType::max));
	lastInput_.resize(static_cast<int>(InputType::max));
}

void
InputState::Update()
{
	lastInput_ = currentInput_;		//直前の入力情報を記憶しておく
	char keystate[256];				//全キー情報取得
	GetHitKeyStateAll(keystate);
	
	int padstate = GetJoypadInputState(DX_INPUT_PAD1);		//パッド1紺の情報を所得する
	int mousestate = GetMouseInput();						//マウスの情報

	for (const auto& keymap : inputMapTable_)		//マップの全情報をループする
	{
		for (const auto& input : keymap.second)		//入力情報配列をループする
		{
			//このInputの中身は、keybd,KEY_INPUT_RETURNなどのセット（Inputinfo）が入っている
			//keymap.firstには、対応するゲーム入力名の"InputType::next"などが入っている
			if (input.cat == InputCategory::keybd)
			{
				currentInput_[static_cast<int>(keymap.first)] = keystate[input.id];
			}

			else if (input.cat == InputCategory::pad)
			{
				currentInput_[static_cast<int>(keymap.first)] = padstate&input.id;
			}

			else if (input.cat == InputCategory::mouse)
			{
				currentInput_[static_cast<int>(keymap.first)] = mousestate & input.id;
			}
			//3つの入力のうちどれかがtrueだったらもう「入力されている」
			//とみなして、breakする。
			if (currentInput_[static_cast<int>(keymap.first)])			//上書きされないようにbreakでループを抜ける
			{
				break;
			}
		}
	}
}

void InputState::RewriteInpurInfo(InputType type, InputCategory cat, int id)
{
	//入力種別（割当先）がなければ、無効なので無視
	if (tempMapTable_.count(type) == 0)
	{
		return;
	}
	bool isRewrite = false;
	for (auto& InputInfo : tempMapTable_[type])
	{
		if (InputInfo.cat == cat)		//カテゴリがヒットしたら
		{
			InputInfo.id = id;			//IDを上書き
			isRewrite = true;
			break;
		}
	}
	if (!isRewrite)			//もしカテゴリが存在しなかったらここで追加しておく
	{
		tempMapTable_[type].push_back({ cat,id });
	}
}

void InputState::CommitChangedInputInfo()
{
	inputMapTable_ = tempMapTable_;
}

void InputState::RollbackChangedInputInfo()
{
	tempMapTable_ = inputMapTable_;
}

void InputState::ResetInputInfo()
{
	inputMapTable_ = defaultMapTable_;
	tempMapTable_ = defaultMapTable_;
}


void InputState::SaveKeyInfo()const
{
	FILE* fp = nullptr;
	auto err = fopen_s(&fp,"key.info","wb");
	if (fp == nullptr)
	{
		assert(0);
		return;
	}
	// 仮想キータイプの数を書き込む
	int keytypeNum = inputMapTable_.size();
	fwrite(&keytypeNum, sizeof(keytypeNum), 1, fp);


	// 仮想キータイプ(next,prevなど)のループ
	for (const auto& key : inputMapTable_)
	{
		int keytype = static_cast<int> (key.first);
		//仮想入力キー
		fwrite(&keytype, sizeof(keytype), 1, fp);
		int dataSize = key.second.size();
		//実入力キーデータ
		fwrite(&dataSize, sizeof(dataSize), 1, fp);
		
		//VECTORがたのdata()は先頭のアドレスを返す
		//一気にその入力のデータを書き込む
		fwrite(key.second.data(),dataSize * sizeof(InputInfo),1,fp);

	}
	fclose(fp);
}

void InputState::LoadKeyInfo()
{
	int handle = FileRead_open(L"key.info");
	if (handle == 0)
	{
		return;
	}
	int keytypeNum = 0;
	FileRead_read(&keytypeNum, sizeof(keytypeNum), handle);
	inputMapTable_.clear();
	for (int i = 0; i < keytypeNum; ++i)
	{
		int inputType;
		FileRead_read(&inputType, sizeof(inputType), handle);

		int dataSize = 0;
		FileRead_read(&dataSize, sizeof(dataSize), handle);
		std::vector <InputInfo> inputInfoes(dataSize);
		FileRead_read(inputInfoes.data(), sizeof(InputInfo) * dataSize, handle);
		inputMapTable_[static_cast<InputType>(inputType)] = inputInfoes;
	}
	tempMapTable_ = inputMapTable_;
	FileRead_close(handle);
}

//void InputState::LoadKeyInfo() const
//{
//	int handle = FileRead_open(L"key.info");
//	int data = 0;
//	FileRead_read(&data, sizeof(data), handle);
//	FileRead_close(handle);
//}

bool
InputState::IsPressed(InputType type)const
{
	return currentInput_[static_cast<int>(type)];
}

bool
InputState::IsTrigger(InputType type)const
{
	return IsPressed(type) && !lastInput_[static_cast<int>(type)];
}
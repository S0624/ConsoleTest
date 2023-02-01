#include "InputState.h"
#include<DxLib.h>
#include<cassert>

InputState::InputState()
{
	//����
	defaultMapTable_[InputType::next] = { {InputCategory::keybd,KEY_INPUT_RETURN},
										{InputCategory::pad,PAD_INPUT_R},		//�X�^�[�g�{�^��
										//{InputCategory::pad,PAD_INPUT_1},		//�X�^�[�g�{�^��
										{InputCategory::mouse,MOUSE_INPUT_LEFT} };

	//�O��
	defaultMapTable_[InputType::prev] = { {InputCategory::keybd,KEY_INPUT_SPACE},
										{InputCategory::pad,PAD_INPUT_B}};
										//{InputCategory::pad,PAD_INPUT_2}};

	//�|�[�Y
	defaultMapTable_[InputType::pause] = { {InputCategory::keybd,KEY_INPUT_P},
									{InputCategory::pad,PAD_INPUT_L} };			//�Z���N�g
									//{InputCategory::pad,PAD_INPUT_3} };			//�Z���N�g
	
	//�L�[�R���t�B�O
	defaultMapTable_[InputType::keyconf] = { {InputCategory::keybd,KEY_INPUT_K},
									{InputCategory::pad,PAD_INPUT_Y} };			//���V�����_�[
									//{InputCategory::pad,PAD_INPUT_4} };			//���V�����_�[

	//�ύX
	defaultMapTable_[InputType::change] = { {InputCategory::keybd,KEY_INPUT_C},
									{InputCategory::pad,PAD_INPUT_Z} };			//�E�V�����_�[
								//{InputCategory::pad,PAD_INPUT_4} };			//�E�V�����_�[

	//��
	defaultMapTable_[InputType::up] = { {InputCategory::keybd,KEY_INPUT_UP},
									{InputCategory::pad,PAD_INPUT_UP} };			//��V�����_�[
								//{InputCategory::pad,PAD_INPUT_4} };			//��V�����_�[

	//��
	defaultMapTable_[InputType::down] = { {InputCategory::keybd,KEY_INPUT_DOWN},
									{InputCategory::pad,PAD_INPUT_DOWN} };			//���V�����_�[
								//{InputCategory::pad,PAD_INPUT_4} };			//���V�����_�[
	//��
	defaultMapTable_[InputType::left] = { {InputCategory::keybd,KEY_INPUT_LEFT},
									{InputCategory::pad,PAD_INPUT_LEFT} };			//���V�����_�[
								//{InputCategory::pad,PAD_INPUT_4} };			//���V�����_�[

	//�E
	defaultMapTable_[InputType::right] = { {InputCategory::keybd,KEY_INPUT_RIGHT},
									{InputCategory::pad,PAD_INPUT_RIGHT} };			//��V�����_�[
								//{InputCategory::pad,PAD_INPUT_4} };			//��V�����_�[

	defaultMapTable_[InputType::shot] = { {InputCategory::keybd,KEY_INPUT_Z},
									{InputCategory::pad,PAD_INPUT_C} };			//��V�����_�[
								//{InputCategory::pad,PAD_INPUT_4} };			//��V�����_�[
	
	inputMapTable_ = defaultMapTable_;
	LoadKeyInfo();

	//�ʒu�Ƀ}�b�v�e�[�u���ɃR�s�[
	tempMapTable_ = inputMapTable_;

	//���̓^�C�v�̖��O�̃e�[�u�������
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
	lastInput_ = currentInput_;		//���O�̓��͏����L�����Ă���
	char keystate[256];				//�S�L�[���擾
	GetHitKeyStateAll(keystate);
	
	int padstate = GetJoypadInputState(DX_INPUT_PAD1);		//�p�b�h1���̏�����������
	int mousestate = GetMouseInput();						//�}�E�X�̏��

	for (const auto& keymap : inputMapTable_)		//�}�b�v�̑S�������[�v����
	{
		for (const auto& input : keymap.second)		//���͏��z������[�v����
		{
			//����Input�̒��g�́Akeybd,KEY_INPUT_RETURN�Ȃǂ̃Z�b�g�iInputinfo�j�������Ă���
			//keymap.first�ɂ́A�Ή�����Q�[�����͖���"InputType::next"�Ȃǂ������Ă���
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
			//3�̓��͂̂����ǂꂩ��true������������u���͂���Ă���v
			//�Ƃ݂Ȃ��āAbreak����B
			if (currentInput_[static_cast<int>(keymap.first)])			//�㏑������Ȃ��悤��break�Ń��[�v�𔲂���
			{
				break;
			}
		}
	}
}

void InputState::RewriteInpurInfo(InputType type, InputCategory cat, int id)
{
	//���͎�ʁi������j���Ȃ���΁A�����Ȃ̂Ŗ���
	if (tempMapTable_.count(type) == 0)
	{
		return;
	}
	bool isRewrite = false;
	for (auto& InputInfo : tempMapTable_[type])
	{
		if (InputInfo.cat == cat)		//�J�e�S�����q�b�g������
		{
			InputInfo.id = id;			//ID���㏑��
			isRewrite = true;
			break;
		}
	}
	if (!isRewrite)			//�����J�e�S�������݂��Ȃ������炱���Œǉ����Ă���
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
	// ���z�L�[�^�C�v�̐�����������
	int keytypeNum = inputMapTable_.size();
	fwrite(&keytypeNum, sizeof(keytypeNum), 1, fp);


	// ���z�L�[�^�C�v(next,prev�Ȃ�)�̃��[�v
	for (const auto& key : inputMapTable_)
	{
		int keytype = static_cast<int> (key.first);
		//���z���̓L�[
		fwrite(&keytype, sizeof(keytype), 1, fp);
		int dataSize = key.second.size();
		//�����̓L�[�f�[�^
		fwrite(&dataSize, sizeof(dataSize), 1, fp);
		
		//VECTOR������data()�͐擪�̃A�h���X��Ԃ�
		//��C�ɂ��̓��͂̃f�[�^����������
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
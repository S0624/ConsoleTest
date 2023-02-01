#pragma once

#include<map>
#include<vector>
#include<string>

enum class InputType {
	next,	//���֍s���{�^��
	prev,	//�O�ɖ߂�{�^��
	pause,	//�|�[�Y�{�^��
	keyconf,	//�L�[�{�^��
	change,		//�`�F���W�{�^��
	up,			//��
	down,		//��
	right,		//�E
	left,		//��
	shot,		//�e����
	max			//�ő���̓C���f�b�N�X
};

/// <summary>
/// ���͑��u�J�e�S��
/// </summary>
enum class InputCategory
{
	keybd,	//�L�[�{�[�h
	pad,	//�Q�[���p�b�h
	mouse	//�}�E�X
};

struct InputInfo
{
	InputCategory cat;	//���͑��u�J�e�S��
	int id;	//����ID(KEY_INPUT�`	PAD�`_INPUT		MOUSE�`_INPUT)
};

//�t�����h�p�Ƀv���g�^�C�v�錾
class KeyConfigScene;

/// <summary>
///���͏�Ԃ��Ǘ�����
/// </summary>
class InputState
{
	friend KeyConfigScene;		//KeyConfigScene�ɂ����A���ׂĂ�������B
private:
	//���z���͏��Ǝ��ۂ̓��̓e�[�u�������
	//�L�[�ifirst�j = InputType
	//�l�isecond�j = std::vector<InputInfo>
	using InputMap_t = std::map<InputType, std::vector<InputInfo>>;		//���ۂ̓��͂ƑΉ��̃{�^��
	InputMap_t inputMapTable_;		//���ۂ̓��͂ƑΉ��̃{�^��

	//���������悤�̈ꎞ�I��inputMapTable_�̃R�s�[
	//�����Ȃ菑�������Ă��܂�Ȃ��悤��
	InputMap_t tempMapTable_;

	//���Z�b�g�p�̃}�b�v�e�[�u��
	InputMap_t defaultMapTable_;

	//���̓^�C�v�Ƃ��̖��O
	std::map<InputType, std::wstring>inputNameTable_;

	std::vector<bool> currentInput_;		//���݂̓��͕��@(�����Ă��邩�����Ă��Ȃ���)
	std::vector<bool> lastInput_;			//���O�̓��͏��(���O�����Ă��邩�����Ă��Ȃ���)

	//int keypadState;		//�L�[�p�b�h���
	//int lastKeypadState;	//���O�̃L�[�p�b�h���
	//char keystate[256];		//�L�[�{�[�h���
	//char lastKeystate[256];	//���O�̃L�[�{�[�h���

public:
	InputState();
	/// <summary>
	/// �������u�Ԃ�True�ɂȂ�
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>�������u�ԂȂ�True�A����ȊO�Ȃ�False</returns>
	bool IsTrigger(InputType type)const;
	/// <summary>
	/// ������Ă���True�ɂȂ�
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>������Ă���True�A����ȊO��Flase</returns>
	bool IsPressed(InputType type)const;
	/// <summary>
	/// ���͏�Ԃ��X�V
	/// �i���Ӂj���t���[��Update����΂Ȃ���΍X�V����Ȃ�
	/// </summary>
	void Update();

	/// <summary>
	/// ���͏����X�V
	/// </summary>
	/// <param name="type">�Q�[���ɂ�������͎��</param>
	/// <param name="cat">���̓J�e�S��</param>
	/// <param name="id">���ۂ̓���</param>
	void RewriteInpurInfo(InputType type,InputCategory cat,int id);

	/// <summary>
	/// ���ݕҏW���̃L�[�R���t�B�O���m�肷��
	/// </summary>
	void CommitChangedInputInfo();

	/// <summary>
	/// ���ݕҏW���̃L�[�R���t�B�O�̕ύX���Ȃ��������Ƃɂ���
	/// </summary>
	void RollbackChangedInputInfo();

	/// <summary>
	/// �L�[�}�b�v���f�t�H���g�Ƀ��Z�b�g����
	/// </summary>
	void ResetInputInfo();
	
	/// <summary>
	/// �L�[�}�b�v�t�@�C���ɕۑ�����
	/// </summary>
	void SaveKeyInfo()const;

	void LoadKeyInfo();
	//void LoadKeyInfo()const;
};


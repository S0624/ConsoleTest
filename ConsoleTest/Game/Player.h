#pragma once

#include"../Geometry.h"

class InputState;
class Enemy;

class Player
{
private:
	Enemy* enemy_ = nullptr;
	Position2 pos_;		//���@�̍��W
	int handle_;		//���@�摜�n���h��
	int imgIdx_ = 0;			//�\������摜
public:
	Player();
	
	const Position2& GetPosition()const;

	/// <summary>
	/// �v���C���[�̏�Ԃ̍X�V
	/// </summary>
	/// <param name="input"></param>
	void Update(const InputState& input);

	/// <summary>
	/// �v���C���[�̕`�揈��
	/// </summary>
	void Draw();

	void Dameaged(){}
};


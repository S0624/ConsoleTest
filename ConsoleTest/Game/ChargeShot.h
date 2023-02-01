#pragma once
#include"../Geometry.h"

class ChargeShot
{
private:
	Position2 pos_;		//���@�̍��W
	Vector2 vel_;		//���@�̍��W
	int handle_;
	int imgIdx_ = 0;			//�\������摜
	//�e�L���t���O
	bool isEnabled_ = false;	//���e�͐����Ă���

public:
	ChargeShot();

	//�e�𕜊�������
	void Fire(const Position2& pos);
	//�e�̗L�������t���O�𓾂�
	bool IsEnabled()const;
	void Update();
	void Draw();
};


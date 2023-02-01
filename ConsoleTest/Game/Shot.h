#pragma once
#include"../Geometry.h"

class Shot
{
private:
	Position2 pos_;		//���@�̍��W
	Vector2 vel_;		//���@�̍��W
	int handle_;
	int imgIdx_ = 0;			//�\������摜
	bool isEnabled_ = false;	//���e�͐����Ă���t���O�itrue : �����Ă���@false : ����ł���j

public:
	Shot(int handle);
	
	//�e�𕜊�������
	void Fire(const Position2& pos);
	//�e�̗L�������t���O�𓾂�
	bool IsEnabled()const;
	void Update();
	void Draw();

};


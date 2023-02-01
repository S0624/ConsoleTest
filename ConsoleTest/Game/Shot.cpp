#include "Shot.h"
#include"DxLib.h"

constexpr int img_width = 19;
constexpr int img_height = 6;
constexpr float img_scale = 2.0f;

Shot::Shot(int handle) : handle_(handle),
vel_(6.0f,0.0f)		//�e�̃X�s�[�h	
{
}

void Shot::Fire(const Position2& pos)
{
	pos_ = pos;
	isEnabled_ = true;
}

bool Shot::IsEnabled() const
{
	return isEnabled_;
}

void Shot::Update()
{
	//����ł���̂Ȃ瓮�����Ȃ�
	if (!isEnabled_) return;
	pos_ += vel_;		//�e�����ݑ��x�ňړ�������

	//�摜�̃C���f�b�N�X��؂�ւ���
	imgIdx_ = (imgIdx_ + 1) % 2;
	
	//�e����ʊO�ɏo����A���񂾂��Ƃɂ���
	if (pos_.x < -img_width || 640 + img_width < pos_.x)
	{
		isEnabled_ = false;
	}
}

void Shot::Draw()
{
	//����ł���̂Ȃ�\�����Ȃ�
	if (!isEnabled_) return;
	DrawRectRotaGraph(pos_.x, pos_.y,			//�\�����W
		imgIdx_ * img_width, 0,						//�؂��荶��
		img_width, img_height,									//���A����
		img_scale, 0.0f,								//�g�嗦�A��]�p�x
		handle_, true);
}

#include "Player.h"
#include"../DrawFunctions.h"
#include"../InputState.h"
#include"DxLib.h"

//���@�摜�������̕��ƍ���
constexpr int img_widht = 26;
constexpr int img_height = 21;
constexpr float draw_scale = 2.0f;

Player::Player() :pos_(320,240)
{
	handle_ = my::MyLoadGraph(L"../Data/img/game/player.png");
}

const Position2& Player::GetPosition() const
{
		return pos_;
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}

void Player::Update(const InputState& input)
{
	constexpr float speed = 1.0f;

	Vector2 vel = {0.0f,0.0f};	//���x�x�N�g��

	if (input.IsPressed(InputType::up))
	{
		imgIdx_ = 2;
		vel.y = -1.0f;
	}
	else if (input.IsPressed(InputType::down))
	{
		imgIdx_ = 1;
		vel.y = +1.0f;
	}
	else			//���������ĂȂ�
	{
		imgIdx_ = 0;
	}
	if (input.IsPressed(InputType::left))
	{
		//pos_.x -= 2;
		vel.x = -1.0f;
	}
	else if (input.IsPressed(InputType::right))
	{
		//pos_.x += 2;
		vel.x = +1.0f;
	}
	if (vel.Length() > 0.0f)		//�x�N�g���̑傫�����P�ȏ�̂Ƃ��݈̂ړ����s��
	{
		vel.Normalize();		//�����ɂ�����炤�傫������ɂ���
		vel *= speed;			//1�̕����ɃX�s�[�h����Z����
		//���̌��ʁA�����ɂ�����炸�X�s�[�h��2.0f�ɂȂ�
		//�����pos_�ɉ��Z����
	}
	pos_ += vel;
}

void Player::Draw()
{
	my::MyDrawRectRotaGraph(pos_.x, pos_.y,			//�\�����W�̒��S
		imgIdx_ * img_widht, 0,							//�؂��荶��
		img_widht, img_height,							//���A����
		draw_scale, 0.0f,						//�g�嗦�A��]�p�x
		handle_, true);
}

#include "Player.h"
#include"../DrawFunctions.h"
#include"../InputState.h"
#include"DxLib.h"

//自機画像一個あたりの幅と高さ
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
	// TODO: return ステートメントをここに挿入します
}

void Player::Update(const InputState& input)
{
	constexpr float speed = 1.0f;

	Vector2 vel = {0.0f,0.0f};	//速度ベクトル

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
	else			//何も押してない
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
	if (vel.Length() > 0.0f)		//ベクトルの大きさが１以上のときのみ移動を行う
	{
		vel.Normalize();		//方向にかかわらう大きさを一にする
		vel *= speed;			//1の方向にスピードを乗算する
		//この結果、方向にかかわらずスピードは2.0fになる
		//それをpos_に加算する
	}
	pos_ += vel;
}

void Player::Draw()
{
	my::MyDrawRectRotaGraph(pos_.x, pos_.y,			//表示座標の中心
		imgIdx_ * img_widht, 0,							//切り取り左上
		img_widht, img_height,							//幅、高さ
		draw_scale, 0.0f,						//拡大率、回転角度
		handle_, true);
}

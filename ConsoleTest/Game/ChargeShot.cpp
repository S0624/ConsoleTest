#include "ChargeShot.h"
#include"../DrawFunctions.h"
#include"DxLib.h"

constexpr int img_width = 63;
constexpr int img_height = 32;
constexpr float img_scale = 1.0f;
constexpr int anim_fraem_per_img = 4;
constexpr int anim_num = 4;

ChargeShot::ChargeShot() : vel_(6.0f, 0.0f)
{
	handle_ = my::MyLoadGraph(L"../Data/img/game/charge_shot.png");
}

void ChargeShot::Fire(const Position2& pos)
{
	pos_ = pos;
	isEnabled_ = true;
}

bool ChargeShot::IsEnabled() const
{
	return isEnabled_;
}

void ChargeShot::Update()
{
	pos_ += vel_;		//弾を現在速度で移動させる

//画像のインデックスを切り替える
	imgIdx_ = (imgIdx_ + 1) % (anim_num * anim_fraem_per_img);

	//弾が画面外に出たら、死んだことにする
	if (pos_.x < -img_width || 640 + img_width < pos_.x)
	{
		isEnabled_ = false;
	}
}

void ChargeShot::Draw()
{
	DrawRectRotaGraph(pos_.x, pos_.y,			//表示座標
		(imgIdx_ / anim_fraem_per_img) * img_width, 0,						//切り取り左上
		img_width, img_height,									//幅、高さ
		img_scale, 0.0f,								//拡大率、回転角度
		handle_, true);
}

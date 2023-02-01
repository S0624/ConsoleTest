#include "Shot.h"
#include"DxLib.h"

constexpr int img_width = 19;
constexpr int img_height = 6;
constexpr float img_scale = 2.0f;

Shot::Shot(int handle) : handle_(handle),
vel_(6.0f,0.0f)		//弾のスピード	
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
	//死んでいるのなら動かさない
	if (!isEnabled_) return;
	pos_ += vel_;		//弾を現在速度で移動させる

	//画像のインデックスを切り替える
	imgIdx_ = (imgIdx_ + 1) % 2;
	
	//弾が画面外に出たら、死んだことにする
	if (pos_.x < -img_width || 640 + img_width < pos_.x)
	{
		isEnabled_ = false;
	}
}

void Shot::Draw()
{
	//死んでいるのなら表示しない
	if (!isEnabled_) return;
	DrawRectRotaGraph(pos_.x, pos_.y,			//表示座標
		imgIdx_ * img_width, 0,						//切り取り左上
		img_width, img_height,									//幅、高さ
		img_scale, 0.0f,								//拡大率、回転角度
		handle_, true);
}

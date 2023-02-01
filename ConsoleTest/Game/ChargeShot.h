#pragma once
#include"../Geometry.h"

class ChargeShot
{
private:
	Position2 pos_;		//自機の座標
	Vector2 vel_;		//自機の座標
	int handle_;
	int imgIdx_ = 0;			//表示する画像
	//弾有効フラグ
	bool isEnabled_ = false;	//今弾は生きている

public:
	ChargeShot();

	//弾を復活させる
	void Fire(const Position2& pos);
	//弾の有効無効フラグを得る
	bool IsEnabled()const;
	void Update();
	void Draw();
};


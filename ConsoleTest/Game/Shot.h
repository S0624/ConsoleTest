#pragma once
#include"../Geometry.h"

class Shot
{
private:
	Position2 pos_;		//自機の座標
	Vector2 vel_;		//自機の座標
	int handle_;
	int imgIdx_ = 0;			//表示する画像
	bool isEnabled_ = false;	//今弾は生きているフラグ（true : 生きている　false : 死んでいる）

public:
	Shot(int handle);
	
	//弾を復活させる
	void Fire(const Position2& pos);
	//弾の有効無効フラグを得る
	bool IsEnabled()const;
	void Update();
	void Draw();

};


#pragma once

#include"../Geometry.h"

class InputState;
class Enemy;

class Player
{
private:
	Enemy* enemy_ = nullptr;
	Position2 pos_;		//自機の座標
	int handle_;		//自機画像ハンドル
	int imgIdx_ = 0;			//表示する画像
public:
	Player();
	
	const Position2& GetPosition()const;

	/// <summary>
	/// プレイヤーの状態の更新
	/// </summary>
	/// <param name="input"></param>
	void Update(const InputState& input);

	/// <summary>
	/// プレイヤーの描画処理
	/// </summary>
	void Draw();

	void Dameaged(){}
};


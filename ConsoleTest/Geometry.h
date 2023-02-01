#pragma once

/// <summary>
/// ベクトル構造体
/// プレイヤーの座標や速度を表すためのもの
/// </summary>
struct  Vector2
{
	float x;
	float y;

	Vector2() : x(0),y(0){}
	Vector2(float inx, float iny) : x(inx), y(iny) {}

	//加算、減算
	Vector2 operator + (const Vector2& rval)
	{
		return { x + rval.x,y + rval.y };
	}
	Vector2 operator - (const Vector2& rval)
	{
		return { x - rval.x,y - rval.y };
	}
	void operator += (const Vector2& rval);
	void operator -= (const Vector2& rval);
	
	//スカラー倍、スカラー割
	Vector2 operator*(float scale)const;
	Vector2 operator/(float div)const;
	void operator*=(float scale);
	void operator/=(float div);
	
	//ベクター逆転（-）
	Vector2 operator -()const;

	//ベクトルの大きさを返す
	float Length()const;

	//ベクトルの大きさの二乗を返す
	float SQLength()const;

	//ベクトルの正規化
	void Normalize();

	//正規化したベクトルを返す
	Vector2 GetNormalized()const;

};


//座標を示す別名
using Position2 = Vector2;
#pragma once
#include<tchar.h>

//自分用ライブラリ用名前空間
namespace my
{
	int MyLoadGraph(const TCHAR* path);

	int MyDrawRectRotaGraph(int x, int y, int left, int top,
		int width, int height, float scale, float angle, int handle, bool transFlag);
}

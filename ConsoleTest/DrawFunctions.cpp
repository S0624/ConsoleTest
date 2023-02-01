#include<DXLib.h>
#include<assert.h>
#include"DrawFunctions.h"

namespace my
{
	int MyLoadGraph(const TCHAR* path)
	{
		int handle = LoadGraph(path);
		assert(handle >= 0);
		return handle;
	}
	int MyDrawRectRotaGraph(int x, int y, int left, int top, int width, int height, float scale, float angle, int handle, bool transFlg)
	{
		return DrawRectRotaGraph(x, y,
			left, top,
			width, height,
			scale, angle,
			handle, transFlg);
	}
}

//end of namaspace my
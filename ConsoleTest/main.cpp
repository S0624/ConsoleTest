#include<stdio.h>
#include<memory>
#include<DxLib.h>
#include<cassert>
#include<array>
#include<iostream>
#include"Scene/SceneManager.h"
#include"Scene/TitleScene.h"
#include"InputState.h"
#include"DrawFunctions.h"

//中でメモリを動的確保して返す
//void CreateInt(int** in)
//{
//	*in = (int*)malloc(sizeof(int));
//	*(*in) = 100;
//}
//
//class Animal
//{
//public:
//	virtual void Attack() = 0;
//	virtual void Cry() = 0;
//};
//
//class Cat: public::Animal
//{
//public:
//	void Attack()
//	{
//		std::cout << "ひっかき";
//	}
//	void Cry()
//	{
//		std::cout << "にゃー" ;
//	}
//};
//class Dog: public::Animal
//{
//public:
//	void Attack()
//	{
//		std::cout << "噛みつき";
//	}
//	void Cry()
//	{
//		std::cout << "わん" ;
//	}
//};
//
//void AnimalAttack(Animal& animal)
//{
//	animal.Attack();
//}
//void AnimalCry(Animal& animal)
//{
//	animal.Cry();
//}

//int main()
//{
//	//Dog dog;
//	//Cat cat;
//	//AnimalAttack(dog);
//	//AnimalCry(cat);
//	/*int array[] = {1,3,5,7,9};
//
//	int darray[2][2]{ {1,2},{3,4} };
//
//	union Nandemo
//	{
//		int a;
//		float b;
//		char c[4];
//	};
//
//	Nandemo n;
//	n.b = 3.14f;
//	printf("NandemoSize = %d\n",sizeof(n));
//	printf("int = %d\n", n.a);
//	printf("float = %f\n", n.b);
//	printf("str = %s\n", n.c);
//
//	struct BitField
//	{
//		uint32_t a : 10;
//		uint32_t b : 8;
//		uint32_t c : 6;
//		uint32_t d : 4;
//		uint32_t e : 2;
//		uint32_t f : 1;
//		uint32_t g : 1;
//	};
//	BitField bit = { 256,64,32,15,3,1,0 };
//	printf("BitFieldSize = %d\n", sizeof(BitField));
//	printf("a = %d \n", bit.a);
//	printf("b = %d \n", bit.b);
//	printf("c = %d \n", bit.c);
//	printf("d = %d \n", bit.d);
//	printf("e = %d \n", bit.e);
//	printf("f = %d \n", bit.f);
//	printf("g = %d \n", bit.g);
//
//	int g = 0b1001001;
//	printf("1001001 = %d \n", g);
//
//	//int* i = nullptr;
//	//CreateInt(&i);
//	//printf("%d", *i);
//
//	//int a = rand() %12 + 1;
//	//char str[256];
//	//sprintf_s(str, "%d o'clock now", a);
//	//FILE* fp = nullptr;
//	//fopen_s(&fp,str, "wb");
//	//fwrite(&a, sizeof(a), 1, fp);
//	//fclose(fp);
//
//	//printf("%s\n", str);*/
//
//	//Vector3 vectors[4];
//	//while (ProcessMessage() != -1)
//	//{
//	//	ClearDrawScreen();
//	//	for (int i = 0; i < _countof(vectors); i++)
//	//	{
//	//	}
//	//}
//
//
//	return 0;
//}

//class C
//{
//private:
//	void FuncA()
//	{
//		std::cout << "A";
//	}
//	void FuncB()
//	{
//		std::cout << "B";
//	}	
//	void FuncC()
//	{
//		std::cout << "C";
//	}
//	void(C::* func_)() = nullptr;
//
//public:
//	C() : func_(&C::FuncA)
//	{
//
//	}
//	void CallFunc()
//	{
//		(this->*func_)();
//	}
//};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//void (*f)() = Function;
	//std::cout << f;

	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	//int count = 0;
	//int value = 0;
	//int handle = 0;
	//handle = my::MyLoadGraph(L"img.png");

	//++value;
	//int array[] = { 1,2,3,4,5,6,-1,8,9,10 };
	//int temp = 0;

	//Vector3 vectors[4];
	////vectors[0].x;
	//for (auto& v : vectors)
	//{
	//	//v.x = rand() / 1000;
	//}

	InputState input;
	SceneManager scenemanager;
	scenemanager.ChangeScene(new TitleScene(scenemanager));

	while (ProcessMessage() != -1)
	{
		ClearDrawScreen();
		
		//入力の更新
		input.Update();

		scenemanager.Update(input);
		scenemanager.Draw();

		auto fps = GetFPS();	//Frame　Per Second;
		auto drawcall = GetDrawCallCount();		//描画命令数

		DrawFormatString(10, 10, 0xffffff, L"FPS = %2.2f", fps);
		DrawFormatString(10, 30, 0xffffff, L"DC = %d", drawcall);

		ScreenFlip();

		// escキーを押したら終了する
		//if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}

	DxLib_End();
	return 0;

}
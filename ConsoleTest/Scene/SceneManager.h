#pragma once

#include<deque>

//プロトタイプ宣言
class Scene;		//シーン基底クラス
class InputState;	//入力ステート

//シーン監視クラス
class SceneManager
{
private:
	//「今実行中」のシーンを切り替えていきたいので
	//参照ではなくポインタとして宣言
	std::deque<Scene*> scenes_;
	//Scene* scene_ = nullptr;

public:
	/// <summary>
	/// シーンの切り替えを行う
	/// </summary>
	/// <param name="scene">切り替えたい次のシーンのアドレス</param>
	void ChangeScene(Scene* scene);
	/// <summary>
	/// シーンを上に積む
	/// Updateで実行されるのは上に積まれたシーンのみ
	/// </summary>
	/// <param name="scene"></param>
	void PushScene(Scene* scene);

	/// <summary>
	/// 一番上のシーンを削除する
	/// Updateで実行されるのは上に積まれたシーンのみ
	/// </summary>
	/// <param name="scene"></param>
	void PopScene();
	
	/// <summary>
	/// 各シーンのUpdateを（更新）行う
	/// </summary>
	/// <param name="input"></param>
	void Update(const InputState& input);
	/// <summary>
	/// 各シーンの描画
	/// </summary>
	void Draw();
};


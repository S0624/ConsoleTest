#pragma once
#include "Scene.h"
class OptionScene :
    public Scene
{
public:
	OptionScene(SceneManager& manager) : Scene(manager) {};
	~OptionScene() {};

	void Update(const InputState& input);
	void Draw();
};

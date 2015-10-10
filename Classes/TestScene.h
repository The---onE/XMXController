#pragma once

#include "XMX_Global.h"
#include "TestLayer.h"

class TestScene : public Scene
{
private:
	TestLayer* layer;

public:
	CREATE_FUNC(TestScene);
	bool init();
	void quit();
};


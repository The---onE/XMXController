#include "TestScene.h"

bool TestScene::init()
{
	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_0(TestScene::quit, this));
	closeItem->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
	closeItem->setPosition(Point(WIDTH, 0));
	SETSIZE(closeItem, 0.15);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	layer = TestLayer::create();
	addChild(layer);

	return true;
}

void TestScene::quit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
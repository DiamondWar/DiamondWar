#include "ChoseTowerUIManager.h"
#include "cocostudio/CocoStudio.h"
#include "HelloWorldScene.h"

USING_NS_CC;
Scene* CChoseTowerUIManager::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CChoseTowerUIManager::create();

	// add layer as a child to scene
	scene->addChild(layer);
	return scene;
}
bool CChoseTowerUIManager::init()
{
	if (!Layer::init())
		return false;

	auto*node = CSLoader::createNode("ChoseTowerRoot.csb");
	auto* title1 = node->getChildByName("cost_title_1");
	auto *title2 = node->getChildByName("cost_title_2");
	auto *title3 = node->getChildByName("cost_title_3");
	auto *title4 = node->getChildByName("cost_title_4");
	auto * title5 = node->getChildByName("cost_title_5");
	title1->setPosition(Init_x+60, Init_y + 170);
	title2->setPosition(Init_x + 160 + 60, Init_y + 170);
	title3->setPosition(Init_x + 320 + 60, Init_y + 170);
	title4->setPosition(Init_x + 480 + 60, Init_y + 170);
	title5->setPosition(Init_x + 640 + 60, Init_y + 170);
	StartGame = static_cast<Button*>(node->getChildByName("Button_1"));
	StartGame->setPressedActionEnabled(true);
	StartGame->setEnabled(true);
	StartGame->addClickEventListener(CC_CALLBACK_0(CChoseTowerUIManager::OnStartButtonClickHandleEvent, this));
	addChild(node);
	for (int i = 0; i < 20; i++)
	{
		CTowerItemUI* item = CTowerItemUI::create();
		item->InitInfo(i, 0, false,this);
		item->setPosition(Init_x + i % 5 * 160, Init_y - i / 5 * 160);
		item->ChoseDelegate_ = this;
		addChild(item);
		ShowTowerList_.pushBack(item);
	}
	return true;
}
void CChoseTowerUIManager::OnStartButtonClickHandleEvent()
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void CChoseTowerUIManager::OnChoseTower(int index, bool flag)
{

}
void CChoseTowerUIManager::ClickTower(int index)
{

}
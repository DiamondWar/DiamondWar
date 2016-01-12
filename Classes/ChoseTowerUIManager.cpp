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
	StartGame = static_cast<Button*>(node->getChildByName("Button_1"));
	StartGame->setPressedActionEnabled(true);
	StartGame->setEnabled(false);
	StartGame->addClickEventListener(CC_CALLBACK_0(CChoseTowerUIManager::OnStartButtonClickHandleEvent, this));
	addChild(node);
	return true;
}
void CChoseTowerUIManager::OnStartButtonClickHandleEvent()
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
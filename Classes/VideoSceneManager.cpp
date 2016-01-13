#include "VideoSceneManager.h"
#include "ChoseTowerUIManager.h"
USING_NS_CC; 
CVideoSceneManager::CVideoSceneManager()
{
}


CVideoSceneManager::~CVideoSceneManager()
{
}
Scene* CVideoSceneManager::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CVideoSceneManager::create();
	// add layer as a child to scene
	scene->addChild(layer);
	return scene;
}
bool CVideoSceneManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}
void CVideoSceneManager::onEnter()
{
	Layer::onEnter();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
	videoPlayer->setKeepAspectRatioEnabled(!videoPlayer->isKeepAspectRatioEnabled());
	videoPlayer->setFullScreenEnabled(! videoPlayer->isFullScreenEnabled());
	videoPlayer->setPosition(ccp(960, 540));
	videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	videoPlayer->setContentSize(Size(1920, 1080));
	this->addChild(videoPlayer);
	videoPlayer->addEventListener(CC_CALLBACK_2(CVideoSceneManager::videoEventCallback, this));
#endif
	showVideo("IMG_0395.mp4");
}
void CVideoSceneManager::showVideo(const char *sName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	if (videoPlayer)
	{
		videoPlayer->setFileName(sName);
		videoPlayer->play();
	}
	else
	{
		this->videoPlayOverCallBack();
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	this->videoPlayOverCallBack();
#endif
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void CVideoSceneManager::videoEventCallback(Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType){
	switch (eventType) {
	case cocos2d::experimental::ui::VideoPlayer::EventType::PLAYING:
		break;
	case cocos2d::experimental::ui::VideoPlayer::EventType::PAUSED:
		videoPlayOverCallBack();
		break;
	case cocos2d::experimental::ui::VideoPlayer::EventType::STOPPED:
		break;
	case cocos2d::experimental::ui::VideoPlayer::EventType::COMPLETED:
		videoPlayOverCallBack();
		break;
	default:
		break;
	}
}
#endif
void CVideoSceneManager::videoPlayOverCallBack()
{
	Director::getInstance()->replaceScene(CChoseTowerUIManager::createScene());
}
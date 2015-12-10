#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Bullet.h"
#include "SoliderConfig.h"
#include "SkillConfig.h"
#include "BaseBoss.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    //// 'scene' is an autorelease object
    //auto scene = Scene::create();
    //
    //// 'layer' is an autorelease object
    //auto layer = HelloWorld::create();

    //// add layer as a child to scene
    //scene->addChild(layer);

	//创建有物理空间的场景 
	Scene* scene = Scene::createWithPhysics();
	//设置Debug模式，你会看到物体的表面被线条包围，主要为了在调试中更容易地观察 
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	HelloWorld* layer = HelloWorld::create();
	//把空间保持我们创建的层中，就是上面所说m_world的作用，方便后面设置空间的参数 
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet.plist", "Bullet.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet1.plist", "Bullet1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BZ.plist", "BZ.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("JZ.plist", "JZ.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PZ.plist", "PZ.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ZDZ.plist", "ZDZ.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BattleBoss.plist", "BattleBoss.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SF.plist", "SF.png");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("A1.plist", "A1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("A2.plist", "A2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("B1.plist", "B1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("B2.plist", "B2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("C1.plist", "C1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("C2.plist", "C2.png");
	CSoliderConfig::GetInstance()->LoadText();
	CSkillConfig::GetInstance()->LoadText();
    
	
	Node* node = CSLoader::createNode("MainScene.csb");
	addChild(node);
	CBaseBoss* boss = new CBaseBoss(1);
	addChild(boss->Obj);
	CBaseBoss* boss1 = new CBaseBoss(2);
	addChild(boss1->Obj);
	CSolider* sol = new CSolider(202,1,1);
	addChild(sol->Obj);
	CBattleObjectManager::GetInstance()->AddObject(sol);
	CSolider* sol2 = new CSolider(101, 1, 2);
	addChild(sol2->Obj);
	CBattleObjectManager::GetInstance()->AddObject(sol2);

	this->scheduleUpdate();
    return true;
}
void HelloWorld::update(float dt)
{
	CCGlobleConfig::Game_time++;
	CBattleObjectManager::GetInstance()->Update();
}

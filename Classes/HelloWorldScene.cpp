#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Bullet.h"
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

    
	Node* node = CSLoader::createNode("MainScene.csb");
	addChild(node);
	CSolider* sol = new CSolider("heyeguai.csb", 100,480,1,1,500);
	addChild(sol->Obj);
	CBattleObjectManager::GetInstance()->AddObject(sol);
	CSolider* sol2 = new CSolider("heyeguai.csb", 1900, 480, 1, 2, 200);
	addChild(sol2->Obj);
	CBattleObjectManager::GetInstance()->AddObject(sol2);

	/*CBullet* buttlet = new CBullet(1, "Bullet", 960, 480, sol2, 1, 2);
	addChild(buttlet->Obj);
	CBattleObjectManager::GetInstance()->AddObject(buttlet);*/

	this->scheduleUpdate();
    return true;
}
void HelloWorld::update(float dt)
{
	CBattleObjectManager::GetInstance()->Update();
}

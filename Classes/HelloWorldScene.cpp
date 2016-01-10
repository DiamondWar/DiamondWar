#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SoliderConfig.h"
#include "SkillConfig.h"
#include "BattleUIManager.h"
#include "GameSceneControl.h"
#include "AttackConfig.h"
#include "StrengthConfig.h"
#include "AudioManager.h"
#include "EnemyLevelConfig.h"
#include "SpellConfig.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	//创建有物理空间的场景 
	//Scene* scene = Scene::createWithPhysics();
	////设置Debug模式，你会看到物体的表面被线条包围，主要为了在调试中更容易地观察 
	////scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//HelloWorld* layer = HelloWorld::create();
	////把空间保持我们创建的层中，就是上面所说m_world的作用，方便后面设置空间的参数 
	////layer->setPhyWorld(scene->getPhysicsWorld());
	//scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Battle.plist", "Battle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BattleShuiJing.plist", "BattleShuiJing.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BZ.plist", "BZ.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("JZ.plist", "JZ.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PZ.plist", "PZ.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ZDZ.plist", "ZDZ.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BattleBoss.plist", "BattleBoss.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Line.plist", "Line.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("caihong.plist", "caihong.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("DuiHua.plist", "DuiHua.png");
	//初始化技能资源
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_1001_2.plist", "Skill/ASkill_1001_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_1001_3.plist", "Skill/ASkill_1001_3.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_1002_3.plist", "Skill/ASkill_1002_3.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_1003_2.plist", "Skill/ASkill_1003_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_2001_2.plist", "Skill/ASkill_2001_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_2002_1.plist", "Skill/ASkill_2002_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_2002_2.plist", "Skill/ASkill_2002_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_2003_1.plist", "Skill/ASkill_2003_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_2003_2.plist", "Skill/ASkill_2003_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_3001_1.plist", "Skill/ASkill_3001_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_3001_2.plist", "Skill/ASkill_3001_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_3001_3.plist", "Skill/ASkill_3001_3.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_3002_2.plist", "Skill/ASkill_3002_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_3002_3.plist", "Skill/ASkill_3002_3.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_3003_1.plist", "Skill/ASkill_3003_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/ASkill_3003_2.plist", "Skill/ASkill_3003_2.png");
	//初始化普通攻击的资源
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet_1003_1.plist", "Bullet/Bullet_1003_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet_2001_1.plist", "Bullet/Bullet_2001_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet_2001_3.plist", "Bullet/Bullet_2001_3.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet_2002_1.plist", "Bullet/Bullet_2002_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet_2003_1.plist", "Bullet/Bullet_2003_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet_3001_1.plist", "Bullet/Bullet_3001_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet_3002_1.plist", "Bullet/Bullet_3002_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet_3003_1.plist", "Bullet/Bullet_3003_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet_3003_2.plist", "Bullet/Bullet_3003_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet_common_1.plist", "Bullet/Bullet_common_1.png");
	//初始化法术的资源
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Spell/Spell_1_1.plist", "Spell/Spell_1_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Spell/Spell_1_2.plist", "Spell/Spell_1_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Spell/Spell_1_3.plist", "Spell/Spell_1_3.png");

	//预加载音效
	CAudioManager::GetInstance()->PreLoadAudio("Audio/ASkillVoiceRun_1001.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/ASkillVoiceRun_1002.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/ASkillVoiceRun_1003.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/ASkillVoiceRun_2001.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/ASkillVoiceRun_2002.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/ASkillVoiceRun_2003.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/ASkillVoiceRun_3001.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/ASkillVoiceRun_3002.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/ASkillVoiceRun_3003.mp3");
	//加载音乐
	CAudioManager::GetInstance()->PreLoadAudioBackground("Audio/background.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceHurt_2001.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceHurt_2002.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceHurt_2003.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceHurt_3001.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceHurt_3002.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceHurt_3003.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceIdle_1001.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceIdle_1002.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceIdle_1003.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceIdle_2001.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceIdle_2002.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceIdle_2003.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceIdle_3001.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceIdle_3002.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/AttackVoiceIdle_3003.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/SkillVoiceHurt_2003.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/SkillVoiceHurt_3003.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/SpellVoiceIdle_1.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/audio_nan_golden.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/audio_nan_haha.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/audio_nan_welcome.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/audio_nv_caiseshuijing.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/audio_nv_heropower.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/audio_nv_hewin.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/audio_nv_monkey.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/audio_nv_start.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/audio_nan_welldone.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/moveshuijing.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/touchshuijing.mp3");
	//加载配置文件
	CSoliderConfig::GetInstance()->LoadText();
	CSkillConfig::GetInstance()->LoadText();
	CAttackConfig::GetInstance()->LoadText();
	CStrengthConfig::GetInstance()->LoadText();
	CEnemyLevelConfig::GetInstance()->LoadText();
	CSpellConfig::GetInstance()->LoadText();
	CAudioManager::GetInstance()->PlayerBackGroundMusic("background.mp3");
	
	
	CGameSceneControl::GetInstance()->InitGameData();
	Node* node = Node::create();
	node->setAnchorPoint(ccp(0.5, 0.5));
	addChild(node);
	auto*battle = CSLoader::createNode("BattleScene.csb");
	node->addChild(battle);
	CGameSceneControl::GetInstance()->SetRoot(node);
	auto manager = CBattleUIManager::create();
	manager->setAnchorPoint(ccp(0, 0));
	manager->setPosition(0, 0);
	addChild(manager);
	this->scheduleUpdate();
	LastFrameCount = 0;
	

	CGameSceneControl::GetInstance()->CreateBoss(1);
	CGameSceneControl::GetInstance()->CreateBoss(2);
	EnemyData_ = CEnemyLevelConfig::GetInstance()->GetItemByIndex(EnemeyCount);
	return true;
}
void HelloWorld::update(float dt)
{
	CCGlobleConfig::Game_time++;
	CBattleObjectManager::GetInstance()->Update();
	if (EnemyData_ != nullptr && (LastFrameCount + EnemyData_->ReadyTime <= CCGlobleConfig::Game_time))
	{
		LastFrameCount = CCGlobleConfig::Game_time;
		CGameSceneControl::GetInstance()->CreateSolider(EnemyData_->RoleId, 2, 1);
		EnemeyCount++;
		EnemyData_ = CEnemyLevelConfig::GetInstance()->GetItemByIndex(EnemeyCount);
	}
}
void HelloWorld::onExit()
{
	Layer::onExit();
	SpriteFrameCache::getInstance()->removeSpriteFrames();
	//预加载音效
	CAudioManager::GetInstance()->UnLoadAudio("Audio/ASkillVoiceRun_1001.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/ASkillVoiceRun_1002.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/ASkillVoiceRun_1003.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/ASkillVoiceRun_2001.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/ASkillVoiceRun_2002.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/ASkillVoiceRun_2003.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/ASkillVoiceRun_3001.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/ASkillVoiceRun_3002.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/ASkillVoiceRun_3003.mp3");
	//加载音乐
	CAudioManager::GetInstance()->UnLoadAudio("Audio/background.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceHurt_2001.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceHurt_2002.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceHurt_2003.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceHurt_3001.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceHurt_3002.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceHurt_3003.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceIdle_1001.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceIdle_1002.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceIdle_1003.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceIdle_2001.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceIdle_2002.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceIdle_2003.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceIdle_3001.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceIdle_3002.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/AttackVoiceIdle_3003.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/SkillVoiceHurt_2003.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/SkillVoiceHurt_3003.mp3");
	CAudioManager::GetInstance()->UnLoadAudio("Audio/SpellVoiceIdle_1.mp3");

}

#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"EnemyManager.h"
EnemyManager::EnemyManager()
	:EnemyHandle(0)
{
	enemyBase = 0;
}

EnemyManager::~EnemyManager()
{
	// ˆ—‚È‚µ.
}

void EnemyManager::Initialize()
{
	EnemyHandle = MV1LoadModel("data/model/Enemy/kookie.mv1");
}

void EnemyManager::Update()
{
	//enemyBaseUpdate();
}
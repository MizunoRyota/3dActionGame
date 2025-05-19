#include"DxLib.h"
#include"EnemyBase.h"

EnemyBase::EnemyBase()
	:EnemyHandle(-1)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{

}

void EnemyBase::Draw()
{
	MV1DrawModel(EnemyHandle);
}
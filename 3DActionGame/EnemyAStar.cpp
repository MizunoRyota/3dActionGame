#include"DxLib.h"
#include"EnemyAStar.h"
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

A_Star::A_Star()
{
}

A_Star::~A_Star()
{
}

void A_Star::CalcDistance()
{
	//プレイヤーの位置からエネミーの位置を計算
	DistancePos = VSub(PlayerPos, EnemyPos);
}

void A_Star::Update()
{





}
#include"DxLib.h"
#include"EnemyAStar.h"
#include <vector>
#include <queue>
#include <cmath>

A_Star::A_Star()
	: playerPos(VGet(0, 0.0f, 0.0f))
	, enemyPos(VGet(0, 0.0f, 10.0f))
	, distancePos(VGet(0, 0.0f, 0.0f))
	, goalPos(VGet(0, 0.0f, 0.0f))
	, distance(0.0f)
{

}


A_Star::~A_Star()
{

}

void A_Star::CalcDistance()
{
	//プレイヤーの位置からエネミーの位置を計算
	distancePos = VSub(playerPos, enemyPos);
	distance = VSize(distancePos);
}

void A_Star::MapInitialize()
{
	for (int i = 0; i < MapWidth; i++)
	{
		for (int j = 0; j < MapHeight; j++)
		{
			int x_pos = (-AllMapChipSize_X * Harf ) + (j * MapChipSize) + MapChipSizeOffset;
				
			int z_pos = (AllMapChipSize_Z * Harf ) - (i * MapChipSize) - MapChipSizeOffset;

			mapCheck[i][j].position = VECTOR(x_pos, 0, z_pos);
			mapCheck[i][j].isenemy = false;
			mapCheck[i][j].isplayer = false;
		}
	}
}

/// @brief 
/// @param enemypos 
/// @param playerpos 
void A_Star::Update(VECTOR enemypos,VECTOR playerpos)
{

	this->enemyPos = enemypos;
	this->playerPos = playerpos;

	CheckCharacter(enemyPos);
	CheckCharacter(playerPos);

}


void A_Star::CheckCharacter(VECTOR pos)
{

	float distance = 0.0f;						// キャラクターとマップチップの中心の距離
	VECTOR checkdistance = VGet(0, 0, 0);		//チェック用の距離VECTOR

	for (int i = 0; i < MapWidth; i++)
	{
		for (int j = 0; j < MapHeight; j++)
		{
			// 各マップチップの位置と引数の位置を比較
			checkdistance = VSub(mapCheck[i][j].position, pos);

			distance = VSize(checkdistance);


			
		}
	}
}

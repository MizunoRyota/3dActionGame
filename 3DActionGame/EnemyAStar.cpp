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
	distancePos = VSub(playerPos, enemyPos);
}

void A_Star::MapInitialize()
{
	for (int i = 0; i < MapWidth; i++)
	{
		for (int j = 0; j < MapHeight; j++)
		{
			int x_pos = (-AllMapChipSize_X * Harf) + (i * MapChipSize) + MapChipSizeOffset;
				
			int z_pos = (AllMapChipSize_Z * Harf) - (j * MapChipSize) - MapChipSizeOffset;

			map[i][j] = VECTOR(x_pos, 0, z_pos);
		}
	}
}

void A_Star::Update(VECTOR enemypos)
{




	
}
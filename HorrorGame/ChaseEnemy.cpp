#include"DxLib.h"
#include"ChaseEnemy.h"

ChaseEnemy::ChaseEnemy()
	:position (VGet(0,0,0))
	,moveVec(VGet(0,0,0))
{
}

ChaseEnemy::~ChaseEnemy()
{
}
/// @brief 
/// 更新
/// @param playerpos 
/// @param enemypos 
/// @return 
VECTOR ChaseEnemy::Update(const VECTOR& playerpos, const VECTOR& enemypos)
{
	moveVec = VGet(0, 0, 0);

	if (CheckCameraViewClip(enemypos))
	{
		// プレイヤーと敵の位置ベクトルの差分
		VECTOR toTarget = VSub(playerpos, enemypos);

		// プレイヤーに向かって進む方向を単位ベクトルで求める
		VECTOR direction = VNorm(toTarget);

		// 敵が進む距離（移動速度に基づく）
		 moveVec = VScale(direction, MoveSpeed);

		// 敵の位置を更新
		position = VAdd(enemypos, moveVec);

		return position;
	}
	else
	{
		return enemypos;
	}
}
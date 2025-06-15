#include"DxLib.h"
#include"Pallet.h"
#include"CheckChaseRange.h"

CheckRange::CheckRange()
    :lengthRange(0)
    //,isChaseWithin(false)
    ,distance(0)
{
}

CheckRange::~CheckRange()
{
}

/// @brief 
/// 更新
/// @param playerpos 
/// @param enemypos 
void CheckRange::Update(const VECTOR& playerpos, const VECTOR& enemypos)
{
     CheckWithin(playerpos, enemypos);
}
/// @brief 
/// プレイヤーを追いかける距離に入っているか調べる関数
/// @param playerpos 
/// @param enemypos 
/// @return 
bool CheckRange::CheckWithin(const VECTOR& playerpos, const VECTOR& enemypos)
{
    //プレイヤーとEnemyの距離の合計を獲得
    keepDistance = VSub(playerpos, enemypos);
    //プレイヤーとEnemyの半径の合計
    lengthRange = playerRadius + enemeyRadius;
    //ベクトルを2乗
    distance = VSquareSize(keepDistance);
    //LengthよりDistanceちいさくなったとき返す
    return distance <= (lengthRange * lengthRange);
}

/// @brief 
/// 範囲を表示する関数
/// @param playerpos 
/// @param enemypos 
void CheckRange::DebugDraw(const VECTOR& playerpos, const VECTOR& enemypos)
{
    DrawSphere3D(enemypos, enemeyRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    DrawSphere3D(playerpos, playerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
}
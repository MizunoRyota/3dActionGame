#include"Dxlib.h"
#include"CheckGetScore.h"
#include"MapChip.h"

CheckGetScore::CheckGetScore()
{
}

CheckGetScore::~CheckGetScore()
{
}

bool CheckGetScore::Update(const VECTOR& playerpos, const VECTOR& fragmentpos,MapChip& mapchip)
{
        CheckGetFraguments(playerpos, fragmentpos, mapchip);

    return isGetFragment;
}

bool CheckGetScore::CheckGetFraguments(const VECTOR& playerpos, const VECTOR& fragmentpos, MapChip& mapchip)
{
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            //プレイヤーとEnemyの距離の合計を獲得
            keepDistance = VSub(playerpos, mapchip.GetMapChipPosition(i,j));
            //プレイヤーとEnemyの半径の合計
            lengthRange = playerRadius + FragmentRadius;
            //ベクトルを2乗
            distance = VSquareSize(keepDistance);
            //LengthよりDistanceちいさくなったとき返す
            if (distance <= (lengthRange * lengthRange))
            {
               return isGetFragment = true;
            }
            else
            {
                isGetFragment = false;
            }
        }
    }
}
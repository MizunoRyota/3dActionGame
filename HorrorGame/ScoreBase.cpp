#include"Dxlib.h"
#include"ScoreBase.h"
#include"ObjectBase.h"

ScoreBase::ScoreBase()
	:currentScore(50)
	,isDecreaceScore(false)
{
	checkgetscore = new CheckGetScore();
	scoreeffect = new ScoreEffect();
}

// 追加: ObjectBaseのfragmentPositionをコピーするメソッド
void ScoreBase::SetFragmentPositionsFromObject(const ObjectBase& obj)
{
	for (int i = 0; i < FragmentNum; i++)
	{
		FragmentPosition[i] = obj.GetFragmentPosition(i);
	}
}

ScoreBase::~ScoreBase()
{
}

void ScoreBase::Initialize(const VECTOR& playerpos, MapChip& mapchipconst, const ObjectBase& obj)
{
	SetFragmentPositionsFromObject(obj); // ObjectBaseからフラグメントの位置を設定
}

void ScoreBase::Update(const VECTOR& playerpos, MapChip& mapchip)
{
	for (int i = 0; i < FragmentNum; i++)
	{
		isDecreaceScore = checkgetscore->Update(playerpos, FragmentPosition[i], mapchip);
		if (isDecreaceScore)
		{

			break;
		}
		else
		{
			isDecreaceScore = false;
		}
	}
	DecreaceScore();
}

void ScoreBase::DecreaceScore()
{
	if (isDecreaceScore)
	{
		currentScore--;
	}
}
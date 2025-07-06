#pragma once
#include"CheckGetScore.h"
#include"ScoreEffect.h"
#include"ObjectBase.h" // 追加: ObjectBaseを使うため

class ScoreBase
{
public:
	ScoreBase();
	~ScoreBase();
	void Initialize(const VECTOR& playerpos, MapChip& mapchip, const ObjectBase& obj);
	void GetPosition(const VECTOR& playerpos, MapChip& mapchip);
	void Update(const VECTOR& playerpos, MapChip& mapchip);
	void DecreaceScore();
	// 追加: ObjectBaseのfragmentPositionをコピーする
	void SetFragmentPositionsFromObject(const ObjectBase& obj);

private:
	static constexpr int FragmentNum = 50;					//モデルの大きさの倍数
	VECTOR FragmentPosition[FragmentNum];					// フラグメントの位置	
	VECTOR playerPosition;									//プレイヤーの座標
	int currentScore = 50;									//
	bool isDecreaceScore;

	CheckGetScore* checkgetscore;							//
	ScoreEffect* scoreeffect;								//エフェクト
};

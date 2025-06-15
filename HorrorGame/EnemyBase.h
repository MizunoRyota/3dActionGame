#pragma once
#include"EnemyAStar.h"
#include"ChaseEnemy.h"
#include"CheckChaseRange.h"

class Stage;

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	void Initialize();	//初期化

	virtual void Update(const VECTOR& playerpos, Stage& stage);//更新
	void UpdateAngle(const VECTOR& player);						//向きの更新
	virtual void Move(const VECTOR& MoveVector, Stage& stage);	//ポジションセット
	virtual void Draw(const VECTOR& playerpos);					//表示

	void VibeTimer(const VECTOR& playerpos);					//コントローラーの振動タイマー

	//モデルのgetter
	// モデルハンドルの取得.
	int GetModelHandle() const { return EnemyHandle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }
	void SetPos(const VECTOR set) { position = set; }

private:
	bool debugPauseFlag = false;							//

	static constexpr float Scale = 1.20f;					//モデルの大きさの倍数
	static constexpr float VibeLimit = 1000.0f;				//大きさ
	static constexpr float WithinVibeLimit = 500.0f;		//大きさ

	int EnemyHandle;		//モデルハンドル
	float angle;			//方向
	VECTOR position;		//ポジション
	VECTOR angleVector;		//方向
	float vibeTime;			//バイブレーション時間

	//インスタンス生成
	A_Star* astar;				
	ChaseEnemy* chase;
	CheckRange* checkrange;
};
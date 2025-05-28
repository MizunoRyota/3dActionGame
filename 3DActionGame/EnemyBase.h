#pragma once

#include"EnemyAStar.h"

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	void Initialize();

	virtual void Update(VECTOR playerpos);
	virtual void Move();
	virtual void Draw();

	int GetModelHandle() { return EnemyHandle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return position; }
	void SetPos(const VECTOR set) { position = set; }

private:
	static constexpr float Scale = 1.0f;	//モデルの大きさの倍数
	
	int EnemyHandle;
	VECTOR position;

	//インスタンス生成
	A_Star* astar;

};
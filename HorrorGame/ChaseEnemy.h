#pragma once

class ChaseEnemy
{
public:
	ChaseEnemy();
	~ChaseEnemy();

	VECTOR Update(const VECTOR& playerpos, const VECTOR& enemypos);	//メインの更新

	const VECTOR& GetMoveScale() const { return moveVec; }

private:
	static constexpr float MoveSpeed = 0.03f;	//アニメーションを進める速度

	VECTOR position;
	VECTOR moveVec;
};


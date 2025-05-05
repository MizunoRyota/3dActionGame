#pragma once

#include"DxLib.h"

class EnemyBase 
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Update();
	virtual void Draw();

	int GetModelHandle() { return EnemyHandle; }

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }

private:
	int EnemyHandle;
	VECTOR pos;
};


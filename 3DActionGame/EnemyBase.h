#pragma once

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Update();
	virtual void Draw();

	int GetModelHandle() { return EnemyHandle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return position; }
	void SetPos(const VECTOR set) { position = set; }

private:
	static constexpr float Scale = 1.0f;	//モデルの大きさの倍数
	
	int EnemyHandle;
	VECTOR position;
};
#pragma once
class EnemyBase;

class EnemyManager final
{
public:
	EnemyManager();
	~EnemyManager();

	void Initialize();
	void Update();
private:
	EnemyBase* enemyBase;
	int EnemyHandle;
};
#include"DxLib.h"
#include"EnemyAnimationManager.h"

EnemyAnimationManager::EnemyAnimationManager(int modelhandle)
	:currentPlayAnim(-1)
	,currentAnimCount(0.0f)
	,prevPlayAnim(-1)
	,prevAnimCount(0.0f)
	,prevPlayTime(0.0f)
	,animBlendRate(1.0f)
	,currentState(State::Idle)
{
	enemyHandle = modelhandle;
	PlayAnim(AnimKind::Idle); // 初期状態はIdleアニメーション
}

EnemyAnimationManager::~EnemyAnimationManager()
{
}

void EnemyAnimationManager::Update()
{
	State prevState = currentState;


}



void EnemyAnimationManager::PlayAnim(AnimKind nextPlayAnim)
{
	// 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
	if (prevPlayAnim != -1)
	{
		MV1DetachAnim(enemyHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}

	// 今まで再生中のモーションだったものの情報をPrevに移動する
	prevPlayAnim = currentPlayAnim;
	prevAnimCount = currentAnimCount;

	// 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
	currentPlayAnim = MV1AttachAnim(enemyHandle, static_cast<int>(nextPlayAnim));
	currentAnimCount = 0.0f;

	// ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;
}


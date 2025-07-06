#pragma once

class EnemyAnimationManager
{
public:
	// 状態
	enum class State : int
	{
		Idle = 0,		// 立ち止まり
		Jogging = 1,		// 走り
		Bite = 2,		// ジャンプ
		Scream = 3,		// 立ち止まり状態
	};

	// プレイヤーのアニメーション種別
	enum class AnimKind : int
	{
		None = -1,		// なし
		Idle = 0,		// 不明
		Jogging = 1,	//ジョギング
		Bite = 2,		// 走り
		Scream = 3,		// 立ち止まり
	};

	EnemyAnimationManager(int modelhandle);
	~EnemyAnimationManager();

	void Update();
	void PlayAnim(AnimKind nextPlayAnim);
	void UpdateAnimationState(State prevState);	// アニメーションステートの更新
	void UpdateAnimation();						// アニメーション処理
private:
	// プレイヤー関係の定義
	static constexpr float	PlayAnimSpeed = 250.0f;		// アニメーション速度
	static constexpr float	prevPlayAnimSpeed = 250.0f;	// アニメーション速度
	static constexpr float	AnimBlendSpeed = 0.1f;		// アニメーションのブレンド率変化速度

	int			currentPlayAnim;		// 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float		currentAnimCount;		// 再生しているアニメーションの再生時間
	int			prevPlayAnim;			// 前の再生アニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float		prevAnimCount;			// 前の再生アニメーションの再生時間
	float		 prevPlayTime;			// 前のアニメーションの時間の合計
	float		animBlendRate;			// 現在と過去のアニメーションのブレンド率

	State currentState;					//状態
	int enemyHandle;					//プレイヤーハンドル
};
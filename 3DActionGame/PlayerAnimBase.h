#pragma once

class PlayerAnimBase 
{
public:
	// 状態
	enum class State : int
	{
		Walk = 0,		// 立ち止まり
		Jogging = 1,		// 走り
		Run = 2,		// ジャンプ
		Idle = 3,		// 立ち止まり状態
	};

	// プレイヤーのアニメーション種別
	enum class AnimKind : int
	{
		None = -1,		// なし
		Walk = 0,		// 不明
		Jogging = 1,	//ジョギング
		Run = 2,		// 走り
		Idle = 3,		// 立ち止まり
	};
	PlayerAnimBase(int PlayerHandle);
	virtual ~PlayerAnimBase();

	virtual void Update();	//更新

protected:
	// プレイヤー関係の定義
	static constexpr float	PlayAnimSpeed = 250.0f;	// アニメーション速度
	static constexpr float	prevPlayAnimSpeed = 250.0f;	// アニメーション速度

	static constexpr float	MoveSpeed = 30.0f;	// 移動速度
	static constexpr float	AnimBlendSpeed = 0.1f;		// アニメーションのブレンド率変化速度

	int			currentPlayAnim;		// 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float		currentAnimCount;		// 再生しているアニメーションの再生時間
	int			prevPlayAnim;			// 前の再生アニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float		prevAnimCount;			// 前の再生アニメーションの再生時間
	float		 prevPlayTime;			// 前のアニメーションの時間の合計
	float		animBlendRate;			// 現在と過去のアニメーションのブレンド率

	State currentState;					//状態
	int PlayerHandle;					//プレイヤーハンドル

	void UpdateAnimationState(State prevState);		// アニメーションステートの更新
	void ChangeMotion(AnimKind nextPlayAnim);		// 新たなアニメーションを再生する
	void UpdateAnimation();							//アニメーションの入れ替え
};


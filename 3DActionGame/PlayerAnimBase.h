#pragma once

class PlayerAnimBase
{
public:
	// 状態
	enum class State : int
	{
		Stand = 0,		// 立ち止まり
		Run = 1,		// 走り
		Jump = 2,		// ジャンプ
		Idle = 3,		// 立ち止まり状態
	};

	// プレイヤーのアニメーション種別
	enum class AnimKind : int
	{
		None = -1,		// なし
		Unknown = 0,	// 不明
		Run = 1,		// 走り
		Idle = 2,		// 立ち止まり
	};
	PlayerAnimBase();
	~PlayerAnimBase();

	void Update(int playerHandle);

private:
	// プレイヤー関係の定義
	static constexpr float	PlayAnimSpeed = 250.0f;	// アニメーション速度
	static constexpr float	MoveSpeed = 30.0f;	// 移動速度
	static constexpr float	AnimBlendSpeed = 0.1f;		// アニメーションのブレンド率変化速度

	int			currentPlayAnim;		// 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float		currentAnimCount;		// 再生しているアニメーションの再生時間
	int			prevPlayAnim;			// 前の再生アニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float		prevAnimCount;			// 前の再生アニメーションの再生時間
	float		animBlendRate;			// 現在と過去のアニメーションのブレンド率

	State currentState;					//状態

	void UpdateAnimationState(State prevState);	// アニメーションステートの更新
	void PlayAnim(AnimKind nextPlayAnim,int playerHandle);			// 新たなアニメーションを再生する
	void UpdateAnimation(int playerHandle)
};


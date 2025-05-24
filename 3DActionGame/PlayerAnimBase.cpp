#include"DxLib.h"
#include"math.h"
#include"PlayerAnimBase.h"

PlayerAnimBase::PlayerAnimBase(int PlayerHandle)
: currentState(State::Idle)
,PlayerHandle(0)
{
	this->PlayerHandle = PlayerHandle;
}

PlayerAnimBase::~PlayerAnimBase()
{
}

void PlayerAnimBase::Update()
{
	State prevState = currentState;

	// アニメーションステートの更新
	UpdateAnimationState(prevState);

	// アニメーション処理
	UpdateAnimation();

}

void PlayerAnimBase::UpdateAnimationState(State prevState)
{
	// 立ち止まりから走りに変わったら
	if (prevState == State::Idle && currentState == State::Jogging)
	{
		// 走りアニメーションを再生する
		ChangeMotion(AnimKind::Jogging);
	}
	// 走りから立ち止まりに変わったら
	else if (prevState == State::Jogging && currentState == State::Idle)
	{
		// 立ち止りアニメーションを再生する
		ChangeMotion(AnimKind::Idle);
	}
}

void PlayerAnimBase::ChangeMotion(AnimKind nextPlayAnim)
{
	// 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
	if (prevPlayAnim != -1)
	{
		MV1DetachAnim(PlayerHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}

	// 今まで再生中のモーションだったものの情報をPrevに移動する
	prevPlayAnim = currentPlayAnim;
	prevAnimCount = currentAnimCount;

	// 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
	currentPlayAnim = MV1AttachAnim(PlayerHandle, static_cast<int>(nextPlayAnim));
	currentAnimCount = 0.0f;

	// ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;
}

void PlayerAnimBase::UpdateAnimation()
{
	float animTotalTime;		// 再生しているアニメーションの総時間

	// ブレンド率が１以下の場合は１に近づける
	if (animBlendRate < 1.0f)
	{
		animBlendRate += AnimBlendSpeed;
		if (animBlendRate > 1.0f)
		{
			animBlendRate = 1.0f;
		}
	}

	// 再生しているアニメーション１の処理
	if (currentPlayAnim != -1)
	{
		// アニメーションの総時間を取得
		animTotalTime = MV1GetAttachAnimTotalTime(PlayerHandle, currentPlayAnim);

		// 再生時間を進める
		currentAnimCount += PlayAnimSpeed;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (currentAnimCount >= animTotalTime)
		{
			currentAnimCount = static_cast<float>(fmod(currentAnimCount, animTotalTime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(PlayerHandle, currentPlayAnim, currentAnimCount);

		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(PlayerHandle, currentPlayAnim, animBlendRate);
	}
	// 再生しているアニメーション２の処理
	if (prevPlayAnim != -1)
	{
		// アニメーションの総時間を取得
		animTotalTime = MV1GetAttachAnimTotalTime(PlayerHandle, prevPlayAnim);

		// 再生時間を進める
		prevPlayTime += PlayAnimSpeed;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (prevPlayTime > animTotalTime)
		{
			prevPlayTime = static_cast<float>(fmod(prevPlayTime, animTotalTime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(PlayerHandle, prevPlayAnim, prevPlayTime);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(PlayerHandle, prevPlayAnim, 1.0f - animBlendRate);
	}
}

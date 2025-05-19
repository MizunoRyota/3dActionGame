#include"DxLib.h"
#include"math.h"
#include"PlayerAnimBase.h"

PlayerAnimBase::PlayerAnimBase()
{
}

PlayerAnimBase::~PlayerAnimBase()
{
}

void PlayerAnimBase::Update(int playerHandle)
{
	State prevState = currentState;

	// アニメーションステートの更新
	UpdateAnimationState(prevState);



	// アニメーション処理
	UpdateAnimation(playerHandle);

}

void PlayerAnimBase::UpdateAnimationState(State prevState)
{

}

void PlayerAnimBase::PlayAnim(AnimKind nextPlayAnim,int playerHandle)
{
	// HACK: 指定した番号のアニメーションをアタッチし、直前に再生していたアニメーションの情報をprevに移行している
// 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
	if (prevPlayAnim != -1)
	{
		MV1DetachAnim(playerHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}

	// 今まで再生中のモーションだったものの情報をPrevに移動する
	prevPlayAnim = currentPlayAnim;
	prevAnimCount = currentAnimCount;

	// 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
	currentPlayAnim = MV1AttachAnim(playerHandle, static_cast<int>(nextPlayAnim));
	currentAnimCount = 0.0f;

	// ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;
}

void PlayerAnimBase::UpdateAnimation( int playerHandle)
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
		animTotalTime = MV1GetAttachAnimTotalTime(playerHandle, currentPlayAnim);

		// 再生時間を進める
		currentAnimCount += PlayAnimSpeed;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (currentAnimCount >= animTotalTime)
		{
			currentAnimCount = static_cast<float>(fmod(currentAnimCount, animTotalTime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(playerHandle, currentPlayAnim, currentAnimCount);

		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(playerHandle, currentPlayAnim, animBlendRate);
}
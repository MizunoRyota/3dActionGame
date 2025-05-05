#include <math.h>
#include"DxLib.h"
#include"PlayerMove.h"
#include"Camera.h"
#include"Input.h"
PlayerMove::PlayerMove()
{
}

PlayerMove::~PlayerMove()
{
}

void PlayerMove::Update()
{
	// パッド入力によって移動パラメータを設定する
	VECTOR	upMoveVec;		// 方向ボタン「↑」を入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	leftMoveVec;	// 方向ボタン「←」を入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	moveVec;		// このフレームの移動ベクトル

	// 移動ベクトルを元にコリジョンを考慮しつつプレイヤーを移動
	Move(moveVec);

}

void PlayerMove::UpdateMoveParameterWithPad(const Input& input, const Camera& camera,VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{

	// 方向ボタン「←」を押したときのプレイヤーの移動ベクトルは上を押したときの方向ベクトルとＹ軸のプラス方向のベクトルに垂直な方向
	leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));

	// 二つのベクトルを正規化( ベクトルの長さを１．０にすること )
	upMoveVec = VNorm(upMoveVec);
	leftMoveVec = VNorm(leftMoveVec);

	// このフレームでの移動ベクトルを初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// 移動したかどうかのフラグを初期状態では「移動していない」を表すFALSEにする
	bool isPressMoveButton = false;

	// パッドの３ボタンと左シフトがどちらも押されていなかったらプレイヤーの移動処理
	if (CheckHitKey(KEY_INPUT_LSHIFT) == 0 && (input.GetNowFrameInput() & PAD_INPUT_C) == 0)
	{
		// 方向ボタン「←」が入力されたらカメラの見ている方向から見て左方向に移動する
		if (input.GetNowFrameInput() & PAD_INPUT_LEFT)
		{
			// 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
			moveVec = VAdd(moveVec, leftMoveVec);

			// 移動したかどうかのフラグを「移動した」にする
			isPressMoveButton = true;
		}
		else
			// 方向ボタン「→」が入力されたらカメラの見ている方向から見て右方向に移動する
			if (input.GetNowFrameInput() & PAD_INPUT_RIGHT)
			{
				// 移動ベクトルに「←」が入力された時の移動ベクトルを反転したものを加算する
				moveVec = VAdd(moveVec, VScale(leftMoveVec, -1.0f));

				// 移動したかどうかのフラグを「移動した」にする
				isPressMoveButton = true;
			}

		// 方向ボタン「↑」が入力されたらカメラの見ている方向に移動する
		if (input.GetNowFrameInput() & PAD_INPUT_UP)
		{
			// 移動ベクトルに「↑」が入力された時の移動ベクトルを加算する
			moveVec = VAdd(moveVec, upMoveVec);

			// 移動したかどうかのフラグを「移動した」にする
			isPressMoveButton = true;
		}
		else
			// 方向ボタン「↓」が入力されたらカメラの方向に移動する
			if (input.GetNowFrameInput() & PAD_INPUT_DOWN)
			{
				// 移動ベクトルに「↑」が入力された時の移動ベクトルを反転したものを加算する
				moveVec = VAdd(moveVec, VScale(upMoveVec, -1.0f));

				// 移動したかどうかのフラグを「移動した」にする
				isPressMoveButton = true;
			}
	}
		// 移動ボタンが押されたかどうかで処理を分岐
		if (isPressMoveButton)
		{

			// 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
			targetMoveDirection = VNorm(moveVec);

			// プレイヤーが向くべき方向ベクトルをプレイヤーのスピード倍したものを移動ベクトルとする
			moveVec = VScale(targetMoveDirection, MoveSpeed);
		}
		else
		{
		}
}


void PlayerMove::Move(const VECTOR& MoveVector)
{
	// HACK: 移動距離が0.01未満で微妙に移動していた場合はじんわり移動してバグる
// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
	if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}

	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(PlayerHandle, position);
}
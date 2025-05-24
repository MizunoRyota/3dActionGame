#pragma once

#include"PlayerMove.h"
#include"PlayerAnimBase.h"

class Stage;

class PlayerBase 
{
public:

	PlayerBase();
	virtual ~PlayerBase();

	virtual void Update(const Input& input, const Camera& camera,Stage& stage) ;					// 更新.
	virtual void Draw() const ;				// 描画.

	// モデルハンドルの取得.
	int GetModelHandle() const { return PlayerHandle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }
	void Setposition(const VECTOR set) { position = set; }

protected:
	static constexpr float Scale = 0.0052f;	//モデルの大きさの倍数

	int PlayerHandle;	//モデルハンドル
	int currentState;	//現在のプレイヤーの状態
	VECTOR position;	// プレイヤーの座標
	PlayerMove* playermove;
	PlayerAnimBase* playeranim;
	// 移動処理
	void Move(const VECTOR& MoveVector,Stage& stage);

};

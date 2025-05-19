#pragma once

#include"PlayerMove.h"
class Stage;

class PlayerBase 
{
public:

	PlayerBase();
	virtual ~PlayerBase();

	virtual void Update(const Input& input, const Camera& camera,Stage& stage) ;					// 更新.
	virtual void Draw() const ;				// 描画.

	// モデルハンドルの取得.
	int GetModelHandle() { return PlayerHandle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }
	void Setposition(const VECTOR set) { position = set; }

protected:
	static constexpr float Scale = 0.0052f;	//モデルの大きさの倍数


	int PlayerHandle;	//モデルハンドル
	VECTOR position;	// プレイヤーの座標
	PlayerMove* playermove;

	// 移動処理
	void Move(const VECTOR& MoveVector,Stage& stage);
};

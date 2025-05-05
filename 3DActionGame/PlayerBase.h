#pragma once

class PlayerBase 
{
public:

	PlayerBase();
	virtual ~PlayerBase();

	virtual void Update() ;					// 更新.
	virtual void Draw();					// 描画.

	// モデルハンドルの取得.
	int GetModelHandle() { return PlayerHandle; }

	// ポジションのgetter/setter.
	const VECTOR& Getposition() const { return position; }
	void Setposition(const VECTOR set) { position = set; }

protected:
	int PlayerHandle;
	VECTOR position;
};

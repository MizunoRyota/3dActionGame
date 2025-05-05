#pragma once

class Skydome
{
public:
	Skydome();
	~Skydome();
	void Update();
	void Draw();
private:
	int SkydomeHandle;		//モデルハンドル
	VECTOR pos;				//ポジション
	// 静的定数.
	static constexpr float Scale = 0.10f;		//大きさ
};

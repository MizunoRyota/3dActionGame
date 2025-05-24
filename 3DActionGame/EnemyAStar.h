#pragma once
class A_Star
{
public:
	A_Star();
	~A_Star();
	void MapInitialize();
	void CalcDistance();
	void Update();
private:
    // マップサイズ（必要に応じて変更）
    static constexpr int MapHeight = 10;		//マップの横軸
    static constexpr int MapWidth = 10;			//マップの縦幅
    //static constexpr int MapDepth = 10;		//マップの奥行

	//map配列
	VECTOR map[MapHeight][MapWidth] = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};

	VECTOR PlayerPos = VGet(0,0,0);		//プレイヤーのポジション
	VECTOR EnemyPos;		//エネミーのポジション
	VECTOR DistancePos;		//プレイヤーとエネミーの距離


};
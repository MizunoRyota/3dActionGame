#pragma once


class A_Star
{
public:

	A_Star();
	~A_Star();
	
	void MapInitialize();

	void CalcDistance();
	
	void Update(VECTOR enemypos);



private:
	static constexpr float Harf = 0.5f;			//ハーフサイズ
    // マップサイズ（必要に応じて変更）
    static constexpr int MapHeight = 11;		//マップの横軸
    static constexpr int MapWidth = 11;			//マップの縦幅
    static constexpr int MapChipSize = 100;		//マップのサイズ
    static constexpr int AllMapChipSize_X = MapHeight * MapChipSize;		//
    static constexpr int AllMapChipSize_Z = MapWidth * MapChipSize;			//
    static constexpr int MapChipSizeOffset = MapChipSize * Harf;			// 個々の座標を中心に設定するためのオフセット
	//map配列
	VECTOR map[MapHeight][MapWidth];

	VECTOR playerPos;					//プレイヤーのポジション
	VECTOR enemyPos;					//エネミーのポジション
	VECTOR distancePos;					//プレイヤーとエネミーの距離

};
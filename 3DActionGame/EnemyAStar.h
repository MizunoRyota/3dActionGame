#pragma once


class A_Star
{
public:

	A_Star();
	~A_Star();
	
	void MapInitialize();

	void CalcDistance();	
	
	void Update(VECTOR enemypos,VECTOR playerpos);

	void CheckCharacter(VECTOR pos);

private:
	static constexpr float Harf = 0.5f;			//ハーフサイズ
    // マップサイズ（必要に応じて変更）
    static constexpr int MapHeight = 11;		//マップの横軸
    static constexpr int MapWidth = 11;			//マップの縦幅
    static constexpr int MapChipSize = 10;		//マップのサイズ
    static constexpr int AllMapChipSize_X = MapHeight * MapChipSize;		//
    static constexpr int AllMapChipSize_Z = MapWidth * MapChipSize;			//
    static constexpr int MapChipSizeOffset = MapChipSize * Harf;			// 個々の座標を中心に設定するためのオフセット
	struct mapchip
	{
		VECTOR position;	//マップチップの中心座標
		bool isplayer;		//プレイヤーがいるかどうか
		bool isenemy;		//エネミーがいるかどうか
	};


	//map配列
	mapchip mapCheck[MapHeight][MapWidth];	//マップのチェック用配列

	VECTOR playerPos;					//プレイヤーのポジション
	VECTOR enemyPos;					//エネミーのポジション
	VECTOR distancePos;					//プレイヤーとエネミーの距離
	VECTOR goalPos;						//ゴールのポジション			//チェック用の距離
	float distance;						//プレイヤーとエネミーの距離



};
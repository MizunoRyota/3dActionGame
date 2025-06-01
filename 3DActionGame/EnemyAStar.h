#pragma once
#include <stdio.h>
#include <memory.h>
#include <utility>
#include<list>



class A_Star
{
private:
	static constexpr float Harf = 0.5f;			//ハーフサイズ
    // マップサイズ（必要に応じて変更）
    static constexpr int MapHeight = 11;		//マップの横軸
    static constexpr int MapWidth = 11;			//マップの縦幅
    static constexpr int MapChipSize = 10;		//マップのサイズ
    static constexpr int AllMapChipSize_X = MapHeight * MapChipSize;		//
    static constexpr int AllMapChipSize_Z = MapWidth * MapChipSize;			//
    static constexpr int MapChipSizeOffset = MapChipSize * Harf;			// 個々の座標を中心に設定するためのオフセット
	static constexpr int MaxDireciton = 4;	//前後左右の4方向

#define X_ELM 0					// 親子ノードのx成分
#define Z_ELM 1					// 親子ノードのz成分

	// 地形の種類
	typedef enum _CHIPTYPE { PLANE, WALL, } CHIPTYPE;
	// ノード状態定数
	typedef enum _STATE { UNCHECKED = 0, IN_OPEN_LIST, IN_CLOSE_LIST } STATE;

	// 地形コスト(地形によるコスト差がない場合は壁以外をすべて1にする)
	unsigned char chip_cost[4] = { 1, 3, 5, 255 };

	//マップチップ構造体の定義
	struct mapchip  
	{
		VECTOR position;	//マップチップの中心座標
		bool isplayer;		//プレイヤーがいるかどうか
		bool isenemy;		//エネミーがいるかどうか
	};

	// ノード構造体の定義
	typedef struct _node {
		short cost;			// 当該ノードまでのコスト
		short score;		// 当該ノード評価値
		char state;			// ノード状態
		char direction;		// 親ノードの方向
	} node;

	struct position {
		int x;
		int z;

		// 代入演算子のオーバーロード
		position& operator=(const position& v) {
			this->x = v.x;
			this->z = v.z;
			return *this;
		}

		// 等価演算子のオーバーロード
		bool operator==(const position& other) const {
			return this->x == other.x && this->z == other.z;
		}

		// 非等価演算子のオーバーロード
		bool operator!=(const position& other) const {
			return this->x != other.x || this->z != other.z;
		}
	};

	int direction_delta[MaxDireciton][2] = {

	{  0,-1 },{ -1, 0 },{ +1, 0 },{ 0, +1 },

	};

	//map配列
	 mapchip mapCheck[MapHeight][MapWidth];	//マップのチェック用配列

	 // マップ
	 char map[MapHeight][MapWidth] = {
		 {0,0,0,3,0,0,0,3,0,0,0},
		 {0,3,0,0,0,0,0,0,0,3,0},
		 {0,0,0,3,0,0,0,3,0,0,0},
		 {3,0,3,0,0,0,0,3,3,0,3},
		 {0,0,0,0,0,0,0,0,0,0,0},
		 {3,0,3,3,0,0,0,3,3,0,3},
		 {3,0,3,3,3,0,3,3,3,0,3},
		 {3,0,3,3,3,0,3,3,3,0,3},
		 {0,0,0,3,0,0,0,3,0,0,0},
		 {0,3,0,0,0,0,0,0,0,3,0},
		 {0,0,0,3,0,0,0,3,0,0,0},
	 };

	VECTOR playerPos;					//プレイヤーのポジション
	VECTOR enemyPos;					//エネミーのポジション
	VECTOR distancePos;					//プレイヤーとエネミーの距離
	float distance;						//プレイヤーとエネミーの距離

	VECTOR enemyLoad;					//エネミーからプレイヤーまでの道のり

public:

	A_Star();
	~A_Star();
	
	void MapInitialize();		//マップの初期化

	void CalcDistance();		//プレイヤーと敵の直線距離を計算
	
	void Update(VECTOR enemypos,VECTOR playerpos);	//メインの更新

	std::pair<int,int> CheckCharaPos(const VECTOR& pos);		//マップチップ内のエネミーの位置特定


	int CheckPlusMinus(int chip);		//マイナスだった場合プラスに変更


	std::list<position> CalcEnemyLoad(position start, position goal);//エネミーのプレイヤーまでの道のり計算

	void Draw();		//デバッグ用の描画

};
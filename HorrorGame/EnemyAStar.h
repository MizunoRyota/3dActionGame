#pragma once
#include <stdio.h>
#include <memory.h>
#include <utility>
#include<list>

class MapChip;

class A_Star
{
private:
	static constexpr float Harf = 0.5f;				//ハーフサイズ
	// マップサイズ（必要に応じて変更）
	static constexpr int MapHeight = 11;			//マップの横軸
	static constexpr int MapWidth = 11;				//マップの縦幅
	static constexpr int nextChip = 1;				//マップの縦幅
	static constexpr float MapChipSize = 10.0f;		//マップのサイズ
	static constexpr int MapChipSizeOffset = MapChipSize * Harf;			//個々の座標を中心に設定するためのオフセット
	static constexpr int MaxDireciton = 4;									//前後左右の4方向

	bool Up;	//マップチップを上に移動するかどうか
	bool Down;	//マップチップを下に移動するかどうか
	bool Right;	//マップチップを右に移動するかどうか
	bool Left;	//マップチップを左に移動するかどうか
	bool isMove;	//マップチップの移動フラグ

#define X_ELM 0					// 親子ノードのx成分
#define Z_ELM 1					// 親子ノードのz成分

	// 地形の種類
	typedef enum _CHIPTYPE { PLANE, GLASS, POND, WALL, } CHIPTYPE;
	// ノード状態定数
	typedef enum _STATE { UNCHECKED = 0, IN_OPEN_LIST, IN_CLOSE_LIST } STATE;

	// 地形コスト(地形によるコスト差がない場合は壁以外をすべて1にする)
	short chip_cost[4] = { 1, 3, 5, 255 };

	//マップチップ構造体の定義
	struct mapchip
	{
		VECTOR position;	//マップチップの中心座標
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
	mapchip AstarMap[MapHeight][MapWidth];	//マップのチェック用配列

	static constexpr float MoveSpeed = 0.08f;	//
	VECTOR playerPos;					//プレイヤーのポジション
	VECTOR enemyPos;					//エネミーのポジション
	VECTOR moveVec;						//エネミーの移動ベクトル
	VECTOR angleVec;					//エネミーの移動ベクトル
	VECTOR TargetVec;					//ターゲットの方向
	VECTOR nextChipPos;					//次のマップチップの位置
	int nextChip_X;		//次のマップチップのX座標
	int nextChip_Z;		//次のマップチップのZ座標
	int currentChip_X;	//現在のマップチップのX座標
	int currentChip_Z;	//現在のマップチップのZ座標
	bool isArrrived;				//到達フラグ
	std::list<position> prevResult;
	position prevGoalPos;		//ゴール位置
public:
	A_Star();
	~A_Star();

	void MapInitialize();		//マップの初期化

	VECTOR Update(const VECTOR& enemypos, const VECTOR& playerpos, const MapChip& mapchip);	//メインの更新

	std::pair<int, int> CheckCharaPos(const VECTOR& pos);		//マップチップ内のエネミーの位置特定

	void CalcMoveDistance(std::list<A_Star::position> result, position start);

	std::list<position> CalcEnemyLoad(position start, position goal, const MapChip& mapchip);	//エネミーのプレイヤーまでの道のり計算

	VECTOR MoveEnemy();		//移動したエネミーのポジションをセット

	void CheckMoveNextPos();	//次に移動するマップチップの位置をチェック
		
	void CheckEmptyList();		//マップチップの道のりのリストが空かどうか確認

	void CheckMoveGoalPos(position prevgoal, position currentgoal);		//プレイヤーが移動したときのゴール位置のチェック
};
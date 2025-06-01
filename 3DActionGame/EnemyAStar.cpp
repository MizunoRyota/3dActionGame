#include"DxLib.h"
#include"EnemyAStar.h"

using namespace std;

A_Star::A_Star()
	: playerPos(VGet(0, 0.0f, 0.0f))
	, enemyPos(VGet(0, 0.0f, 10.0f))
	, distancePos(VGet(0, 0.0f, 0.0f))
	, distance(0.0f)
	, enemyLoad (VGet(0,0,0))
{

}


A_Star::~A_Star()
{

}

void A_Star::CalcDistance()
{
	//プレイヤーの位置からエネミーの位置を計算
	distancePos = VSub(playerPos, enemyPos);
	distance = VSize(distancePos);
}

void A_Star::MapInitialize()
{
	for (int i = 0; i < MapWidth; i++)
	{
		for (int j = 0; j < MapHeight; j++)
		{
			int x_pos = (-AllMapChipSize_X * Harf ) + (j * MapChipSize) + MapChipSizeOffset;
				
			int z_pos = (AllMapChipSize_Z * Harf ) - (i * MapChipSize) - MapChipSizeOffset;

			mapCheck[i][j].position = VECTOR(x_pos, 0, z_pos);
			mapCheck[i][j].isenemy = false;
			mapCheck[i][j].isplayer = false;
		}
	}
}

/// @brief 
/// @param enemypos 
/// @param playerpos 
void A_Star::Update(VECTOR enemypos,VECTOR playerpos)
{
	this->enemyPos = enemypos;
	this->playerPos = playerpos;
	auto start = CheckCharaPos(enemyPos);
	auto goal = CheckCharaPos(playerPos);
	position  startPos = { start.first,start.second };
	position  goalPos = { goal.first,goal.second };

	// startからゴールまでの経路を探索する
	list<position> result = CalcEnemyLoad(startPos, goalPos);


}


std::pair<int,int> A_Star::CheckCharaPos(const VECTOR& pos)
{

	VECTOR checkdistance = VGet(0, 0, 0);					// キャラクターとマップチップの中心との距離
	int isCharaChip_X = 0;									//チェック用の距離VECTOR
	int isCharaChip_Z = 0;									//チェック用の距離VECTOR

	// 各マップチップの位置と引数の位置を比較
	checkdistance = VSub(pos, mapCheck[5][5].position);

	isCharaChip_X= checkdistance.x / 10;
	isCharaChip_Z = checkdistance.z / 10;

	return { isCharaChip_X,isCharaChip_Z };

}

std::list<A_Star::position> A_Star::CalcEnemyLoad(position start, position goal)
{
	clsDx();
	printfDx("playerxpos%f\n", goal.x);
	printfDx("playerzpos%f\n", goal.z);
	printfDx("Enemyxpos%f\n", start.x);
	printfDx("Enemyzpos%f\n", start.z);

	// ノード用メモリの確保
	static node map_node[MapHeight][MapWidth];
	// ノード用ワーク変数
	position current;
	int tmpx, tmpz;					// 隣接座標
	int deltax, deltaz;				// x,y差分
	short cost, score, heuristic;	// 評価値計算用
	list<position> result;
	// nodeデータの初期化
	memset(map_node, 0, sizeof(map_node));
	// オープンリストの作成
	list<position> open_list = { start };
	// とりあえずスタート地点をオープンリストに追加したフラグを立てる
	map_node[start.x][start.z].state = IN_OPEN_LIST;

	while (!open_list.empty()) {

		if (open_list.front() == goal) {
			// ゴールに到達した
			result.push_front(goal);
			// ゴールから親ノードへ順に辿りながらルートを格納する
			// 先頭に挿入することで、反転処理を省略している
			for (current = open_list.front(); current != start; result.push_front(current)) {
				node& current_node = map_node[current.z][current.x];
				current.x -= direction_delta[current_node.direction][X_ELM];
				current.z -= direction_delta[current_node.direction][Z_ELM];
			}
			// ループ脱出
			break;
		}
		// オープンリストの先頭要素を取得する。
		current = open_list.front();
		node& current_node = map_node[current.z][current.x];
		// 未到達なので周囲のセルを検査(iが各方向を表すことに注意する)
		for (int i = 0; i < MaxDireciton; i++) {
			// 隣セル位置を計算
			tmpx = current.x + direction_delta[i][X_ELM];
			tmpz = current.z + direction_delta[i][Z_ELM];
			// 隣セルがマップ外だったらチェックしない
			if (tmpx < 0 || tmpx == MapWidth) {
				continue;
			}
			if (tmpz < 0 || tmpz == MapHeight) {
				continue;
			}
			// 壁だったらチェックしない
			char chip_type = map[tmpz][tmpx];
			if (chip_type == WALL) {
				continue;
			}
			node& next_node = map_node[tmpz][tmpx];
			// オープンリストかクローズリスト入りだったらチェックしない
			if (next_node.state != UNCHECKED) {
				continue;
			}
			// 隣セルのコスト、スコア、ヒューリスティックの計算
			cost = current_node.cost + chip_cost[chip_type];
			deltax = tmpx > goal.x ? tmpx - goal.x : goal.x - tmpx;
			deltaz = tmpz > goal.z ? tmpz - goal.z : goal.z - tmpz;

			// 4方向移動の場合のヒューリスティック
			heuristic = (short)(deltax + deltaz);

			score = cost + heuristic;
			// コスト、スコアを隣セルノードに記入
			next_node.cost = cost;
			next_node.score = score;
			next_node.direction = (char)i;			// 親セルの方向
			// 隣セルノードをオープンリストに追加する
			next_node.state = IN_OPEN_LIST;
			list<position>::iterator iter;
			// オープンリスト内のノードがスコアの昇順になるように新ノードを挿入する
			for (iter = open_list.begin(); iter != open_list.end(); ++iter) {
				if (score <= map_node[iter->z][iter->x].score) {
					open_list.insert(iter, { tmpx, tmpz });
					break;
				}
			}
			// イテレータがリストの終端の「次」に到達したならば、挿入できていない
			// （＝過去最悪のスコア）なので、オープンリストの末尾に新ノードを挿入する
			if (iter == open_list.end()) {
				open_list.push_back({ tmpx, tmpz });
			}
		}
			// 現在位置をクローズする
			current_node.state = IN_CLOSE_LIST;
			open_list.remove(current);
	}
		// コンテナを返す
		return result;
}

//void A_Star::CheckPlayer(static VECTOR& playerpos)
//{
//	VECTOR checkdistance = VGet(0, 0, 0);					// キャラクターとマップチップの中心との距離
//	int isCharaChip_X = 0;									//チェック用の距離VECTOR
//	int isCharaChip_Z = 0;									//チェック用の距離VECTOR
//
//	// 各マップチップの位置と引数の位置を比較
//	checkdistance = VSub(mapCheck[5][5].position, playerpos);
//
//	isCharaChip_X = checkdistance.x / 10;
//	isCharaChip_Z = checkdistance.z / 10;
//	
//	isCharaChip_X = CheckPlusMinus(isCharaChip_X);
//	isCharaChip_Z = CheckPlusMinus(isCharaChip_Z);
//
//	if (mapCheck[isCharaChip_X][isCharaChip_Z].isplayer == false)
//	{
//		mapCheck[isCharaChip_X][isCharaChip_Z].isplayer = true;
//	}
//}

int A_Star::CheckPlusMinus(int chip)
{
	if (chip>=0)
	{
		chip = chip * -1;
	}

	return chip;
}


void A_Star::Draw()
{

	auto start = CheckCharaPos(enemyPos);
	auto goal = CheckCharaPos(playerPos);
	position  startPos = { start.first,start.second };
	position  goalPos = { goal.first,goal.second };

	// startからゴールまでの経路を探索する
	list<position> result = CalcEnemyLoad(startPos, goalPos);
}
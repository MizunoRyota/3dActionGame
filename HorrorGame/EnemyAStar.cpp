#include"iostream"
#include"DxLib.h"
#include"EnemyAStar.h"

using namespace std;

A_Star::A_Star()
	: playerPos(VGet(0, 0.0f, 0.0f))
	, enemyPos(VGet(0, 0.0f, 0.0f))
	,nextChip_X(0)
	,nextChip_Z(0)
{
}

A_Star::~A_Star()
{
}
/// @brief 
///マップチップの初期化
void A_Star::MapInitialize()
{
	for (int i = 0; i < MapWidth; i++)
	{
		for (int j = 0; j < MapHeight; j++)
		{
			float x_pos = (j * MapChipSizeOffset) ;

			float z_pos = (i * MapChipSizeOffset) ;

			mapCheck[i][j].position = VECTOR(x_pos, 0, z_pos);
		}
	}
}

/// @brief 
/// 更新
/// @param enemypos 
/// @param playerpos 
VECTOR A_Star::Update(const VECTOR& enemypos, const VECTOR& playerpos)
{
	this->enemyPos = enemypos;
	this->playerPos = playerpos;
	
	printfDx("playerxpos%f\n", playerPos.x);
	printfDx("Enemyxpos%f\n", enemyPos.x);
	printfDx("Enemyzpos%f\n", enemyPos.z);
	printfDx("UP%d\n", Up);
	printfDx("Down%d\n", Down);
	printfDx("Right%d\n", Right);
	printfDx("Left%d\n", Left);

	auto start = CheckCharaPos(enemyPos);
	auto goal = CheckCharaPos(playerPos);

	position  startPos = { start.first,start.second };
	position  goalPos = { goal.first,goal.second };

	// startからゴールまでの経路を探索する
	list<position> result = CalcEnemyLoad(startPos, goalPos);

	CalcMoveDistance(result,startPos);

	MoveEnemy();

	return enemyPos;

}

/// @brief 
/// キャラクターがマップチップのどの位置にいるか探索
/// @param pos 
/// @return 
std::pair<int,int> A_Star::CheckCharaPos(const VECTOR& pos)
{
	int isCharaChip_X = 0.0f;								//チェック用の距離VECTOR
	int isCharaChip_Z = 0.0f;								//チェック用の距離VECTOR

	float padd_X = 0.0f;
	float padd_Z = 0.0f;
	float madd_X = 0.0f;
	float madd_Z = 0.0f;

	for (int i = 0; i < MapWidth; i++)
	{
		for (int j = 0; j < MapHeight; j++)
		{
			padd_X = (j + 1) * 5.0f;
			padd_Z = (i + 1) * 5.0f;
			madd_X = j* 5.0f;
			madd_Z = i * 5.0f;

			if (padd_X >= pos.x && pos.x >madd_X && padd_Z >= pos.z && pos.z > madd_Z)
			{

				isCharaChip_X = j;
				isCharaChip_Z = i;

				return { isCharaChip_X,isCharaChip_Z };
			}
 		}
	}


	return { isCharaChip_X,isCharaChip_Z };

}

/// @brief 
/// 最短距離の計算
/// @param start 
/// @param goal 
/// @return 
std::list<A_Star::position> A_Star::CalcEnemyLoad(position start, position goal)
{
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

	printfDx("playerxpos%d\n", goal.x);
	printfDx("playerzpos%d\n", goal.z);

	printfDx("Enemyxpos%d\n", start.x);
	printfDx("Enemyzpos%d\n", start.z);
	// 経路が見つかったので、順に結果を表示する
	for (list<position>::iterator p = result.begin(); p != result.end(); p++) {
		printfDx("(%d, %d)", p->x, p->z);
	}

	// コンテナを返す
	return result;
}

/// @brief 
/// 次に移動するマップチップの探索
/// @param result 
/// @param start 
void A_Star::CalcMoveDistance(std::list<A_Star::position> result, position start)
{

	 nextChip_X = start.x;	
	 nextChip_Z = start.z;

	// 次に移動するマスを調べる
	for (list<position>::iterator nextchip = result.begin(); nextchip != result.end(); nextchip++)
	{
		nextChip_X = start.x - nextchip->x;
		nextChip_Z = start.z - nextchip->z;
		if (nextChip_X != 0 && nextChip_Z != 0)
		{
			nextChip_X > 0 ? Right = true : Right = false;
			nextChip_Z > 0 ? Down = true : Down = false;
			nextChip_X < 0 ? Left = true : Left = false;
			nextChip_Z < 0 ? Up = true : Up = false;
		}
		break;
	}
}

void A_Star::MoveEnemy()
{
	if (Up)
	{

	}
}
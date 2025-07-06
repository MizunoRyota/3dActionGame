#include"iostream"
#include"DxLib.h"
#include"EnemyAStar.h"
#include"MapChip.h"

using namespace std;

A_Star::A_Star()
	: playerPos(VGet(0, 0.0f, 0.0f))
	, enemyPos(VGet(0, 0.0f, 0.0f))
	, nextChip_X(0)
	, nextChip_Z(0)
	, isMove(false)
	, Up(false)
	, Down(false)
	, Right(false)
	, Left(false)
	, isArrrived(true)
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
			float z_pos = (i * -MapChipSizeOffset) ;
			float x_pos = (j * MapChipSizeOffset) ;
			AstarMap[i][j].position = VECTOR(x_pos + 2.5f, 0, z_pos - 2.5f);
		}
	}
}

/// @brief 
/// 更新
/// @param enemypos 
/// @param playerpos 
VECTOR A_Star::Update(const VECTOR& enemypos, const VECTOR& playerpos, const MapChip& mapchip)
{
	this->enemyPos = enemypos;
	this->playerPos = playerpos;

	//printfDx("playerxpos%f\n", playerPos.x);
	//printfDx("playerzpos%f\n", playerPos.z);
	//printfDx("Enemyxpos%f\n", enemyPos.x);
	//printfDx("Enemyzpos%f\n", enemyPos.z);
	//printfDx("UP%d\n", Up);
	//printfDx("Down%d\n", Down);
	//printfDx("Right%d\n", Right);
	//printfDx("Left%d\n", Left);
	for (auto& debug : prevResult) {
		printfDx("(%d, %d)", debug.x, debug.z);
	}
	//それぞれのキャラクターの位置を取得
	auto start = CheckCharaPos(enemyPos);
	auto goal = CheckCharaPos(playerPos);

	//printfDx("start%d\n", start.first);
	//printfDx("start%d\n", start.second);
	//printfDx("goal%d\n", goal.first);
	//printfDx("goal%d\n", goal.second);
	if (!isMove) {
		list<position> result;
		position  startChip = { start.first,start.second };
		position  goalChip = { goal.first,goal.second };
		prevGoalPos = goalChip;
		// startからゴールまでの経路を探索する
		if (isArrrived) {
			result = CalcEnemyLoad(startChip, goalChip, mapchip);
			CalcMoveDistance(result, startChip);
		}
		else {
			// すでに移動中なら、経路を再計算しない
			result = prevResult;
			CalcMoveDistance(result, startChip);
		}
		//プレイヤーが移動している場合、ゴール位置を更新
		CheckMoveGoalPos(prevGoalPos, goalChip);
	}
	//敵の移動
	MoveEnemy();
	//敵の移動後の位置を取得
	CheckMoveNextPos();
	//敵がゴールに到達したか確認
	CheckEmptyList();
	return enemyPos;
}

/// @brief 
/// キャラクターがマップチップのどの位置にいるか探索
/// @param pos 
/// @return 
std::pair<int,int> A_Star::CheckCharaPos(const VECTOR& pos)
{
	int currentChip_X = 0.0f;								//チェック用の距離VECTOR
	int currentChip_Z = 0.0f;								//チェック用の距離VECTOR

	float padd_X = 0.0f;
	float padd_Z = 0.0f;
	float madd_X = 0.0f;
	float madd_Z = 0.0f;

	for (int i = 0; i < MapWidth; i++)
	{
		for (int j = 0; j < MapHeight; j++)
		{
			padd_X = (j + 1) * 5.0f;
			padd_Z = (i + 1) * -5.0f;
			madd_X = j * 5.0f;
			madd_Z = i * -5.0f;

			if (padd_X >= pos.x && pos.x > madd_X && padd_Z < pos.z && pos.z <= madd_Z)
			{
				currentChip_X = j;
				currentChip_Z = i;
				return { currentChip_X,currentChip_Z };
			}
		}
	}

	return { currentChip_X,currentChip_Z };
}

/// @brief 
/// 最短距離の計算
/// @param start 
/// @param goal 
/// @return 
std::list<A_Star::position> A_Star::CalcEnemyLoad(position start, position goal, const MapChip& mapchip)
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
			int chip_type = mapchip.GetMapChip(tmpz,tmpx);
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

/// @brief 
/// 次に移動するマップチップの探索
/// @param result 
/// @param start 
void A_Star::CalcMoveDistance(std::list<A_Star::position> result, position start)
{
	if (!isMove)
	{
		nextChip_X = start.x;
		nextChip_Z = start.z;
		currentChip_X = start.x;
		currentChip_Z = start.z;
		// 次に移動するマスを調べる
		for (auto& nextchip : result)
		{
			nextChip_X = nextchip.x - start.x ;
			nextChip_Z = nextchip.z - start.z;
			if (nextChip_X != 0 || nextChip_Z != 0)
			{
				// 次のマスの方向を決める
				Up = nextChip_Z < 0 ? true : false;
				Down = nextChip_Z > 0 ? true : false;
				Right = nextChip_X > 0 ? true : false;
				Left = nextChip_X < 0 ? true : false;
				isMove = true;
				isArrrived = false;	// 到達フラグを初期化
				result.pop_front();
				prevResult = result;
				break;
			}
		}
	}
}

VECTOR A_Star::MoveEnemy()
{
	if (isMove)
	{
		int nextChiopPos_X = 0;
		int nextChiopPos_Z = 0;

		TargetVec = VGet(0, 0, 0);	// ターゲットベクトルの初期化

		if (Up)
		{
			nextChiopPos_X = currentChip_X;
			nextChiopPos_Z = currentChip_Z - nextChip;
			TargetVec = VSub(AstarMap[nextChiopPos_Z][nextChiopPos_X].position, enemyPos);
			nextChipPos = AstarMap[nextChiopPos_Z][nextChiopPos_X].position;
		}
		else if (Down)
		{
			nextChiopPos_X = currentChip_X;
			nextChiopPos_Z = currentChip_Z + nextChip;
			TargetVec = VSub(AstarMap[nextChiopPos_Z][nextChiopPos_X].position, enemyPos);
			nextChipPos = AstarMap[nextChiopPos_Z][nextChiopPos_X].position;
		}
		else if (Right)
		{
			nextChiopPos_X = currentChip_X + nextChip;
			nextChiopPos_Z = currentChip_Z;
			TargetVec = VSub(AstarMap[nextChiopPos_Z][nextChiopPos_X].position, enemyPos);
			nextChipPos = AstarMap[nextChiopPos_Z][nextChiopPos_X].position;
		}
		else if (Left)
		{
			nextChiopPos_X = currentChip_X - nextChip;
			nextChiopPos_Z = currentChip_Z;
			TargetVec = VSub(AstarMap[nextChiopPos_Z][nextChiopPos_X].position, enemyPos);
			nextChipPos = AstarMap[nextChiopPos_Z][nextChiopPos_X].position;
		}

		// プレイヤーに向かって進む方向を単位ベクトルで求める
		VECTOR direction = VNorm(TargetVec);

		// 敵が進む距離（移動速度に基づく）
		moveVec = VScale(direction, MoveSpeed);

		// 敵の位置を更新
		enemyPos = VAdd(enemyPos, moveVec);

		return enemyPos;

	}
}

void A_Star::CheckMoveNextPos()
{
	// x軸かy軸方向に 0.5f 以上移動した場合は「移動した」フラグを１にする
	if (nextChipPos.x - 0.05f <= enemyPos.x && nextChipPos.x + 0.05f >= enemyPos.x && nextChipPos.z + 0.05f >= enemyPos.z && nextChipPos.z - 0.05f <= enemyPos.z)
	{
		isMove = false;
	}
}

void A_Star::CheckEmptyList()
{
	if (prevResult.size() )
	{
		isArrrived = true;
	}
}

void A_Star::CheckMoveGoalPos(position prevgoal, position currentgoal)
{
	if (prevgoal.x - currentgoal.x != 0 || prevgoal.z - currentgoal.z != 0)
	{
		isArrrived = true;
	}
}
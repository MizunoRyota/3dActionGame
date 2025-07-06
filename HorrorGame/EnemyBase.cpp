#include"DxLib.h"
#include"Stage.h"
#include"EnemyBase.h"

EnemyBase::EnemyBase()
	:EnemyHandle(0)
	,position(VGet(30.0f, 0.0f,-23.0f))
	,angleVector(VGet(0,0,0))
	,angle(0)
	,vibeTime(0)
{
	EnemyHandle = MV1LoadModel(_T("data/3dmodel/Enemy/sample.mv1"));
	// 3Dモデルのスケール決定
	MV1SetScale(EnemyHandle, VGet(Scale, Scale, Scale));
	// 3Dモデルの位置決定
	MV1SetPosition(EnemyHandle, position);
	//インスタンス生成
	astar = new A_Star();
	chase = new ChaseEnemy();
	checkrange = new CheckRange();
	enemyanimmanager = new EnemyAnimationManager(EnemyHandle);
}

EnemyBase::~EnemyBase()
{
}
/// @brief 
///初期化
void EnemyBase::Initialize()
{
	//A*のマップ初期化
	astar->MapInitialize();
	//enemyanimmanager->Initialize(EnemyHandle);
}
/// @brief 
/// 更新
/// @param playerpos 
/// @param stage 
void EnemyBase::Update(const VECTOR& playerpos, Stage& stage, const MapChip& mapchip)
{
	if (CheckCameraViewClip(position))
	{
		position = astar->Update(position, playerpos, mapchip);
	}
	VibeTimer(playerpos);

	UpdateAngle(playerpos);
	Move(chase->GetMoveScale(), stage);

}
/// <summary>
/// コントローラーの振動タイマー
/// </summary>
/// <param name="playerpos"></param>
void EnemyBase::VibeTimer(const VECTOR& playerpos)
{
	// 初回の呼び出し時に開始時刻を設定
	if (vibeTime == 0)
	{
		vibeTime = GetNowCount();  // ミリ秒単位で現在時刻を取得
	}
	if (checkrange->CheckWithin(playerpos, position) && GetNowCount() - vibeTime >= WithinVibeLimit)
	{
		// 振動開始
		StartJoypadVibration(DX_INPUT_PAD1, 600, 100, -1);
		vibeTime = 0;
	}
	else
	{
		if (GetNowCount() - vibeTime >= VibeLimit)
		{
			// 振動開始
			StartJoypadVibration(DX_INPUT_PAD1, 400, 100, -1);
			vibeTime = 0;
		}
	}
}

/// @brief 
/// 向く方向計算
/// @param playerpos 
void EnemyBase::UpdateAngle(const VECTOR& playerpos)
{
	// ３Ｄモデル２から３Ｄモデル１に向かうベクトルを算出
	angleVector = VSub(playerpos, position);

	// atan2 を使用して角度を取得
	angle = atan2(angleVector.x, angleVector.z);

	// atan2 で取得した角度に３Ｄモデルを正面に向かせるための補正値( DX_PI_F )を
	// 足した値を３Ｄモデルの Y軸回転値として設定
	MV1SetRotationXYZ(EnemyHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// @brief 
/// ポジションをセット
/// @param MoveVector 
/// @param stage 
void EnemyBase::Move(const VECTOR& MoveVector, Stage& stage)
{
	// 当たり判定をして、新しい座標を保存する
	//position = stage.CheckEnemyCollision(*this, MoveVector);
	MV1SetPosition(EnemyHandle, position);
}

/// @brief 
/// 表示関数
/// @param playerpos 
void EnemyBase::Draw(const VECTOR& playerpos)
{
	MV1DrawModel(EnemyHandle);
	checkrange->DebugDraw(playerpos,position);
}
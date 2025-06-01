#include"DxLib.h"
#include"EnemyBase.h"

EnemyBase::EnemyBase()
	:EnemyHandle(0)
	,position(VGet(-30.0f,0.0f,40.0f))
{
	EnemyHandle = MV1LoadModel(_T("data/3dmodel/Enemy/siren.mv1"));
	// 3Dモデルのスケール決定
	MV1SetScale(EnemyHandle, VGet(Scale, Scale, Scale));
	// 3Dモデルの位置決定
	MV1SetPosition(EnemyHandle, position);
	//インスタンス生成
	astar = new A_Star();

}

EnemyBase::~EnemyBase()
{
}
void EnemyBase::Initialize()
{
	//A*のマップ初期化
	astar->MapInitialize();
}
void EnemyBase::Update(VECTOR playerpos)
{

	astar->Update(position,playerpos);


}

void EnemyBase::Move()
{

	MV1SetPosition(EnemyHandle, position);
}

void EnemyBase::Draw()
{
	MV1DrawModel(EnemyHandle);
	astar->Draw();		// A*のデバッグ用描画
}
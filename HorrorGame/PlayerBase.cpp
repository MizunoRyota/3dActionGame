#include"DxLib.h"
#include"Stage.h"
#include"PlayerBase.h"

PlayerBase::PlayerBase()
	:position(VGet(26.0f,0.0f,-26.0f))
{
	PlayerHandle = MV1LoadModel(_T("data/3dmodel/Player/Player.mv1"));
	// 3Dモデルのスケール決定
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
	MV1SetPosition(PlayerHandle, position);
	playermove = new PlayerMove();
	playeranim = new PlayerAnimBase(PlayerHandle);
}

PlayerBase::~PlayerBase()
{
}

void PlayerBase::Initialize()
{
	
}
void PlayerBase::Update(const Input& input, const Camera& camera, Stage& stage)
{
	playermove->Update(input,camera);

	playeranim->Update();

	Move(playermove->GetMoveScale(), stage);
}

void PlayerBase::Move(const VECTOR& MoveVector, Stage& stage)
{
	//プレイヤーの座標変更
	position = VAdd(position, playermove->GetMoveScale());
	// 当たり判定をして、新しい座標を保存する
	//position = stage.CheckCollision(*this, MoveVector);
	//プレイヤーの回転
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, playermove->GetMoceAngle() + DX_PI_F, 0.0f));
	//プレイヤーのモデルの設置
	MV1SetPosition(PlayerHandle, position);
}

void PlayerBase::Draw() const
{
	MV1DrawModel(PlayerHandle);
}
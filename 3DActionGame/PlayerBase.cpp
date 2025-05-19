#include"DxLib.h"
#include"Stage.h"
#include"PlayerBase.h"
PlayerBase::PlayerBase()
	:position(VGet(0,0.0f,5.0f))
{
	PlayerHandle = MV1LoadModel("data/3dmodel/Player/Player.mv1");
	// 3Dモデルのスケール決定
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
	MV1SetPosition(PlayerHandle, position);
	playermove = new PlayerMove();
}

PlayerBase::~PlayerBase()
{
}

void PlayerBase::Update(const Input& input, const Camera& camera, Stage& stage)
{

	playermove->Update(input,camera);

	position = VAdd(position, playermove->GetMoveScale());

	Move(playermove->GetMoveScale(), stage);

}

void PlayerBase::Move(const VECTOR& MoveVector, Stage& stage)
{

	// 当たり判定をして、新しい座標を保存する
	position = stage.CheckCollision(*this, MoveVector);

	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, playermove->GetMoceAngle() + DX_PI_F, 0.0f));
	MV1SetPosition(PlayerHandle, position);
}

void PlayerBase::Draw() const
{
	MV1DrawModel(PlayerHandle);
}
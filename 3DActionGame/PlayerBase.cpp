#include"DxLib.h"
#include"PlayerBase.h"
PlayerBase::PlayerBase()
	:position(VGet(0,0,0))
{
	PlayerHandle = MV1LoadModel("data/3dmodel/Player/Player.mv1");
	MV1SetPosition(PlayerHandle, position);
}

PlayerBase::~PlayerBase()
{
}

void PlayerBase::Update()
{

}

void PlayerBase::Draw()
{
}
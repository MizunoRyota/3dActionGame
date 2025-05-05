#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"PlayerDraw.h"

PlayerDraw::PlayerDraw()
{
}

PlayerDraw::~PlayerDraw()
{
}

void PlayerDraw::Draw()
{
	MV1DrawModel(PlayerHandle);
}
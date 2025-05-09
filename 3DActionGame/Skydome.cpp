#include"DxLib.h"
#include"Skydome.h"

Skydome::Skydome()
	:pos(VGet(0,0,0))
	,SkydomeHandle(0)
{
	SkydomeHandle = MV1LoadModel("data/3dmodel/skydome/Night/Dome_Y901.pmx");
	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(SkydomeHandle, pos);
	// 3Dモデルのスケール決定
	MV1SetScale(SkydomeHandle, VGet(Scale, Scale, Scale));
}

Skydome::~Skydome()
{
	MV1DeleteModel(SkydomeHandle);
}

void Skydome::Update()
{
	//スカイドームを回転させる
	pos.y -= 0.0003;
	MV1SetRotationXYZ(SkydomeHandle, VGet(0.0f, pos.y, 0.0f));
}

void Skydome::Draw()
{
	MV1DrawModel(SkydomeHandle);
}
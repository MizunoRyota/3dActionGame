#include"DxLib.h"
#include"Fragment.h"
#include"MapChip.h"

Fragment::Fragment()
{
	for (int i = 0; i < FragmentNum; i++)
	{
		FragmentHandle[i] = 0; // 初期化
	}
	FragmentHandle[0] = MV1LoadModel(_T("data/3dmodel/Objects/Crystal.mv1"));
	// 3Dモデルのスケール決定
	MV1SetScale(FragmentHandle[0], VGet(Scale, Scale, Scale));
	for (int i = 1; i < FragmentNum; i++)
	{
		FragmentHandle[i] = MV1DuplicateModel(FragmentHandle[0]);
		// 3Dモデルのスケール決定
		MV1SetScale(FragmentHandle[i], VGet(Scale, Scale, Scale));
	}
}
Fragment::~Fragment()
{
}

void Fragment::InitializeFragment(MapChip& mapchip)
{
	int fragmentNum = 0;
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			// フラグメントだったら設置
			int chip_type = mapchip.GetMapChip(i, j);
			if (chip_type == FRAGMENT) {
				setFragmetChip[i][j].position = mapchip.GetMapChipPosition(i, j);
				setFragmetChip[i][j].position.y = Floating;
				MV1SetPosition(FragmentHandle[fragmentNum], setFragmetChip[i][j].position);
				fragmentNum++;
			}
		}
	}
}

void Fragment::Update()
{
	RotateFragment();
}

void Fragment::DecreaceFragment()
{
	
}

void Fragment::RotateFragment()
{
	angle += 1.0f; // フラグメントの回転速度

	for (int i = 0; i < FragmentNum; i++)
	{
		// フラグメントの回転
		MV1SetRotationXYZ(FragmentHandle[i], VGet(0.0f,  angle * DX_PI_F / 180.0f, 0.0f));
		if (angle ==360)
		{
			angle = 0;
		}
	}
}

void Fragment::Draw()
{
	for (int i = 0; i < FragmentNum; i++)
	{
		MV1DrawModel(FragmentHandle[i]);
	}
}
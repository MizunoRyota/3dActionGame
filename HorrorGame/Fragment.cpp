#include"DxLib.h"
#include"Fragment.h"

Fragment::Fragment()
	:FragmentHandle(0)
{
	FragmentHandle[0] = MV1LoadModel("data/3dmodel/Objects/Crystal.mv1");
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

void Fragment::InitializeFragment()
{

	int fragmentNum = 0;

	for (int i = 0; i < MapWidth; i++)
	{
		for (int j = 0; j < MapHeight; j++)
		{
			float x_pos = (j * MapChipSizeOffset);
			float z_pos = (i * MapChipSizeOffset);

			setFragmetChip[i][j].position = VECTOR(x_pos, 0, z_pos);
			
			// フラグメントだったら設置
			char chip_type = map[j][i];

			if (chip_type == FRAGMENT) {
				MV1SetPosition(FragmentHandle[fragmentNum], setFragmetChip[i][j].position);
				fragmentNum++;
			}
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
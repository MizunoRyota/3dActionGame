#include"Dxlib.h"
#include"ObjectBase.h"
#include"MapChip.h"
ObjectBase::ObjectBase()
	:decreaceFragment(0)
{
	fragment = new Fragment();
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Initialize(MapChip& mapchip)
{
	int fragmentNum = 0;
	fragment->InitializeFragment(mapchip);
	for (int i = 0; i < MapWidth; i++)
	{
		for (int j = 0; j < MapHeight; j++)
		{
			// フラグメントだったら設置
			char chip_type = mapchip.GetMapChip(i, j);
			if (chip_type == FRAGMENT) {
				fragmentPosition[fragmentNum] = fragment->GetFragmentPosition(i,j);
				fragmentNum++;
			}
		}
	}
}

void ObjectBase::Update()
{
	fragment->Update();
}

void ObjectBase::Draw()
{
	fragment->Draw();
}
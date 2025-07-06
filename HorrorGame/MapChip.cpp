#include"Dxlib.h"
#include"MapChip.h"

MapChip::MapChip()
{
}
MapChip::~MapChip()
{
}

void MapChip::InitializeMap()
{

	std::fstream file("MapChip.csv");
	
	std::string line;
	while (std::getline(file , line))
	{
		std::vector<mapchip> row;

		for (char c:line)
		{

			if (c != ',')
			{
				mapchip mc{};
				mc.chipNum = int(c - '0');
				mc.position.x = (mapchipdata.size() * MapChipSizeOffset) + 2.5f;
				mc.position.z = static_cast<float>(row.size()) * -MapChipSizeOffset - 2.5f;
				row.push_back(mc);
			}
		}
		mapchipdata.push_back(row);

	}

	//for (int i = 0; i < MapWidth; i++)
	//{
	//	for (int j = 0; j < MapHeight; j++)
	//	{
	//		float x_pos = (j * MapChipSizeOffset);
	//		float z_pos = (i * -MapChipSizeOffset);
	//		mapChip[i][j].position = VECTOR(x_pos + 2.5f, Floating, z_pos - 2.5f);
	//		continue;
	//	}
	//}
}
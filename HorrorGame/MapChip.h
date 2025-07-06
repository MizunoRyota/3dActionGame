#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

class MapChip
{
private:
	//map配列
	static constexpr float Harf = 0.5f;				//ハーフサイズ
	static constexpr float Floating = 0.75f;		//ハーフサイズ
	// マップサイズ（必要に応じて変更）
	static constexpr float MapChipSize = 10.0f;		//マップのサイズ
	static constexpr int MapChipSizeOffset = MapChipSize * Harf;	//個々の座標を中心に設定するためのオフセット

	//マップチップ構造体の定義
	struct mapchip
	{
		VECTOR position;	//マップチップの中心座標
		int chipNum;
	};
	std::vector<std::vector<mapchip>> mapchipdata;	//マップチップデータ

public:
	MapChip();
	~MapChip();
	void InitializeMap();

	const VECTOR GetMapChipPosition(int z, int x) const { return mapchipdata[z][x].position; }
	const int& GetMapChip(int z, int x) const { return mapchipdata[z][x].chipNum; }
};
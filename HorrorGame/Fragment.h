#pragma once
#include"MapChip.h"

class Fragment
{

private:
	static constexpr int FragmentNum = 50;			// フラグメントのサイズ
	static constexpr float Harf = 0.5f;				//ハーフサイズ
	static constexpr float Floating = 0.75f;				//ハーフサイズ

	// マップサイズ（必要に応じて変更）
	static constexpr int MapHeight = 11;			//マップの横軸
	static constexpr int MapWidth = 11;				//マップの縦幅
	static constexpr float MapChipSize = 10.0f;		//マップのサイズ
	static constexpr int MapChipSizeOffset = MapChipSize * Harf;			// 個々の座標を中心に設定するためのオフセット
	static constexpr float Scale = 0.001f;			//モデルの大きさの倍数

	//マップチップ構造体の定義
	struct mapchip
	{
		VECTOR position;	//マップチップの中心座標
	};

	//map配列
	mapchip setFragmetChip[30][30];	//マップのチェック用配列

	int FragmentHandle[FragmentNum];
	float angle = 0.0f;		//フラグメントの角度
	// 地形の種類
	typedef enum _CHIPTYPE { PLANE, GLASS, POND, FRAGMENT, } CHIPTYPE;
public:
	Fragment();
	~Fragment();

	void InitializeFragment(MapChip& mapchip);
	void Update();
	void RotateFragment();
	void DecreaceFragment();
	void Draw();

	const VECTOR& GetFragmentPosition(int z,int x) const { return setFragmetChip[z][x].position; }
};

#pragma once
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
	static constexpr int AllMapChipSize_X = MapHeight * MapChipSize;		//
	static constexpr int AllMapChipSize_Z = MapWidth * MapChipSize;			//
	static constexpr int MapChipSizeOffset = MapChipSize * Harf;			// 個々の座標を中心に設定するためのオフセット
	static constexpr float Scale = 0.001f;			//モデルの大きさの倍数

	int FragmentHandle[FragmentNum];
	float angle = 0.0f;		//フラグメントの角度

	// 地形の種類
	typedef enum _CHIPTYPE { PLANE, GLASS, POND, FRAGMENT, } CHIPTYPE;

	// マップ
	char map[MapHeight][MapWidth] = {
		// 0,1,2,3,4,5,6,7,8,9,10
		  {3,3,3,3,3,3,3,3,3,3,3},//0
		  {3,0,0,0,0,0,0,0,0,0,0},//1
		  {3,0,0,0,0,0,0,0,0,0,0},//2
		  {3,0,0,0,0,0,0,0,0,0,0},//3
		  {3,0,0,0,3,3,3,0,0,0,0},//4
		  {3,0,0,0,3,0,3,0,0,0,0},//5
		  {3,0,0,0,3,0,3,0,0,0,0},//6
		  {3,0,0,0,0,0,0,0,0,0,0},//7
		  {3,0,0,0,0,0,0,0,0,0,0},//8
		  {3,0,0,0,0,0,0,0,0,0,0},//9
		  {3,3,3,3,3,0,3,3,3,3,3},//10
	};

	//マップチップ構造体の定義
	struct mapchip
	{
		VECTOR position;	//マップチップの中心座標
	};

	//map配列
	mapchip setFragmetChip[MapHeight][MapWidth];	//マップのチェック用配列

public:
	Fragment();
	~Fragment();

	void InitializeFragment();
	void Update();
	void RotateFragment();
	void Draw();
};


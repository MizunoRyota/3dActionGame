#pragma once
#include"Fragment.h"

class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();
	void Initialize(MapChip&mapchip);
	void Update(); 

	void Draw();
	const VECTOR& GetFragmentPosition(int fragnum) const { return fragmentPosition[fragnum]; }

private:
	static constexpr int FragmentNum = 50;			// フラグメントのサイズ
	static constexpr int MapHeight = 11;			//マップの横軸
	static constexpr int MapWidth = 11;				//マップの縦幅

	// 地形の種類
	typedef enum _CHIPTYPE { PLANE, GLASS, POND, FRAGMENT, } CHIPTYPE;
	Fragment* fragment;
	VECTOR fragmentPosition[FragmentNum]; // フラグメントの位置
	bool decreaceFragment;
};
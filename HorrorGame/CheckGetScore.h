#pragma once
class MapChip;

class CheckGetScore
{
public:
	CheckGetScore();
	~CheckGetScore();

	bool Update(const VECTOR& playerpos, const VECTOR& fragmentpos, MapChip& mapchip);
	bool CheckGetFraguments(const VECTOR& playerpos, const VECTOR& fragmentpos,MapChip& mapchip);
	void DebugDraw(const VECTOR& playerpos, const VECTOR& fragmentpos);

private:
	static constexpr  float PlayerHight = 0.8f;		//プレイヤーの高さ
	static constexpr  float playerRadius = 0.5f;		//プレイヤーの当たり判定の半径
	static constexpr  float FragmentRadius = 1.5f;		//Enemyの当たり判定の半径

	//bool isChaseWithin;			//追跡距離判定
	float lengthRange;				//円と円の距離
	float distance;					//距離
	VECTOR keepDistance;			//保持する距離
	bool isGetFragment;
};
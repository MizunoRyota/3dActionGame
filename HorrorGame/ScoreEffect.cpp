#include"Dxlib.h"
#include"EffekseerForDXLib.h"
#include"ScoreEffect.h"

ScoreEffect::ScoreEffect()
	:time(0)
{

}
ScoreEffect::~ScoreEffect()
{
}

void ScoreEffect::Update(VECTOR effectposition)
{
	if (!isPlay)
	{
		// エフェクトを再生する
		isPlay = true;
		isEnd = false;
		position = effectposition;
	}
	else
	{
		time++;
		if (time > 60) // 60フレーム経過したらエフェクトを終了
		{
			isEnd = true;
			isPlay = false;
			time = 0; // 時間をリセット
		}
	}
}


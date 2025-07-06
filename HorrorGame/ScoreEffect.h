#pragma once

class ScoreEffect
{
public:
	ScoreEffect();
	~ScoreEffect();
	void Update(VECTOR effectposition);

private:
	int ScoreEffectHandle;	// エフェクトリソースを読み込む。
	int time;				// 時間を初期化する(定期的にエフェクトを再生するため)
	bool isPlay;			// エフェクトが再生中かどうかを示すフラグ
	bool isEnd;				// エフェクトが終了したかどうかを示すフラグ
	VECTOR position;		//	エフェクトの位置
};

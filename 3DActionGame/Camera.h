#pragma once

class Input;

/// <summary>
/// カメラ
/// </summary>
class Camera
{
public:
	Camera();			// コンストラクタ.
	~Camera();			// デストラクタ.
	void Load();		//初期化
	void Update();
	void FixCameraPosition();
	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }
	const VECTOR& GetTarget()	const { return targetPosition; }

private:
	static constexpr float Zoom = 3.0f;
	static constexpr float TargetHight = 1.3;		//ターゲットの見る高さ
	static constexpr float AngleSpeed = 0.15f;		//向きが変わるスピード
	float            angleVertical;					// カメラの垂直角度
	float            angleHorizontal;				// カメラの水平角度

	float shakeTime;			//揺れ時間
	bool isDamage;				//ダメージを受けているか
	bool isShake;				//揺れているか
	Input* rightInput;			//右スティック情報
	VECTOR Offset;				//
	VECTOR OriginalOffset;		//
	VECTOR AngleVec;			//向きベクトル
	VECTOR	position;			// ポジション.
	VECTOR targetPosition;		//　カメラが注視するポジション
};
#include"EffekseerForDXLib.h"
#include"Camera.h"
#include"Skydome.h"
#include"Stage.h"
#include"Input.h"
#include"PlayerBase.h"
#include"PlayerMove.h"
#include"EnemyBase.h"
#include"EnemyAStar.h"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 画面モードのセット
	SetGraphMode(1920, 1080, 32);
	ChangeWindowMode(FALSE);

	// DXライブラリを初期化する。
	if (DxLib_Init() == -1) return -1;

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// DirectX9を使用するようにする。(DirectX11も可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面を描画対象にする
	SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
	SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みを行う
	SetUseBackCulling(TRUE);		// バックカリングを行う

	// フォグを有効にする
	SetFogEnable(TRUE);

	// フォグの色を暗い色にする
	SetFogColor(0.0f, 10.0f, 10.0f);
	// フォグの開始距離を０、終了距離を15にする
	SetFogStartEnd(0.0f, 25.0f);


	//std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	//std::shared_ptr<PlayerManager> player = std::make_shared<PlayerManager>();
	//std::shared_ptr<Skydome> skydome = std::make_shared<Skydome>();
	Camera* camera = new Camera();
	Skydome* skydome = new Skydome();
	Stage* stage = new Stage();
	Input* input = new Input();
	// プレイヤーを生成
	PlayerBase* player = new PlayerBase();
	EnemyBase* enemy = new EnemyBase();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		auto prevTime = GetNowHiPerformanceCount();	// 処理が始まる前の時間

		skydome->Update();
		input->Update();
		enemy->Update();
		player->Update(*input,*camera,*stage);
		camera->Update(player->GetPosition());
		// 障害物制御

		// 画面を初期化する
		ClearDrawScreen();
		skydome->Draw();
		stage->Draw();
		player->Draw();
		enemy->Draw();



		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
		// 差を求めて、1回の画面更新が1/60秒になるようにwhileループ回して待つ
		auto afterTime = GetNowHiPerformanceCount(); // 処理が終わった後の時間
		while (afterTime - prevTime < 16667)
		{
			afterTime = GetNowHiPerformanceCount();
		}
	}

	// Effekseerを終了する。
	Effkseer_End();
	// 後始末
	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}
#include"EffekseerForDXLib.h"
#include"Camera.h"
#include"Skydome.h"
#include"PlayerManager.h"
#include"EnemyManager.h"
enum STATE
{
	STATE_LOAD,			//ロード.
	STATE_INIT,			//初期化.
	STATE_TITLE,		//タイトル.
	STATE_READY,        //準備
	STATE_TUTORIAL,     //準備
	STATE_LESSON,		//ゲームが始まるまでのカウント
	STATE_GAME,			//ゲーム中.
	STATE_READYGAMEOVER,//やられている状態
	STATE_READYCLEAR,	//クリア状態
	STATE_GAMEOVER,		//ゲームオーバー.
	STATE_CLEAR,		//ゲームクリア.
};
const int HITCHECK_NUM = 2;
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

	//// DXライブラリのデバイスロストした時のコールバックを設定する。
	//// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	//// ただし、DirectX11を使用する場合は実行する必要はない。
	//Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面を描画対象にする
	SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
	SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みを行う
	SetUseBackCulling(TRUE);		// バックカリングを行う

	//std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	//std::shared_ptr<PlayerManager> player = std::make_shared<PlayerManager>();
	//std::shared_ptr<Skydome> skydome = std::make_shared<Skydome>();
	Camera* camera = new Camera();
	Skydome* skydome = new Skydome();
	PlayerManager* player = new PlayerManager();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		auto prevTime = GetNowHiPerformanceCount();	// 処理が始まる前の時間



		





		camera->Update();
		skydome->Update();

		// 画面を初期化する
		ClearDrawScreen();
		skydome->Draw();
		player->Draw();









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
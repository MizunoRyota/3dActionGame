#pragma once


class GameSceneBase
{
public:
	GameSceneBase();
	virtual ~GameSceneBase();

	//シーンごとの初期化処理
	virtual void Initialize() abstract;	// 初期化

	//シーンごとの更新処理
	virtual void Update() abstract;		// 更新

	//シーンごとの描画処理
	virtual void Draw()  abstract;		// 描画

private:

};


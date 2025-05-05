#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"PlayerManager.h"
#include"PlayerBase.h"
#include"PlayerDraw.h"
#include"PlayerMove.h"

PlayerManager::PlayerManager()
	:PlayerHandle (-1)
{
	for (int i = 0; i < StatusNum; i++)
	{
		player[i] = NULL;
	}
}

PlayerManager::~PlayerManager()
{

}

void PlayerManager::Initialize()
{
	player[0] = new PlayerBase();
	player[1] = new PlayerDraw();
	player[2] = new PlayerMove();
}

void PlayerManager::Update()
{
	for (int  i = 0; i < StatusNum; i++)
	{
		player[i]->Update();
	}
}

void PlayerManager::Draw()
{
	for (int i = 0; i < StatusNum; i++)
	{
		player[i]->Draw();
	}
}
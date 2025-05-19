#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"PlayerManager.h"
#include"PlayerBase.h"
#include"PlayerMove.h"

PlayerManager::PlayerManager()
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

}

void PlayerManager::Update()
{


}

void PlayerManager::Draw()
{
	//for (int i = 0; i < StatusNum; i++)
	//{
	//	if (player[i] != nullptr) {
	//		player[i]->Draw();
	//	}
	//}
}
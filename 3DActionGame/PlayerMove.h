#pragma once

#include"PlayerBase.h"

class Camera;
class Input;

class PlayerMove : public PlayerBase
{
public:
	PlayerMove();
	~PlayerMove();
	void Update();
	void UpdateMoveParameterWithPad(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	void Move(const VECTOR& MoveVector);
private:
	VECTOR dir;
	static constexpr float	MoveSpeed = 30.0f;	// 移動速度
	VECTOR		targetMoveDirection;	// モデルが向くべき方向のベクトル
	bool		isMove;					// そのフレームで動いたかどうか
};
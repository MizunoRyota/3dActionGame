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
	static constexpr float	MoveSpeed = 30.0f;	// �ړ����x
	VECTOR		targetMoveDirection;	// ���f���������ׂ������̃x�N�g��
	bool		isMove;					// ���̃t���[���œ��������ǂ���
};
#pragma once

class Input;

/// <summary>
/// �J����
/// </summary>
class Camera
{
public:
	Camera();			// �R���X�g���N�^.
	~Camera();			// �f�X�g���N�^.
	void Load();		//������
	void Update();
	void FixCameraPosition();
	// �|�W�V������getter/setter.
	const VECTOR& GetPosition() const { return position; }
	const VECTOR& GetTarget()	const { return targetPosition; }

private:
	static constexpr float Zoom = 3.0f;
	static constexpr float TargetHight = 1.3;		//�^�[�Q�b�g�̌��鍂��
	static constexpr float AngleSpeed = 0.15f;		//�������ς��X�s�[�h
	float            angleVertical;					// �J�����̐����p�x
	float            angleHorizontal;				// �J�����̐����p�x

	float shakeTime;			//�h�ꎞ��
	bool isDamage;				//�_���[�W���󂯂Ă��邩
	bool isShake;				//�h��Ă��邩
	Input* rightInput;			//�E�X�e�B�b�N���
	VECTOR Offset;				//
	VECTOR OriginalOffset;		//
	VECTOR AngleVec;			//�����x�N�g��
	VECTOR	position;			// �|�W�V����.
	VECTOR targetPosition;		//�@�J��������������|�W�V����
};
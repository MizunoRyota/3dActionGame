#include"DxLib.h"
#include"Input.h"
#include"Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
    :OriginalOffset(VGet(0, 0, 0))
    , position(VGet(0, 0, 0))
    ,targetPosition(VGet(0,0,0))
    , AngleVec(VGet(0, 0, 0))
    , isShake(false)
    , isDamage(true)
    , shakeTime(0)
{

    //�����p�x��0�x
    angleVertical = 0.0f;

    //���s0.1�`400�܂ł��J�����̕`��͈͂Ƃ���
    SetCameraNearFar(0.1f, 400.0f);

    // �J�����Ɉʒu�𔽉f.
    SetCameraPositionAndTarget_UpVecY(position, targetPosition);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
    // �����Ȃ�.
}

void Camera::Update()
{
    // �u���v�{�^����������Ă����琅���p�x���}�C�i�X����
    if (rightInput->IsInputAnalogKey(Input::AnalogLeft))
    {
        angleHorizontal += AngleSpeed;

        // �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
        if (angleHorizontal > DX_PI_F)
        {
            angleHorizontal -= DX_TWO_PI_F;
        }
    }

    // �u���v�{�^����������Ă����琅���p�x���v���X����
    if (rightInput->IsInputAnalogKey(Input::AnalogRight))
    {
        angleHorizontal -= AngleSpeed;

        // �P�W�O�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
        if (angleHorizontal < -DX_PI_F)
        {
            angleHorizontal += DX_TWO_PI_F;
        }
    }

    // �u���v�{�^����������Ă����琂���p�x���}�C�i�X����
    if (rightInput->IsInputAnalogKey(Input::AnalogUp))
    {
        angleVertical += AngleSpeed;

        //// ������p�x�ȉ��ɂ͂Ȃ�Ȃ��悤�ɂ���
        if (angleVertical > DX_PI_F * 0.5f - 0.6f)
        {
            angleVertical = DX_PI_F * 0.5f - 0.6f;
        }
    }

    // �u���v�{�^����������Ă����琂���p�x���v���X����
    if (rightInput->IsInputAnalogKey(Input::AnalogDown))
    {
        angleVertical -= AngleSpeed;

        //// ������p�x�ȏ�ɂ͂Ȃ�Ȃ��悤�ɂ���
        if (angleVertical < -DX_PI_F * 0.5f + 0.6f)
        {
            angleVertical = -DX_PI_F * 0.5f + 0.6f;
        }
    }
    // �u���v�{�^����������Ă����琅���p�x���}�C�i�X����
    if (rightInput->IsInputAnalogKey(Input::AnalogLeft))
    {
        angleHorizontal += AngleSpeed;

        // �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
        if (angleHorizontal > DX_PI_F)
        {
            angleHorizontal -= DX_TWO_PI_F;
        }
    }

    // �u���v�{�^����������Ă����琅���p�x���v���X����
    if (rightInput->IsInputAnalogKey(Input::AnalogRight))
    {
        angleHorizontal -= AngleSpeed;

        // �P�W�O�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
        if (angleHorizontal < -DX_PI_F)
        {
            angleHorizontal += DX_TWO_PI_F;
        }
    }

    // �u���v�{�^����������Ă����琂���p�x���}�C�i�X����
    if (rightInput->IsInputAnalogKey(Input::AnalogUp))
    {
        angleVertical += AngleSpeed;

        //// ������p�x�ȉ��ɂ͂Ȃ�Ȃ��悤�ɂ���
        if (angleVertical > DX_PI_F * 0.5f - 0.6f)
        {
            angleVertical = DX_PI_F * 0.5f - 0.6f;
        }
    }

    // �u���v�{�^����������Ă����琂���p�x���v���X����
    if (rightInput->IsInputAnalogKey(Input::AnalogDown))
    {
        angleVertical -= AngleSpeed;

        //// ������p�x�ȏ�ɂ͂Ȃ�Ȃ��悤�ɂ���
        if (angleVertical < -DX_PI_F * 0.5f + 0.6f)
        {
            angleVertical = -DX_PI_F * 0.5f + 0.6f;
        }
    }

    targetPosition = VGet(0,0,10.0f);

    // �J�����Ɉʒu�𔽉f.
    SetCameraPositionAndTarget_UpVecY(position, targetPosition);
}

void Camera::FixCameraPosition()
{
    // ���������̉�]�͂x����]
    auto rotY = MGetRotY(angleHorizontal);

    // ���������̉�]�͂y����] )
    auto rotZ = MGetRotZ(angleVertical);

    // �J��������v���C���[�܂ł̏����������Z�b�g
    float cameraPlayerLength = Zoom;

    // �J�����̍��W���Z�o
    // �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
    // ����������]( �y����] )���������Ɛ���������]( �x����] )���čX��
    // �����_�̍��W�𑫂������̂��J�����̍��W
    position = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ), rotY), targetPosition);

    if (position.y<=0)
    {
        position.y = 0.50f;
    }
}
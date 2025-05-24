#include"DxLib.h"
#include"Input.h"
#include"Camera.h"

/// <summary>
/// コンストラクタ
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

    //垂直角度は0度
    angleVertical = 0.0f;

    //奥行0.1～400までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 400.0f);

    // カメラに位置を反映.
    SetCameraPositionAndTarget_UpVecY(position, targetPosition);

}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
    // 処理なし.
}

void Camera::Update(VECTOR playerPos)
{
    //ぼたんおしたら
    clsDx();
    printfDx(_T("xpos%f\n", position.x));
    printfDx(_T("ypos%f\n", position.y));
    printfDx(_T("zpos%f\n", position.z));
    printfDx(_T("xpos%f\n", targetPosition.x));
    printfDx(_T("ypos%f\n", targetPosition.y));
    printfDx(_T("zpos%f\n", targetPosition.z));

    // 「←」ボタンが押されていたら水平角度をマイナスする
    if (rightInput->IsInputAnalogKey(Input::AnalogLeft))
    {
        angleHorizontal += AngleSpeed;

        // －１８０度以下になったら角度値が大きくなりすぎないように３６０度を足す
        if (angleHorizontal > DX_PI_F)
        {
            angleHorizontal -= DX_TWO_PI_F;
        }
    }

    // 「→」ボタンが押されていたら水平角度をプラスする
    if (rightInput->IsInputAnalogKey(Input::AnalogRight))
    {
        angleHorizontal -= AngleSpeed;

        // １８０度以上になったら角度値が大きくなりすぎないように３６０度を引く
        if (angleHorizontal < -DX_PI_F)
        {
            angleHorizontal += DX_TWO_PI_F;
        }
    }

    // 「↑」ボタンが押されていたら垂直角度をマイナスする
    if (rightInput->IsInputAnalogKey(Input::AnalogUp))
    {
        angleVertical += AngleSpeed;

        //// ある一定角度以下にはならないようにする
        if (angleVertical > DX_PI_F * 0.5f - 0.6f)
        {
            angleVertical = DX_PI_F * 0.5f - 0.6f;
        }
    }

    // 「↓」ボタンが押されていたら垂直角度をプラスする
    if (rightInput->IsInputAnalogKey(Input::AnalogDown))
    {
        angleVertical -= AngleSpeed;

        //// ある一定角度以上にはならないようにする
        if (angleVertical < -DX_PI_F * 0.5f + 0.6f)
        {
            angleVertical = -DX_PI_F * 0.5f + 0.6f;
        }
    }

    FixCameraPosition();

    // カメラの注視点はプレイヤー座標から規定値分高い座標
    targetPosition = VAdd(playerPos, VGet(0.0f, CameraPlayerTargetHeight, 0.0f));

    // カメラに位置を反映.
    SetCameraPositionAndTarget_UpVecY(position, targetPosition);
}

void Camera::FixCameraPosition()
{

    //// カメラの座標を算出
    //// Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
    //// 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
    //// 注視点の座標を足したものがカメラの座標
    //position = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ), rotY), targetPosition);
        // 水平方向の回転はＹ軸回転
    auto rotationY = MGetRotY(angleHorizontal);

    // 垂直方向の回転はＺ軸回転 )
    auto rotationX = MGetRotX(angleVertical);

    position = VAdd(VTransform(VTransform(VGet(0.0f, 0.0f, ToPlayerLength + shakeOffset), rotationX), rotationY), targetPosition);

    if (position.y<=0)
    {
        position.y = 0.50f;
    }
}
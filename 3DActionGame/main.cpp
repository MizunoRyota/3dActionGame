#include"EffekseerForDXLib.h"
#include"Camera.h"
#include"Skydome.h"
#include"PlayerManager.h"
#include"EnemyManager.h"
enum STATE
{
	STATE_LOAD,			//���[�h.
	STATE_INIT,			//������.
	STATE_TITLE,		//�^�C�g��.
	STATE_READY,        //����
	STATE_TUTORIAL,     //����
	STATE_LESSON,		//�Q�[�����n�܂�܂ł̃J�E���g
	STATE_GAME,			//�Q�[����.
	STATE_READYGAMEOVER,//����Ă�����
	STATE_READYCLEAR,	//�N���A���
	STATE_GAMEOVER,		//�Q�[���I�[�o�[.
	STATE_CLEAR,		//�Q�[���N���A.
};
const int HITCHECK_NUM = 2;
/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(1920, 1080, 32);
	ChangeWindowMode(FALSE);

	// DX���C�u����������������B
	if (DxLib_Init() == -1) return -1;

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effkseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// DirectX9���g�p����悤�ɂ���B(DirectX11����)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	//// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	//// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	//// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	//Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	SetDrawScreen(DX_SCREEN_BACK);	// ����ʂ�`��Ώۂɂ���
	SetUseZBufferFlag(TRUE);		// �y�o�b�t�@���g�p����
	SetWriteZBufferFlag(TRUE);		// �y�o�b�t�@�ւ̏������݂��s��
	SetUseBackCulling(TRUE);		// �o�b�N�J�����O���s��

	//std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	//std::shared_ptr<PlayerManager> player = std::make_shared<PlayerManager>();
	//std::shared_ptr<Skydome> skydome = std::make_shared<Skydome>();
	Camera* camera = new Camera();
	Skydome* skydome = new Skydome();
	PlayerManager* player = new PlayerManager();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		auto prevTime = GetNowHiPerformanceCount();	// �������n�܂�O�̎���



		





		camera->Update();
		skydome->Update();

		// ��ʂ�����������
		ClearDrawScreen();
		skydome->Draw();
		player->Draw();









		// �������߂āA1��̉�ʍX�V��1/60�b�ɂȂ�悤��while���[�v�񂵂đ҂�
		auto afterTime = GetNowHiPerformanceCount(); // �������I�������̎���
		while (afterTime - prevTime < 16667)
		{
			afterTime = GetNowHiPerformanceCount();
		}
	}

	// Effekseer���I������B
	Effkseer_End();
	// ��n��
	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}
#pragma once

#include "Audio.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene {

  public: // �����o�֐�
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

  private: // �����o�ϐ�
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0;
	// �X�v���C�g
	Sprite* sprite_ = nullptr;
	// 3D���f��
	Model* model_ = nullptr;
	// ���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	// �r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	// �T�E���h�f�[�^�n���h��
	uint32_t soundDataHandle_ = 0;
	// �����Đ��n���h��
	uint32_t voiceHandle_ = 0;
	// �l��\���������ϐ�
	int32_t value_ = 0;

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
};
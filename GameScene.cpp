#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	// �t�@�C�������w�肵�ăe�N�X�`����ǂݍ���
	textureHandle_ = TextureManager::Load("mario.jpg");
	// �X�v���C�g�̕`�搶��
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	// 3D���f���̐���
	model_ = Model::Create();
	for (size_t i = 0; i < _countof(worldTransform_); i++) {
		// X,Y,Z�����̃X�P�[�����O��ݒ�
		worldTransform_[i].scale_ = {5.0f, 5.0f, 5.0f};
		// X,Y,Z������̉�]�p��ݒ�
		worldTransform_[i].rotation_ = {0, 0, 0};
		// X,Y,Z������̕��s��ݒ�
		if (i < 9.0f) {
			worldTransform_[i].translation_ = {-40.0f + i * 10.0f, 20.0f, 0};
		} else{
			worldTransform_[i].translation_ = {-40.0f + (i - 9) * 10.0f, -20.0f, 0};
		}
		// ���[���h�g�����X�t�H�[���̏�����
		worldTransform_[i].Initialize();
	}
	//�J�������_���W��ݒ�
	viewProjection_.eye = {0, 0, -50};
	//�J���������_���W��ݒ�
	viewProjection_.target = {0, 0, 0};
	//�J����������x�N�g����ݒ�
	viewProjection_.up = {0.0f, 1.0f, 0.0f};
	// �r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();
	//// �T�E���h�f�[�^�̓ǂݍ���
	//soundDataHandle_ = audio_->LoadWave("se_sad03.wav");
	// �����Đ�
	//audio_->PlayWave(soundDataHandle_);
	//voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
}

void GameScene::Update() {
	//���_�ړ�����
	{
		//���_�̈ړ��x�N�g��
		XMFLOAT3 move = {0, 0, 0};

		//���_�̈ړ�����
		const float kEyeSpeed = 0.2f;

		//�����������ňړ��x�N�g����ύX
		if (input_->PushKey(DIK_W)) {
			move = {0, 0, kEyeSpeed};
		} else if (input_->PushKey(DIK_S)) {
			move = {0, 0, -kEyeSpeed};
		}

		//���_�ړ�(�x�N�g���̉��Z)
		viewProjection_.eye.x += move.x;
		viewProjection_.eye.y += move.y;
		viewProjection_.eye.z += move.z;

		//�s��̍Čv�Z
		viewProjection_.UpdateMatrix();

		////�f�o�b�O�p�\��
		//debugText_->SetPos(50, 50);
		//debugText_->Printf(
		//  "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	}

	//�����_�ړ�����
	{
		//�����_�̈ړ��x�N�g��
		XMFLOAT3 move = {0, 0, 0};

		//�����_�̈ړ�����
		const float kTargetSpeed = 0.2f;

		//�����������ňړ��x�N�g����ύX
		if (input_->PushKey(DIK_LEFT)) {
			move = {-kTargetSpeed, 0, 0};
		} else if (input_->PushKey(DIK_RIGHT)) {
			move = {kTargetSpeed, 0, 0};
		}

		//���_�ړ�(�x�N�g���̉��Z)
		viewProjection_.target.x += move.x;
		viewProjection_.target.y += move.y;
		viewProjection_.target.z += move.z;

		//�s��̍Čv�Z
		viewProjection_.UpdateMatrix();

		////�f�o�b�O�p�\��
		//debugText_->SetPos(50, 70);
		//debugText_->Printf(
		//  "target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
		//  viewProjection_.target.z);
	}
	////�X�v���C�g�̍��̍��W���擾
	//XMFLOAT2 position = sprite_->GetPosition();
	////���W��{2,0}�ړ�
	//position.x += 2.0f;
	//position.y += 1.0f;
	//// �ړ��������W���X�v���C�ɔ��f
	//sprite_->SetPosition(position);
	//// �X�y�[�X�L�[���������u��
	//if (input_->TriggerKey(DIK_SPACE)) {
	//	// ������~
	//	audio_->StopWave(voiceHandle_);
	//}
	//// �����w��t���\��
	//debugText_->SetPos(50, 50);
	//debugText_->Printf(
	//  "translation:%f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	//  worldTransform_.translation_.z);
	//debugText_->SetPos(50, 70);
	//debugText_->Printf(
	//  "rotation:%f,%f,%f", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	//  worldTransform_.rotation_.z);
	//debugText_->SetPos(50, 90);
	//debugText_->Printf(
	//  "scale:%f,%f,%f", worldTransform_.scale_.x, worldTransform_.scale_.y,
	//  worldTransform_.scale_.z);
}

void GameScene::Draw() {

	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Model::PreDraw(commandList);

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>
	for (size_t i = 0; i < _countof(worldTransform_); i++) {
		model_->Draw(worldTransform_[i], viewProjection_, textureHandle_);
	}

	// 3D�I�u�W�F�N�g�`��㏈��
	Model::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>
	//sprite_->Draw();

	// �f�o�b�O�e�L�X�g�̕`��
	debugText_->DrawAll(commandList);
	//
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

#pragma endregion
}
#include "PlayScene.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"MeshCollider.h"
#include"TouchableObject.h"
#include"CollisionManager.h"
#include"SphereCollider.h"
#include"Player.h"
//�V�[���̃R���X�g���N�^
PlayScene::PlayScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region ������
void PlayScene::Initialize(DirectXCommon* dxCommon)
{	
	Sprite::LoadTexture(0, L"Resources/back.jpeg");
	BackSprite = Sprite::Create(0, { 0,0 }, { 1,1,1,1});
	BackSprite->SetSize({ window_width,window_height});
	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

	playermodel = Model::CreateFromOBJ("chr_sword");
	//�v���C���[
	player = Player::Create(playermodel, dxcomn, camera);
	player->Initialize(dxCommon, camera);
}
#pragma endregion

#pragma region �X�V����
void PlayScene::Update(DirectXCommon* dxCommon)
{
	
	Input::MouseMove mouseMove = Input::GetInstance()->GetMouseMove();
	//�}�E�X�̓��͏�Ԏ擾
	if (Input::GetInstance()->Pushkey(DIK_F)) {
		
	}
	player->Update({ 1,1,1,1 }, dxCommon, camera);
	
	camera->SetEye({ Player_Pos.x,Player_Pos.y ,Player_Pos.z - 100 });
	camera->SetTarget({ Player_Pos.x,Player_Pos.y ,Player_Pos.z });//�����_

	camera->Update();
	BackSprite->SpriteUpdate(camera->GetViewMatrix(), camera->GetProjectionMatrix(), { 1,1,1,1 });
	//collisionManager->CheckAllCollisions();
	//�V�[���`�F���W
	if (Input::GetInstance()->TriggerKey(DIK_R)) {//�����ꂽ��
		BaseScene* scene = new TitleScene(sceneManager_);//���̃V�[���̃C���X�^���X����
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
	}
}
#pragma endregion 

//���ɓ���
#pragma region �`��(imgui�ƃX�v���C�g�ƃ��f���܂Ƃ߂�����)
void PlayScene::Draw(DirectXCommon* dxcomn)
{
	dxcomn->BeginDraw();
	//�v���C���[
	Sprite::PreDraw(dxcomn->GetCmdList());
	BackSprite->Draw();
	Sprite::PostDraw(dxcomn->GetCmdList());
	dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
		
	
	player->PreDraw();
	player->Draw();
	player->PostDraw();
	ImGuiDraw();
	dxcomn->EndDraw();
}
#pragma endregion

void PlayScene::ImGuiDraw()
{
	{
		ImGui::Begin("Player");
		ImGui::SetWindowPos(ImVec2(0, 500));
		ImGui::SetWindowSize(ImVec2(500, 300));
		float j = player->GetPosition().x;
		float o = player->GetPosition().y;
		float p = player->GetPosition().z;
		if (ImGui::TreeNode("Position")) {
			ImGui::SliderFloat("x", &j, -50, 50);
			ImGui::SliderFloat("y", &o, -50, 50);
			ImGui::SliderFloat("z", &p, -50, 50);
			player->SetPosition({ j,o,p });
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Move")) {
			if (ImGui::RadioButton("moveX", &player)) {
				player->SetFall_X(true);
			}
			if (ImGui::RadioButton("moveY", &player)) {
				player->SetFall_Y(true);
			}
			ImGui::TreePop();
		}
		ImGui::End();
	}
}
#pragma region �������
void PlayScene::Finalize()
{
	delete player;
}
#pragma endregion
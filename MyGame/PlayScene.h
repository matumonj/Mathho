#pragma once
#include"BaseScene.h"
#include"Audio.h"
#include"Sprite.h"
#include"Input.h"
#include"WinApp.h"

#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"DebugTxt.h"
#include"LightGroup.h"
#include"DebugCamera.h"
#include"DirectXCommon.h"
#include"Texture.h"
#include"PostEffect.h"
#include"Enemy.h"
#include"TargetMarker.h"
#include"GameUI.h"
#include"OBBCollision.h"

#pragma comment(lib,"winmm.lib")
class TouchableObject;
class CollisionManager;
class Player;
class PlayScene :public BaseScene
{
public:
	//�V�[���̃R���X�g���N�^
	PlayScene(SceneManager* sceneManager);
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	const float window_width = 1900;
	const float window_height = 1020;
	static const int debugTextTexNumber = 0;

private:
	XMFLOAT3 CameraPosition;
	DirectXCommon* dxcomn;
	Player* player = nullptr;
	Sprite* BackSprite;
	Model* playermodel = nullptr;
	DebugCamera* camera;
private:


private:
	XMFLOAT3 Player_Pos;// = player->GetPosition();
	XMFLOAT3 Player_Rot;// = player->GetRotation();

private://�_����
	
public:
	
public:
	void Initialize(DirectXCommon* dxCommon)override;
	void Update(DirectXCommon* dxCommon)override;
	void Draw(DirectXCommon* dxcomn)override;
	void ImGuiDraw();
	void Finalize()override;

	CollisionManager* collisionManager = nullptr;
};


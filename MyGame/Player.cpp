#include "Player.h"
#include"Input.h"
#include"DebugTxt.h"
#include"SphereCollider.h"
#include"TargetMarker.h"

#define PI 3.145265
using namespace DirectX;
Player* Player::Create(Model* model, DirectXCommon* dxcomn, DebugCamera* camera)
{
	Player* instance = new Player();	//インスタンスを生成

	if (instance == nullptr) {
		return nullptr;
	}

	//初期化
	instance->Initialize(dxcomn, camera);//	delete instance;
	//	assert(0);

	if (model) {
		instance->SetModel(model);
	}
	return instance;
}

bool Player::Initialize(DirectXCommon* dxcomn, DebugCamera* camera)
{
	if (!Object3d::Initialize(dxcomn, camera))
	{
		return false;
	}
	position = { 0,20,0 };
	//aaaaaaa
	// コライダーの追加
	//character
	//CollisionFieldSet();
	Fallflag = State::None;
	return true;
}
void Player::Update(XMFLOAT4 color, DirectXCommon* dxcomn, DebugCamera* camera)
{
	scale = { 3,3,3 };
	//移動ベクトルをy軸周りの角度で回転
	XMVECTOR move = { 0,0,0.1f,0 };
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	move = XMVector3TransformNormal(move, matRot);

	//向いてる方向に移動
	const float Speed = 1.0f;
	if (Input::GetInstance()->Pushkey(DIK_D)) {
		position.x += Speed;
	} else if (Input::GetInstance()->Pushkey(DIK_A)) {
		position.x -= Speed;
	} else if (Input::GetInstance()->Pushkey(DIK_W)) {
		position.y += Speed;
	} else if (Input::GetInstance()->Pushkey(DIK_S)) {
		position.y -= Speed;
	}

	switch (Fallflag)
	{
	case State::None:
		position = { 0,20,0 };
		vy = 0;
		vx = 0;
		break;

	case State::Move_X:
		vx += xmove;
		if (position.x >100) {
			Fallflag = State::None;
		}
		break;

	case State::Move_Y:
		vy += grav;
		if (position.y < -100) {
			Fallflag = State::None;
		}
		break;
	}

	position.x += vx * 2.5f;
	position.y += vy * 2.5f;
	// 行列の更新など
	Object3d::Update({ 1,1,1,1 }, dxcomn, camera);

}



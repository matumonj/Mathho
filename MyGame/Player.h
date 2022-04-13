#pragma once

#include"Character.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include"DirectXCommon.h"
class Enemy;
class TargetMarker;
class Player:public Object3d //:public Character
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	static Player* Create(Model* model, DirectXCommon* dxcomn, DebugCamera* camera);
public:
	bool Initialize(DirectXCommon* dxcomn, DebugCamera* camera)override;

	void Update(XMFLOAT4 color, DirectXCommon* dxcomn, DebugCamera* camera)override;
private:
	enum class State {
		None,
		Move_Y,
		Move_X,
	};
	State Fallflag;
	float vy = 0.0f,vx=0.0f;
	const float grav = -0.5f / 60.0f;
	const float xmove=0.5f / 60.0f;
public:
	State GetState() { return Fallflag; }
	void SetFall_Y(bool flag) { Fallflag = State::Move_Y; }
	void SetFall_X(bool flag) { Fallflag = State::Move_X; }
	
private:
	Input* input = Input::GetInstance();
};


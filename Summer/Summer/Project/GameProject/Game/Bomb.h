#pragma once
#include"../Base/Base.h"
class Bomb :public Base {
public:
	CImage m_img;
public:
	Bomb(const CVector2D& pos);
	void Update();
	void Draw();
};
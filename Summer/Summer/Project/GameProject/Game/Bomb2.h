#pragma once
#include"../Base/Base.h"
class Bomb2 :public Base {
public:
	CImage m_img;
	bool m_flip;
public:
	Bomb2( const CVector2D& pos);
	void Update();
	void Draw();
};
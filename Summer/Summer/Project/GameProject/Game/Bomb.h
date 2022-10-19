#pragma once
#include"../Base/Base.h"
class Bomb :public Base {
public:
	CImage m_img;
	bool m_flip;
	int m_time;
	int m_attack_no;
public:
	Bomb(bool flip,const CVector2D& pos);
	void Update();
	void Draw();
};
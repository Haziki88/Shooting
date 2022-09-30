#pragma once
#include"../Base/Base.h"

class Bullet :public Base {
	CImage m_img;
	int m_speed;
public:
	Bullet(int type,const CVector2D& pos);
	~Bullet();
	void Update();
	void Draw();
	void Collision(Base* b);
};
#pragma once
#include"../Base/Base.h"

class Bullet :public Base {
	CImage m_img;
	int m_speed;
	bool m_flip;
public:
	Bullet(int type,bool flip,const CVector2D& pos,float speed);
	~Bullet();
	void Update();
	void Draw();
	void Collision(Base* b);
};
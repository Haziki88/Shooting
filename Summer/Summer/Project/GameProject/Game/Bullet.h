#pragma once
#include"../Base/Base.h"

class Bullet :public Base {
	CImage m_img;
	int m_speed;
	bool m_flip;
	int m_attack_no;
public:
	Bullet(int type,bool flip,const CVector2D& pos,float speed,int attack_no);
	~Bullet();
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
};
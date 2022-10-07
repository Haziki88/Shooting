#pragma once
#include"../Base/Base.h"

class Explosion :public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;
	//���]�t���O
	bool m_flip;
	//�U���ԍ�
	int m_attack_no;
public:
	Explosion(const CVector2D& pos, bool flip, int type);
	void Update();
	void Draw();
	int GetAttackNo() {
		return m_attack_no;
	}
};
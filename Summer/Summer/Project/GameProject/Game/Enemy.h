#pragma once
#include "../Base/Base.h"

class Enemy : public Base {
private:
	//���
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
		eState_Wait,
	};
	//��ԕϐ�
	int m_state;
	int m_cnt;
	int m_hp = 100;
	CImage m_img;
	bool	m_flip;
	//���n�t���O
	bool	m_is_ground;
	//�U���ԍ�
	int m_attack_no;
	//�_���[�W�ԍ�
	int m_damage_no;
	

	//�e��Ԃł̋���

	void StateWait();
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDown();

public:
	Enemy(const CVector2D& p, bool flip);
	~Enemy();
	void Update();
	void Draw();
	void Collision(Base* b);
	int gethp() {
		Base* Enemy = Base::FindObject(eType_Enemy);
		if (Enemy) {
			return m_hp;
		}
	}
	int GetAttackNo() {
		Base* Enemy = Base::FindObject(eType_Enemy);
		if (Enemy) {
			return m_attack_no;
		}
	}
};

#include "Bullet.h"
#include"Map.h"

Bullet::Bullet(int type,bool flip,const CVector2D& pos,float speed,int attack_no)
	:Base(type)
{
	if (type == eType_Player_Bullet) {
		m_img = COPY_RESOURCE("Bullet", CImage);
	}
	else {
		m_img = COPY_RESOURCE("Bullet2", CImage);
	}
	m_pos = pos;
	m_img.SetCenter(16, 16);
	m_speed = speed;
	m_flip = flip;
	m_rect = CRect(-8, -8, 8, 8);
	m_attack_no = attack_no;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (m_flip) {
		m_pos.x-=m_speed;
	}
	else {
		m_pos.x += m_speed;
	}
	
}

void Bullet::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}

void Bullet::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(m_pos,m_rect);
			if (t != 0)
				SetKill();
		}
		break;
	case eType_Player:
		if (m_type == eType_Enemy_Bullet && Base::CollisionRect(this, b)) {
			SetKill();
			b->SetKill();
		}
		break;
	case eType_Enemy:
		if (m_type == eType_Player_Bullet && Base::CollisionRect(this,b)) {
			SetKill();
		}
		break;
	}
}

#include "Bullet.h"
#include"Map.h"

Bullet::Bullet(int type,const CVector2D& pos, float ang, float speed)
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
	m_ang = ang;
	m_speed = speed;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_vec = CVector2D(sin(m_ang), cos(m_ang)) * m_speed;
	m_pos += m_vec;
}

void Bullet::Draw()
{
	m_img.SetPos(m_pos);
	m_img.SetAng(m_ang);
	m_img.Draw();
}

void Bullet::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(m_pos);
			if (t != 0)
				SetKill();
		}
		break;
	case eType_Player:
		if (m_type == eType_Enemy_Bullet && Base::CollisionCircle(this, b)) {
			SetKill();
			b->SetKill();
		}
		break;
	case eType_Enemy:
		if (m_type == eType_Player_Bullet && Base::CollisionCircle(this,b)) {
			SetKill();
			b->SetKill();
		}
		break;
	}
}

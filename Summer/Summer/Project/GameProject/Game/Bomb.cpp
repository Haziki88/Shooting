#include "Bomb.h"
#include"Explosion.h"
#include"Map.h"

Bomb::Bomb(bool flip,const CVector2D& pos):Base(eType_Bomb)
{
	m_img = COPY_RESOURCE("Bomb", CImage);
	m_pos = pos;
	m_img.SetSize(30, 30);
	m_img.SetCenter(15, 15);
	m_rect = CRect(-8, -8, 8, 8);
	m_flip = flip;
	m_attack_no = rand();
	
}

void Bomb::Update()
{
	m_time++;
	Base* map = Base::FindObject(eType_Field);
	//if(m_img.GetIndex()==4){
	if (Map* m = dynamic_cast<Map*>(map)) {
		int t = m->CollisionMap(m_pos, m_rect);
		if (m_flip) {
			m_pos.x -= 3;
			if (m_time >= 30|| t != 0) {
				SetKill();
				m_time = 0;
				Base::Add(new Explosion(m_pos + CVector2D(-64, -40), m_flip, eType_Player_Attack,m_attack_no));
			}
		}
		else {
			m_pos.x += 3;
			if (m_time >= 30|| t != 0) {
				SetKill();
				m_time = 0;
				Base::Add(new Explosion(m_pos + CVector2D(64, -40), m_flip, eType_Player_Attack,m_attack_no));
			}
		}
	//}	
	}
}

void Bomb::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	//DrawRect();
}

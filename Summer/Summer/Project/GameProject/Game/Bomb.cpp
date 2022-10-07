#include "Bomb.h"

Bomb::Bomb(bool flip,const CVector2D& pos):Base(eType_Bomb)
{
	m_img = COPY_RESOURCE("Bomb", CImage);
	m_pos = pos;
	m_img.SetSize(30, 30);
	m_img.SetCenter(15, 15);
	m_rect = CRect(-8, -8, 8, 8);
	m_flip = flip;
	
}

void Bomb::Update()
{
	m_time++;
	if (m_flip) {
		m_pos.x -= 3;
		if (m_time >= 30) {
			SetKill();
			m_time = 0;
		}
	}
	else {
		m_pos.x += 3;
		if (m_time >= 30) {
			SetKill();
			m_time = 0;
		}
	}
	
}

void Bomb::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	//DrawRect();
}

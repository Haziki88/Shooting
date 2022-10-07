#include "Bomb.h"

Bomb::Bomb(bool flip,const CVector2D& pos):Base(eType_Bomb)
{
	m_img = COPY_RESOURCE("Bomb", CImage);
	m_pos = pos;
	m_img.SetSize(30, 30);
	m_img.SetCenter(15, 15);
	m_rect = CRect(-8, -8, 8, 8);
}

void Bomb::Update()
{
}

void Bomb::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}

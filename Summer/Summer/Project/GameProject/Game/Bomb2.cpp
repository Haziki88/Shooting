#include "Bomb2.h"

Bomb2::Bomb2(const CVector2D& pos):Base(eType_Bomb)
{
	m_img = COPY_RESOURCE("Bomb", CImage);
	m_pos = pos;
	m_img.SetSize(30, 30);
	m_img.SetCenter(15, 15);
	m_rect = CRect(-8, -8, 8, 8);
}

void Bomb2::Update()
{
}

void Bomb2::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
}

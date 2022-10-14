#include "Item.h"

Item::Item(int type,const CVector2D& pos):Base(type)
{
	if (type == eType_Item) {
		m_img = COPY_RESOURCE("Item", CImage);
	}
	else {

	}
	
	m_pos = pos;
	m_img.SetSize(24, 24);
	m_img.SetCenter(12, 12);
	m_rect = CRect(-8, -8, 8, 8);
}

void Item::Update()
{
}

void Item::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}

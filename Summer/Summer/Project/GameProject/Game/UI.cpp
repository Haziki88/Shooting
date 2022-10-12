#include "UI.h"
#include"Player.h"

UI::UI()
	:Base(eType_UI)
{
	m_img. Load("Image/ui x2.png");
}

void UI::Draw()
{
	Base* player = Base::FindObject(eType_Player);
	Player* p = dynamic_cast<Player*>(player);
	//for (int i = 10; i > 0; hp/=10 ) {
		int h =64* p->gethp()/100;
		m_img.SetRect(64 * 0, 32, 64 * 0 + h, 64);
		m_img.SetSize(h, 32);
		m_img.SetPos(0, 0);
		m_img.Draw();
	//}
}

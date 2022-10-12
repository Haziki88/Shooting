#include "UI.h"
#include"Player.h"

UI::UI()
	:Base(eType_UI)
{
	m_img. Load("Image/ui x2.png");
}

void UI::Draw()
{
	//for (int i = 10; i > 0; hp/=10 ) {
		//int h = hp % 10;
		m_img.SetRect(64 * 10, 0, 64 * 10 + 64, 64);
		m_img.SetSize(64, 64);
		m_img.SetPos(0, 0);
		m_img.Draw();
	//}
}

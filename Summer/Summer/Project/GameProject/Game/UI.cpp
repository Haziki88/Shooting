#include "UI.h"

UI::UI()
	:Base(eType_UI)
{
	m_img. Load("Image/ui x2.png");
}

void UI::Draw()
{
	/*for (int i = 10; i > 0; i--) {
		
	}*/
	m_img.SetRect(0,-32,64,64);
	m_img.SetSize(64, 64);
	m_img.SetPos(100,50);
	m_img.Draw();
}

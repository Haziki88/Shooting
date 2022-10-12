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
	m_img.SetRect(0,32,32,32+31);
	m_img.SetSize(64, 63);
	m_img.SetPos(0,0);
	m_img.Draw();
}

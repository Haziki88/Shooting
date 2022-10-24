#include "Gameover.h"

Gameover::Gameover() :Base(eType_Scene),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	m_img = COPY_RESOURCE("Gameover", CImage);
	m_img.SetPos(1280, 720);
}

Gameover::~Gameover()
{
}

void Gameover::Update()
{
	//ボタン１でゲームオーバー破棄
	if (PUSH(CInput::eButton1)) {
		m_kill = true;
	}
}

void Gameover::Draw()
{
	m_img.Draw();
	m_title_text.Draw(64, 900, 0, 0, 0, "Push Z");
}

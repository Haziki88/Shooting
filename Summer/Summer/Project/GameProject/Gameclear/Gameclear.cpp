#include "Gameclear.h"

Gameclear::Gameclear():Base(eType_Scene2),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	m_img = COPY_RESOURCE("towerED",CImage);
	m_img.SetPos(1280, 720);
}

Gameclear::~Gameclear()
{
}

void Gameclear::Update()
{
	//ボタン１でゲームオーバー破棄
	if (PUSH(CInput::eButton1)) {
		m_kill = true;
	}
}

void Gameclear::Draw()
{
	m_img.Draw();
	m_title_text.Draw(64, 900, 0, 0, 0, "Push Z");
}

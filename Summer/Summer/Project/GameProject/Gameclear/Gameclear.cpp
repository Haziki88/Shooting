#include "Gameclear.h"

Gameclear::Gameclear():Base(eType_Scene2)
{

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
}

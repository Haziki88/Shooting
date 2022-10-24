#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "../Title/Title.h"
#include"../Gameover/Gameover.h"
#include"../Gameclear/Gameclear.h"
#include"Map.h"

Game::Game() :Base(eType_Scene)
{
	
		//Base::Add(new Field());
		//SOUND("BGM_maoudamasii")->Play(true);
	
}

Game::~Game()
{
	//全てのオブジェクトを破棄
	Base::KillAll();
	//タイトルシーンへ
	Base::Add(new Title());


	if (!Base::FindObject(eType_Player) ) {
		Base::Add(new Gameover());
		m_kill = true;
	}
}

void Game::Update()
{

	//ゴールが無ければゲームシーン終了
	//if (!Base::FindObject(eType_Goal)) {
	//	SetKill();
	//}

	//プレイヤー死亡　ボタン１でゲームシーン終了
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		m_kill = true;
	}
}


#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "../Title/Title.h"
#include"../Gameover/Gameover.h"
#include"../Gameclear/Gameclear.h"
#include"Map.h"
#include"UI.h"
int stage = 1;

Game::Game() :Base(eType_Scene)
{
	Base::Add(new UI());
	Base::Add(new Map(1));
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
	Base* enemy = Base::FindObject(eType_Enemy);
	if (enemy == nullptr ) {
		Base* field = Base::FindObject(eType_Field);
		Base* player = Base::FindObject(eType_Player);
		Base* enemy = Base::FindObject(eType_Enemy);
		field->SetKill();
		player->SetKill();
		stage++;
		if (stage >= 3) {
			//ゲームクリアに移行
			//全てのオブジェクトを破棄
			Base::KillAll();

			//Base::Add(new Gameclear());
		}
		else
		{
			Base::Add(new Map(stage));
		}
	}
	//プレイヤー死亡　ボタン１でゲームシーン終了
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		m_kill = true;
	}
}


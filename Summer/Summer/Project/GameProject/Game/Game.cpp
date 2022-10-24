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
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	Base::Add(new Title());


	if (!Base::FindObject(eType_Player) ) {
		Base::Add(new Gameover());
		m_kill = true;
	}
}

void Game::Update()
{

	//�S�[����������΃Q�[���V�[���I��
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
			//�Q�[���N���A�Ɉڍs
			//�S�ẴI�u�W�F�N�g��j��
			Base::KillAll();

			//Base::Add(new Gameclear());
		}
		else
		{
			Base::Add(new Map(stage));
		}
	}
	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		m_kill = true;
	}
}


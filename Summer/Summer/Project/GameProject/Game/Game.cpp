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

	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		m_kill = true;
	}
}


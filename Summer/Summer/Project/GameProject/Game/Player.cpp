#include "Player.h"
#include "AnimData.h"
#include"Explosion.h"
#include"Bullet.h"
#include"Bomb.h"
#include"Enemy.h"
#include"Map.h"
#include"Enemy.h"

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	//�摜����
	m_img = COPY_RESOURCE("players blue x2", CImage);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos_old=m_bom_pos=m_gun_pos=m_pos = p;
	//���S�ʒu�ݒ�
	m_img.SetCenter(32, 64);
	m_rect = CRect(-12, -32, 12, 0);
	//���]�t���O
	
	//�ʏ��Ԃ�
	m_state = eState_Idle;
	//���n�t���O
	m_is_ground=true;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
	m_damage_no = -1;
	//�̗�
	m_hp = 100;
	//�c�e��
	m_count = 6;
	//�e�̏��
	m_bullet = m_count;
	//���e�̎����Ă��鐔
	m_countb = 2;
	
	


}void Player::StateIdle()
{
	//�ړ���
	const float move_speed = 6;
	//�ړ��t���O
	bool move_flag = false;
	//�W�����v��
	const float jump_pow = 10;
	Base* player = Base::FindObject(eType_Player);
	if(player){
		//���ړ�
		if (HOLD(CInput::eLeft)) {
			//�ړ��ʂ�ݒ�
			m_pos.x += -move_speed;
			//���]�t���O
			m_flip = true;
			move_flag = true;
		}
		//�E�ړ�
		if (HOLD(CInput::eRight)) {
			//�ړ��ʂ�ݒ�
			m_pos.x += move_speed;
			//���]�t���O
			m_flip = false;
			move_flag = true;
		}
		
		//�W�����v
		if (m_is_ground && PUSH(CInput::eButton5)) {
			m_vec.y = -jump_pow;
			m_is_ground = false;
		}
		//�����[�h
		if (m_count < m_bullet && PUSH(CInput::eButton6)) {
			m_state=eState_ReLoad;
		}

	

		//�U��
		if (PUSH(CInput::eButton1)) {
				//�U����Ԃֈڍs
				m_state = eState_Attack;
				m_attack_no++;
				m_count--;
				if (m_count <= 0) {
					m_state = eState_ReLoad;
				}
				Base::Add(new Bullet(eType_Player_Bullet, m_flip, m_gun_pos, 4, m_attack_no));
		}
		if (m_countb>0&&PUSH(CInput::eButton7)) {
				m_attack_no++;
				Base::Add(new Bomb(m_flip,m_bom_pos));
				m_countb--;
		
		}

		//�W�����v���Ȃ�
		/*if (!m_is_ground) {
			if (m_vec.y < 0)
				//�㏸�A�j���[�V����
				m_img.ChangeAnimation(eAnimJumpUp, false);
			else
				//���~�A�j���[�V����
				m_img.ChangeAnimation(eAnimJumpDown, false);
		}*/
		//�ړ����Ȃ�
		else
		{
			if (move_flag) {
				//����A�j���[�V����
				m_img.ChangeAnimation(eAnimRun);
			}
			else {
				//�ҋ@�A�j���[�V����
				m_img.ChangeAnimation(eAnimIdle);
			}

		}
	}

}
void Player::StateAttack()
{
	//�U���A�j���[�V�����֕ύX
	
	m_img.ChangeAnimation(eAnimAttack01, false);
	
	
	//3�Ԗڂ̃p�^�[���Ȃ�
	/*if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Player_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Player_Attack, m_attack_no));
		}
	}*/
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}


void Player::StateDamage()
{
	//m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Player::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		m_kill = true;
	}
}
void Player::StateReLoad()
{
	m_img.ChangeAnimation(eAnimReLoad, false);
	if (m_img.CheckAnimationEnd()) {
		m_count = m_bullet;
		m_state = eState_Idle;
	}
}
void Player::Update() {
	m_pos_old = m_pos;
	m_gun_pos = CVector2D(m_pos.x, m_pos.y-14);
	m_bom_pos = CVector2D(m_pos.x, m_pos.y - 8);
	switch (m_state) {
		//�ʏ���
	case eState_Idle:
		StateIdle();
		break;
		//�U�����
	case eState_Attack:
		StateAttack();
		break;
		//�_���[�W���
	case eState_Damage:
		StateDamage();
		break;
		//�_�E�����
	case eState_Down:
		StateDown();
		break;
	case eState_ReLoad:
		StateReLoad();
		break;
	}
	
	//�����Ă����痎������Ԃֈڍs
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//�d�͂ɂ�闎��
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	

	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();

	//�X�N���[���ݒ�
	m_scroll.x = m_pos.x - 1280 / 2;
	m_scroll.y = m_pos.y - 600;
}

void Player::Draw() {
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	
}
void Player::Collision(Base* b)
{
	switch (b->m_type) {
		//�S�[������
	case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			SetKill();
		}
		break;
	case eType_Item:
		if (Base::CollisionRect(this, b)) {
			m_hp += 20;
			if (m_hp >= 100) {
				m_hp = 100;
			}
			b->SetKill();
		}
		break;
	case eType_Item2:
		if (Base::CollisionRect(this, b)) {
			m_hp += 50;
			if (m_hp >= 100) {
				m_hp = 100;
			}
			b->SetKill();
		}
		break;
	case eType_Bomb2:
		if (Base::CollisionRect(this, b)) {
			if (m_countb <= 3) {
				m_countb++;
			}
			else {
				m_countb = 3;
			}
			
			b->SetKill();
		}
		break;
	case eType_Explosion:
		if (Explosion* e = dynamic_cast<Explosion*>(b)) {
			if (m_damage_no != e->GetAttackNo() && Base::CollisionRect(this, e)) {
				//�����U���̘A���_���[�W�h�~

				m_damage_no = e->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
			}
		}
		break;
		//�G�Ƃ̔���
	case eType_Enemy:
		if (Enemy* e = dynamic_cast<Enemy*>(b)) {
				if (m_damage_no != e->GetAttackNo() && Base::CollisionRect(this, e)) {
					//�����U���̘A���_���[�W�h�~
					m_damage_no = e->GetAttackNo();
					m_hp -= 25;
					if (m_hp <= 0) {
						m_state = eState_Down;
					}
				}
		}
		break;
	case eType_Field:
		//Field�^�փL���X�g�A�^�ϊ��ł�����
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y),m_rect);
			if (t != 0)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y),m_rect);
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
	}

}






#include "Enemy.h"
#include "AnimData.h"
#include "Slash.h"
#include "Effect.h"
#include"Item.h"
#include "Bomb2.h"
#include"Bullet.h"
#include"Map.h"
#include"Explosion.h"

Enemy::Enemy(const CVector2D& p, bool flip) :
	Base(eType_Enemy) {
	//画像複製
	m_img = COPY_RESOURCE("Enemy.png", CImage);

	//m_img.Load("Image/Enemy.png", enemy_anim_data, 256, 256);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old=m_pos = p;
	//中心位置設定
	m_img.SetCenter(32, 64);
	//当たり判定用矩形設定
	m_rect = CRect(-30, -64, 0, -20);
	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_attack_no = -1;
	m_rad = 16;
	m_cnt = 0;
	m_hp = 100;
	
}
Enemy::~Enemy() {
	int r = rand() % 100;
	if (0 <= r && r < 10) {
		//10%でItem
		Base::Add(new Item(eType_Item, m_pos));
	}
	else if (10 <= r && r < 30) {
		//20%でItem2
		Base::Add(new Item(eType_Item2, m_pos));
	}
	else if (30 <= r && r < 40) {
		//10%でBomb2
		Base::Add(new Bomb2(m_pos));
	}
}



void Enemy::StateIdle()
{
	//移動量
	const float move_speed = 6;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 12;

	Base* player = Base::FindObject(eType_Player);

	if (player) {
		//左移動
		if (player->m_pos.x < m_pos.x - 4) {
			//移動量を設定
			m_pos.x += -move_speed;
			//反転フラグ
			m_flip = true;
			move_flag = true;
		}
		else
			//右移動
			if (player->m_pos.x > m_pos.x + 4) {
				//移動量を設定
				m_pos.x += move_speed;
				//反転フラグ
				m_flip = false;
				move_flag = true;
			}
			else {
				//攻撃状態へ移行
				m_state = eState_Attack;
				m_attack_no++;
			}
	}


	

	if (!m_is_ground) {
		if (m_vec.y < 0)
			//上昇アニメーション
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else
			//下降アニメーション
			m_img.ChangeAnimation(eAnimJumpDown, false);
	}
	//移動中なら
	else
	{
		if (move_flag) {
			//走るアニメーション
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			//待機アニメーション
			m_img.ChangeAnimation(eAnimIdle);
		}

	}
	if (--m_cnt <= 0) {
		m_cnt = rand() % 120 + 180;
		m_state = eState_Wait;
	}

}
void Enemy::StateWait() {
	//待機アニメーション
	m_img.ChangeAnimation(eAnimIdle);
	if (--m_cnt <= 0) {
		m_cnt = rand() % 120 + 180;
		m_state = eState_Idle;
	}
}
void Enemy::StateAttack()
{
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack01, false);
	if (m_flip) {
		m_rect = CRect(-50, -64, 0,-20);
	}else{
		m_rect = CRect(-30, -64, 20, -20);
		}
	//3番目のパターンなら
	/*if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
	}*/
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Wait;
		m_rect = CRect(-30, -64, 0, -20);
	}

}
void Enemy::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Wait;
	}
}
void Enemy::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {

		m_kill = true;
	}
}
void Enemy::Update() {
	m_pos_old = m_pos;
	switch (m_state) {
		//通常状態
	case eState_Wait:
		StateWait();
		break;
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
		//攻撃状態
	case eState_Attack:
		StateAttack();
		break;
		//ダメージ状態
	case eState_Damage:
		StateDamage();
		break;
		//ダウン状態
	case eState_Down:
		StateDown();
		break;
	}
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;

	//アニメーション更新
	m_img.UpdateAnimation();

	//スクロール設定
//	m_scroll.x = m_pos.x - 1280 / 2;

}

void Enemy::Draw() {
	//位置設定
	if (m_flip) {
		m_img.SetPos(GetScreenPos(m_pos) + CVector2D(-32, 0));
	}else{
		m_img.SetPos(GetScreenPos(m_pos) + CVector2D(0, 0));
		}
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	
}
void Enemy::Collision(Base* b)
{
	switch (b->m_type) {
	//攻撃エフェクトとの判定
		//Slash型へキャスト、型変換できたら

	case eType_Player_Bullet:
		if (Bullet*  p= dynamic_cast<Bullet*>(b)) {
			if (m_damage_no != p->GetAttackNo() && Base::CollisionRect(this, p)) {
				//同じ攻撃の連続ダメージ防止

				m_damage_no = p->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;

				}
				//Base::Add(new Effect("Effect_Blood",
					//m_pos + CVector2D(0, -128), m_flip));

				//Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -64), m_flip));
			}
		}
		break;
	case eType_Explosion:
		if (Explosion* e = dynamic_cast<Explosion*>(b)) {
			if (m_damage_no != e->GetAttackNo() && Base::CollisionRect(this, e)) {
				//同じ攻撃の連続ダメージ防止

				m_damage_no = e->GetAttackNo();
				m_hp -= 100;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;

				}
			}
		}
		break;
	case eType_Player:
		//Enemy* e = dynamic_cast<Enemy*>(b);
		if (Base::CollisionRect(this, b)) {
			m_hp -= 5;
			if (m_hp <= 0) {
				m_state = eState_Down;
				b->SetKill();
			}
			else {
				
			}
		}
		break;
	case eType_Field:
		//Field型へキャスト、型変換できたら
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





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
	//画像複製
	m_img = COPY_RESOURCE("players blue x2", CImage);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old=m_bom_pos=m_gun_pos=m_pos = p;
	//中心位置設定
	m_img.SetCenter(32, 64);
	m_rect = CRect(-12, -32, 12, 0);
	//反転フラグ
	
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground=true;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_damage_no = -1;
	//体力
	m_hp = 100;
	//残弾数
	m_count = 6;
	//弾の上限
	m_bullet = m_count;
	//爆弾の持っている数
	m_countb = 2;
	
	


}void Player::StateIdle()
{
	//移動量
	const float move_speed = 6;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 10;
	Base* player = Base::FindObject(eType_Player);
	if(player){
		//左移動
		if (HOLD(CInput::eLeft)) {
			//移動量を設定
			m_pos.x += -move_speed;
			//反転フラグ
			m_flip = true;
			move_flag = true;
		}
		//右移動
		if (HOLD(CInput::eRight)) {
			//移動量を設定
			m_pos.x += move_speed;
			//反転フラグ
			m_flip = false;
			move_flag = true;
		}
		
		//ジャンプ
		if (m_is_ground && PUSH(CInput::eButton5)) {
			m_vec.y = -jump_pow;
			m_is_ground = false;
		}
		//リロード
		if (m_count < m_bullet && PUSH(CInput::eButton6)) {
			m_state=eState_ReLoad;
		}

	

		//攻撃
		if (PUSH(CInput::eButton1)) {
				//攻撃状態へ移行
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

		//ジャンプ中なら
		/*if (!m_is_ground) {
			if (m_vec.y < 0)
				//上昇アニメーション
				m_img.ChangeAnimation(eAnimJumpUp, false);
			else
				//下降アニメーション
				m_img.ChangeAnimation(eAnimJumpDown, false);
		}*/
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
	}

}
void Player::StateAttack()
{
	//攻撃アニメーションへ変更
	
	m_img.ChangeAnimation(eAnimAttack01, false);
	
	
	//3番目のパターンなら
	/*if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Player_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Player_Attack, m_attack_no));
		}
	}*/
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
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
	case eState_ReLoad:
		StateReLoad();
		break;
	}
	
	//落ちていたら落下中状態へ移行
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	

	//アニメーション更新
	m_img.UpdateAnimation();

	//スクロール設定
	m_scroll.x = m_pos.x - 1280 / 2;
	m_scroll.y = m_pos.y - 600;
}

void Player::Draw() {
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	
}
void Player::Collision(Base* b)
{
	switch (b->m_type) {
		//ゴール判定
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
				//同じ攻撃の連続ダメージ防止

				m_damage_no = e->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
			}
		}
		break;
		//敵との判定
	case eType_Enemy:
		if (Enemy* e = dynamic_cast<Enemy*>(b)) {
				if (m_damage_no != e->GetAttackNo() && Base::CollisionRect(this, e)) {
					//同じ攻撃の連続ダメージ防止
					m_damage_no = e->GetAttackNo();
					m_hp -= 25;
					if (m_hp <= 0) {
						m_state = eState_Down;
					}
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






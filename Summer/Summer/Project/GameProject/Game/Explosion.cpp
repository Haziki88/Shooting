#include "Explosion.h"
#include"Enemy.h"

Explosion::Explosion(const CVector2D& pos, bool flip, int type)
	:Base(eType_Explosion)
{
	//画像複製
	m_img = COPY_RESOURCE("explosion-3", CImage);
	//反転フラグ設定
	m_flip = flip;
	//座標設定
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(128,80);
	//中心位置設定
	m_img.SetCenter(64, 40);
	//当たり判定用矩形
	m_rect = CRect(-64, -40, 64, 40);
	//再生アニメーション設定(非ループ)
	m_img.ChangeAnimation(0, false);
	//攻撃番号
	
}

void Explosion::Update()
{
	//アニメーション更新
	m_img.UpdateAnimation();
	//アニメーション終了チェック
	Base* enemy = Base::FindObject(eType_Enemy);
	Enemy* e = dynamic_cast<Enemy*>(enemy);
	if (m_img.CheckAnimationEnd()) {
		//エフェクトを削除
		SetKill();
		e->m_hp -= 100;
	}
}

void Explosion::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	//DrawRect();
}

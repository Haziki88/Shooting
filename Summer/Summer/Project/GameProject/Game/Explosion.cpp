#include "Explosion.h"

Explosion::Explosion(const CVector2D& pos, bool flip, int type)
	:Base(eType_Explosion)
{
	//�摜����
	m_img = COPY_RESOURCE("explosion-3", CImage);
	//���]�t���O�ݒ�
	m_flip = flip;
	//���W�ݒ�
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(128,80);
	//���S�ʒu�ݒ�
	m_img.SetCenter(64, 40);
	//�����蔻��p��`
	m_rect = CRect(-64, -40, 64, 40);
	//�Đ��A�j���[�V�����ݒ�(�񃋁[�v)
	m_img.ChangeAnimation(0, false);
	//�U���ԍ�
	
}

void Explosion::Update()
{
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	//�A�j���[�V�����I���`�F�b�N
	if (m_img.CheckAnimationEnd()) {
		//�G�t�F�N�g���폜
		SetKill();
	}
}

void Explosion::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	//DrawRect();
}

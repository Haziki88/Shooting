#pragma once
#include"../Base/Base.h"
class Item :public Base {
public:
	CImage m_img;
public:
	Item(int type,const CVector2D& pos);
	void Update();
	void Draw();
};
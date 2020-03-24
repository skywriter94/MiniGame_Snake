#pragma once
#include "gameNode.h"
#define TAILMAX 300
#define PI 3.14

struct tagTails
{
	float x, y;
	float speed;
	float angle;
	float radius;
};

class playGround : public gameNode
{
private:
	tagTails tails[TAILMAX];

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render(HDC hdc);	//�׸��� ���� �Լ�

	void TailControl();
};
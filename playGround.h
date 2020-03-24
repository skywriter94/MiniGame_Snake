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

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용 함수
	virtual void render(HDC hdc);	//그리기 전용 함수

	void TailControl();
};
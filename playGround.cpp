#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init();
	for (int i = 0; i < TAILMAX; i++)
	{
		tails[i].radius = 20;
		tails[i].speed = 5.0f;
		tails[i].angle = PI / 2;
		if (i == 0)
		{
			tails[i].x = WINSIZEX / 2;
			tails[i].y = WINSIZEY / 2;
		}
		else // 꺾일때 빗변 받아오는 길이가 점차 손실되니까 꺾일때 빗변 받아오는 길이를 고정시키는게 키포인트 
		{	// 꼬리i번째 x값 => 꼬리 i번째의 전번.x값 - 코사인f(현재 꼬리 각도)* 현재 꼬리 반지름 * 2;
			tails[i].x = tails[i - 1].x - (cosf(tails[i].angle) * tails[i].radius * 2);
			tails[i].y = tails[i - 1].y - (-sinf(tails[i].angle) * tails[i].radius * 2);
		}
	}
	return S_OK;
}

void playGround::release()
{
	gameNode::release();
}

void playGround::update()
{
	gameNode::update();
	TailControl();
	float distance;
	for (int i = 0; i < TAILMAX; i++)
	{
		if (i == 0)
		{
			if (tails[i].x - tails[i].radius < 0)
			{
				tails[i].x = tails[i].radius;
				tails[i].angle = PI - tails[i].angle;
			}
			if (tails[i].x + tails[i].radius > WINSIZEX)
			{
				tails[i].x = WINSIZEX - tails[i].radius;
				tails[i].angle = PI - tails[i].angle;
			}
			if (tails[i].y - tails[i].radius < 0)
			{
				tails[i].y = tails[i].radius;
				tails[i].angle = 2 * PI - tails[i].angle;
			}
			if (tails[i].y - tails[i].radius > WINSIZEY)
			{
				tails[i].y = WINSIZEY - tails[i].radius;
				tails[i].angle = 2 * PI - tails[i].angle;
			}
			tails[i].x += cosf(tails[i].angle) * tails[i].speed;
			tails[i].y += -sinf(tails[i].angle) * tails[i].speed;
		}
		else
		{
			if (getDistance(tails[i].x, tails[i].y, tails[i - 1].x, tails[i - 1].y) >= tails[i].radius * 2)
			{
				tails[i].angle = getAngle(tails[i].x, tails[i].y, tails[i - 1].x, tails[i - 1].y);

				tails[i].x = tails[i - 1].x - (cosf(tails[i].angle) * tails[i].radius * 2);
				tails[i].y = tails[i - 1].y - (-sinf(tails[i].angle) * tails[i].radius * 2);
			}
			tails[i].x += cosf(tails[i].angle) * tails[i].speed;
			tails[i].y += -sinf(tails[i].angle) * tails[i].speed;
		}
	}
}

void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================
	for (int i = 0; i < TAILMAX; i++)
	{
		EllipseMakeCenter(backDC, tails[i].x, tails[i].y, tails[i].radius * 2, tails[i].radius * 2);
	}
	//===================================================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::TailControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		tails[0].angle += 0.05f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		tails[0].angle -= 0.05f;
	}
}
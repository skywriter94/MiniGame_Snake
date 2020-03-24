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
		else // ���϶� ���� �޾ƿ��� ���̰� ���� �սǵǴϱ� ���϶� ���� �޾ƿ��� ���̸� ������Ű�°� Ű����Ʈ 
		{	// ����i��° x�� => ���� i��°�� ����.x�� - �ڻ���f(���� ���� ����)* ���� ���� ������ * 2;
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
#include "stdafx.h"
#include "image.h"


image::image()
	: _backBuffer(NULL)
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	//����۰� �����ϸ� �޸� ����
	if (_backBuffer != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_backBuffer = new IMAGE_INFO;
	_backBuffer->hMemDC = CreateCompatibleDC(hdc);	// �� DC���� �ϳ��� �����
	_backBuffer->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_backBuffer->hOBit = (HBITMAP)SelectObject(_backBuffer->hMemDC, _backBuffer->hBit);
	_backBuffer->width = width;
	_backBuffer->height = height;

	//���� ������ �����ؼ� ����۰� �������� �ʾҴٸ�
	if (_backBuffer == NULL)
	{
		//�޸� ����
		release();

		//�׸��� �����ߴ� �޼����� ȣ��
		return E_FAIL;
	}


	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_backBuffer)
	{
		SelectObject(_backBuffer->hMemDC, _backBuffer->hOBit);
		DeleteObject(_backBuffer->hBit);
		DeleteDC(_backBuffer->hMemDC);


		SAFE_DELETE(_backBuffer);
	}

}

void image::render(HDC hdc, int destX, int destY)
{
	//DC���� ���� ��Ӻ��縦 ����ϴ� �Ծ�
	BitBlt(hdc,				//������ DC
		destX,				//������ X��ǥ(left)
		destY,				//������ Y��ǥ(top)
		_backBuffer->width,	//������ ũ��(width)
		_backBuffer->height,//������ ũ��(height)
		_backBuffer->hMemDC,//����� DC
		0, 0,				//����� X, Y (left, top)
		SRCCOPY);			//�������� �����ϰڴ�
}

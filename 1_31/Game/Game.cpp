// Game.cpp : ����Ӧ�ó������ڵ㡣
//

#include <Windows.h>
#include <mmsystem.h>
#include "stdafx.h"
#include "Game.h"
//#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <d3dx9math.h>


LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIB = NULL;
LPDIRECT3DTEXTURE9  g_pTexture = NULL;



struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	FLOAT tu, tv;
};


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)
#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//
//int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
//                     _In_opt_ HINSTANCE hPrevInstance,
//                     _In_ LPTSTR    lpCmdLine,
//                     _In_ int       nCmdShow)
//{
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);
//
// 	// TODO:  �ڴ˷��ô��롣
//	MSG msg;
//	HACCEL hAccelTable;
//
//	// ��ʼ��ȫ���ַ���
//	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//	LoadString(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
//	MyRegisterClass(hInstance);
//
//	// ִ��Ӧ�ó����ʼ��: 
//	if (!InitInstance (hInstance, nCmdShow))
//	{
//		return FALSE;
//	}
//
//	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));
//
//	// ����Ϣѭ��: 
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//	}
//
//	return (int) msg.wParam;
//}
//


//
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GAME);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
//
//HRESULT InitD3D(HWND hWnd)
//{
//	// Create the D3D object.
//	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
//		return E_FAIL;
//
//	// Set up the structure used to create the D3DDevice
//	D3DPRESENT_PARAMETERS d3dpp;
//	ZeroMemory(&d3dpp, sizeof(d3dpp));
//	d3dpp.Windowed = TRUE;
//	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
//	d3dpp.EnableAutoDepthStencil = TRUE;
//	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
//	// Create the D3DDevice
//	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
//		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//		&d3dpp, &g_pd3dDevice)))
//	{
//		return E_FAIL;
//	}
//	return S_OK;
//}
HRESULT InitD3D(HWND hWnd)
{
	IDirect3D9 *d3d = 0;
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		MessageBox(hWnd, _T("Direct3DCreate9 ERROR!"), _T("ERROR"), MB_OK);
		return false;
	}

	D3DDEVTYPE d3dt = D3DDEVTYPE_HAL;
	D3DCAPS9 caps;
	d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, d3dt, &caps);
	int vp = 0;
	if (caps.DevCaps& D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.Flags = 0;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = TRUE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;

	if (hWnd)//����ģʽ
	{
		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferHeight = 0;    //����ģʽ��Ĭ��ʹ��0
		d3dpp.BackBufferWidth = 0;    //����ģʽ��Ĭ��ʹ��0
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;    //����ģʽһ������ D3DPRESENT_INTERVAL_DEFAULT ��
		d3dpp.FullScreen_RefreshRateInHz = 0;//��ʾ��ˢ���ʣ�����ģʽ��ֵ����Ϊ0
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    //ָ��ϵͳ��ν���̨�����������ݸ��Ƶ�ǰ̨������ D3DSWAPEFFECT_DISCARD:�����̨���������

	}
	else
	{
		//ȫ��ģʽ
		d3dpp.BackBufferCount = 2;
		d3dpp.BackBufferHeight = GetSystemMetrics(SM_CXSCREEN);//������ GetSystemMetrics(SM_CXSCREEN) �����Ļ��
		d3dpp.BackBufferWidth = GetSystemMetrics(SM_CYSCREEN);    //������ GetSystemMetrics(SM_CYSCREEN) �����Ļ��
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//��ʾ��ˢ���ʣ�����ģʽ��ֵ����Ϊ0
		d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;    //D3DSWAPEEFECT_FLIP:������̨��������ݡ���������>1ʱ��
	}

	//if (m_bWindowed)//����ģʽ
	//{
	//	m_hwnd = CreateWindowEx(NULL, _T("DXCLASSNAME"), lpcwTitle,
	//		(WS_OVERLAPPEDWINDOW | WS_VISIBLE)&~WS_THICKFRAME, 0, 0,
	//		m_width, m_height, NULL, NULL, hinstance, NULL);
	//}
	//else
	//{
	//	//ȫ��ģʽ
	//	m_hwnd = CreateWindowEx(NULL, _T("DXCLASSNAME"), lpcwTitle,
	//		(WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP), 0, 0,
	//		m_width, m_height, NULL, NULL, hinstance, NULL);
	//}


	HRESULT hr = 0;
	hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, d3dt, hWnd, vp, &d3dpp, &g_pd3dDevice);

	if (FAILED(hr))
	{
		MessageBox(hWnd, _T("CreateDevice ERROR"), _T("ERROR"), MB_OK);
		d3d->Release();
		return false;
	}
	return true;
}
HRESULT InitGeometry()
{
	CUSTOMVERTEX vertices[] =
	{
		{ -10.0f, -10.0f, 0.0f, 0, 1 },
		{ -10.0f, 10.0f, 0.0f, 0, 0 },
		{ 10.0f, 10.0f, 0.0f, 1, 0 },
		{ 10.0f, -10.0f, 0.0f, 1, 1 },
	};

	// Create the vertex buffer.
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(sizeof(vertices) / sizeof(vertices[0]) * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	// Fill the vertex buffer.
	VOID* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, (void*)vertices, sizeof(vertices));
	g_pVB->Unlock();

	WORD indices[] = { 0, 1, 2, 0, 2, 3 };

	if (FAILED(g_pd3dDevice->CreateIndexBuffer(sizeof(indices) / sizeof(indices[0]) * sizeof(WORD),
		0, D3DFMT_INDEX16,
		D3DPOOL_DEFAULT, &g_pIB, NULL)))
	{
		return E_FAIL;
	}

	VOID* pIndices = NULL;
	if (FAILED(g_pIB->Lock(0, sizeof(indices), (void**)&pIndices, 0)))
		return E_FAIL;
	memcpy(pIndices, (VOID*)indices, sizeof(indices));
	g_pIB->Unlock();

	return S_OK;
}

//void GenerateTexture()
//{//���ɺ졢�̡�����������
//	int width = 240, height = 240;
//
//	g_pd3dDevice->CreateTexture(width, height, 1, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &g_pTexture, 0);
//	D3DLOCKED_RECT lockrect;
//	g_pTexture->LockRect(0, &lockrect, 0, 0);
//
//	char*  nPbit = (char*)lockrect.pBits;
//	int nPitch = lockrect.Pitch;
//	int stride = nPitch / (4 * 3);//����Ϊ3�ȷݣ�strideΪ����
//
//	DWORD* pwd = (DWORD*)nPbit;
//	for (UINT row = 0; row < height; row++)
//	{
//		for (int col = 0; col < stride; col++)
//		{
//			pwd[row * nPitch / 4 + col] = 0xFFFF0000;
//			pwd[row * nPitch / 4 + col + stride] = 0xFF00FF00;
//			pwd[row * nPitch / 4 + col + 2 * stride] = 0xFF0000FF;
//		}
//	}
//	g_pTexture->UnlockRect(0);
//}
void GenerateTexture()
{//���ɺ졢�̡�����������
	int width = 240, height = 240;

	g_pd3dDevice->CreateTexture(width, height, 1, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &g_pTexture, 0);
	D3DLOCKED_RECT lockrect;
	g_pTexture->LockRect(0, &lockrect, 0, 0);

	char*  nPbit = (char*)lockrect.pBits;
	int nPitch = lockrect.Pitch;
	int stride = nPitch / (4 * 3);//����Ϊ3�ȷݣ�strideΪ����

	DWORD* pwd = (DWORD*)nPbit;
	for (UINT row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			pwd[row * nPitch / 4 + col] = 0xffff0000;
		}
	}
	g_pTexture->UnlockRect(0);
}
VOID SetupMatrices()
{
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -30);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	//D3DXMatrixPerspectiveFovLH()�����е���Զ���������Ϊ������ӵ�ľ��루��vEyePt�еľ��룩
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 200.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

}

VOID GameCleanup()
{
	if (g_pTexture != NULL)
		g_pTexture->Release();

	if (g_pVB != NULL)
		g_pVB->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}

VOID Render()
{
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		SetupMatrices();
		GenerateTexture();

		g_pd3dDevice->SetTexture(0, g_pTexture);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		g_pd3dDevice->SetIndices(g_pIB);

		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		float pointsize = 10;
		g_pd3dDevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&pointsize));
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		GameCleanup();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"D3D Tutorial", NULL
	};
	RegisterClassEx(&wc);

	// Create the application's window
	HWND hWnd = CreateWindow("D3D Tutorial", "D3D : Texture",
		WS_OVERLAPPEDWINDOW, 100, 100, 700, 700,
		NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		// Create the scene geometry
		if (SUCCEEDED(InitGeometry()))
		{
			// Show the window
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			// Enter the message loop
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
					Render();
			}
		}
	}

	UnregisterClass("D3D Tutorial", wc.hInstance);
	return 0;
}

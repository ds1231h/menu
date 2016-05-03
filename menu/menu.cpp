#include <windows.h>
#include <windowsx.h>
#include "resource.h"

//��������
BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

/*******************************************************************
������WinMain ()
���ܣ�Win32 Ӧ�ó�����ں��������������ڣ�������Ϣѭ��
********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance,         //��ǰʵ�����
	HINSTANCE hPrevInstance,     //ǰһ��ʵ�����
	PSTR szCmdLine,              //�������ַ�
	int iCmdShow)                //������ʾ��ʽ
{
	MSG msg;

	//����������
	if (!InitWindow(hInstance, iCmdShow))
		return FALSE;

	//������Ϣѭ�����Ӹ�Ӧ�ó������Ϣ�����м�ȡ��Ϣ��
	//�͵���Ϣ������̣�����ȡ��WM_QUIT��Ϣʱ���˳���Ϣѭ����
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

BOOL CALLBACK InputDlgProc (HWND hDlg, UINT message, 
	WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		//����Ի����и��ؼ�֪ͨ��Ϣ
		switch (LOWORD (wParam))
		{
		case IDD_DIALOG1:
			if(DialogBox((HINSTANCE)GetWindowLong(hDlg, NULL), 
				edit_time,
				hDlg, 
				(LPCWSTR)DeleteItemProc)==IDOK)  // ��֪���������Ӧ����ʲô
			{

			}

		case IDOK:
			
			EndDialog (hDlg, TRUE);      //�رնԻ���
			return TRUE;

		case IDCANCEL:
			//��Ӧ"ȡ��"��ť��ֱ�ӹرնԻ���
			EndDialog (hDlg, FALSE);
			return TRUE;
		}
		break;
	}
	return FALSE;
};//���� InputDlgProc

/******************************************************************
������InitWindow ()
���ܣ��������ڡ�
*******************************************************************/
BOOL InitWindow(HINSTANCE hInstance, int iCmdShow)
{
	TCHAR szAppName[] = TEXT("EasyWin");		  //Ӧ�ó�������
	HWND hwnd;                                    //���ھ��
	WNDCLASS wcMainWnd;                           //������ṹ
	ATOM a;

	//��䴰����ṹ
	wcMainWnd.style = CS_VREDRAW | CS_HREDRAW;
	wcMainWnd.lpfnWndProc = WinProc;
	wcMainWnd.cbClsExtra = 0;
	wcMainWnd.cbWndExtra = 0;
	wcMainWnd.hInstance = hInstance;
	wcMainWnd.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcMainWnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcMainWnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcMainWnd.lpszMenuName = NULL;
	wcMainWnd.lpszClassName = szAppName;

	//ע�ᴰ����
	a = RegisterClass(&wcMainWnd);

	if (!a)
	{
		MessageBox(NULL, TEXT("ע�ᴰ����ʧ�ܣ�"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	//����������
	hwnd = CreateWindow(szAppName, 						//����������
		TEXT("Windows Ӧ�ó���������"),  //���ڱ���
		WS_OVERLAPPEDWINDOW,				//���ڷ��
		100,								//����λ�õ�x����
		100,								//����λ�õ�y����
		400,								//���ڵĿ��
		300,								//���ڵĸ߶�
		NULL,								//�����ھ��
		LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)),								//�˵����
		hInstance,							//Ӧ�ó���ʵ�����
		NULL);								//���ڴ�������ָ��

	if (!hwnd) return FALSE;

	//��ʾ�����´���
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}

/******************************************************************
������WinProc ()
���ܣ�������������Ϣ
*******************************************************************/
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;
	POINT pt;
	static HMENU hMenuPop;

	switch (message)
	{
	/*case WM_CREATE:
		hMenuPop = LoadMenu ((HINSTANCE)GetWindowLong(hWnd, NULL), (LPCWSTR)"MENUDEMO");
		hMenuPop = GetSubMenu (hMenuPop, 2);
		return 0;
		*/
	case WM_COMMAND:
		if (lParam == 0)
		{
			switch (wParam)
			{
			case show:
				MessageBox (hWnd,TEXT ("��ʾ"), 
					TEXT ("�˵�ʾ������"), MB_OK|MB_OKCANCEL);
				return 0;

			case exit:
				PostQuitMessage(0);
				return 0;
			}
		}
		return 0;

	case WM_RBUTTONUP:
		hMenuPop = LoadMenu ((HINSTANCE)GetWindowLong(hWnd, NULL), (LPCWSTR)"MENUDEMO");
		hMenuPop = GetSubMenu (hMenuPop, 2);
		pt.x = LOWORD (lParam);
		pt.y = HIWORD (lParam);
		ClientToScreen (hWnd, &pt);
		TrackPopupMenu (hMenuPop,                            //��ݲ˵����
			TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, //��־ѡ��
			pt.x, pt.y, 0, hWnd, NULL);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	//����ȱʡ��Ϣ�������
	return DefWindowProc(hWnd, message, wParam, lParam);

} //���� WinProc ����


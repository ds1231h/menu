#include <windows.h>
#include <windowsx.h>
#include "resource.h"

//函数声明
BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

/*******************************************************************
函数：WinMain ()
功能：Win32 应用程序入口函数。创建主窗口，处理消息循环
********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance,         //当前实例句柄
	HINSTANCE hPrevInstance,     //前一个实例句柄
	PSTR szCmdLine,              //命令行字符
	int iCmdShow)                //窗口显示方式
{
	MSG msg;

	//创建主窗口
	if (!InitWindow(hInstance, iCmdShow))
		return FALSE;

	//进入消息循环：从该应用程序的消息队列中检取消息，
	//送到消息处理过程，当检取到WM_QUIT消息时，退出消息循环。
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
		//处理对话框中各控件通知消息
		switch (LOWORD (wParam))
		{
		case IDD_DIALOG1:
			if(DialogBox((HINSTANCE)GetWindowLong(hDlg, NULL), 
				edit_time,
				hDlg, 
				(LPCWSTR)DeleteItemProc)==IDOK)  // 不知道这个参数应该是什么
			{

			}

		case IDOK:
			
			EndDialog (hDlg, TRUE);      //关闭对话框
			return TRUE;

		case IDCANCEL:
			//响应"取消"按钮，直接关闭对话框
			EndDialog (hDlg, FALSE);
			return TRUE;
		}
		break;
	}
	return FALSE;
};//结束 InputDlgProc

/******************************************************************
函数：InitWindow ()
功能：创建窗口。
*******************************************************************/
BOOL InitWindow(HINSTANCE hInstance, int iCmdShow)
{
	TCHAR szAppName[] = TEXT("EasyWin");		  //应用程序名称
	HWND hwnd;                                    //窗口句柄
	WNDCLASS wcMainWnd;                           //窗口类结构
	ATOM a;

	//填充窗口类结构
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

	//注册窗口类
	a = RegisterClass(&wcMainWnd);

	if (!a)
	{
		MessageBox(NULL, TEXT("注册窗口类失败！"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	//创建主窗口
	hwnd = CreateWindow(szAppName, 						//窗口类名称
		TEXT("Windows 应用程序基本框架"),  //窗口标题
		WS_OVERLAPPEDWINDOW,				//窗口风格
		100,								//窗口位置的x坐标
		100,								//窗口位置的y坐标
		400,								//窗口的宽度
		300,								//窗口的高度
		NULL,								//父窗口句柄
		LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)),								//菜单句柄
		hInstance,							//应用程序实例句柄
		NULL);								//窗口创建数据指针

	if (!hwnd) return FALSE;

	//显示并更新窗口
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}

/******************************************************************
函数：WinProc ()
功能：处理主窗口消息
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
				MessageBox (hWnd,TEXT ("显示"), 
					TEXT ("菜单示例程序"), MB_OK|MB_OKCANCEL);
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
		TrackPopupMenu (hMenuPop,                            //快捷菜单句柄
			TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, //标志选项
			pt.x, pt.y, 0, hWnd, NULL);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	//调用缺省消息处理过程
	return DefWindowProc(hWnd, message, wParam, lParam);

} //函数 WinProc 结束


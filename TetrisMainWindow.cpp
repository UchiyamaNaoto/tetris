#include <windows.h>

#include "resource.h"

#include "TetrisDef.h"
#include "TetrisGble.h"
#include "TetrisPro.h"

//////////////////////////////////////////////////////////
//
// 関数名：InitApp
//
// 戻り値：クラス識別番号（失敗時0）
//
// 引　数：hInst       - インスタンスハンドル
//         szClassName - ウィンドウクラスの名前
//
// 機　能：ウィンドウクラスの登録
//
//////////////////////////////////////////////////////////
BOOL InitApp(HINSTANCE hInst, LPCSTR szClassName)
{
    WNDCLASS wc;		// ウィンドウクラス

	wc.hInstance		= hInst;										// インスタンス
	wc.lpszClassName	= (LPCSTR)szClassName;							// ウィンドウクラスの名前
	wc.style			= CS_HREDRAW | CS_VREDRAW;						// 水平方向・垂直方向のサイズ変更があったら全体を描き直す
	wc.lpfnWndProc		= WndProc;										// ウィンドウプロシージャ名
	wc.cbClsExtra		= 0;											// 補助のメモリ領域は不要
	wc.cbWndExtra		= 0;											// 補助のメモリ領域は不要
	wc.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));	// アイコン名
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);					// マウスカーソルは矢印
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);			// 背景色は黒
	wc.lpszMenuName		= MAKEINTRESOURCE(IDR_MENU1);					// メニュー名

	// ウィンドウクラスを登録する
	return RegisterClass(&wc);
}

//////////////////////////////////////////////////////////
//
// 関数名：InitInstance
//
// 戻り値：クラス識別番号（失敗時0）
//
// 引　数：szClassName - ウィンドウクラスの名前
//         nCmdShow    - ウィンドウ表示方法
//
// 機　能：ウィンドウの生成
//
//////////////////////////////////////////////////////////
BOOL InitInstance(HINSTANCE hInst, LPCSTR szClassName, int nCmdShow)
{
	HWND hWnd;			// ウィンドウハンドル

	// ウィンドウを作成する
	hWnd = CreateWindow(szClassName,					// ウィンドウクラスの名前
						"テトリス",						// ウィンドウタイトル
						WS_OVERLAPPEDWINDOW,			// ウィンドウの種類
						CW_USEDEFAULT,					// Ｘ座標
						CW_USEDEFAULT,					// Ｙ座標
						WINDOW_WIDTH,					// 幅
						WINDOW_HEIGHT,					// 高さ
						NULL,							// 親ウィンドウのハンドル、親を作るときはNULL
						NULL,							// メニューハンドル、クラスメニューを使うときはNULL
						hInst,							// インスタンスハンドル
						NULL);

	// 失敗した場合はFALSEを返す
	if(hWnd == NULL){
		return FALSE;
	}

	// ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ウィンドウハンドルを保存
	hParent = hWnd;
	
	return TRUE;
}

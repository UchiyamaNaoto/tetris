#include <windows.h>

#include "TetrisDef.h"
#include "TetrisGble.h"
#include "TetrisPro.h"

//////////////////////////////////////////////////////////
//
// 関数名：DrawMap
//
// 戻り値：なし
//
// 引　数：hMemoryDC - 裏画面のデバイスコンテキスト
//
// 機　能：マップ全体の描画
//
//////////////////////////////////////////////////////////
void DrawMap(HDC *hMemoryDC)
{
	int i, j;

	for(i = 0; i < 12; i++){
		for(j = 0; j < 27; j++){
    		BitBlt(hMemoryDC[0], i*SIZE, j*SIZE, SIZE, SIZE,
				   hMemoryDC[1], SIZE*Map[i][j], 0,
				   SRCCOPY);
		}
	}
}

//////////////////////////////////////////////////////////
//
// 関数名：DrawBlock
//
// 戻り値：なし
//
// 引　数：hMemoryDC - 裏画面のデバイスコンテキスト
//
// 機　能：落下途中のブロックを描画
//
//////////////////////////////////////////////////////////
void DrawBlock(HDC *hMemoryDC)
{
	int i, j;

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(FallingBlock[i][j] != 0){
				BitBlt(hMemoryDC[0], (BlockX+i)*SIZE, (BlockY+j)*SIZE, SIZE, SIZE,
					   hMemoryDC[1], SIZE*FallingBlock[i][j], 0,
					   SRCCOPY);
			}
		}
	}
}

//////////////////////////////////////////////////////////
//
// 関数名：DrawScore
//
// 戻り値：なし
//
// 引　数：hMemoryDC - 裏画面のデバイスコンテキスト
//
// 機　能：スコア表示
//
//////////////////////////////////////////////////////////
void DrawScore(HDC *hMemoryDC)
{
	char  StrScore[256];		// スコア表示用
	RECT  rt;					// ウィンドウのサイズ
	HFONT hFont;				// フォントハンドル

	// ウィンドウのサイズを取得
	GetClientRect(hParent, &rt);
	rt.left += 16;
	rt.top  += 16;

	// スコアの表示文字列を作成
	wsprintf((LPSTR)StrScore, "SCORE %4d\nLINES %4d\nLEVEL %4d", Score, Lines, Level);

	// 背景をそのまま残すモードにする
	SetBkMode(hMemoryDC[0], TRANSPARENT);

	// フォントを作成
	hFont = SetFont("ＭＳ ゴシック");
	// 作成したフォントを選択
	SelectObject(hMemoryDC[0], hFont);

	// 文字色は白とする
	SetTextColor(hMemoryDC[0], RGB(255, 255, 255));
	// スコアを裏画面に描画する
	DrawText(hMemoryDC[0], StrScore, -1, &rt, DT_WORDBREAK);
	
	// 作成したフォントを解放
	DeleteObject(hFont);
}
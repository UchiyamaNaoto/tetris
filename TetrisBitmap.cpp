#include <windows.h>

#include "TetrisDef.h"
#include "TetrisGble.h"
#include "TetrisPro.h"

//////////////////////////////////////////////////////////
//
// 関数名：MakeBitmap
//
// 戻り値：TRUE  - 成功
//         FALSE - 失敗
//
// 引　数：hMemoryDC - 裏画面のデバイスコンテキスト
//         hBitmap   - ビットマップハンドル
//         dwWidth   - ウィンドウの幅
//         dwHeight  - ウィンドウの高さ
//
// 機　能：裏画面用のメモリ領域を作成
//
//////////////////////////////////////////////////////////
BOOL MakeBitmap(HDC *hMemoryDC, HBITMAP *hBitmap, DWORD dwWidth, DWORD dwHeight)
{
    HDC					hDC;				// デバイスコンテキストハンドル
    RGBTRIPLE			*rgbt;              // 色データ設定用
    BITMAPINFOHEADER	bi;					// ビットマップのヘッダ設定用構造体

    hDC = GetDC(hParent);					// デバイスコンテキストハンドルを取得
    *hMemoryDC = CreateCompatibleDC(hDC);	// 互換性のあるメモリデバイスコンテキストハンドルを作成

    ZeroMemory(&bi, sizeof(bi));			// 構造体のデータを０でクリア

    bi.biSize        = sizeof(BITMAPINFOHEADER);	// 構造体のサイズ
    bi.biWidth       = dwWidth;						// ビットマップの横幅
    bi.biHeight      = dwHeight;					// ビットマップの高さ
    bi.biPlanes      = 1;							// プレーン数（常に１）
    bi.biBitCount    = 16;							// １ピクセル当たりのビット数
    bi.biCompression = BI_RGB;

    // メモリ上にビットマップを作成してビットマップハンドルを取得
    *hBitmap = CreateDIBSection(hDC, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)(&rgbt), NULL, 0 );
    if(*hBitmap == NULL){
		// 取得できなかったらFALSEを返す
		return FALSE;
	}

    // デバイスとビットマップを対応させる
    SelectObject(*hMemoryDC, *hBitmap);

	// デバイスコンテキストハンドルを解放
    ReleaseDC(hParent, hDC);

    return TRUE;
}

//////////////////////////////////////////////////////////
//
// 関数名：LoadBitmapImage
//
// 戻り値：TRUE  - 成功
//         FALSE - 失敗
//
// 引　数：hMemoryDC   - 裏画面のデバイスコンテキスト
//         hBitmap     - ビットマップハンドル
//         lpImageName - ビットマップ（リソース）名
//
// 機　能：ブロックイメージをメモリにロード
//
//////////////////////////////////////////////////////////
BOOL LoadBitmapImage(HDC *hMemoryDC, HBITMAP *hBitmap, LPCSTR lpImageName)
{
	HDC			hDC;						// デバイスコンテキストハンドル

    hDC = GetDC(hParent);					// デバイスコンテキストハンドルを取得
    *hMemoryDC = CreateCompatibleDC(hDC);	// 互換性のあるメモリデバイスコンテキストハンドルを作成

    // まず lpImageName で指定された名前がリソースにあるかどうか調べて
    // あるならリソースから読み込む
    *hBitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(lpImageName), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    // リソースにないときはファイルから読み込む
    if(*hBitmap == NULL){
        *hBitmap = (HBITMAP)LoadImage(hInst, lpImageName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
        // ファイルにもなかったら失敗＆終了
		if(*hBitmap == NULL){
			return FALSE;
		}
    }
    
    // デバイスとビットマップを対応させる
    SelectObject(*hMemoryDC, *hBitmap);

	// デバイスコンテキストハンドルを解放
    ReleaseDC(hParent, hDC);

    return TRUE;
}

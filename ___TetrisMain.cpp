#include <windows.h>
#include <time.h>
#include <stdio.h>

#include "resource.h"

#include "TetrisDef.h"
#include "TetrisGbl.h"
#include "TetrisPro.h"


int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow)
{
    char    szClassName[] = "Tetris";       // ウィンドウクラス
    MSG     msg;                            // メッセージ
    HACCEL  hAccel;                         // アクセラレータハンドル

    hInst = hCurInst;                   // インスタンスハンドルをグローバル変数にコピー

    // ウィンドウクラスの登録
    if(InitApp(hCurInst, szClassName) == 0){
        return FALSE;
    }

    // ウィンドウの生成
    if(InitInstance(hCurInst, szClassName, nCmdShow) == FALSE) {
        return FALSE;
    }

    // キーボードアクセラレータをロード
    hAccel = LoadAccelerators(hCurInst, MAKEINTRESOURCE(IDR_ACCELERATOR1));

    while(GetMessage(&msg, NULL, 0, 0)){
        if(!TranslateAccelerator(hParent, hAccel, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}


//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HDC      hMemoryDC[2];
    static HBITMAP  hBitmap[2];
    HDC             PaintDC;
    PAINTSTRUCT     ps;

    switch(msg){
        case WM_CREATE:         // ウィンドウ生成時
            // 裏画面用のメモリ領域を作成
            if(MakeBitmap(&hMemoryDC[0], &hBitmap[0], WINDOW_WIDTH, WINDOW_HEIGHT) != TRUE){
                // APIエラー表示
                ShowLastError();
            }
            // ブロックイメージをメモリにロード
            if(LoadBitmapImage(&hMemoryDC[1], &hBitmap[1], MAKEINTRESOURCE(IDB_BLOCK)) != TRUE){
                // APIエラー表示
                ShowLastError();
            }

            // ブロックデータを配列に格納
            DefaultBlock();

            // 乱数の初期化
            srand((unsigned int)time(NULL));

            // マップ全体を初期化
            MapFormat();

            // 一時停止（ポーズを設定）
            Halt(HALT_PAUSE);

            break;

        case WM_PAINT:          // ウィンドウ再描画時
            // マップ全体の描画
            DrawMap(hMemoryDC);
            // 落下途中のブロックを描画
            DrawBlock(hMemoryDC);
            // スコア表示
            DrawScore(hMemoryDC);

            // 裏画面から実画面にコピー
            PaintDC = BeginPaint(hWnd, &ps);
            BitBlt(PaintDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                   hMemoryDC[0], 0, 0,
                   SRCCOPY );
            EndPaint(hWnd, &ps);

            break;

        case WM_COMMAND:        // コマンド入力時
            switch(LOWORD(wParam)){
                case IDM_START:                 // スタート
                    // 一時停止（ポーズを解除）
                    Halt(HALT_PAUSE_CANCEL);
                    // リトライ時の初期化
                    Prepare();

//                  ShellExecute(hWnd, NULL, "ファイルオペレーション.htm", NULL, NULL, SW_SHOWNORMAL);

//                  mciSendString("play DING.WAV",NULL,0,NULL);
//                  waveOutSetVolume( NULL, 0x1111);
                    break;

                case IDM_PAUSE:                 // ポーズ
                    // 一時停止（ポーズを設定）
                    Halt(HALT_PAUSE);
                    MessageBox(NULL, "ポーズ中。", "ポーズ", MB_OK);
                    // 一時停止（ポーズを解除）
                    Halt(HALT_PAUSE_CANCEL);

                    break;

                case IDM_END:                   // 終了
                    SendMessage(hWnd, WM_DESTROY, 0, 0L);

                    break;

                default:
                    return DefWindowProc(hWnd, msg, wParam, lParam);
            }
            break;
        case WM_TIMER:                          // 指定時間経過時
            switch(FallBlock()){
                case 1:                         // ブロックが着地
                    // スペースキーが押されているとき
                    if(OnSpaceFlag != 0){
                        // スピードを調整
                        SetTimer(hParent, ID_TIMER, SpeedConf(), NULL);
                    }
                    break;
                case 0:                         // ブロック落下中
                    // スペースキーが押されているとき
                    if(OnSpaceFlag != 0){
                        // スコアを加算
                        Score++;
                    }

                    break;
                case -1:                        // ブロックが積み上がった
                    // スペースキーが押されているとき
                    if(OnSpaceFlag != 0){
                        // スペース押下の解除
                        OnSpaceFlag = 0;
                    }
                    // ゲームオーバー
                    GameOver();

                    break;

                default:
                    break;
            }
            // 画面を再描画
            InvalidateRect(hParent ,NULL ,FALSE);

            break;
        case WM_KEYDOWN:                        // キーボードを押したとき
            // ポーズの状態を確認
            if(Halt(HALT_GETCONDITION) != HALT_PAUSE_CANCEL){
                return 0L;  //ポーズ中はキー操作無効
            }

            // 何が押されたかを確認
            switch ((int)wParam){
/***** ここから入力してください① *****/
                case VK_RIGHT:                  // →キー
                    // ブロックを右にずらす
                    BlockX++;

                    // ずらした結果重なるようであれば
                    if(CheckOverlap() == FALSE){
                        // 位置を元に戻す
                        BlockX--;
                    }else{
                        // 重ならなければ再描画
                        InvalidateRect(hWnd ,NULL ,FALSE);
                    }

                    break;

                case VK_LEFT:                   // ←キー
                    // ブロックを左にずらす
                    BlockX--;

                    // ずらした結果重なるようであれば
                    if(CheckOverlap() == FALSE){
                        // 位置を元に戻す
                        BlockX++;
                    }else{
                        // 重ならなければ再描画
                        InvalidateRect(hWnd ,NULL ,FALSE);
                    }

                    break;
/***** ここまで① *****/

                case VK_UP:                     // ↑キー
/***** ここから入力してください② *****/
                    // 方向をインクリメント
                    Vctr++;
                    // 方向が３を超えたら
                    if(Vctr > 3){
                        // ０にする
                        Vctr = 0;
                    }
/***** ここまで② *****/

                    // 落下途中用のブロック配列に新しい方向のブロックデータを格納
                    SetBlock();
                    // 回転した結果重なるようであれば
                    if(CheckOverlap() == FALSE){
                        // 方向を元に戻す
                        Vctr--;
                        if(Vctr < 0){
                            Vctr = 3;
                        }

                        // 落下途中用のブロック配列に新しい方向のブロックデータを格納
                        SetBlock();
                    }
                    else{
                        // 重ならなければ再描画
                        InvalidateRect(hWnd ,NULL ,FALSE);
                    }

                    break;

                case VK_DOWN:                   // ↓キー
/***** ここから入力してください③ *****/

                    // 方向をデクリメント
                    Vctr--;
                    // 方向が０未満になったら
                    if(Vctr < 0){
                        // ３にする
                        Vctr = 3;
                    }
/***** ここまで③ *****/

                    // 落下途中用のブロック配列に新しい方向のブロックデータを格納
                    SetBlock();
                    // 回転した結果重なるようであれば
                    if(CheckOverlap() == FALSE){
                        // 方向を元に戻す
                        Vctr++;
                        if(Vctr > 3){
                            Vctr = 0;
                        }

                        // 落下途中用のブロック配列に新しい方向のブロックデータを格納
                        SetBlock();
                    }
                    else{
                        // 重ならなければ再描画
                        InvalidateRect(hWnd ,NULL ,FALSE);
                    }
                    break;

                case VK_SPACE:                  // スペースキー
                    // スペースキーが押された状態でないとき
                    if(OnSpaceFlag == 0){
                        // 押された状態にして
                        OnSpaceFlag = 1;
                        // タイマー間隔を２０ミリ秒に縮める
                        SetTimer(hWnd, ID_TIMER, 20, NULL);
                    }

                    break;

                default:
                    return DefWindowProc(hWnd, msg, wParam, lParam);
            }
            break;

        case WM_KEYUP:                      // キーボードを離したとき
            // ポーズの状態を確認
            if(Halt(HALT_GETCONDITION) != HALT_PAUSE_CANCEL){
                return 0L;  //ポーズ中はキー操作無効
            }
            // 何が離されたかを確認
            switch ((int)wParam){
                case VK_SPACE:                  // スペースキー
                    // スペースキーを話した状態にして
                    OnSpaceFlag = 0;
                    // タイマー間隔をレベルに応じた値に設定する
                    SetTimer(hParent, ID_TIMER, SpeedConf(), NULL);

                    break;
                default:
                    break;
            }

            break;

        case WM_DESTROY:                    // ウィンドウ廃棄時
            // タイマーを解除
            KillTimer(hWnd, ID_TIMER);

            // ビットマップハンドルを開放
            DeleteObject(hBitmap[0]);
            DeleteObject(hBitmap[1]);

            // 裏画面のデバイスコンテキストを開放
            DeleteDC(hMemoryDC[0]);
            DeleteDC(hMemoryDC[1]);

            PostQuitMessage(0);

            break;
        default:    //自分で処理しないメッセージはシステムに任せる
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0L;
}

//////////////////////////////////////////////////////////
//
// 関数名：SetFont
//
// 戻り値：フォントハンドル
//
// 引　数：face - フォント名称
//
// 機　能：フォントの作成
//
//////////////////////////////////////////////////////////
HFONT SetFont(LPCTSTR face)
{
    HFONT hFont;

    // フォントを作成
    hFont = CreateFont(0,                       // フォント高さ
                       0,                       // 文字幅
                       0,                       // テキストの角度
                       0,                       // ベースラインとｘ軸との角度
                       FW_REGULAR,              // フォントの重さ（太さ）
                       FALSE,                   // イタリック体
                       FALSE,                   // アンダーライン
                       FALSE,                   // 打ち消し線
                       SHIFTJIS_CHARSET,        // 文字セット
                       OUT_DEFAULT_PRECIS,      // 出力精度
                       CLIP_DEFAULT_PRECIS,     // クリッピング精度
                       PROOF_QUALITY,           // 出力品質
                       FIXED_PITCH | FF_MODERN, // ピッチとファミリー
                       face);                   // 書体名

    return hFont;
}

//////////////////////////////////////////////////////////
//
// 関数名：ShowLastError
//
// 戻り値：なし
//
// 引　数：なし
//
// 機　能：ＡＰＩのエラー情報を表示
//
//////////////////////////////////////////////////////////
void ShowLastError(void)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0,
        NULL);
    MessageBox(NULL, (char*)lpMsgBuf, "ErrorMessage", MB_OK);
    LocalFree(lpMsgBuf);
}

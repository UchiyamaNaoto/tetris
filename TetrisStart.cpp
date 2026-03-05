#include <windows.h>

#include "resource.h"

#include "TetrisDef.h"
#include "TetrisGble.h"
#include "TetrisPro.h"

//////////////////////////////////////////////////////////
//
// 関数名：Prepare
//
// 戻り値：なし
//
// 引　数：なし
//
// 機　能：リトライ時の初期化
//
//////////////////////////////////////////////////////////
void Prepare(void)
{
	// タイマーを設定（１０００ミリ秒）
	if(SetTimer(hParent, ID_TIMER, 1000, NULL) == 0){
		// APIエラー表示
		ShowLastError();
	}

	// マップ全体を初期化
	MapFormat();

	// 新しいブロックを生成
	NewBlock();

	// スコア、消したライン、レベル、速度調整用レベルを初期化
	Score		= 0;
	Lines		= 0;
	Level		= 0;
	SubLevel	= 0;

	// 画面を再描画
	InvalidateRect(hParent, NULL, FALSE);
}

//////////////////////////////////////////////////////////
//
// 関数名：Halt
//
// 戻り値：現在の状態
//
// 引　数：Switch - 指定方法
//
// 機　能：一時停止
//
//////////////////////////////////////////////////////////
int Halt(int Switch)
{
	static int Condition;		// 現在の状態

	switch (Switch){
		case HALT_PAUSE_CANCEL:		// 一時停止を解除
			Condition = HALT_PAUSE_CANCEL;
			
			// タイマーを設定（現在のレベルの状態で）
			SetTimer(hParent, ID_TIMER, SpeedConf(), NULL);

			// メニューの「ポーズ」を有効化
			EnableMenuItem(GetMenu(hParent), IDM_PAUSE, MF_ENABLED);
			
			break;

		case HALT_PAUSE:			// 一時停止を設定
			Condition = HALT_PAUSE;

			// タイマーを解除
			KillTimer(hParent, ID_TIMER);

			// メニューの「ポーズ」を無効化
			EnableMenuItem(GetMenu(hParent), IDM_PAUSE, MF_GRAYED);
			
			break;
	}

	return Condition;
}

//////////////////////////////////////////////////////////
//
// 関数名：GameOver
//
// 戻り値：なし
//
// 引　数：なし
//
// 機　能：ゲームオーバー
//
//////////////////////////////////////////////////////////
void GameOver(void)
{
	// 一時停止（ポーズ設定）
	Halt(HALT_PAUSE);

	// ゲームオーバー表示
	MessageBox(hParent, "ゲームオーバー！", "ゲーム制作", MB_OK | MB_ICONEXCLAMATION);

	// リトライメッセージを表示
	if(MessageBox(hParent, "リトライしますか？", "確認", MB_YESNO | MB_ICONQUESTION) == IDYES){
		// 一時停止（ポーズを解除）
		Halt(HALT_PAUSE_CANCEL);

		// リトライ時の初期化
		Prepare();
	}else{
		// ウィンドウ破棄メッセージを送信
		SendMessage(hParent, WM_DESTROY, 0, 0L);
	}
}

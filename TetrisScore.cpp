#include <windows.h>

#include "TetrisDef.h"
#include "TetrisGble.h"
#include "TetrisPro.h"

//////////////////////////////////////////////////////////
//
// 関数名：CalcScore
//
// 戻り値：なし
//
// 引　数：DelLineNum - 消したライン数
//
// 機　能：スコア加算
//
//////////////////////////////////////////////////////////
void CalcScore(int DelLineNum)
{
	// 消したライン数を加算する
	Lines += DelLineNum;

	// 消したライン数によって得点を振り分ける
	switch(DelLineNum){
		case 1:				// １行
			Score += 40;
			break;
		case 2:				// ２行
			Score += 100;
			break;
		case 3:				// ３行
			Score += 300;
			break;
		case 4:				// ４行
			Score += 1200;
			break;
		default:
			break;
	}
}

//////////////////////////////////////////////////////////
//
// 関数名：SpeedConf
//
// 戻り値：タイマー間隔
//
// 引　数：なし
//
// 機　能：速度計算
//
//////////////////////////////////////////////////////////
int SpeedConf(){
	int Interval;

	switch(Level){
		case 0:
		case 1:
	        Interval = 1000 - SubLevel * 350;
			break;
		case 2:
		case 3:
			Interval = 800 - SubLevel * 300;
			break;
		case 4:
		case 5:
			Interval = 600 - SubLevel * 220;
			break;
		case 6:
		case 7:
			Interval = 400 - SubLevel * 140;
			break;
		case 8:
		case 9:
			Interval = 300 - SubLevel * 100;
			break;
		case 10:
		case 11:
			Interval = 300 - SubLevel * 105;
			break;
		default:
			Interval = 300 - SubLevel * 110;
	}

	return Interval;
}

//////////////////////////////////////////////////////////
//
// 関数名：Effect
//
// 戻り値：なし
//
// 引　数：DelY - 消去ラインのＹ座標配列
//
// 機　能：消去したときの演出効果
//
//////////////////////////////////////////////////////////
void Effect(int *DelY){
	int i, j, k;
	RECT rc;

	//この時点ではスコア領域を更新しないように設定
	rc.left	  = DEFMAP_X * 16;
	rc.top	  = DEFMAP_Y * 16;
	rc.right  = (DEFMAP_X + 10) * 16;
	rc.bottom = (DEFMAP_Y + 21) * 16;

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			FallingBlock[i][j] = 0;	// FallingBlockは表示させない
		}
	}

	// ４回点滅させる
	for(k = 0; k < 4; k++){
		for(i = 0; i < 4; i++){
			if(DelY[i] != 0){
				for(j = DEFMAP_X; j < DEFMAP_X + 10; j++){
					Map[j][DelY[i]] = 6 + k % 2;	// 青、または白を描く
				}
			}
		}

		// 画面を再描画
		InvalidateRect(hParent ,&rc ,FALSE);
		UpdateWindow(hParent);
		
		// 点滅の間隔は３０ミリ秒
		Sleep(30);
	}
}
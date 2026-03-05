#include <windows.h>

#include "TetrisDef.h"
#include "TetrisGble.h"
#include "TetrisPro.h"

//////////////////////////////////////////////////////////
//
// 関数名：MapFormat
//
// 戻り値：なし
//
// 引　数：なし
//
// 機　能：マップ全体を初期化
//
//////////////////////////////////////////////////////////
void MapFormat(void)
{
	int i, j;

	// まず全体を「８」（壁）で埋める
	for(i = 0; i < 12; i++){
		for(j = 0; j < 27; j++){
			Map[i][j] = 8;
		}
	}

	// その後、内側を「０」（なにもなし）で埋める
	for(i = DEFMAP_X; i < 10 + DEFMAP_X; i++){
		for(j = 1; j < 26; j++){
			Map[i][j] = 0;
		}
	}
}

//////////////////////////////////////////////////////////
//
// 関数名：DeleteCheck
//
// 戻り値：消去可能行数
//
// 引　数：なし
//
// 機　能：消去可能かチェック
//
//////////////////////////////////////////////////////////
int DeleteCheck(void)
{
	int DelY[4] = {0};
	int n, ChkLine, DelLineNum = 0;
	int i, j;

	// 縦棒の時だけ4列目まで調べる
	if(Type == 0){
		ChkLine = 4;
	}else{
		ChkLine = 3;
	}

	// ブロックの位置から調査行数分チェックする
	for(i = BlockY; i < BlockY + ChkLine; i++){
		n = 0;
		// 横１列分ループ
		for(j = DEFMAP_X; j < DEFMAP_X + 10; j++){
			// 対象ブロックが「なにもなし」または「壁」以外の場合
			if((Map[j][i] > 0) && (Map[j][i] < 8)){
				// ブロック数をインクリメント
				n++;
			}else{
				break;
			}
		}
		// ブロック数が１０（１列分）カウントされたとき
		if(n == 10){
			// 消える行目のｙ座標を設定
			DelY[DelLineNum] = i;
			// 消えた行数をインクリメント
			DelLineNum++;
		}
	}

	// 消去可能となったとき
	if(DelLineNum != 0){
		// 消去したときの演出効果
		Effect(DelY);
		
		// 消去可能な行を
		for(i = 0; i < 4; i++){
			if(DelY[i] != 0){
				// ブロック消去する
				DeleteLine(DelY[i]);
			}
		}
	}

	// 消去可能な行数を返す
	return DelLineNum;
}

//////////////////////////////////////////////////////////
//
// 関数名：DeleteLine
//
// 戻り値：なし
//
// 引　数：DelY - 消去行Ｙ座標
//
// 機　能：ブロックを消去
//
//////////////////////////////////////////////////////////
void DeleteLine(int DelY)
{
	int i;

	for(; DelY > DEFMAP_Y + 1; DelY--){
		for(i = DEFMAP_X; i < DEFMAP_X + 10; i++){
			// １行上のマップデータを持ってくる
			Map[i][DelY] = Map[i][DelY - 1];
		}
	}
}

//////////////////////////////////////////////////////////
//
// 関数名：CheckOverlap
//
// 戻り値：TRUE  - 重ならない
//         FALSE - 重なる
//
// 引　数：なし
//
// 機　能：ブロックの重なりチェック
//
//////////////////////////////////////////////////////////
BOOL CheckOverlap(void)
{
	int i, j;

	// 範囲外エラーになるので、縦棒は場合分け
	if((Type == 0) && ((Vctr % 2) == 1) && (BlockX == 9)){
		return FALSE;
	}

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			// 今落ちているブロックがある場合
			if(FallingBlock[i][j] != 0){
				// 次の位置のブロックがあれば
				if(Map[BlockX + i][BlockY + j] != 0){
					// 重なっているとする
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}

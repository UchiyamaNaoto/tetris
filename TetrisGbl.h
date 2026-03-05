// グローバル変数の宣言

HWND		hParent;				// メインウィンドウのハンドル
HINSTANCE	hInst;					// インスタンスハンドル

int			Block[7][4][4][4]={0};	// メモリからコピーするブロックの場所。種類、方向、4×4マップのX座標、Y座標
int			Map[12][27]={0};		// 仮想マップ

int			FallingBlock[4][4];		// 落ちる過程のブロックデータ


int			Score;					// スコア
int			Lines;					// 消したライン数
int			Level;					// レベル
int			SubLevel;				// 速度調整用レベル

int			BlockX;					// 落下途中のブロック左上位置
int			BlockY;					// 落下途中のブロック左上位置

int			Type;					// ブロックの種類
int			Vctr;					// ブロックの方向

int			OnSpaceFlag;			// スペースキーの状態

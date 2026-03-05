// グローバル変数の宣言（外部宣言）

extern	HWND		hParent;				// メインウィンドウのハンドル
extern	HINSTANCE	hInst;					// インスタンスハンドル

extern	int			Block[7][4][4][4];		//メモリからコピーするブロックの場所。種類、方向、4×4マップのX座標、Y座標
extern	int			Map[12][27];			// 仮想マップ

extern	int			FallingBlock[4][4];		// 落ちる過程のブロックデータ


extern	int			Score;					// スコア
extern	int			Lines;					// 消したライン数
extern	int			Level;					// レベル
extern	int			SubLevel;				// 速度調整用レベル

extern	int			BlockX;					// 落下途中のブロック左上位置
extern	int			BlockY;					// 落下途中のブロック左上位置

extern	int			Type;					// ブロックの種類
extern	int			Vctr;					// ブロックの方向

extern	int			OnSpaceFlag;			// スペースキーの状態

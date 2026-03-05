// 各関数のプロトタイプ宣言


// ウィンドウ関数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// APIエラー表示
void ShowLastError(void);
// スコア表示のフォントをセット
HFONT SetFont(LPCTSTR);


// ウィンドウクラスの登録
BOOL InitApp(HINSTANCE, LPCSTR);
// ウィンドウの生成
BOOL InitInstance(HINSTANCE, LPCSTR, int);


// ブロックデータを配列に格納
void DefaultBlock(void);
// 新しいブロックを生成
void NewBlock(void);
// 落下途中用のブロック配列に新しいブロックデータを格納
void SetBlock(void);
// 次のブロックを表示
void SetNext(void);
// ブロックを落下
int FallBlock(void);
// 着地したブロックをマップに固定
void FixBlock(void);


// 裏画面用のメモリ領域を作成
BOOL MakeBitmap(HDC *, HBITMAP *, DWORD, DWORD);
// ブロックイメージをメモリにロード
BOOL LoadBitmapImage(HDC *, HBITMAP *, LPCSTR);


// マップ全体を初期化
void MapFormat(void);
// 消去可能かチェック
int DeleteCheck(void);
// ブロックを消去
void DeleteLine(int);
// ブロックの重なりチェック
BOOL CheckOverlap(void);


// リトライ時の初期化
void Prepare(void);
// 一時停止
int Halt(int);
// ゲームオーバー
void GameOver(void);


// マップ全体の描画
void DrawMap(HDC *);
// 落下途中のブロックを描画
void DrawBlock(HDC *);
// スコア表示
void DrawScore(HDC *);


// スコア加算
void CalcScore(int);
// 速度計算
int SpeedConf(void);
// 消去したときの演出効果
void Effect(int *);






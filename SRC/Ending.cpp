//======================================================================================//
//
//							ゲームプログラム
//
//======================================================================================//
#include		<windows.h>
#include		<stdio.h>
#include		<math.h>
#include		"MASTER/Ci-Lib.H"
#include		"Game.H"

//****************************************************************************
//	■	定義
//
//****************************************************************************

//****************************************************************************
//	■	内部使用　変数
//
//****************************************************************************


//--------------------------------------------------------------------------//
//	●	初期化		：シーンに移る時一回、変数の初期化
//
//--------------------------------------------------------------------------//
void	EndingInit(void)
{

}

//--------------------------------------------------------------------------//
//	●	内部処理	：シーン中の処理、現在のシーンで行う処理
//
//--------------------------------------------------------------------------//
// ゲームメインループ
void	EndingLoop(void)
{

	if (Gs_GetKEYtrg(kKEYENTER)) {
		SceneChange(TITLE_SCENE);
	}

}

//--------------------------------------------------------------------------//
//	●	描画		：シーン中の描画、現在のシーンで表示するBMPはここで
//
//--------------------------------------------------------------------------//
// ゲーム画面　描画
void	EndingDraw(void)
{

	Gs_DrawText(50,300,"Win",ARGB(255,200,200,100));

}

//--------------------------------------------------------------------------//
//	●	ロード		：シーンに入る時、そのシーンで必要なデータの読み込み
//
//--------------------------------------------------------------------------//
short	EndingLoad(void)
{

	return		ENDING_SCENE;
}

//--------------------------------------------------------------------------//
//	●	後処理		：現在のシーンから抜ける時、データの破棄
//
//--------------------------------------------------------------------------//
void	EndingExit(void)
{

}

//****************************************************************************
//	★　シーンテーブル：各シーンで呼び出される関数の登録
//****************************************************************************

SCENE_TBL	EndingSceneTbl = {
		EndingLoad,
		EndingInit,
		EndingLoop,
		EndingDraw,
		EndingExit
};

//======================================================================================//
//							EOP															//
//======================================================================================//
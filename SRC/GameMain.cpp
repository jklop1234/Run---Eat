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
#include		"Lib/Misc.h"

//****************************************************************************
//	■	定義
//
#define			Ball_H   64
#define			Ball_W	 64	
#define			Wall_H   64
#define			Wall_W	 64
#define			Ar_H	 64
#define			Ar_W	 64	
#define			PLAY_SPEED 4.0f


//****************************************************************************
typedef	struct{
	short	Rot;
	float	Px,Py;
	float	Dx,Dy;
	float	Speed;

}AR;

typedef	struct{
	short	Rot;
	float	Px,Py;
	float	Dx,Dy;
	float	Speed;

}BALL;

typedef	struct{
	short	Rot;
	float	Px,Py;
	float	Dx,Dy;
	float	Speed;

}WALL;


typedef	struct{
	float	Px,Py;

}BOX;


	
//****************************************************************************
//	■	内部使用　変数
//
//****************************************************************************
GsTEXTURE		Ar;
GsTEXTURE		Item;
GsTEXTURE		WA;
GsTEXTURE		Kabe;
GsTEXTURE		BG_Main;
GsTEXTURE		BLOCK;
GsTEXTURE		MAP;
GsTEXTURE		TREE;
GsTEXTURE	    MONSTER;


AR				ar;
BALL			Ball;
BOX				Box;
short			Item_Flg;
WALL			Wall;
short			KABE[12];
float			Ai_Rot;
short			Walk_Flg;
short			run;
float			Chr1_AnmPtn;
float			Chr1_AnmCnt;
short			count;







//--------------------------------------------------------------------------//
//	●	初期化		：シーンに移る時一回、変数の初期化
//
//--------------------------------------------------------------------------//
void	GameInit(void)
{


	//self
	ar.Px = 700.0f;
	ar.Py = 560.0f;
	ar.Dx =0.0f;
	ar.Dy =0.0f;
	ar.Rot = 0;
	ar.Speed=1.0f;

	//monster
	Ball.Px= 0;
	Ball.Py= 0;
	Ball.Dx =1.5f;
	Ball.Dy=1.5f;
	Ball.Rot=0;

	//item
	Box.Px = 600;
	Box.Py = 400;
	
	Item_Flg  = ON;

	Wall.Px  = 600;
	Wall.Py  = 360;
	Walk_Flg = OFF;

	//背景
	for(short i = 0; i<12; i=i+1){
		KABE[i] = i;
	}
		Chr1_AnmCnt		 = 0;
	Chr1_AnmPtn      =0;
	count  = 0;
}

//--------------------------------------------------------------------------//
//	●	内部処理	：シーン中の処理、現在のシーンで行う処理
//
//--------------------------------------------------------------------------//
// ゲームメインループ
void	GameLoop(void)
{
	
	
	//キャラの画面限界

	if(ar.Px>=800-Ar_W/2){
		ar.Px = 800-Ar_W/2;
	}
	if(ar.Py>=600-Ar_H/2){
		ar.Py = 600-Ar_H/2;
	}
	if(ar.Px<=Ar_W/2){
		ar.Px = Ar_W/2;
	}
	if(ar.Py<=Ar_H){
		ar.Py = Ar_H;
	}
	ar.Dx = 0;
	ar.Dy = 0;

	//キャラの移動量----4方向（4种状态0,1,2,3）


	run = 65535;  //移动状态（初始状态）
	if	(Gs_GetKEY(kKEYLEFT))
	{    run = 0;
		count = count +1;
		Chr1_AnmPtn = 1;
	}
		
	 if	(Gs_GetKEY(kKEYRIGHT))
	{    run = 1;
		count = count +1;
		Chr1_AnmPtn = 2;
		
	}
	
	
	if	(Gs_GetKEY(kKEYUP))
	{run = 2;
	count = count +1;
		Chr1_AnmPtn = 3;
	}
	 if	(Gs_GetKEY(kKEYDOWN))
	{run =3;
	 Chr1_AnmPtn = 0;
	count = count +1;
		}

	  if(run ==0)ar.Dx = -PLAY_SPEED;
		if(run ==1)ar.Dx = PLAY_SPEED;
			if(run ==2)ar.Dy =	-PLAY_SPEED;
				if(run ==3)ar.Dy =	+PLAY_SPEED;

	 //10帧之后变一个动作，之后帧数重计
	 if(count>=10) 
	 {
		 count = 0;
		  Chr1_AnmCnt		 = Chr1_AnmCnt+1;
	 }

			
	// 当动作变第四个的时候归零  LOOP
	 if(Chr1_AnmCnt>=4) 
	 {Chr1_AnmCnt = 0;}


	

	//キャラクター当たり判定（自キャラ）
	if	( (ar.Px - 32 < Wall.Px + 32 + 1) && (ar.Px + 32 > Wall.Px - 32 - 1) && (ar.Py - 32 < Wall.Py + 10) && (ar.Py + 32 > Wall.Py - 10) )
	{
	}
	ar.Px = ar.Px + ar.Dx;
	ar.Py = ar.Py + ar.Dy;

//接近すると加速
	if	(LEN_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py) < 300)
	{
		//Box is important than player
		 if	(LEN_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py) <= 150)
		{
			Ball.Dx = ROUND_X(AngleConvert(DIR_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py)),6.0f,0);
			Ball.Dy = ROUND_Y(AngleConvert(DIR_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py)),6.0f,0);
		}
		else if	(LEN_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py) <= 100)
		{
			Ball.Dx = ROUND_X(AngleConvert(DIR_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py)),4.5f,0);
			Ball.Dy = ROUND_Y(AngleConvert(DIR_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py)),4.5f,0);
		}
		else if	(LEN_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py) <= 200)
		{
			Ball.Dx = ROUND_X(AngleConvert(DIR_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py)),3.0f,0);
			Ball.Dy = ROUND_Y(AngleConvert(DIR_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py)),3.0f,0);
		}
		else
		{
			Ball.Dx = ROUND_X(AngleConvert(DIR_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py)),1.5f,0);
			Ball.Dy = ROUND_Y(AngleConvert(DIR_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py)),1.5f,0);
		}
	}
	else	//索敵範囲外（アイテムを食う）
	{
		if	(LEN_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py) <= 1000)	//sqrt(800^2+600^2)=1000,that means box is in screen
		{
			Ball.Dx = ROUND_X(AngleConvert(DIR_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py)),1.5f,0);
			Ball.Dy = ROUND_Y(AngleConvert(DIR_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py)),1.5f,0);
		}
		else
		{
			Ball.Dx = ROUND_X(AngleConvert(DIR_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py)),1.0f,0);
			Ball.Dy = ROUND_Y(AngleConvert(DIR_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py)),1.0f,0);
		}
	}
//Feel Ai（敵）
//Need to be fixed
	if	(Ball.Px-32<Wall.Px+32+1&&Ball.Px+32>Wall.Px-32-1&&Ball.Py-32<Wall.Py+10&&Ball.Py+32>Wall.Py-10)
//上は当たり判定
	{
		Ai_Rot = DIR_AtoB(Wall.Px,Wall.Py,Ball.Px,Ball.Py);
		Ball.Py = ROUND_Y(Ai_Rot,LEN_AtoB(Wall.Px,Wall.Py,Ball.Px,Ball.Py)+3,Wall.Py);
		Ball.Px = ROUND_X(Ai_Rot,LEN_AtoB(Wall.Px,Wall.Py,Ball.Px,Ball.Py)+3,Wall.Px);
	}
	else
	{
		Ball.Px = Ball.Px - Ball.Dx;
		Ball.Py = Ball.Py - Ball.Dy;
	}
//画面限界
	if(Ball.Px>800-Ball_W/2){
		Ball.Px = 800-Ball_W/2;
	}
	else if(Ball.Px<Ball_W/2){
		Ball.Px=Ball_W/2;
	}

	if(Ball.Py>600-Ball_H/2){
		Ball.Py=600-Ball_H;
	}
	else if(Ball.Py<Ball_H/2){
		Ball.Py=Ball_H;
	}
//Eat Box
	if(LEN_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py)<32)
	{
		Item_Flg = OFF;
		Box.Px = 65535;
		Box.Py = 65535;
	}
//画面転換
	if (Gs_GetKEYtrg(kKEYENTER))
	{
		SceneChange(ENDING_SCENE);
	}
//Debug
	DEB_TEXT("%d",Ball.Dx);
}

//--------------------------------------------------------------------------//
//	●	描画		：シーン中の描画、現在のシーンで表示するBMPはここで
//
//--------------------------------------------------------------------------//
// ゲーム画面　描画
void	
GameDraw(void)
{
	//Background
	Gs_DrawLayer(400,300,BG_Main,0,0,800,600,NO,ARGB(255,255,255,255),ON,0,1.0f,1.0f);
	//敵
	Gs_DrawLayer(I(Ball.Px),I(Ball.Py),MONSTER,64,0,Ball_W,Ball_H,NO,ARGB(255,255,255,255),ON,Ball.Rot,1.0f,1.0f);
	//自キャラ
	Gs_DrawLayer(I(ar.Px),I(ar.Py),Ar,Chr1_AnmCnt*32,Chr1_AnmPtn*32,32,32,NO,ARGB(254,255,255,255),ON,ar.Rot,1.0f,1.0f);
	//道具
	if	(Item_Flg == ON)
	{
		Gs_DrawLayer(I(Box.Px),I(Box.Py),Item,0,0,Ar_W/2,Ar_H/2,NO,ARGB(255,255,255,255),ON,0,1.0f,1.0f);
	}
	//壁（罠-8）
	Gs_DrawLayer(I(Wall.Px),I(Wall.Py),WA,0,8,64,24,NO,ARGB(255,255,255,255),ON,0,1.0f,1.0f);
	//Statue
	//Gs_DrawLayer(104,200,BLOCK,0,0,32,64,OFF,ARGB(255,255,255,255),ON,0,1.0f,1.0f);
	//TREE
	for(short i=0; i<40;i =i++ ){
		Gs_DrawLayer(0+(i*34),0,TREE,0,0,32,64,NO,ARGB(255,255,255,0),ON,0,1.0f,1.0f);
	}
	
	

}

//--------------------------------------------------------------------------//
//	●	ロード		：シーンに入る時、そのシーンで必要なデータの読み込み
//
//--------------------------------------------------------------------------//
short	GameLoad(void)
{						
	
	Ar =  Gs_LoadBMP("DATA/BMP/kyara3.PNG");
	MONSTER  = Gs_LoadBMP("DATA/BMP/PN.PNG");
	Item = Gs_LoadBMP("DATA/BMP/BOX.PNG");
	WA = Gs_LoadBMP("DATA/BMP/Wall.PNG");
	Kabe = Gs_LoadBMP("DATA/BMP/KABE.PNG");
	BG_Main = Gs_LoadBMP("DATA/BMP/BG_MAIN.PNG");
	BLOCK = Gs_LoadBMP("DATA/BMP/Block.PNG");
	MAP =	Gs_LoadBMP("DATA/BMP/Map.PNG");
	TREE =	Gs_LoadBMP("DATA/BMP/TREE.PNG");

	return		GAME_SCENE;
}

//--------------------------------------------------------------------------//
//	●	後処理		：現在のシーンから抜ける時、データの破棄
//
//--------------------------------------------------------------------------//
void	GameExit(void)
{
		Gs_ReleaseBMP(Ar);
		Gs_ReleaseBMP(Item);

}


//****************************************************************************
//	★　シーンテーブル：各シーンで呼び出される関数の登録
//****************************************************************************

SCENE_TBL	GameSceneTbl = {
		GameLoad,
		GameInit,
		GameLoop,
		GameDraw,
		GameExit
};

//======================================================================================//
//							EOP															//
//======================================================================================//
//======================================================================================//
//
//							�Q�[���v���O����
//
//======================================================================================//
#include		<windows.h>
#include		<stdio.h>
#include		<math.h>
#include		"MASTER/Ci-Lib.H"
#include		"Game.H"

//****************************************************************************
//	��	��`
//
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
	float	Px,Py;

}BOX;


	
//****************************************************************************
//	��	�����g�p�@�ϐ�
//
//****************************************************************************
GsTEXTURE		Ar;
GsTEXTURE		Item;

AR				ar;
BALL			Ball;
BOX				Box;
short			Item_Flg;





//--------------------------------------------------------------------------//
//	��	������		�F�V�[���Ɉڂ鎞���A�ϐ��̏�����
//
//--------------------------------------------------------------------------//
void	GameInit(void)
{		ar.Px = 320.0f;
		ar.Py = 240.0f;
		ar.Dx =0.0f;
		ar.Dy =0.0f;
		ar.Rot = 0;
		ar.Speed=1.0f;
		Ball.Px= 0;
		Ball.Py= 0;
		Ball.Dx =1.5f;
		Ball.Dy=1.5f;
		Ball.Rot=0;
		Box.Px = 600;
		Box.Py = 400;
}

//--------------------------------------------------------------------------//
//	��	��������	�F�V�[�����̏����A���݂̃V�[���ōs������
//
//--------------------------------------------------------------------------//
// �Q�[�����C�����[�v
void	GameLoop(void)
{
	/*if(ar.Px>=640-32){
		ar.Dx=-ar.Dx;
	}
	if(ar.Py>=480-32){
		ar.Dy=-ar.Dy;
	}
	if(ar.Px<32){
		ar.Dx=-ar.Dx;
	}
	if(ar.Py<32){
		ar.Dy=-ar.Dy;
	}

*/
	
	ar.Px = ar.Px+ar.Dx;
	ar.Py = ar.Py+ar.Dy;
	if (Gs_GetKEYtrg(kKEYLEFT)) {
		ar.Dx =ar.Dx-1.0f;
	}
	if (Gs_GetKEYtrg(kKEYRIGHT)) {
		ar.Dx =ar.Dx+1.0f;
	}
	
	if (Gs_GetKEYtrg(kKEYUP)) {
		ar.Dy =ar.Dy-1.0f;
	}
	
	if (Gs_GetKEYtrg(kKEYDOWN)) {
		ar.Dy =ar.Dy+1.0f;
	}

	if (Gs_GetKEYtrg(kKEYENTER)) {
		SceneChange(ENDING_SCENE);
	}
	if (Gs_GetKEYtrg(kKEYSPACE)) {
		ar.Rot = 0;
	}
	if(LEN_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py)<=64)
	{SceneChange(ENDING_SCENE);
	}





	
//�{�[����P��ǂ������܂�
	
	Ball.Dx= ROUND_X(DIR_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py),1.0f,0);
	Ball.Dy= ROUND_Y(DIR_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py),1.0f,0);

	Ball.Px = Ball.Px - Ball.Dx;
	Ball.Py = Ball.Py -	Ball.Dy;


//����
	if(Ball.Px>=640-32){
		Ball.Dx=-Ball.Dx;
	}
	if(Ball.Py>=480-32){
		Ball.Dy=-Ball.Dy;
	}
	if(Ball.Px<32){
		Ball.Dx=-Ball.Dx;
	}
	if(Ball.Py<32){
		Ball.Dy=-Ball.Dy;
	}




        //�ڋ߂���Ɖ���
	
		 if(LEN_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py)<=240)
		 {
		 Ball.Px = Ball.Px - Ball.Dx-Ball.Dx/100;
		 Ball.Py = Ball.Py - Ball.Dy-Ball.Dy/100;
	     }
		  else//���G�͈͊O
		  { if(LEN_AtoB(ar.Px,ar.Py,Ball.Px,Ball.Py)>240){
		 Ball.Dx= ROUND_X(DIR_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py),1.5f,0);
		 Ball.Dy= ROUND_Y(DIR_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py),1.5f,0);
		 Ball.Px = Ball.Px - Ball.Dx;
		 Ball.Py = Ball.Py - Ball.Dy;
	       if(LEN_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py)<180){
		 Ball.Dx= ROUND_X(DIR_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py),2.5f,0);
		 Ball.Dy= ROUND_Y(DIR_AtoB(Box.Px,Box.Py,Ball.Px,Ball.Py),2.5f,0);
		 Ball.Px = Ball.Px - Ball.Dx;
		 Ball.Py = Ball.Py - Ball.Dy;
	      }
		 }
		 
		 }


	
	
	



	


	
	DEB_TEXT("%d",ar.Speed);
}

//--------------------------------------------------------------------------//
//	��	�`��		�F�V�[�����̕`��A���݂̃V�[���ŕ\������BMP�͂�����
//
//--------------------------------------------------------------------------//
// �Q�[����ʁ@�`��
void	
GameDraw(void)
{	Gs_DrawLayer(I(Ball.Px),I(Ball.Py),Ar,64,0,64,64,NO,ARGB(255,255,255,255),ON,Ball.Rot,1.0f,1.0f);
	Gs_DrawLayer(I(ar.Px),I(ar.Py),Ar,0,0,64,64,NO,ARGB(255,255,255,255),ON,ar.Rot,1.0f,1.0f);
	Gs_DrawLayer(I(Box.Px),I(Box.Py),Item,0,0,32,32,NO,ARGB(255,255,255,255),ON,0,1.0f,1.0f);

	


}

//--------------------------------------------------------------------------//
//	��	���[�h		�F�V�[���ɓ��鎞�A���̃V�[���ŕK�v�ȃf�[�^�̓ǂݍ���
//
//--------------------------------------------------------------------------//
short	GameLoad(void)
{						
	
	Ar =  Gs_LoadBMP("DATA/BMP/PN.PNG");
	Item = Gs_LoadBMP("DATA/BMP/BOX.PNG");

	return		GAME_SCENE;
}

//--------------------------------------------------------------------------//
//	��	�㏈��		�F���݂̃V�[�����甲���鎞�A�f�[�^�̔j��
//
//--------------------------------------------------------------------------//
void	GameExit(void)
{
		Gs_ReleaseBMP(Ar);
		Gs_ReleaseBMP(Item);

}


//****************************************************************************
//	���@�V�[���e�[�u���F�e�V�[���ŌĂяo�����֐��̓o�^
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

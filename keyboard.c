#include <stdio.h>
#include <stdlib.h>
#include "acllib.h"
#include "main.h"
/* ===== 键盘事件：按 R 启动游戏+重开+控制方向 ===== */
void keyEvent(int key,int event)
{
	if (event!=KEY_DOWN)return;
	/* 音乐 */
	if(key=='L')
	{
		vox=!vox;
	}
	/* 说明书 */
	if(key=='M')
	{
		spe=!spe;
	}
	/* 选择模式 */
	if(pattern==0&&select_j==0&&pause==0&&gameOver==-1&&prop==0)
	{
		if(key=='5')
		{
			pattern_i=5;
			pattern=1;
		}
		if(key=='6')
		{
			pattern_i=6;
			pattern=1;
		}
		if(key=='7')
		{
			pattern_i=7;
			pattern=1;
		}
	}
	/* 选择道具 */
	if(pattern==1&&select_j==0&&pause==0&&gameOver==-1&&prop==0)
	{
		if(key=='C')
		{
			prop_i[5]=5;
		}
		if(key=='V')
		{
			prop_i[6]=6;
		}
		if(key=='B')
		{
			prop_i[7]=7;
		}
		if(key=='N')
		{
			prop=1;
		}
	}

	/* 选择难度 */
	if(select_j==0&&pause==0&&pattern==1&&gameOver==-1&&prop==1)
	{
		if(key=='1')
		{
			select_i=0;
			reset(select_i);
			select_j=1;
		}
		if(key=='2')
		{
			select_i=6;
			reset(select_i);
			select_j=1;
		}
		if(key=='3')
		{
			select_i=15;
			reset(select_i);
			select_j=1;
		}	
	}

	//暂停 
	if(key==27&&gameOver==1&&select_j==1&&pattern==1)
	{
		pause=!pause;
	}
	/* 玩家1控制方向 */	
	if(pause==1&&gameOver==1&&select_j==1&&pattern==1)
	{
		if(key=='W'&&dy!=MOVE)
		{
			dx=0;
			dy=-MOVE;
		}
		else if(key=='S'&&dy!=-MOVE)
		{
			dx=0;
			dy=MOVE;
		}
		else if(key=='A'&&dx!=MOVE)
		{
			dx=-MOVE;
			dy=0;
		}
		else if(key=='D'&&dx!=-MOVE)
		{
			dx=MOVE;
			dy=0;
		}		
	}
	/* 玩家2控制方向 */
	if(pause==1&&gameOver==1&&select_j==1&&pattern==1&&pattern_i==6)
	{
		if((key==38||key==104)&&dy_t!=MOVE)
		{
			dx_t=0;
			dy_t=-MOVE;
		}
		else if((key==40||key==98)&&dy_t!=-MOVE)
		{
			dx_t=0;
			dy_t=MOVE;
		}
		else if((key==37||key==100)&&dx_t!=MOVE)
		{
			dx_t=-MOVE;
			dy_t=0;
		}
		else if((key==39||key==102)&&dx_t!=-MOVE)
		{
			dx_t=MOVE;
			dy_t=0;
		}
	}
	/* 重启/开始 */
    if (key=='R'&&gameOver!=1&&pause==0&&select_j==1&&pattern==1)
    {
    	gameOver=1;
    	pause=1; 
    	if(prop_i[7]==7)
    	{
    		ai_time=0;				
			ai_time_f=0;
			player2_time=0;
			player2_time_f=0;
			player1_time=0;
			player1_time_f=0;	
		}
    	if(pattern_i==7)
    	{
    	 	ai_reset();  		
		}
    	if(pattern_i==6)
    	{
    	 	reset_t(select_i);  		
		}		
 		reset(select_i);
    }
    if (key=='4'&&(pause==0||gameOver==0)&&pattern==1&&select_j==1)
    {
        select_j=0;      /* 回菜单 */
    	gameOver=-1;     /* 菜单状态（显示难度选择） */
    	pause=0;         /* 暂停（不移动） */
    	prop=0;
    	pattern=0;
    }  
}

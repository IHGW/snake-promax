#include <stdio.h>
#include <stdlib.h>
#include "acllib.h"
#include "main.h"
/* ===== 定时器：每 16ms 一次，负责"动"和"画" ===== */
void timerEvent(int id)
{
	/* ===== 受伤闪光 ===== */
	if(flash>0)
	{
		flash--;
	}
	if(flash_t>0)
	{
		flash_t--;
	}
	if(ai_flash>0)
	{
		ai_flash--;
	}
	
	static int bgm=-1;
	int tag;
	if(vox==0)tag=0;
	else if(gameOver==1)tag=1;
	else tag=2;
	if(tag!=bgm)
	{
		if(tag==0)
		{
			PlaySound(NULL,NULL,0);
		}
		else if(tag==1)
		{
			PlaySound("bgm_game.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
		}
		else 
		{
			PlaySound("bgm.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
		}
		bgm=tag;
	}
	
	if(pause)
	{
		/* 记录"现在过了多少帧" */
		tick++;
		if(score_m%3==0&&score_m!=0)
		{
			life++;
			score_m=0;
		}
		if(score_t_m%3==0&&score_t_m!=0)
		{
			life_t++;
			score_t_m=0;
		}
		if(ai_score_m%3==0&&ai_score_m!=0)
		{
			ai_life++;
			ai_score_m=0;
		}
		while(speed_x>=3&&speed>1)
		{
			speed--;
			speed_x=speed_x-3;
			if(wall<18&&prop_i[5]==5)
			{
				wall=wall+3;
				wall_j=0;			
			}
			if(door<4&&prop_i[6]==6)
			{
				door=door+1;
				door_j=0;			
			}
			if(mys<9&&prop_i[7]==7)
			{
				mys++;
				mys_j=0;			
			}
		}
		/* 生成障碍物坐标 */
		if(wall_j!=1&&prop_i[5]==5)
		{
			for(tamp=0;tamp<wall;tamp++)
			{
				wallX[tamp]=(rand()%28+1)*MOVE;   //对齐网格 
				wallY[tamp]=(rand()%28+1)*MOVE;
				if(gen_ins(wallX[tamp],wallY[tamp],5)==0)
				{
					tamp--;
				}
			}
			wall_j=1;
		}
		/* 生成神秘小道具坐标 */
		if(mys_j!=1&&prop_i[7]==7)
		{
			int k; 
    		for(tamp_j=0;tamp_j<10;tamp_j++)
   	 		for(k=0;k<4;k++)
       			 mysX[tamp_j][k]=mysY[tamp_j][k]=0;
			for(tamp=0;tamp<mys;tamp++)
			{
				mys_m=rand()%4;
				mysX[tamp][mys_m]=(rand()%28+1)*MOVE;   //对齐网格 
				mysY[tamp][mys_m]=(rand()%28+1)*MOVE;
				if(gen_ins(mysX[tamp][mys_m],mysY[tamp][mys_m],7)==0)
				{
					tamp--;
				}
			}
			mys_j=1;
		}
		/* 生成门的坐标 */
		if(door_j!=1&&prop_i[6]==6)
		{
			for(tamp=0;tamp<door;tamp++)
			{
				doorX[tamp][0]=(rand()%28+1)*MOVE;   //对齐网格 
				doorY[tamp][0]=(rand()%28+1)*MOVE;
				doorX[tamp][1]=(rand()%28+1)*MOVE;   //对齐网格 
				doorY[tamp][1]=(rand()%28+1)*MOVE;
				if((gen_ins(doorX[tamp][0],doorY[tamp][0],6)||gen_ins(doorX[tamp][1],doorY[tamp][1],6))==0)
				{
					tamp--;
				}
			}
			door_j=1;
		}
		/* AI */
		if(pattern_i==7&&gameOver==1)
		{
			if(ai_time>0)
			{
				ai_time--;
				ai(speed/2);
			}
			else if(ai_time_f>0)
			{
				ai_time_f--;
				ai(speed*2);
			}
			else
			{
				ai(speed);
			}
		}
   		/* --- 只有在游戏进行中，才更新位置 --- */
   		if (gameOver==1)
   		{
   			//玩家2 
   			if(pattern_i==6)
   			{
    			if(player2_time>0)
				{
					player2_time--;
					player2(speed/2);
				}
				else if(player2_time_f>0)
				{
					player2_time_f--;
					player2(speed*2);
				}
				else
				{
					player2(speed);
				}				
			}
			//玩家1 
    		if(player1_time>0)
			{
				player1_time--;
				player1(speed/2);
			}
			else if(player1_time_f>0)
			{
				player1_time_f--;
				player1(speed*2);
			}
			else
			{
				player1(speed);
			}
		}
    }

    /* --- 不管结没结束，都要画（不然结束画面出不来）--- */
    beginPaint();
    clearDevice();               /* 先清屏（必须第一句） */
    
    /* 游戏选择模式文字 */
    if (pattern==0&&select_j==0&&pause==0&&gameOver==-1&&prop==0&&spe==0)
    {
        setTextColor(RED);
        setTextSize(SIZE-20);
        paintText(170,170, "CHOICE MODEL");
        setTextSize(SIZE-30);
        paintText(190,220, "请选择模式：");
        paintText(200,260, "单人游戏(5)");
        paintText(200,290, "双人模式(6)");
        paintText(200,320, "AI对战(7)");
    }
    
    /* 游戏选择道具文字 */
    if (select_j==0&&pattern==1&&pause==0&&gameOver==-1&&prop==0&&spe==0)
    {
        setTextColor(RED);
        setTextSize(SIZE-20);
        paintText(170,170, "SELECT PROP");
        setTextSize(SIZE-30);
        paintText(190,220, "请选择道具：");
        paintText(200,250, "障碍物(C)");
        paintText(200,280, "传送门(V)");
        paintText(200,310, "神秘小道具(B)");
        paintText(200,340, "无(N)");
        if(prop_i[5]==5)
        {
        	paintText(180,250, "O");
		}
		else
		{
			paintText(180,250, "X");
		}
		
		if(prop_i[6]==6)
        {
        	paintText(180,280, "O");
		}
		else
		{
			paintText(180,280, "X");
		}
		
		if(prop_i[7]==7)
        {
        	paintText(180,310, "O");
		}
		else
		{
			paintText(180,310, "X");
		}
    }
    
    /* 游戏选择难度文字 */
    if (select_j==0&&pattern==1&&pause==0&&gameOver==-1&&prop==1&&spe==0)
    {
        setTextColor(RED);
        setTextSize(SIZE-20);
        paintText(120,170, "SELECT DIFFICULTY");
        setTextSize(SIZE-30);
        paintText(140,220, "请按下对应难度的数字：");
        paintText(230,250, "难度1");
        paintText(230,280, "难度2");
        paintText(230,310, "难度3");
    }
    
	/* 游戏开始文字 */
    if (gameOver==-1&&select_j==1&&pattern==1&&pause==0&&prop==1&&spe==0)
    {
        setTextColor(RED);
        setTextSize(SIZE);
        paintText(160,170, "GAME START");
        setTextSize(SIZE-20);
        paintText(210,260, "按 R 开始");
    }
    
    /* 游戏暂停文字 */
    if (pause==0&&select_j==1&&gameOver==1&&pattern==1&&prop==1&&spe==0)
    {
        setTextColor(RED);
        setTextSize(SIZE);
        paintText(170,180, "GAME PAUSE");
        setTextSize(SIZE-20);
        paintText(210,260, "按 ESC 继续");
        paintText(210,300, "选择难度？(4)");
        paintText(210,340, "说明书(M)");
    }
    /* 游戏说明书 */
	if(spe==1&&pause==0)
	{
		setTextColor(RED);
        setTextSize(SIZE-20);
        paintText(170,180, "INSTRUCTAIN:");
        setTextSize(SIZE-30);
        paintText(110,240, "（红色）玩家1：WASD控制");
        paintText(110,280, "（黑色）玩家2：右键盘8426控制");
        paintText(110,320, "		按L关闭音乐");
        paintText(110,360, "		按ESC暂停游戏/重新选择难度");
        paintText(110,360, "		神秘小道具：加血/扣血/加速/减速");
	}
	/* 音乐开 */
	if(vox==1)
	{
		setBrushColor(BLACK);
		setPenWidth(3);
		rectangle(540, 15, 550, 30);
		POINT mouth[4] = {{550,15}, {550,30}, {560,35}, {560,10}};
		polygon(mouth, 4);	
		arc(570,10,580,35,575,10,575,35);
		arc(580,5,600,40,590,5,590,40);
		setPenWidth(1);
	}
    /* 音乐关 */
	if(vox==0)
	{
		setBrushColor(BLACK);
		setPenWidth(3);
		POINT mouth[4] = {{550,15}, {550,30}, {560,35}, {560,10}};
		polygon(mouth, 4);	
		rectangle(540, 15, 550, 30);	
		line(570,12,590,32);
		line(590,12,570,32);
		setPenWidth(1);
	}
    /* 游戏结束文字 */
    if (gameOver==0&&select_j==1&&pattern==1&&pause==0&&prop==1&&spe==0)
    {
    	
        setTextColor(RED);
        setTextSize(SIZE);
        paintText(170,180, "GAME OVER");
        setTextSize(SIZE-20);
        paintText(180,260, "按 R 重新开始");
        paintText(180,300, "选择难度？(4)");
    }
    
    /* 分数 / 生命 */
    {
        char buf1[64];
        char buf2[64];
        char buf3[64];
        setTextColor(BLACK);
        setTextSize(20);		     
        sprintf(buf1, "Life: %d   Speed: %d   Score: %d   Highscore: %d", life, speed_j-speed+1, score, highscore);
        paintText(10,10,buf1);
		if(pattern_i==6)
		{
        	sprintf(buf2, "Life_t: %d   Score_t: %d   Highscore_t: %d",life_t,score_t,highscore_t);			
			paintText(10,40,buf2);
		}
   		if(pattern_i==7)
   		{
   			sprintf(buf3, "AI_life: %d   AI_Score: %d", ai_life, ai_score);
   			paintText(10,70,buf3);
		}
    }
    
    if(gameOver==1)
    {
    	/* 小零食 */
    	setBrushColor(YELLOW);
    	rectangle(foodX-10,foodY-10,foodX+10,foodY+10);
    	/* 障碍物 */
    	if(prop_i[5]==5)
    	{
    		setBrushColor(RGB(128,128,128));
			for(tamp=0;tamp<wall;tamp++)
			{
				rectangle(wallX[tamp]-10,wallY[tamp]-10,wallX[tamp]+10,wallY[tamp]+10);	
			}
		}
		//门 
		if(prop_i[6]==6)
		{
			setBrushColor(GREEN);
			for(tamp=0;tamp<door;tamp++)
			{
				ellipse(doorX[tamp][0]-13,doorY[tamp][0]-13,doorX[tamp][0]+13,doorY[tamp][0]+13);
				ellipse(doorX[tamp][1]-13,doorY[tamp][1]-13,doorX[tamp][1]+13,doorY[tamp][1]+13);			
			}
		}
		/* 神秘道具 */
    	if(prop_i[7]==7)
    	{
    		setBrushColor(MAGENTA);
			for(tamp=0;tamp<mys;tamp++)
			{
				for(tamp_j=0;tamp_j<4;tamp_j++)
				{
					if(mysX[tamp][tamp_j]!=0)
					{
						rectangle(mysX[tamp][tamp_j]-10,mysY[tamp][tamp_j]-10,mysX[tamp][tamp_j]+10,mysY[tamp][tamp_j]+10);	
					}
				}
				
			}
		}
		/* 玩家1贪吃蛇的身体 */
		if(flash>0&&(flash/3)%2==0)
		setBrushColor(WHITE);
		else
		setBrushColor(RED);
		for(tamp=0;tamp<length;tamp++)
		{
			rectangle(snakeX[tamp]-10,snakeY[tamp]-10,snakeX[tamp]+10,snakeY[tamp]+10);	
		}
		/* 玩家2贪吃蛇的身体 */
		if(pattern_i==6)
		{
			if(flash_t>0&&(flash_t/3)%2==0)
			setBrushColor(WHITE);
			else
			setBrushColor(BLACK);
			for(tamp=0;tamp<length_t;tamp++)
			{
				rectangle(snakeX_t[tamp]-10,snakeY_t[tamp]-10,snakeX_t[tamp]+10,snakeY_t[tamp]+10);
			}			
		}
		/* AI贪吃蛇的身体 */			
		if(pattern_i==7)
		{
			if(ai_flash>0&&(ai_flash/3)%2==0)
			setBrushColor(WHITE);
			else
			setBrushColor(BLUE);
			for(tamp=0;tamp<ai_length;tamp++)
			{
				rectangle(ai_X[tamp]-10,ai_Y[tamp]-10,ai_X[tamp]+10,ai_Y[tamp]+10);
			}			
		}
		
	}

    endPaint();
}

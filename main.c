#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "acllib.h"
#include "main.h"

/* ===== 全局变量：整个程序共享 ===== */
int ballX=400,ballY=200;   		/* 玩家1贪吃蛇头的位置 */
int length=3;					/* 玩家1贪吃蛇身体的长度 */
int snakeX[600],snakeY[600];	/* 玩家1贪吃蛇身体的最大长度 */
int dx=MOVE,dy=0;     		    /* 玩家1贪吃蛇每次移动的步长（速度） */
int score=0;        	        /* 玩家1得分 */
int highscore=0;             	/* 玩家1最高得分 */
int life=1;     	            /* 玩家1生命 */
int score_m=0;					/* 玩家1增加生命 */
int flash=0;					/* 玩家1闪光 */

int length_t=3;					/* 玩家2贪吃蛇身体的长度 */
int snakeX_t[600],snakeY_t[600];/* 玩家2贪吃蛇身体的最大长度 */
int dx_t=MOVE,dy_t=0;     		/* 玩家2贪吃蛇每次移动的步长（速度） */
int score_t=0;                	/* 玩家2得分 */
int highscore_t=0;            	/* 玩家2最高得分 */
int life_t=1;                 	/* 玩家2生命 */
int score_t_m=0;				/* 玩家2增加生命 */
int flash_t=0;					/* 玩家2闪光 */

int ai_length=3;				/* AI贪吃蛇身体的长度 */
int ai_X[600],ai_Y[600];		/* AI贪吃蛇身体的最大长度 */
int ai_dx=MOVE,ai_dy=0;    		/* AI贪吃蛇每次移动的步长（速度） */
int ai_score=0;               	/* AI得分 */
int ai_life=1;                	/* AI生命 */
int ai_score_m=0;				/* AI增加生命 */
int ai_flash=0;					/* AI闪光 */

int foodX,foodY;				/* 小零食 */
int tamp;						/* 循环的工具 */
int tamp_j;						/* 循环的工具 */
int tick=1;						/* 记录"现在过了多少帧" */
int speed_x=0;					/* 每三个影响一次SPEED */
int speed=10;					/* 蛇的速度 */
int speed_j=10;					/* 蛇的初始速度 */
int select_i=0;					/* 保存难度 */
int pattern_i=0;				/* 模式保存 */
int spe=0;						/* 说明书 */
int vox=1;						/* 声音 */

int prop_i[10];		  			/* 保存道具 */
int wallX[20],wallY[20];		/* 障碍物坐标 */
int wall;						/* 障碍物数量 */
int wall_j=0;					/* 障碍物的标志 */
int door=1;						/* 门的数量 */
int door_j=0;					/* 门的标志 */
int doorX[20][2];				/* 门0的坐标 */
int doorY[20][2];				/* 门1的坐标 */
int mysX[10][4],mysY[10][4];	/* 神秘物品坐标 */
int mys=3;						/* 神秘物品数量 */
int mys_m=-1;					/* 神秘物品编号(0-3) */
int ai_time;					/* AI神秘物品加速 */
int ai_time_f;					/* AI神秘物品减速 */
int player2_time;				/* 玩家2神秘物品加速 */
int player2_time_f;				/* 玩家2神秘物品减速 */
int player1_time;				/* 玩家1神秘物品加速 */
int player1_time_f;				/* 玩家1神秘物品减速 */
int mys_j;						/* 神秘物品的标志 */

int gameOver=-1;           		/* 0 = 游戏结束  -1=游戏开始  1=游戏进行*/
int pause=0;					/* 1 = 运行 */
int select_j=0;					/* 选择难度(666系统还不给我用select) */
int pattern=0;					/* 1=选择模式*/
int prop=0;						/* 1=选择道具*/

int Setup()
{
	
	FILE *fp1=fopen("highscore.txt","r");
	if (fp1!=NULL)          /* 文件可能不存在 → 必须检查 */
	{
 	   fscanf(fp1,"%d",&highscore);
 	   fclose(fp1);
	}
	FILE *fp2=fopen("highscore_t.txt","r");
	if (fp2!=NULL)          /* 文件可能不存在 → 必须检查 */
	{
 	   fscanf(fp2,"%d",&highscore_t);
 	   fclose(fp2);
	}
	srand((unsigned)time(NULL));
	initWindow("贪吃蛇",100,100,GRID_COLS,GRID_ROWS);
	snakeX[0]=ballX;
	snakeY[0]=ballY;
	snakeX[1]=ballX-20;
	snakeY[1]=ballY;
	snakeX[2]=ballX-40;
	snakeY[2]=ballY;
	food_ceate();
    registerKeyboardEvent(keyEvent);
    registerTimerEvent(timerEvent);
	startTimer(1,10);
	return 0;
}

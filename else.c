#include <stdio.h>
#include <stdlib.h>
#include "acllib.h"
#include "main.h"

void food_ceate()
{
	/* 生成食物 */
	foodX=(rand()%28+1)*MOVE;   //对齐网格 
	foodY=(rand()%28+1)*MOVE;
}
 
void reset(int speed_dz)				//重置玩家1一些乱七八糟的数值 
{
	    snakeX[0]=ballX;
        snakeY[0]=ballY;
       	snakeX[1]=ballX-20;
		snakeY[1]=ballY;
		snakeX[2]=ballX-40;
		snakeY[2]=ballY;
		for(tamp=3;tamp<score+3;tamp++)
		{
			snakeX[tamp]=-1000;	/* 隐藏到屏幕外 */
			snakeY[tamp]=-1000;
		}
        food_ceate();
        length=3;
        dx=MOVE;
        dy=0;
        score=0;
        score_m=0;
        life=1;
        speed_x=speed_dz;					
		speed=10;
		wall=rand()%3+3;
		mys=rand()%3+3;
    	door=1;
    	wall_j=0;
    	door_j=0;
    	mys_j=0;
}
void reset_t(int speed_dz)				//重置玩家2一些乱七八糟的数值 
{
	snakeX_t[0]=400;
    snakeY_t[0]=160;
    snakeX_t[1]=380;
	snakeY_t[1]=160;
	snakeX_t[2]=360;
	snakeY_t[2]=160;
	for(tamp=3;tamp<score_t+3;tamp++)
	{
		snakeX_t[tamp]=-1000;	/* 隐藏到屏幕外 */
		snakeY_t[tamp]=-1000;
	}
    food_ceate();
    dx_t=MOVE;
    dy_t=0;
    length_t=3;
    score_t=0;
    score_t_m=0;
    life_t=1;
}
void ai_reset()
{
	ai_length=3;
	ai_life=1;
	ai_X[0]=60;
	ai_Y[0]=60;
    ai_X[1]=ai_X[0]-20;
	ai_Y[1]=ai_Y[0];
	ai_X[2]=ai_X[0]-40;
	ai_Y[2]=ai_Y[0];
	for(tamp=3;tamp<ai_score+3;tamp++)
	{
	ai_X[tamp]=-1000;			/* 隐藏到屏幕外 */
	ai_Y[tamp]=-1000;
	}
	ai_score=0;
	ai_score_m=0;
}
//通用检查 (只拿来检查一个道具) 
int gen_ins(int x,int y,int sign)
{
	for(tamp_j=0;tamp_j<length;tamp_j++)              
	{
		if((x==foodX&&y==foodY)||((abs(x-snakeX[tamp_j])<=3*MOVE)&&(abs(y-snakeY[tamp_j])<=3*MOVE)))   
		{
			return 0;
		}        
	}
	if(pattern_i==6)
	{
		for(tamp_j=0;tamp_j<length_t;tamp_j++)
		{
			if((abs(x-snakeX_t[tamp_j])<=2*MOVE)&&(abs(y-snakeY_t[tamp_j])<=2*MOVE))
			{
				return 0;
			}						
		}
	}
	if(pattern_i==7)
	{
		for(tamp_j=0;tamp_j<ai_length;tamp_j++)
		{
			if((abs(x-ai_X[tamp_j])<=2*MOVE)&&(abs(y-ai_Y[tamp_j])<=2*MOVE))
			{
				return 0;							
			}
		}
	}
	if(prop_i[5]==5&&sign!=5)
	{
		for(tamp_j=0;tamp_j<wall;tamp_j++)
		{
			if(x==wallX[tamp_j]&&y==wallY[tamp_j])
			{
				return 0;
			}
		}
	}
	if(prop_i[6]==6&&sign!=6)
	{
		for(tamp_j=0;tamp_j<door;tamp_j++)
		{
			if((x==doorX[tamp_j][0]&&y==doorY[tamp_j][0])||(x==doorX[tamp_j][0]&&y==doorY[tamp_j][0]))
			{
				return 0;
			}
		}
	}
	int k=0;
	if(prop_i[7]==7&&sign!=7)
	{
		for(tamp_j=0;tamp_j<mys;tamp_j++)
		{
			for(k=0;k<4;k++)
			{
				if(x==mysX[tamp_j][k]&&y==mysY[tamp_j][k])
				{
					return 0;
				}
			}

		}
	}
	return 1;
}
void ai_move()
{
	int max=99999,best_x,best_y,ds=0;
	int move[4][2]={{0,MOVE},{MOVE,0},{0,-MOVE},{-MOVE,0}};//下，左，上，右
	for(tamp=0;tamp<4;tamp++)
	{
		int k=1;
		int x=ai_X[0]+move[tamp][0];
		int y=ai_Y[0]+move[tamp][1];
		if(x<10||x>590||y<10||y>590)continue;//撞墙检测 
		for(tamp_j=1;tamp_j<ai_length;tamp_j++)//自撞检测 
		{
			if(x==ai_X[tamp_j]&&y==ai_Y[tamp_j])
			{
				k=0;
				break;
			}
		}
		if(!k)continue;
       	for(tamp_j=0;tamp_j<length;tamp_j++)//撞击玩家 
       	{
       		if(abs(x-snakeX[tamp_j])<15&&abs(y-snakeY[tamp_j])<15)
       		{
       			k=0;
       			break;
			}
       	}
       	if(!k)continue;
       	for(tamp_j=0;tamp_j<wall;tamp_j++)//撞击障碍物 
       	{
       		if(abs(x-wallX[tamp_j])<15&&abs(y-wallY[tamp_j])<15)
       		{
       			k=0;
       			break;
			}
       	}       	
		if(!k)continue;
		int x_y=abs(x-foodX)+abs(y-foodY);
		if(x_y<max)
		{
			max=x_y;
			best_x=move[tamp][0];
			best_y=move[tamp][1];
			ds=1;
		}
	}
	if(ds==1)
	{
		ai_dx=best_x;
		ai_dy=best_y;	
	}
}
void door_prop(int *x,int *y)//门、给头坐标 
{
    for(tamp=0;tamp<door;tamp++)
    {
    	if (*x==doorX[tamp][0]&&*y==doorY[tamp][0])
    	{
    		*x=doorX[tamp][1];
    		*y=doorY[tamp][1];
    		break;
   		}
       	if (*x==doorX[tamp][1]&&*y==doorY[tamp][1])
       	{
       			*x=doorX[tamp][0];
       			*y=doorY[tamp][0];
       			break;
       	}       			
	}
}
//AI
void ai(int speed_i)
{
	if(tick%speed_i==0)
	{
		ai_move();	
		/* 1. AI蛇身的移动 */
    	for(tamp=ai_length-1;tamp>0;tamp--)
    	{
    		ai_X[tamp]=ai_X[tamp-1];
    		ai_Y[tamp]=ai_Y[tamp-1];	
		}
			
		/* 1. AI蛇头的移动 */
       	ai_X[0]+=ai_dx;
       	ai_Y[0]+=ai_dy;
       	
       	/* 2. AI贪吃蛇碰到小零食 → 吃掉 + 加分 */
       	if (ai_X[0]==foodX&&ai_Y[0]==foodY)
       	{
			food_ceate();
       		ai_score++;
       		ai_score_m++;
       	    ai_length++;
       	    speed_x++;
       	}
       	/* 2. AI贪吃蛇碰到障碍物 → 扣命 */
       	if(prop_i[5]==5)
       	{
       		for(tamp=0;tamp<wall;tamp++)
       		{
       			if(ai_X[0]==wallX[tamp]&&ai_Y[0]==wallY[tamp])
       			{
					ai_life--;
					if(!ai_flash)
       				{
       					ai_flash=20;
					}
					if(ai_life<1)
       				{
       					ai_reset();
       					break;
					}
       			}
			}       			
		}
		/* 2. AI贪吃蛇碰到门 → 传送 */
       	if(prop_i[6]==6)
       	{
		   door_prop(&ai_X[0],&ai_Y[0]);   			
		}
		/* 2. AI贪吃蛇碰到神秘道具0/1/2 → 加血/加速/减速 */
		if(prop_i[7]==7) 
		{
			mys_prop(ai_X[0],ai_Y[0],&ai_life,&ai_time,&ai_time_f,&ai_flash);
		}
       	/* 2. AI贪吃蛇碰到玩家 → 死亡 */
       	for(tamp=0;tamp<length;tamp++)
       	{
       		if(abs(ai_X[0]-snakeX[tamp])<20&&abs(ai_Y[0]-snakeY[tamp])<20)
       		{
       			ai_life--;
       			if(!ai_flash)
       			{
       				ai_flash=20;
				}
       			life++;
       			if(ai_life<1)
       			{
       				ai_reset();
       				break;
				}
				break;
			}
       	}
       	/* 2. AI贪吃蛇碰到玩家 → 杀死玩家 */
       	for(tamp=0;tamp<ai_length;tamp++)
       	{
       		if(abs(snakeX[0]-ai_X[tamp])<20&&abs(snakeY[0]-ai_Y[tamp])<20)
       		{
				life--;
				if(!flash)
       			{
       				flash=20;
				}
				ai_life++;
				if(life<1)
				{
					pause=0; 
      	      	  	gameOver=0;
					break;						
				}
				break;
			}
		}
       	/* 3. AI蛇碰到自己 → 重生 */
		for(tamp=1;tamp<ai_length;tamp++)
		{
			if(ai_X[0]==ai_X[tamp]&&ai_Y[0]==ai_Y[tamp])
			{
				ai_life--;
				if(!ai_flash)
       			{
       				ai_flash=20;
				}
				if(ai_life<1)
				{
					ai_reset();
       		  		break;						
				}
				break;
			}
		}
			
		/* 3. AI蛇碰到边界 → 重生 */
       	if (boundary(ai_X[0],ai_Y[0]))
       	{
			ai_reset();
  	   	}
	}
}
//神秘道具 
void mys_prop(int x,int y,int *life,int *time,int *time_f,int *flash_j)
{
	for(tamp=0;tamp<mys;tamp++)
    {
    	if (x==mysX[tamp][0]&&y==mysY[tamp][0])
    	{
    		(*life)++;
    		mysX[tamp][0]=0;
    		mysY[tamp][0]=0;
   		}
   		if (x==mysX[tamp][3]&&y==mysY[tamp][3])
    	{
    		(*life)--;
    		mysX[tamp][3]=0;
    		mysY[tamp][3]=0;
       		if(!*flash_j)
       		{
       			*flash_j=20;
			}
			if ((*life)<1)         
  			{
   		     	gameOver=0;
    		    pause=0;
  			}
   		}
       	if (x==mysX[tamp][1]&&y==mysY[tamp][1])
       	{
       		*time=200;
       		mysX[tamp][1]=0;
    		mysY[tamp][1]=0;
       	}     
		if(x==mysX[tamp][2]&&y==mysY[tamp][2])
		{
			*time_f=200;
			mysX[tamp][2]=0;
    		mysY[tamp][2]=0;
		}  			
	}
}
void player2(int speed_i)
{
	if(tick%speed_i==0)
	{
		/* 1. 玩家2蛇身的移动 */
    	for(tamp=length_t-1;tamp>0;tamp--)
    	{
    		snakeX_t[tamp]=snakeX_t[tamp-1];
    		snakeY_t[tamp]=snakeY_t[tamp-1];	
		}
    
       	/* 1. 玩家2蛇头的移动 */
       	snakeX_t[0]+=dx_t;
       	snakeY_t[0]+=dy_t;
       		
       	/* 2. 玩家2贪吃蛇碰到小零食 → 吃掉 + 加分 */
       	if (snakeX_t[0]==foodX&&snakeY_t[0]==foodY)
       	{
			food_ceate();
       		score_t_m++;
       	    length_t++; 
       	    speed_x++; 
       	    if(score_t>highscore_t)
       	    {
     	    	highscore_t=score_t;
       	    	FILE*fp=fopen("highscore_t.txt","w");
       	    	if(fp!=NULL)
       	    	{
       	    		fprintf(fp,"%d",highscore_t);
       	    		fclose(fp);
				}
			}
   		}
       	/* 2. 玩家2贪吃蛇碰到障碍物 → 扣命 */
       	if(prop_i[5]==5)
       	{
          	for(tamp=0;tamp<wall;tamp++)
       		{
       			if (snakeX_t[0]==wallX[tamp]&&snakeY_t[0]==wallY[tamp])
       			{
					life_t--;
					if(!flash_t)
       				{
       					flash_t=20;
					}
					if(life_t<1)
       				{
	        		    gameOver=0;
        		    	pause=0;
        		    	break;
					}
					break;
       			}
			}   				
		}
		/* 2. 玩家2贪吃蛇碰到门 → 传送 */
       	if(prop_i[6]==6)
       	{
		   door_prop(&snakeX_t[0],&snakeY_t[0]);   			
		}
		/* 2. 玩家2贪吃蛇碰到神秘道具0/1/2 → 加血/加速/减速 */
		if(prop_i[7]==7) 
		{
			mys_prop(snakeX_t[0],snakeY_t[0],&life_t,&player2_time,&player2_time_f,&flash_t);
		}
  		/* 3. 玩家2蛇碰到自己 → 结束 */
		for(tamp=1;tamp<length_t;tamp++)
		{
			if(snakeX_t[0]==snakeX_t[tamp]&&snakeY_t[0]==snakeY_t[tamp])
			{
				life_t--;
				if(!flash_t)
       			{
       				flash_t=20;
				}
				if(life_t<1)
				{
	   			    gameOver=0;
     		    	pause=0;
					break;						
				}
      		    break;
			}
		}
			
       	/* 3. 玩家2蛇碰到边界 → 扣命 / 结束 */
       	if (boundary(snakeX_t[0],snakeY_t[0]))
       	{
      	    pause=0;
      	    gameOver=0;
  	   	}  
  	    		
		/* 2. 玩家1贪吃蛇碰到玩家2 → 死亡/杀死玩家(1/2) */
       	for(tamp=0;tamp<length_t;tamp++)
       	{
			if((abs(snakeX[0]-snakeX_t[tamp])<20&&abs(snakeY[0]-snakeY_t[tamp])<20))                                  
       		{
				life--;
				if(!flash)
      			{
       				flash=20;
				}
				life_t++;
				if(life<1)
				{
					pause=0;
      	        	gameOver=0;
					break;						
				}
				break;
			}
       	}
		/* 2. 玩家2贪吃蛇碰到玩家1 → 死亡/杀死玩家(1/2) */
       	for(tamp=0;tamp<length;tamp++)
       	{
			if(abs(snakeX_t[0]-snakeX[tamp])<20&&abs(snakeY_t[0]-snakeY[tamp])<20)                                
       		{
				life_t--;
				if(!flash_t)
       			{
       				flash_t=20;
				}
				life++;
				if(life_t<1)
				{
	    	        gameOver=0;	
					pause=0;
					break;					
				}
				break;
			}
       	}  
			
	}
}
void player1(int speed_i)
{
	if(tick%speed_i==0)
	{
		/* 1. 玩家1蛇身的移动 */
    	for(tamp=length-1;tamp>0;tamp--)
    	{
    		snakeX[tamp]=snakeX[tamp-1];
    		snakeY[tamp]=snakeY[tamp-1];	
		}
    		
       	/* 1. 玩家1蛇头的移动 */
       	snakeX[0]+=dx;
       	snakeY[0]+=dy;
       	
       	/* 2. 玩家1贪吃蛇碰到小零食 → 吃掉 + 加分 */
       	if (snakeX[0]==foodX&&snakeY[0]==foodY)
       	{
			food_ceate();
       		score++;
       		score_m++;
       	    length++; 
       	    speed_x++; 
       	    if(score>highscore)
       	    {
       	    	highscore=score;
       	    	FILE*fp=fopen("highscore.txt","w");
       	    	if(fp!=NULL)
       	    	{
       	    		fprintf(fp,"%d",highscore);
       	    		fclose(fp);
				}
			}
       	}
       	/* 2. 玩家1贪吃蛇碰到障碍物 → 扣命 */
       	if(prop_i[5]==5)
       	{
          	for(tamp=0;tamp<wall;tamp++)
       		{
       			if (snakeX[0]==wallX[tamp]&&snakeY[0]==wallY[tamp])
       			{
					life--;
					if(!flash)
       				{
       					flash=20;
					}
					if(life<1)
       				{
	      		 	    gameOver=0;
        		   		pause=0;
        			   	break;
					}
       			}
			}   			
		}
		/* 2. 玩家1贪吃蛇碰到门 → 传送 */
       	if(prop_i[6]==6)
       	{
		   door_prop(&snakeX[0],&snakeY[0]);   			
		}
		/* 2. 玩家1贪吃蛇碰到神秘道具0/1/2 → 加血/加速/减速 */
		if(prop_i[7]==7) 
		{
			mys_prop(snakeX[0],snakeY[0],&life,&player1_time,&player1_time_f,&flash);
		}
  		/* 3. 玩家1蛇碰到自己 → 结束 */
		for(tamp=1;tamp<length;tamp++)
		{
			if(snakeX[0]==snakeX[tamp]&&snakeY[0]==snakeY[tamp])
			{
				life--;
				if(!flash)
       			{
       				flash=20;
				}
				if(life<1)
				{
        		    gameOver=0;
        		    pause=0;
					break;						
				}
				break;
			}
		}
			
       	/* 3. 玩家1蛇碰到边界 → 扣命 / 结束 */
       	if (boundary(snakeX[0],snakeY[0]))
       	{
      		pause=0;
      	    gameOver=0;
  	   	}
	}
}

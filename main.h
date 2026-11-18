#ifndef _MAIN_h_
#define _MAIN_h_

#define GRID_COLS 600
#define GRID_ROWS 600
#define MOVE 20
#define SIZE 60
#define boundary(x,y) ((x)<10||(x)>590||(y)<10||(y)>590)

/* ===== 全局变量：整个程序共享 ===== */
//玩家1 
extern int ballX,ballY;  
extern int length;				
extern int snakeX[600],snakeY[600];
extern int dx,dy;        
extern int score;  
extern int highscore; 
extern int life; 
extern int score_m;
extern int flash;
//玩家2 
extern int length_t;				
extern int snakeX_t[600],snakeY_t[600];
extern int dx_t, dy_t;     
extern int score_t;              
extern int highscore_t;  
extern int life_t;  
extern int score_t_m;
extern int flash_t;        
//公共变量	          
extern int foodX,foodY;		    
extern int tamp;
extern int tamp_j;					
extern int tick;					
extern int speed_x;
extern int speed; 
extern int speed_j;
extern int select_j;
extern int select_i;
extern int spe;
extern int vox;
//道具 
extern int prop_i[10];
extern int wallX[20],wallY[20];
extern int wall;
extern int wall_j;
extern int door;
extern int door_j;
extern int doorX[20][2];			
extern int doorY[20][2];
extern int mysX[10][4],mysY[10][4];	
extern int mys;					
extern int mys_m;				
extern int ai_time;
extern int ai_time_f;
extern int player2_time;
extern int player2_time_f;
extern int player1_time;
extern int player1_time_f;
extern int mys_j;			
//AI 
extern int ai_length;			
extern int ai_X[600],ai_Y[600];	
extern int ai_dx, ai_dy;    
extern int ai_score;               
extern int ai_life;
extern int ai_score_m;
extern int ai_flash;
//控制按键
extern int gameOver; 
extern int pause;
extern int pattern_i;
extern int pattern;	
extern int prop;			
//函数			              
void keyEvent(int key, int event);
void timerEvent(int id);
void food_ceate();
void reset(int speed_dz);
void reset_t(int speed_dz); 
void ai_reset();
void ai_move();
int gen_ins(int x,int y,int sign);
void door_prop(int *x,int *y);
void ai(int speed_i);
void player1(int speed_i);
void player2(int speed_i);
void mys_prop(int x,int y,int *life,int *time,int *time_f,int *flash_j);
// 音乐

#endif

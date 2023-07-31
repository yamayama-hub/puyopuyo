/* 
    キャラクタ移動プログラム
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>


#define LOCATE(x,y)	gotoxy( (x)+1, (y)+1 )	/* conio.hが必要 */
#define CLS()		system( "cls" )		/* stdlib.hが必要 */
#define MIN 1               //最小値
#define COL 15              //縦(y)
#define ROW 8               //横(x)
#define SPACE 0             //空間
#define WALL 1              //壁
#define RED 2               //ぷよの色
#define BLUE 3              //ぷよの色
#define GREEN 4             //ぷよの色
#define YELLOW 5            //ぷよの色   
#define MAGENTA 6           //ぷよの色   

int xp = 7;         //キャラクタのX座標
int yp = 2;         //キャラクタのY座標
int xx = 7;         //キャラクタのX座標(移動前の座標)
int yy = 2;         //キャラクタのY座標(移動前の座標)
int xp2 = 9;        //キャラクタ2のX座標
int yp2 = 2;        //キャラクタ2のY座標
int xx2 = 9;        //キャラクタ2のX座標(移動前の座標)
int yy2 = 2;        //キャラクタ2のY座標(移動前の座標)
int counter = 0;    //移動回数
int wcounter = 0;   //壁にぶつかった回数
int area[ROW][COL]; //盤面
int ch = 0;         //入力キー
int save;           //二値返還
int rotation = 1;       //回転

/* キャラクター表示 */
void display_character()
{
    LOCATE(xp, yp);
    textcolor(YELLOW);
    cprintf("●");
}

/* キャラクター消去 */
void erase_character()
{
    LOCATE(xx, yy);
    textcolor(YELLOW);
    cprintf("　");
}

/* 情報表示 */
void display_information()
{
    LOCATE(1, COL + 1);
    textcolor(WHITE);
    cprintf("(%02d,%02d) COUNTER:%8d WCOUNTER:%8d",xp,yp,counter,wcounter);
}

/* キャラクターの行動 */
void character_move()
{
    if(kbhit()){
        ch = getch();
        switch(ch){
            case '6' : 
                if(area[xp2+2][yp2] == 0)
                {xp2+=2; area[xp2][yp2] = area[xp2-2][yp2]; area[xp2-2][yp2] = 0;
                 xp+=2; area[xp][yp] = area[xp-2][yp]; area[xp-2][yp] = 0; } break;
            case '4' : 
                if(area[xp-2][yp] == 0)
                {xp-=2; area[xp][yp] = area[xp+2][yp]; area[xp+2][yp] = 0;
                 xp2-=2; area[xp2][yp2] = area[xp2+2][yp2]; area[xp2+2][yp2] = 0;} break;
            case '2' : 
                if(area[xp][yp+1] == 0 && area[xp2][yp2+1] == 0)
                {yp++;  area[xp][yp] = area[xp][yp-1]; area[xp][yp-1] = 0;
                 yp2++;  area[xp2][yp2] = area[xp2][yp2-1]; area[xp2][yp2-1] = 0;} break;
            case '8' : 
                if(area[xp][yp-1] == 0 && area[xp2][yp2-1] == 0)
                {yp--;  area[xp][yp] = area[xp][yp+1]; area[xp][yp+1] = 0;
                 yp2--;  area[xp2][yp2] = area[xp2][yp2+1]; area[xp2][yp2+1] = 0;} break;
            case 'z' :
                save = area[xp][yp];
                area[xp][yp] = area[xp2][yp2];
                area[xp2][yp2] = save;
                break;
        }
    }
}

/* キャラクターの判定 */
void character_crash()
{
    if(xx != xp || yy != yp){
        if(area[xp][yp] == WALL){   //壁とぶつかった
            putchar('\a');
            wcounter++;
            xp = xx;
            yp = yy;
        } else {
            erase_character();
            display_character();
            counter++;
        }
        display_information();
    }
}

/* 盤面の表示 */
void area_view()
{
    for(int x = 3; x <= ROW * 2 - 3; x+= 2){
        for(int y = 2; y <= COL - 1; y++){
            LOCATE(x, y);
            switch(area[x][y]){
                case SPACE:
                    textcolor(WHITE);
                    cprintf("　");
                    break;
                case RED:
                    textcolor(RED);
                    cprintf("●");
                    break;
                case BLUE:
                    textcolor(BLUE);
                    cprintf("●");
                    break;
                case GREEN:
                    textcolor(GREEN);
                    cprintf("●");
                    break;
                case YELLOW:
                    textcolor(YELLOW);
                    cprintf("●");
                    break;
                case MAGENTA:
                    textcolor(MAGENTA);
                    cprintf("●");
                    break;
            }
        }
    }
}

void puyo_re()
{
    xp = 7; 
    yp = 2; 
    xx = 7; 
    yy = 2; 
    xp2 = 9;
    yp2 = 2;
    xx2 = 9;
    yy2 = 2;
    area[7][2] = rand () % 5 + 2;
    area[9][2] = rand () % 5 + 2;
}

int main(void)
{
    // カーソルを非表示に設定
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);


    srand(time(NULL));
    //cls();
    clrscr();
    display_information();

    /* 壁と空間を配列に入れる */
    for(int x = 1; x <= ROW * 2 - 1; x+= 2){
        for(int y = 1; y <= COL ; y++){
            if(x == MIN || x == ROW * 2 - 1 || y == MIN || y == COL){
                area[x][y] = WALL;
            } else {
                area[x][y] = SPACE;
            }
        }
    }

    /* 配列の情報をもとに表示する */
    for(int x = 1; x <= ROW * 2 - 1; x+= 2){
        for(int y = 1; y <= COL; y++){
            if(area[x][y] == WALL){
                LOCATE(x, y);
                textcolor(4);
                cprintf("■");
            } else if(area[x][y] == SPACE){
                LOCATE(x, y);
                textcolor(WHITE);
                cprintf("　");
            }
        }
    }

    area[7][2] = rand () % 5 + 2;
    area[9][2] = rand () % 5 + 2;

    display_character();
    area_view();

    while(1){
        sleep(0.9);
        if(area[xp][yp+1] == 0 && area[xp2][yp2+1] == 0){
            yp++;  area[xp][yp] = area[xp][yp-1]; area[xp][yp-1] = 0;
            yp2++;  area[xp2][yp2] = area[xp2][yp2-1]; area[xp2][yp2-1] = 0;
            }
        character_move();        /* キャラクターの行動 */

        if(ch == '0'){      /* 0が入力されたらプログラム終了 */
            return 0;
        }
        character_crash();
        area_view();
        if(area[xp][yp+1] >= 1){            //左のぷよが地面についたとき
            while(area[xp2][yp2+1] == 0){   //右のぷよを地面まで落とす
                sleep(0.9);
                yp2++;  area[xp2][yp2] = area[xp2][yp2-1]; area[xp2][yp2-1] = 0;
                area_view();
            }
            puyo_re();
            area_view();
        }
        if(area[xp2][yp2+1] >= 1){            //右のぷよが地面についたとき
            while(area[xp][yp+1] == 0){   //左のぷよを地面まで落とす
                sleep(0.9);
                yp++;  area[xp][yp] = area[xp][yp-1]; area[xp][yp-1] = 0;
                area_view();
            }
            puyo_re();
            area_view();
        }

        xx = xp;
        yy = yp;
    }
    return 0;
}
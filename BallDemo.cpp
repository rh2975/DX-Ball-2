///**confine the duration of background music

# include "iGraphics.h"
# include <ctype.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

#define pi 3.14159

FILE *wfp, *rfp;
//bool checkhigh = false;
int screenwidth = 1200;
int screenHight = 650;
int yAxis = 50;
int hscore = 0;

bool mainmenu = true;
bool newgame = false;
bool loadgame = false;
bool highscore = false;
bool exits = false;

int gameover=0;
int a=0;
int level1 = 0;
int level2 = 0;
int level3 = 0;
int countbricks1=50;
int countbricks2=29;

int timer = 0;
int check_if_mega = 0;
int modenew=0;
int modeload=0;
int modehighscore=0;
int modeexit=0;
int life=3;

bool mega = false;
bool mini = false;

int red=255;
int blue=0;
int green=0;
int sc=0;
int powinterval=0;
//char score[1000];
char* score;
//char highscores[1000];
char* highscores;
int high;
int xBall =(int)screenwidth/2;
int yBall=yAxis;
int radiusBall=10;
int paused=0;

int v=10;
int theta=90;       ///theta = 60;
int dx=(int)v*cos(theta*pi/180);
int dy=(int)v*sin(theta*pi/180);
int mbeam=110;      //score for being mega_beam
bool megabeam=false;//for occurring mega_beam power
int mbx, mby;
int mibeam=200;     //score for being mini_beam
bool minibeam=false;//for occurring mini_beam power
int mibx, miby;
int skullpow=360;   //score for falling skull power
bool skull=false;
int skbx, skby;
int fire_pow_score=230;   //score for falling fireball power
bool fireball=false;
bool firepower=false;
int fbx, fby;

struct brickstructure
{
    int x;
    int y;
    int dx=100;
    int dy=20;
    bool show= true;
};

brickstructure bricks[50];

struct brickstructure2
{
    int x_2;
    int y_2;
    int dx2=100;
    int dy2=20;
    bool show2 = true;
};

brickstructure2 bricks2[50];

struct brickstructure3
{
    int x_3;
    int y_3;
    int dx3=100;
    int dy3=20;
    bool show3 = true;
};

brickstructure3 bricks3[90];

int xboard= xBall-50;
int yboard=yBall -20;
int dxboard =100;
int dyboard =10;
//int dyboard = 15;
int idxboard =100;

//int theta=45;
//int velocity=10;
//dx=velocity*cos(theta);
//dy=velocity*sin(theta);

bool isstarted = false;

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        char t = str[end];
        str[end] = str[start];
        str[start] = t;
        start++;
        end--;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

void ballChange();
void restartball();
void definebricks();
void definebricks2();
void definebricks3();
void changebeam();
void sound();
void timechange();
void Skull();
void FireBall();
void resetbricks();

void iDraw()
{
    iClear();
    if(exits)    exit(0);
    if(level1)definebricks();
	if(level2)definebricks2();
	if(level3)definebricks3();                     ///updated
    if(life==0){
        iShowBMP(280, 305, "Game Over.bmp");
        iShowBMP(435, 155, "main menu button brown.bmp");
        gameover = 1;                                   ///updated
        mainmenu = false;                               ///updated
        iText(490, 130, "Press Enter to return", GLUT_BITMAP_TIMES_ROMAN_24);
        resetbricks();
    }
    else{
        if(mainmenu)                                    ///updated
        {
            if(!newgame && !loadgame && !highscore && !exits)
            {
                iShowBMP(0, 0, "bluebackground.bmp");
                iShowBMP(420, 425, "DXBall2Logo.bmp");
            }

            iSetColor(255, 255, 255);
            iRectangle(520, 335, 170, 50);
            iText(540, 350, "NEW GAME",  GLUT_BITMAP_TIMES_ROMAN_24);
            iRectangle(520, 265, 170, 50);
            iText(537, 280, "HIGH SCORE",  GLUT_BITMAP_TIMES_ROMAN_24);
            iRectangle(520, 195, 170, 50);
            iText(580, 210, "EXIT",  GLUT_BITMAP_TIMES_ROMAN_24);
//            iRectangle(520, 125, 170, if(highscore)

//            iText(580, 140, "EXIT",  GLUT_BITMAP_TIMES_ROMAN_24);
        }

//        if(modenew)
//        {
//            iSetColor(178, 190, 181);
//            iFilledRectangle(520, 335, 170, 50);
//            iSetColor(255,250,240);
//            iText(540, 350, "NEW GAME", GLUT_BITMAP_TIMES_ROMAN_24);
//        }
//        else if(modehighscore)
//        {
//            iSetColor(178, 190, 181);
//            iFilledRectangle(520, 265, 170, 50);
//            iSetColor(255,250,240);
//            iText(537, 280, "HIGH SCORE",  GLUT_BITMAP_TIMES_ROMAN_24);
//        }
//        else if(modeexit)
//        {
//            iSetColor(178, 190, 181);
//            iFilledRectangle(520, 195, 170, 50);
//            iSetColor(255,250,240);
//            iText(533, 210, "EXIT",  GLUT_BITMAP_TIMES_ROMAN_24);
//        }
//        else if(modeexit)
//        {
//            iSetColor(178, 190, 181);
//            iFilledRectangle(520, 125, 170, 50);
//            iSetColor(255,250,240);
//            iText(580, 140, "EXIT",  GLUT_BITMAP_TIMES_ROMAN_24);
//        }

        if(newgame){
            if(a==0) level1 = 1;
        }
//        if(level1==1)
//            if(timer <= 3)
//            {
//                iClear();
//                iShowBMP(525, 240, "LEVEL_1_.bmp");
//            }
////        else if(level2==1)
////            if(timer <= 3)
////            {
////                iClear();
////                iShowBMP(500, 240, "LEVEL_2_.bmp");
////            }
        if(level1==1 || level2==1){
            iSetColor(255,0,0);
            iFilledRectangle(540, 610, 110, 3);
            if(level1)  iText(550, 620, "LEVEL 1", GLUT_BITMAP_TIMES_ROMAN_24);
            if(level1)  iShowBMP(0, 0, "Blues2.bmp");  //iShowBMP(0,0,"black_brick_images.bmp");
            if(level2)  iText(550, 620, "LEVEL 2", GLUT_BITMAP_TIMES_ROMAN_24);
            if(level2)  iShowBMP(0, 0, "Grey Background.bmp");

//            iSetColor(200,200,200);
//            iFilledCircle(xBall,yBall,radiusBall,1000);
//            iSetColor(115,206,250);
//            iFilledRectangle(xboard,yboard,dxboard,dyboard);
           // iShowBMP(xboard, yboard, "Paddle2.bmp");
            iSetColor(255,255,255);
            iText(5, 630, "SCORE",  GLUT_BITMAP_HELVETICA_12);
            iText(60, 630, score);
            iSetColor(124,252,0);
            if(life==3)  iText(1000, 600, "LIFE X 3", GLUT_BITMAP_TIMES_ROMAN_24);
            if(life==2)  iText(1000, 600, "LIFE X 2", GLUT_BITMAP_TIMES_ROMAN_24);
            if(life==1)  iText(1000, 600, "LIFE X 1", GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(255,255,255);
            if(paused)
            {
                iShowBMP(470, 270, "Paused.bmp");
                //iText(550, 300, "PAUSED",GLUT_BITMAP_TIMES_ROMAN_24);

            }
            iSetColor(200,200,200);
            if(!fireball)iFilledCircle(xBall,yBall,radiusBall,1000);
            else
            {
                iSetColor(255,69,0);
                iFilledCircle(xBall,yBall,radiusBall,1000);
            }
            iSetColor(115,206,250);
            //iFilledRectangle(xboard,yboard,dxboard,dyboard);
            if(!mega && !mini)iShowBMP(xboard, yboard-4, "Paddle2.bmp");
            else if(mini && !mega)   iShowBMP(xboard, yboard-4, "Paddle3.bmp");
            else if(mega && !mini)   iShowBMP(xboard, yboard-4, "Paddle.bmp");


            if(minibeam)
            {
                  iShowBMP(mibx, miby, "minibeam_powerup.bmp");
//                iSetColor(230, 0, 0);
//                iFilledRectangle(mibx, miby, 30, 20);
//                iSetColor(0, 0, 2);
//                iFilledRectangle(mibx+8, miby+5, 16, 5);
            }
            if(megabeam)
            {
                  iShowBMP(mbx, mby, "megabeam_powerup.bmp");
//                iSetColor(0, 255, 255);
//                iFilledRectangle(mbx, mby, 30, 20);
//                iSetColor(0, 0, 2);
//                iFilledRectangle(mbx+4, mby+5, 22, 5);
            }
            if(skullpow)
            {
                iShowBMP(skbx, skby, "skull.bmp");
            }
            if(firepower)
            {
                iShowBMP(fbx, fby, "Fire Ball.bmp");
            }
            int i;
            if(level1)
            for(i=0;i<50;i++)
            {
                if(bricks[i].show)
                {
                    iSetColor(255, 255, 255);
                    //iRectangle(bricks[i].x-1,bricks[i].y,bricks[i].dx,bricks[i].dy);
    //                iSetColor(bricks[i].red,bricks[i].green,bricks[i].blue);
    //                //iSetColor(132, 31, 39);
    //                iFilledRectangle(bricks[i].x,bricks[i].y,bricks[i].dx,bricks[i].dy);
                    iShowBMP(bricks[i].x, bricks[i].y, "Bricks2.bmp");
                }
            }
            int j;
           // printf("%d\n",level2);
            if(level2){
           //iClear();
            for(j=0;j<50;j++)
            {
                if(bricks2[j].show2)
                {

                    iSetColor(255, 255, 255);
                    if(bricks2[j].x_2 !=0){
                    if(j%10==0 || j%10==8 || j<10 || j>40)iShowBMP(bricks2[j].x_2, bricks2[j].y_2, "blue-brick-wall-texture.bmp");
                    else     iShowBMP(bricks2[j].x_2, bricks2[j].y_2, "fire-bricks.bmp");}
                }
            }
        }

            changebeam();

        }
    }

    if(countbricks2==0)
        resetbricks();
    if(highscore)
    {
        iClear();
        iText(550, 400, "HIGH SCORE", GLUT_BITMAP_TIMES_ROMAN_24);
        rfp = fopen("High Scores.txt", "r");
        high = fscanf(rfp, "%d", &hscore);
        fclose(rfp);
        itoa(high, highscores, 10);
        iText(600, 350, highscores, GLUT_BITMAP_TIMES_ROMAN_24);

    }

}

void ballChange()
{
   if(isstarted){
     xBall += dx;
     yBall += dy;
     if(xBall>=screenwidth-10||xBall<=10)
        dx = -dx;
     if(yBall>=screenHight-10||yBall<=10)
        dy = -dy;

     int i;
     if(level1)
     for(i=0;i<50;i++)
     {
         if(bricks[i].show)
         {
             if(xBall>bricks[i].x && xBall<=bricks[i].x+bricks[i].dx)
             {
                if(yBall>=bricks[i].y-10 && yBall<=bricks[i].y+bricks[i].dy)
                {
                 PlaySound(TEXT("collide.wav"), NULL, SND_ASYNC);
                 countbricks1--;
                 if(countbricks1==0)    {level1=0; a=1; level2=1; restartball();}
                 if(!fireball)dy= -dy;
                 bricks[i].show=false;
                 sc+=10;
                 hscore=sc;
                 itoa(sc, score, 10);
                 wfp = fopen("High Scores.txt", "w");
                 fprintf(wfp, "%d", hscore);
                 fclose(wfp);
                 if(sc==mbeam)
                 {
                     megabeam=true;
                     mbeam+=400;
                     mbx=bricks[i].x;
                     mby=bricks[i].y;
                 }
                 if(sc==mibeam)
                 {
                     minibeam=true;
                     mibeam+=200;
                     mibx=bricks[i].x;
                     miby=bricks[i].y;
                 }
                 if(sc==skullpow)
                 {
                     skull=true;
                     skullpow+=300;
                     skbx=bricks[i].x;
                     skby=bricks[i].y;
                 }
                 if(sc==fire_pow_score)
                 {
                     firepower=true;
                     fire_pow_score+=200;
                     fbx=bricks[i].x;
                     fby=bricks[i].y;
                 }
                }

             }
             else if(yBall>=bricks[i].y-10 && yBall<=bricks[i].y+bricks[i].dy+10)
             {
                 if(xBall>bricks[i].x-10 && xBall<=bricks[i].x+bricks[i].dx+10)
                {
                 PlaySound(TEXT("collide.wav"), NULL, SND_ASYNC);
                 countbricks1--;
                 if(countbricks1==0)    {level1=0; a=1; level2=1;  restartball();}
                 if(!fireball)dx = -dx;
                 bricks[i].show=false;
                 sc+=10;
                 hscore=sc;
                 itoa(sc, score, 10);
                 wfp = fopen("High Scores.txt", "w");
                 fclose(wfp);
                 fprintf(wfp, "%d", hscore);
                 if(sc==mbeam)
                 {
                     megabeam=true;
                     mbeam+=400;
                     mbx=bricks[i].x;
                     mby=bricks[i].y;
                 }
                 if(sc==mibeam)
                 {
                     minibeam=true;
                     mibeam+=200;
                     mibx=bricks[i].x;
                     miby=bricks[i].y;
                 }
                 if(sc==skullpow)
                 {
                     skull=true;
                     skullpow+=300;
                     skbx=bricks[i].x;
                     skby=bricks[i].y;
                 }
                 if(sc==fire_pow_score)
                 {
                     firepower=true;
                     fire_pow_score+=200;
                     fbx=bricks[i].x;
                     fby=bricks[i].y;
                 }
                }
             }
         }
     }

     if(level2)
     for(i=0;i<50;i++)
     {
         if(bricks2[i].show2)
         {
             if(xBall>bricks2[i].x_2 && xBall<=bricks2[i].x_2+bricks2[i].dx2)
             {
                if(yBall>=bricks2[i].y_2-10 && yBall<=bricks2[i].y_2+bricks2[i].dy2)
                {
                 PlaySound(TEXT("collide"), NULL, SND_ASYNC);
                 countbricks2--;
                 if(countbricks2==0)    {level2=0; level3=1; restartball();}
                 if(!fireball)dy= -dy;

                 bricks2[i].show2=false;
                 sc+=10;
                 hscore=sc;
                 itoa(sc, score, 10);
                 wfp = fopen("High Scores.txt", "w");
                 fprintf(wfp, "%d", hscore);
                 fclose(wfp);
                 if(sc==mbeam)
                 {
                     megabeam=true;
                     mbeam+=400;
                     mbx=bricks2[i].x_2;
                     mby=bricks2[i].y_2;
                 }
                 if(sc==mibeam)
                 {
                     minibeam=true;
                     mibeam+=200;
                     mibx=bricks2[i].x_2;
                     miby=bricks2[i].y_2;
                 }
                 if(sc==skullpow)
                 {
                     skull=true;
                     skullpow+=300;
                     skbx=bricks[i].x;
                     skby=bricks[i].y;
                 }
                 if(sc==fire_pow_score)
                 {
                     firepower=true;
                     fire_pow_score+=200;
                     fbx=bricks[i].x;
                     fby=bricks[i].y;
                 }
                }

             }
             else if(yBall>=bricks2[i].y_2-10 && yBall<=bricks2[i].y_2+bricks2[i].dy2+10)
             {
                 if(xBall>bricks2[i].x_2-10 && xBall<=bricks2[i].x_2+bricks2[i].dx2+10)
                {
                 PlaySound(TEXT("collide"), NULL, SND_ASYNC);
                 countbricks2--;
                 if(countbricks2==0)    {level2=0; level3=1; restartball();}
                 if(!fireball)dx = -dx;     ///updated
                 bricks2[i].show2=false;
                 sc+=10;
                 hscore=sc;
                 itoa(sc, score, 10);
                 wfp = fopen("High Scores.txt", "w");
                 fprintf(wfp, "%d", hscore);
                 fclose(wfp);
                 if(sc==mbeam)
                 {
                     megabeam=true;
                     mbeam+=400;
                     mbx=bricks2[i].x_2;
                     mby=bricks2[i].y_2;
                 }
                 if(sc==mibeam)
                 {
                     minibeam=true;
                     mibeam+=200;
                     mibx=bricks2[i].x_2;
                     miby=bricks2[i].y_2;

                 }
                 if(sc==skullpow)
                 {
                     skull=true;
                     skullpow+=300;
                     skbx=bricks[i].x;
                     skby=bricks[i].y;
                 }
                 if(sc==fire_pow_score)
                 {
                     firepower=true;
                     fire_pow_score+=200;
                     fbx=bricks[i].x;
                     fby=bricks[i].y;
                 }
                }
             }
         }
     }

    if(!mega && !mini){
         if(xBall>=xboard-10 && xBall<=xboard+dxboard+10 && yBall>=yboard+10 && yBall<=yboard+dyboard+10)
        {
            theta=(xboard+dxboard-xBall)+40;
            dx=(int)v*cos(theta*pi/180);
            dy=(int)v*sin(theta*pi/180);

        }
         else
         {
             if(yBall<yboard-14)
             {
                 restartball();
                 life--;
             }
         }
    }
    else if(mega){
        if(xBall>=xboard-10 && xBall<=xboard+200+10 && yBall>=yboard+10 && yBall<=yboard+dyboard+10)
         {
            if(!(xBall>=xboard-10+40 && xBall<=xboard+160+10))
                {
                    theta=-(xboard+200-xBall)+10;
                    //printf("xboarddd=%d\n", xboard+200); printf("xBall=%d\n",xBall);   printf("theta=%d\n", theta);
                }
            else    theta=(xboard+200-xBall-50)+40;
            dx=(int)v*cos(theta*pi/180);
            dy=(int)v*sin(theta*pi/180);

         }
         else
         {
             if(yBall<yboard-14)
             {
                 restartball();
                 life--;
             }
         }
    }
    else if(mini)
    {
        if(xBall>=xboard-10 && xBall<=xboard+50+10 && yBall>=yboard+10 && yBall<=yboard+dyboard+10)
         {
            theta=(xboard+50-xBall)+65;
            dx=(int)v*cos(theta*pi/180);
            dy=(int)v*sin(theta*pi/180);

         }
         else
         {
             if(yBall<yboard-14)
             {
                 restartball();
                 life--;
             }
         }
    }

   }

}


void iMouseMove(int mx, int my)
{

}


void iMouse(int button, int state, int mx, int my)
{

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
//	    if(gameover)
//        {
//            if(mx >= 440 && mx <= 740 && my >= 165 && my <= 315){
//                mainmenu = true;
//                gameover = 0;
//                life = 3;
//                newgame = false;
//                level1 = 0;
//                level2 = 0;
//                modenew = modeload = modehighscore = modeexit = false;
//            }
//
//        }
        if(mx >= 520 && mx <= 690 && my >= 350 && my <= 400)  newgame = true;

        if(mx >= 520 && mx <= 690 && my >= 280 && my <= 330)  highscore = true;

        if(mx >= 520 && mx <= 690 && my >= 210 && my <= 260)  exits = true;

        //if(mx >= 520 && mx <= 690 && my >= 140 && my <= 190)  exits = true;


	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}


void iKeyboard(unsigned char key)
{
    if(gameover)                                                       ///updated
    {
        if(key == '\r')
        {
            mainmenu = true;
            gameover = 0;
            life = 3;
            newgame = false;
            level1 = 0;
            level2 = 0;
            modenew = modeload = modehighscore = modeexit = false;
        }
    }
    if(key == 'f'){
        dx = 0;
        dy = 20;
    }
    if(key == 's'){
        dx = 0;
        dy = -10;
    }
	if(key == 'p')
	{
		iPauseTimer(1);
		paused = 1;
	}
	if(key == 'r')
	{
		iResumeTimer(1);
		paused = 0;
	}
    if(!gameover)                                           ///updated
        if(key == '\r')
        {
            if(modenew)         newgame = true;
            if(modeload)        loadgame = true;
            if(modehighscore)   highscore = true;
            if(modeexit)        exits = true;
        }
    if(key == ' ')
    {
        if(newgame && !isstarted){
            if(life>0) isstarted= true;
        }
    }
    if(key == 'q')
    {
        exit(0);
    }
}

/*
	function iSpecialKeyboard() is called whenever user hits special keys like-
	function keys, home, end, pg up, pg down, arrows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
	{
		exit(0);
	}

	if(life>0 ){                                     //add paused
        if(key == GLUT_KEY_LEFT){
            if(xboard>0){
                xboard -= 15;
                if(!isstarted)
                    xBall -=15;
            }
            if(xboard<=0)
                xboard = 0;
        }
        if(key == GLUT_KEY_RIGHT){

            if(xboard<screenwidth-dxboard){
                xboard += 15;
                if(!isstarted)
                    xBall +=15;
            }
            if(!mega && !mini){
                if(xboard >= screenwidth-100)
                    xboard = screenwidth-100;
            }
            else if(mega)
            {
                if(xboard >= screenwidth-200)
                    xboard = screenwidth-200;
            }
            else if(mini)
            {
                if(xboard >= screenwidth-50)
                    xboard = screenwidth-50;
            }
        }
	}


}

void restartball()
{
       xBall = (int)screenwidth/2;
       yBall = yAxis;

       dx=0;
       dy=10;

       xboard= xBall-50;
       yboard=yBall -20;

       isstarted = false;
       megabeam = false;
       minibeam = false;
       mega = false;
       mini = false;
       fireball = false;
       dxboard = idxboard;
}

void megaBeam()
{
    mby-=10;
}

void miniBeam()
{
    miby-=10;
}

void Skull()
{
    skby-=10;
}
void FireBall()
{
    fby-=10;
}

void definebricks()
{

    int i;
    int sumx=100;
    int sumy=450;

    for(i=0;i<50;i++)
    {

        bricks[i].x=sumx;
        bricks[i].y=sumy;

        sumx+=100;
        if(sumx>1000){
            sumx=100;
            sumy+=20;
        }
    }

}
void resetbricks()
{

    newgame = true;
    a = 0;
    countbricks1=50;
    int i;
    int sumx=100;
    int sumy=450;
    sc=0;
    itoa(sc, score, 10);
    level1=1;
    level2=0;

    for(i=0;i<50;i++)
    {
        bricks[i].show=true;
        bricks[i].x=sumx;
        bricks[i].y=sumy;

        sumx+=100;
        if(sumx>1000){
            sumx=100;
            sumy+=20;
        }
    }

}

void definebricks2()
{

    int i;
    int sumx2=200;
    int sumy2=350;

    for(i=1;i<8;i+=2)
    {
        //bricks2[i].show2=true;
        bricks2[i].x_2=sumx2;
        bricks2[i].y_2=sumy2;
        sumx2+=200;

    }
    sumy2+=20;
    sumx2 = 100;
    for(i=10; i<40; i++)
    {
        if(i%10==0) sumy2 += 20;
        if((i%10)==0 || (i%10)==6)
        {
            //bricks2[i].show2=true;
            bricks2[i].x_2=sumx2;
            bricks2[i].y_2=sumy2;
            sumx2+=200;
            i++;
            if(sumx2>1000)  sumx2 = 100;
        }
        else
        {
            if(i%10==9)
            {
                sumx2+=100;
                if(sumx2>1000)  sumx2 = 100;
                continue;
            }
            //bricks2[i].show2=true;
            bricks2[i].x_2=sumx2;
            bricks2[i].y_2=sumy2;
            sumx2+=100;
            if(sumx2>1000)  sumx2 = 100;
        }

    }

    sumy2 += 40;
    sumx2 = 200;
    for(i=41; i<48; i+=2)
    {
        //bricks2[i].show2=true;
        bricks2[i].x_2=sumx2;
        bricks2[i].y_2=sumy2;
        sumx2+=200;
        if(sumx2>1000){
            break;
        }
    }
}
void definebricks3()                            ///updated
{
    int i, j, row=0;
    int sumx3=200;
    int sumy3=270;
    for(i=0; i<50; i++)
    {
        if(i%10==0){
            row++;
            sumy3+=20;
        }


    }
}

void changebeam()
{
    if(mbx>xboard-40 && mbx<xboard+dxboard && mby==yboard+dyboard)
        {
                //dxboard+=20*2;
                xboard-=20;
                mega = true;    //updated
                mini = false;

        }

    else if(mby<yboard)
        {
            megabeam=false;
        }

    if(!mega){
        if(mibx>xboard-40 && mibx<xboard+dxboard && miby==yboard+dyboard)
        //if(mibx>xboard-40 && mibx<xboard+dxboard)
        {

                //dxboard-=15*2;
                xboard+=15;
                mini = true;  ///updated
                mega = false;
                skull = false;
        }
        else if(miby<yboard)
        {
            minibeam=false;
        }
        if(skbx>xboard-40 && skbx<xboard+dxboard && skby==yboard+dyboard)
        {
            mini = false;  ///updated
            mega = false;
            skull = true;
            if(skull){life--; restartball();}
        }
        else if(skby<yboard)
        {
            skull=false;
        }
        if(fbx>xboard-40 && fbx<xboard+dxboard && fby==yboard+dyboard)
        {
            skull = false;
            fireball = true;
        }
        else if(fby<yboard)
        {
            firepower=false;
        }
    }
    else{
        if(mibx>xboard-40 && mibx<xboard+200 && miby==yboard+dyboard)
        //if(mibx>xboard-40 && mibx<xboard+dxboard)
        {

                //dxboard-=15*2;
                xboard+=15;
                mini = true;  ///updated
                mega = false;
                skull = false;
        }
        else if(miby<yboard)
        {
            minibeam=false;
        }
        if(skbx>xboard-40 && skbx<xboard+200 && skby==yboard+dyboard)
        {
            mini = false;  ///updated
            mega = false;
            skull = true;
            if(skull){life--; restartball();}
        }
        else if(skby<yboard)
        {
            skull=false;
        }
        if(fbx>xboard-40 && fbx<xboard+200 && fby==yboard+dyboard)
        {
            skull = false;
            fireball = true;
        }
        else if(fby<yboard)
        {
            firepower=false;
        }
    }

}

void timechange()
{
    timer++;
}



int main()
{
    score = new char[1000];
    highscores = new char[1000];

	definebricks();
	//definebricks2();


	iSetTimer(1000, timechange);
	iSetTimer(20, ballChange);
	iSetTimer(20, megaBeam);
	iSetTimer(20, miniBeam);
	iSetTimer(20, Skull);
	iSetTimer(20, FireBall);
    PlaySound(TEXT("sound"), NULL, SND_ASYNC);
	itoa(sc, score, 10);
    iInitialize(screenwidth,screenHight, "DX Ball 2");

	return 0;
}


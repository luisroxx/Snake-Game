#include <iostream>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include <ctime>
#define MAX 150

using namespace std;

struct body
{
    int x;
    int y;
};

struct food
{
    int x;
    int y;
};

body corpo[MAX];
food comida;
int segmentos=3;
int lastPressed=100;
int velocidade=150;
int capturedKey=0;
int score=0;
bool going=true;
bool loopmenu=true;
string localmenu="hard";
string newmenu="easy";
int xClear=5,yClear=10;

void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void printSnake()
{
    gotoxy(corpo[0].x,corpo[0].y);
    cout <<"O";

    gotoxy(xClear,yClear);
    cout<<" ";

    for(int x=1; x<segmentos; x++)
    {
        gotoxy(corpo[x].x,corpo[x].y);

        if (x==segmentos-1)
        {
            cout<<char(167);
        }
        else if (corpo[x].y>corpo[x-1].y)
            if (corpo[x+1].y!=corpo[x].y)
                cout<<char(186);
            else if (corpo[x+1].x<corpo[x].x)
                cout<<char(188);
            else
                cout<<char(200);

        else if (corpo[x].y<corpo[x-1].y)
            if (corpo[x+1].y!=corpo[x].y)
                cout<<char(186);
            else if (corpo[x+1].x<corpo[x].x)
                cout<<char(187);
            else
                cout<<char(201);
        else if (corpo[x].y==corpo[x-1].y)
        {
            if (corpo[x+1].y==corpo[x].y)
                cout<<char(205);
            else if (corpo[x+1].y>corpo[x].y)
            {
                if (corpo[x].x<corpo[x-1].x)
                    cout<<char(201);
                else
                    cout<<char(187);
            }
            else if (corpo[x].x<corpo[x-1].x)
                cout<<char(200);
            else
                cout<<char(188);
        }
    }

    xClear=corpo[segmentos-1].x;
    yClear=corpo[segmentos-1].y;

    for (int y=segmentos-1; y>0; y--)
    {
        corpo[y].x=corpo[y-1].x;
        corpo[y].y=corpo[y-1].y;
    }
    corpo[1].x=corpo[0].x;
    corpo[1].y=corpo[0].y;

}

void printComida()
{
    gotoxy(comida.x,comida.y);
    cout<<char(178);
}

void printMenu()
{
    gotoxy(25,5);
    cout<<char(201);
    for(int i=0; i<30; i++)
        cout<<char(205);
    cout<<char(187);

    gotoxy(25,17);
    cout<<char(200);
    for(int i=0; i<30; i++)
        cout<<char(205);
    cout<<char(188);

    for (int i=6; i<17; i++)
    {
        gotoxy(25,i);
        cout<<char(186);
    }

    for (int i=6; i<17; i++)
    {
        gotoxy(56,i);
        cout<<char(186);
    }

    gotoxy(38,8);
    cout<<"SNAKE";

    gotoxy(34,12);
    cout<<"EASY MODE";

    gotoxy(34,14);
    cout<<"HARD MODE";
}

void printHud()
{
    gotoxy(0,0);
    cout<<char(201);
    for(int i=1; i<60; i++)
        cout<<char(205);
    cout<<char(187);

    gotoxy(0,24);
    cout<<char(200);
    for(int i=1; i<60; i++)
        cout<<char(205);
    cout<<char(188);

    for (int i=1; i<24; i++)
    {
        gotoxy(0,i);
        cout<<char(186);
    }

    for (int i=1; i<24; i++)
    {
        gotoxy(60,i);
        cout<<char(186);
    }
}

void verificaInput()
{
    if (kbhit())
    {
        capturedKey = getch();
        if (capturedKey==119)
        {
            if (lastPressed!=115)
                lastPressed=119;
        }

        else if (capturedKey==100)
        {
            if (lastPressed!=97)
                lastPressed=100;
        }
        else if (capturedKey==115)
        {
            if (lastPressed!=119)
                lastPressed=115;
        }
        else if (capturedKey==97)
        {
            if (lastPressed!=100)
                lastPressed=97;
        }
    }
}

bool verificaKeyQuit()
{
    if (kbhit())
    {
        capturedKey = getch();
        if (capturedKey==13)
        {
            return true;
        }
    }
    return false;
}

int verificaMenu()
{
    if (kbhit())
    {
        capturedKey = getch();
        if (capturedKey==119)
        {
                newmenu="easy";
        }
        if (capturedKey==115)
        {
                newmenu="hard";
        }
        if (capturedKey==13)
            loopmenu=false;

    }
}

void colidiuCantos()
{
    if (corpo[0].x==0)
    {
        if (localmenu=="easy")
            corpo[0].x=59;
        else
            going=false;
    }
    if (corpo[0].x==60)
    {
        if (localmenu=="easy")
            corpo[0].x=1;
        else
            going=false;
    }
    if (corpo[0].y==0)
    {
        if (localmenu=="easy")
            corpo[0].y=23;
        else
            going=false;
    }
    if (corpo[0].y==24)
    {
        if (localmenu=="easy")
            corpo[0].y=1;
        else
            going=false;
    }
}

void colidiuComida()
{
    if (corpo[0].x==comida.x and corpo[0].y==comida.y)
    {
        int randX;
        int randY;

        randX=rand() % 58 +1;
        randY=rand() % 22 +1;

        comida.x=randX;
        comida.y=randY;

        if (velocidade==50 or velocidade==1)
            velocidade=50;
        else
            velocidade-=25;

        if (segmentos!=MAX)
        {
            segmentos++;
            corpo[segmentos-1].x=corpo[segmentos-2].x;
            corpo[segmentos-1].y=corpo[segmentos-2].y;
        }
        score++;
    }
}

void colidiuCorpo()
{
    for (int x=1; x<segmentos; x++)
    {
        if (corpo[0].x==corpo[x].x and corpo[0].y==corpo[x].y)
        {
            going=false;
        }
    }
}

void verificaColisao()
{
    colidiuCantos();
    colidiuComida();
    colidiuCorpo();
}

void printScore()
{
    gotoxy (65,5);
    cout<<"SCORE: "<<score;
}

void movimentaSnake()
{
    if (lastPressed==119)
        corpo[0].y--;
    else if (lastPressed==100)
        corpo[0].x++;
    else if (lastPressed==115)
        corpo[0].y++;
    else if (lastPressed==97)
        corpo[0].x--;
}

main()
{

    printMenu();
    
    while(loopmenu)
    {
        verificaMenu();
        if (localmenu!=newmenu)
        {
            if (newmenu=="easy")
            {
                gotoxy(30,12);
                cout<<char(175);

                gotoxy(30,14);
                cout<<" ";
                localmenu="easy";
            }
            else
            {
                gotoxy(30,12);
                cout<<" ";

                gotoxy(30,14);
                cout<<char(175);
                localmenu="hard";
            }
        }
        usleep(3000*1000);
    }

    system("cls");

    corpo[0].x=10;
    corpo[0].y=12;
    corpo[1].x=9;
    corpo[1].y=12;
    corpo[2].x=8;
    corpo[2].y=12;

    srand(time(NULL));
    comida.x=rand() % 58 +1;
    comida.y=rand() % 22 +1;

    printHud();

    while(going)
    {
        printScore();
        printSnake();
        printComida();
        usleep(velocidade*1000);
        verificaInput();
        movimentaSnake();
        verificaColisao();
    }

    while (!verificaKeyQuit())
    {
        gotoxy(25,10);
        cout<<"GAME OVER"<<endl;
        gotoxy(20,11);
        cout<<"Press enter to quit";

        usleep(5000*1000);

        gotoxy(25,10);
        cout<<"         "<<endl;
        gotoxy(20,11);
        cout<<"                   ";

        usleep(5000*1000);
    }

    system("cls");
}
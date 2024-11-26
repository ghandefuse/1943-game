#include <conio.h>
#include <stdio.h>
#include <list>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
using namespace std;

void moverchar(int x, int y)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;

    HANDLE han1;
    han1 = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(han1, Pos);
}

class ENEMIGOS
{
    int x,y;
    int asteroide;
    int posX;
public:
    ENEMIGOS(int _x,int _y): x(_x),y(_y){}
    int X() {return x;}
    int Y() {return y;}
    void escAST();
    void movAST();
    void danio(class SHIP &Nave);
    void escENE();
    void movENE();
    void borrarENE();
};

void ENEMIGOS::escENE()
{
    moverchar(x,y); printf("%c%c%c%c%c",60,196,219,196,62);
    moverchar(x,y+1); printf("  %c  ",202);
}

void ENEMIGOS::borrarENE()
{
    moverchar(x,y); printf("     ");
    moverchar(x,y+1); printf("     ");
}

void ENEMIGOS::movENE()
{
    borrarENE();
    posX=rand()%3;
    if (x>6 && x<108)
    {
        switch(posX)
        {
            case 0: x++;
            break;
            case 1: x--;
            break;
        }
    }
    switch(x)
    {
        case 6: x++;
        break;
        case 108: x--;
        break;
    }
    escENE();
}

void ENEMIGOS::escAST()
{
    moverchar(x,y); printf("%c",155);
}

void ENEMIGOS::movAST()
{
    moverchar(x,y); printf(" ");
    y++;
    if (y>34)
    {
        x=rand()%108 + 6;
        y=6;
    }
    escAST();
}

class SHIP
{
      int x,y;
      int escudo;
      int vidas;

public:

    SHIP (int _x, int _y, int _escudo, int _vidas):x(_x),y(_y),escudo(_escudo),vidas(_vidas){}
    int V(){return vidas;};
    int X(){return x;};
    int Y(){return y;};
    void CREAR();
    void BORRAR();
    void MOVIMIENTO();
    void esc_escudo();
    void esc_vidas();
    void escudomenos(){escudo--;}
    void NOSHIELD();

};

void SHIP::CREAR()
{
    moverchar(x,y);   printf("  %c",219);
    moverchar(x,y+1); printf(" %c%c%c",219,219,219);
    moverchar(x,y+2); printf("%c%c%c%c%c",223,64,223,64,223);
    moverchar(x,y+3); printf(" %c %c ",176,176);
}

void SHIP::BORRAR(){
     moverchar(x,y); printf("     ");
     moverchar(x,y+1);printf("     ");
     moverchar(x,y+2);printf("      ");
     moverchar(x,y+3);printf("      ");
}

void SHIP::MOVIMIENTO()
{
    if(_kbhit()) //DETECTA LOS INPUTS DEL TECLADO.
    {
                char input = _getch();
                BORRAR();
                if(input == 75 && x>6) x--;
                if(input == 77 && x<107) x++;
                if(input == 80 && y<31) y++;
                if(input == 72 && y>5) y--;
                CREAR();
                esc_escudo();
                esc_vidas();
                }
}

void SHIP::esc_escudo()
{
    moverchar(105,2); printf("(ESCUDO)");
    moverchar(106,3); printf("     ");
    for (int i=0 ; i<escudo; i++)
    {
        moverchar(106+i,3); printf("%c",4);
    }
}

void SHIP::esc_vidas()
{
    moverchar(94,2); printf("(VIDAS)");
    moverchar(96,3); printf("     ");
    for (int i=0 ; i<vidas; i++)
    {
        moverchar(96+i,3); printf("%c",3);
    }
}

void SHIP::NOSHIELD()
{
    if (escudo==0){
        BORRAR();
        moverchar(x,y);   printf("  %c",178);
        moverchar(x,y+1); printf(" %c%c%c",178,178,178);
        moverchar(x,y+2); printf("%c%c%c%c%c",178,178,178,178,178);
        moverchar(x,y+3); printf("     ");
        Sleep(250);
        BORRAR();
        moverchar(x,y);   printf("  %c",176);
        moverchar(x,y+1); printf(" %c%c%c",176,176,176);
        moverchar(x,y+2); printf("%c%c%c%c%c",176,176,176,176,176);
        moverchar(x,y+3); printf("     ");
        Sleep(250);
        vidas--;
        escudo = 5;
        esc_escudo();
        CREAR();

    }
}

void BORDES()
{
    for (int i=6 ; i<114 ; i++)
    {
           moverchar(i,4); printf("%c",205);
           moverchar(i,35); printf("%c",205);
    }
    for (int i=5; i<35; i++)
    {
           moverchar(5,i); printf("%c",186);
           moverchar(114,i); printf("%c",186);
    }
    moverchar(5,4); printf("%c",201);
    moverchar(114,4); printf("%c",187);
    moverchar(5,35); printf("%c",200);
    moverchar(114,35); printf("%c",188);
    moverchar(120,20);printf("DISPARAR = Z");
    moverchar(120,22);printf("MOVERSE = ARROWS");
    moverchar(55,1); printf("-1943-");
}

void ENEMIGOS::danio(class SHIP &Nave)
{
    if(x >= Nave.X() && x<Nave.X()+5 && y>=Nave.Y() && y<=Nave.Y()+4)
    {
        Nave.escudomenos();
        Nave.BORRAR();
        Nave.CREAR();
        Nave.esc_escudo();
        x=rand()%113 + 5;
        y=6;
    }
}

class DISPARO
{
    int x,y;
public:
    DISPARO(int _x,int _y): x(_x),y(_y){}
    void SHOOT()
     {
      moverchar(x, y); printf(" ");
      if (y > 5) { y--; moverchar(x, y); printf("%c",221); }
     }
     int X() { return x; }
     int Y() { return y; }
     bool out() { if (y < 5) { return true; } return false; }
    };

void NoCursor()
{
    HANDLE han1;
    han1 = GetStdHandle(STD_OUTPUT_HANDLE);
    _CONSOLE_CURSOR_INFO nocur;
    nocur.dwSize = 1;
    nocur.bVisible = FALSE;

    SetConsoleCursorInfo(han1,&nocur);
}

int main()
{
    BORDES();
    NoCursor();
    SHIP Nave(55,30,5,3);
    Nave.CREAR();
    Nave.esc_escudo();
    Nave.esc_vidas();
    int PUNTUACION = 0;
    int ENEREST = 9;

    list<DISPARO*> D;
    list<DISPARO*>::iterator iterar;
    DISPARO Tiro();

    list<ENEMIGOS*> A;
    list<ENEMIGOS*>::iterator iterAST;

    list<ENEMIGOS*> E;
    list<ENEMIGOS*>::iterator iterENE;

    for(int i=0; i<6; i++)
    {
        A.push_back(new ENEMIGOS(rand()%100+6, rand()%6+5));
    }

    for(int i=0; i<4; i++)
    {
        E.push_back(new ENEMIGOS(rand()%104+6, rand()%6+5));
    }

    bool perder = false;
    while(!perder)
    {
        moverchar(5,2);printf("PUNTUACION");
        moverchar(5,3);printf("%d",PUNTUACION);
        moverchar(22,2);printf("ENEMIGOS RESTANTES");
        moverchar(30,3);printf("%d",ENEREST);
        if(kbhit())
        {
           char shoot = _getch();
           if(shoot=='z')
           D.push_back(new DISPARO(Nave.X()+ 2 , Nave.Y()-1));
        }
        for(iterar = D.begin(); iterar != D.end(); iterar++)
        {
            (*iterar)->SHOOT();
            if ((*iterar)->out())
            {
                moverchar((*iterar)->X(),(*iterar)->Y()); printf(" ");
                delete(*iterar);
                iterar = D.erase(iterar);
            }
        }

        for (iterAST = A.begin(); iterAST != A.end(); iterAST++)
        {
            (*iterAST)->movAST();
            (*iterAST)->danio(Nave);

        }

        for (iterENE = E.begin(); iterENE != E.end(); iterENE++)
        {
            (*iterENE)->movENE();
        }

        for (iterAST = A.begin(); iterAST != A.end(); iterAST++)
        {
            for(iterar = D.begin(); iterar != D.end(); iterar++)
            {
                if((*iterAST)->X() == (*iterar)->X() && ((*iterAST)->Y()+1 == (*iterar)->Y() || (*iterAST)->Y() == (*iterar)->Y()))
                    {
                        moverchar((*iterar)->X(),(*iterar)->Y()); printf(" ");
                        delete(*iterar);
                        iterar = D.erase(iterar);
                        A.push_back(new ENEMIGOS(rand()%104+6, 5));
                        moverchar((*iterAST)->X(),(*iterAST)->Y()); printf(" ");
                        delete(*iterAST);
                        iterAST = A.erase(iterAST);
                        PUNTUACION+=100;
                    }
            }
        }

        for (iterENE = E.begin(); iterENE != E.end(); iterENE++)
        {
            for(iterar = D.begin(); iterar != D.end(); iterar++)
            {
                if((*iterENE)->X() == (*iterar)->X() && ((*iterENE)->Y()+1 == (*iterar)->Y() || (*iterENE)->Y() == (*iterar)->Y()))
                    {
                      moverchar((*iterar)->X(),(*iterar)->Y()); printf(" ");
                      delete(*iterar);
                      iterar = D.erase(iterar);
                      E.push_back(new ENEMIGOS(rand()%104+8, rand()%5+6));
                      moverchar((*iterENE)->X(),(*iterENE)->Y()); printf("     ");
                      moverchar((*iterENE)->X(),(*iterENE)->Y()+1); printf("     ");
                      delete(*iterENE);
                      iterENE = E.erase(iterENE);
                      PUNTUACION+=200;
                      ENEREST-=1;
                    }
            }
        }
        if(Nave.V() == 0) perder = true;
        if(ENEREST == 0) perder = true;
        Nave.NOSHIELD();
        Nave.MOVIMIENTO();
        Sleep(30);
    }
    moverchar(55,15);printf("GAME OVER.");
    moverchar(53,36);printf("GRACIAS POR JUGAR.");
    moverchar(50,37);
    std::cout << "PRESIONA ENTER PARA SALIR";
    std::cin.get();
    return 0;
    system("pause>0");
}

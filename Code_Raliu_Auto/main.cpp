#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <MMsystem.h>
#include <winbgim.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int width = GetSystemMetrics(SM_CXSCREEN);
int height = GetSystemMetrics(SM_CYSCREEN);
int mx, my, ok = 1, stopmen1, stopmen3, stopsunet;
bool meniulprincipal = true, meniulsecundar = false, meniulhowtoplay = false;
char arr[100];
int puncte = 0, stop;
bool gameOver = false;
int x = 100, y = 100, antx, anty, viteza, score, car1 = 1, v[10000] = { 0 }, ord[10] = { -1 }, start3 = 0;
enum edirectie { Stop = 0, stanga, dreapta, sus, jos, stangasus, stangajos, dreaptajos, dreaptasus };
edirectie dir;
int a[1000][1000] = { 0 }, pozitiemausx, pozitiemausy, gameOvergreseala, gameovercomplet;
int Ay = height * 200 / 864, Ax = width * 396 / 1536, Gx = Ax, Gy = height * 650 / 864, R = width * 75 / 1536;
int Bx = width * 1025 / 1536, By = Ay - R, Cx = Bx + R, Cy = Ay, Dx = Cx, Dy = Gy, r = R / 2, ax, ay;
bool input = false;
bool meniu2, meniu3 = 0, stoplevels = 0, stopranking = 0, stopbody = 0, stopmentesla = 0, stopmenlamburghini = 0, stopmencar = 1, Level1 = 0;
char tasta, LastNumePLayer[100];
int  ScoreLastNumePlayer, masina = 0, tesla = 0, lamborghini = 0;
void ConturPista()
{
    setcolor(WHITE);

    arc(Ax + 2 + R, Ay, 90, 180, R);
    arc(Ax + 2 + R, Ay - 2, 90, 180, R - 1);
    line(Ax + 1, Ay, Ax + 1, Gy);
    line(Ax + 2, Ay, Ax + 2, Gy);
    line(Ax + 2 + R, By, Bx, By);
    line(Ax + 2 + R, By + 1, Bx, By + 1);
    arc(Bx + 1, By + R, 0, 90, R);
    arc(Bx + 1, By + R, 0, 90, R + 1);
    line(Cx, Cy, Dx, Dy);
    line(Cx + 1, Cy, Dx + 1, Dy);
    arc(Dx - R, Dy, 270, 0, R);
    arc(Dx - R, Dy, 270, 0, R + 1);
    arc(Gx + R, Gy, 180, 270, R);
    arc(Gx + R, Gy, 180, 270, R - 1);
    line(Gx + R, Gy + R, Dx - R, Dy + R);
    line(Gx + R, Gy + R, Dx - R, Dy + R - 1);

    line(Ax + 1 + R, Ay + r / 2, Ax + 1 + R, Gy - r);
    line(Ax + 1 + R, Ay + r / 2, Ax + 1 + R, Gy + 1 - r);
    arc(Ax + 1 + R + r, Ay + r / 2, 90, 180, r);
    arc(Ax + 1 + R + r, Ay + r / 2, 90, 180, r - 1);
    line(Ax + 1 + R + r, Ay - r / 2, Bx - r, Ay - r / 2);
    line(Ax + 1 + R + r, Ay - r / 2, Bx - r, Ay - r / 2 - 1);
    arc(Bx - r, Ay + r / 2, 0, 90, r);
    arc(Bx - r, Ay + r / 2, 0, 90, r - 1);
    line(Bx, Ay + r / 2, Dx - R, Dy - r);
    line(Bx - 1, Ay + r / 2, Dx - R - 1, Dy - r);
    line(Dx - R - r, Dy, Ax + 1 + R + r, Gy);
    line(Dx - R - r, Dy - 1, Ax + 1 + R + r, Gy - 1);
    arc(Dx - R - r, Dy - r, 270, 0, r);
    arc(Dx - R - r, Dy - r, 270, 0, r - 1);
    arc(Ax + 1 + R + r, Gy - r, 180, 270, r);
    arc(Ax + 1 + R + r, Gy - r, 180, 270, r - 1);
    //  line(0,height-130,width,height-130);

}
void SetUp()
{
    gameOver = false;
    dir = Stop;
    readimagefile("Back.jpg", 30, height - 110, 80, height - 50);
    ConturPista();
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(0, 0, WHITE);  //  coloring the exterior of the rally
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(width / 2, height / 2, WHITE); // coloring the interior of the rally
    setfillstyle(HATCH_FILL, GREEN);
    floodfill(Ax + 10, Ay, WHITE); //coloring the interior of the track with squares
    setcolor(BLACK);
    x = (Dx + Gx) / 2 - 15;
    y = (Dy + Gy) / 2 + 10;
    antx = x;
    anty = y;
    score = 0;
}
void Startul()
{
    setcolor(4);
    line((Dx - R - r + Ax + 1 + R + r) / 2 - 3, (Dy + Gy) / 2 + R, (Dx - R - r + Ax + 1 + R + r) / 2 - 3, (Dy + Gy) / 2);
    line((Dx - R - r + Ax + 1 + R + r) / 2 - 4, (Dy + Gy) / 2 + R, (Dx - R - r + Ax + 1 + R + r) / 2 - 4, (Dy + Gy) / 2);
}
struct nod
{
    int x1, y1, x2, y2, nr;
    nod* urm;
};
int fr = 0, numar = 0;
nod* p = NULL, * u = NULL, * q;
void Drum(int x1, int y1, int x2, int y2)
{
    if (p == NULL)
    {
        p = new nod;
        p->x1 = x1;
        p->y1 = y1;
        p->x2 = x2;
        p->y2 = y2;
        p->nr = ++numar;
        u = p;
        u->urm = NULL;
    }
    else
    {
        q = new nod;
        q->x1 = x1;
        q->y1 = y1;
        q->x2 = x2;
        q->y2 = y2;
        q->nr = ++numar;
        u->urm = q;
        u = q;
        u->urm = NULL;
    }
}
void ConstruireDrumAnterior()
{
    setcolor(RED);
    q = p;
    int cx, cy, bx, by, ax, ay, dx, dy, ex, ey;
    while (q != NULL)
    {
        line(q->x1, q->y1, q->x2, q->y2);   //Dreapta(Drumul pe unde a trecut masina)

        if (v[q->nr] == 11) //Sagetile
        {
            cx = q->x1;
            cy = q->y1, bx = q->x2, by = q->y2;
            line((bx + cx) / 2, (by + cy) / 2, (bx + cx) / 2, (cy + by) / 2 + 10);
            line((bx + cx) / 2, (by + cy) / 2, (bx + cx) / 2 - 10, (cy + by) / 2);
            line((bx + cx) / 2 + 1, (by + cy) / 2 + 1, (bx + cx) / 2 + 1, (cy + by) / 2 + 11);
            line((bx + cx) / 2 + 1, (by + cy) / 2 + 1, (bx + cx) / 2 - 9, (cy + by) / 2 + 1);
        }
        else if (v[q->nr] == 22)
        {
            cx = q->x1;
            cy = q->y1, ax = q->x2, ay = q->y2;
            line((ax + cx) / 2, (ay + cy) / 2, (ax + cx) / 2, (ay + cy) / 2 + 10);
            line((ax + cx) / 2, (ay + cy) / 2, (ax + cx) / 2 + 10, (ay + cy) / 2);
            line((ax + cx) / 2 - 1, (ay + cy) / 2 - 1, (ax + cx) / 2 + 1, (ay + cy) / 2 + 9);
            line((ax + cx) / 2 - 1, (ay + cy) / 2 - 1, (ax + cx) / 2 + 9, (ay + cy) / 2 + 1);
        }
        else if (v[q->nr] == 32)
        {
            cx = q->x1;
            cy = q->y1, dx = q->x2, dy = q->y2;
            line((dx + cx) / 2, (dy + cy) / 2, (dx + cx) / 2 + 10, (dy + cy) / 2);
            line((dx + cx) / 2, (dy + cy) / 2, (dx + cx) / 2, (cy + dy) / 2 - 10);
        }
        else if (v[q->nr] == 42)
        {
            cx = q->x1;
            cy = q->y1, ex = q->x2, ey = q->y2;
            line((ex + cx) / 2, (ey + cy) / 2, (ex + cx) / 2 - 10, (ey + cy) / 2);
            line((ex + cx) / 2, (ey + cy) / 2, (ex + cx) / 2, (cy + ey) / 2 - 10);
        }
        else if (v[q->nr] == 12)
        {
            cx = q->x1;
            cy = q->y1, ex = q->x2, ey = q->y2;
            line((cx + ex) / 2, (cy + ey) / 2, (cx + ex) / 2 - 7, (cy + ey) / 2 + 7);
            line((cx + ex) / 2, (cy + ey) / 2, (cx + ex) / 2 + 7, (cy + ey) / 2 + 7);
        }
        else if (v[q->nr] == 33)
        {
            cx = q->x1;
            cy = q->y1, ex = q->x2, ey = q->y2;
            line((cx + ex) / 2, (cy + ey) / 2, (cx + ex) / 2 - 7, (cy + ey) / 2 - 7);
            line((cx + ex) / 2, (cy + ey) / 2, (cx + ex) / 2 + 7, (cy + ey) / 2 - 7);
        }
        else if (v[q->nr] == 31)
        {
            cx = q->x1;
            cy = q->y1, ex = q->x2, ey = q->y2;
            line((cx + ex) / 2, (cy + ey) / 2, (cx + ex) / 2 + 7, (cy + ey) / 2 - 7);
            line((cx + ex) / 2, (cy + ey) / 2, (cx + ex) / 2 + 7, (cy + ey) / 2 + 7);
        }
        else if (v[q->nr] == 10)
        {
            cx = q->x1;
            cy = q->y1, ex = q->x2, ey = q->y2;
            line((cx + ex) / 2, (cy + ey) / 2, (cx + ex) / 2 - 7, (cy + ey) / 2 - 7);
            line((cx + ex) / 2, (cy + ey) / 2, (cx + ex) / 2 - 7, (cy + ey) / 2 + 7);
        }
        q = q->urm;
    }
    setcolor(WHITE);
}

void Draw()
{
    for (int i = 10; i <= 1800; i++)
        for (int j = 10; j <= 1700; j++)
            if (i == x && j == y)
            {
                if (getpixel(x, y) == BLUE || (tesla == 0 && masina == 0 && lamborghini == 0))
                {
                    gameOver = true;
                    gameovercomplet = 0;
                    gameOvergreseala = 1;
                    p = NULL;
                    q = NULL;
                    setcolor(RED);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
                    outtextxy(100, height - 80, "                         ");
                    outtextxy(100, height - 110, "      Ati iesit de pe pista        ");
                }
                if (stop == 3)
                {
                    gameOver = true;
                    gameovercomplet = 1;
                    gameOvergreseala = 0;
                    p = NULL;
                    q = NULL;
                }

                if (car1 == 1 && masina == 1)
                    readimagefile("car1dirstanga.gif", x - 10, y - 10, x + 10, y + 10);
                else
                    if (car1 == 2 && masina == 1)
                        readimagefile("car1dirdreapta.gif", x - 10, y - 10, x + 10, y + 10);
                    else
                        if (car1 == 0 && masina == 1)
                            readimagefile("car1dirinainte.gif", x - 10, y - 10, x + 10, y + 10);
                        else
                            if (car1 == 3 && masina == 1)
                                readimagefile("car1dirinapoi.gif", x - 10, y - 10, x + 10, y + 10);
                            else
                                if (car1 == 4 && masina == 1)
                                    readimagefile("car1dirstangajos.gif", x - 15, y - 15, x + 15, y + 15);
                                else
                                    if (car1 == 5 && masina == 1)
                                        readimagefile("car1dirstangasus.gif", x - 35, y - 35, x + 35, y + 35);
                                    else
                                        if (car1 == 6 && masina == 1)
                                            readimagefile("car1dirdreaptajos.gif", x - 15, y - 15, x + 15, y + 15);
                                        else
                                            if (car1 == 7 && masina == 1)
                                                readimagefile("car1dirdreaptasus.gif", x - 15, y - 15, x + 15, y + 15);
                                            else
                                                if (car1 == 1 && tesla == 1)
                                                    readimagefile("tesla270.gif", x - 10, y - 10, x + 10, y + 10);
                                                else
                                                    if (car1 == 2 && tesla == 1)
                                                        readimagefile("tesla90.gif", x - 10, y - 10, x + 10, y + 10);
                                                    else
                                                        if (car1 == 0 && tesla == 1)
                                                            readimagefile("tesla0.gif", x - 10, y - 10, x + 10, y + 10);
                                                        else
                                                            if (car1 == 3 && tesla == 1)
                                                                readimagefile("tesla180.gif", x - 10, y - 10, x + 10, y + 10);
                                                            else
                                                                if (car1 == 4 && tesla == 1)
                                                                    readimagefile("tesla225.gif", x - 15, y - 15, x + 15, y + 15);
                                                                else
                                                                    if (car1 == 5 && tesla == 1)
                                                                        readimagefile("tesla325.gif", x - 15, y - 15, x + 15, y + 15);
                                                                    else
                                                                        if (car1 == 6 && tesla == 1)
                                                                            readimagefile("tesla135.gif", x - 15, y - 15, x + 15, y + 15);
                                                                        else
                                                                            if (car1 == 7 && tesla == 1)
                                                                                readimagefile("tesla45.gif", x - 15, y - 15, x + 15, y + 15);
                                                                            else
                                                                                if (car1 == 1 && lamborghini == 1)
                                                                                    readimagefile("lambo270.gif", x - 10, y - 10, x + 10, y + 10);
                                                                                else
                                                                                    if (car1 == 2 && lamborghini == 1)
                                                                                        readimagefile("lambo90.gif", x - 10, y - 10, x + 10, y + 10);
                                                                                    else
                                                                                        if (car1 == 0 && lamborghini == 1)
                                                                                            readimagefile("lambo0.gif", x - 10, y - 10, x + 10, y + 10);
                                                                                        else
                                                                                            if (car1 == 3 && lamborghini == 1)
                                                                                                readimagefile("lambo180.gif", x - 10, y - 10, x + 10, y + 10);
                                                                                            else
                                                                                                if (car1 == 4 && lamborghini == 1)
                                                                                                    readimagefile("lambo225.gif", x - 15, y - 15, x + 15, y + 15);
                                                                                                else
                                                                                                    if (car1 == 5 && lamborghini == 1)
                                                                                                        readimagefile("lambo315.gif", x - 15, y - 15, x + 15, y + 15);
                                                                                                    else
                                                                                                        if (car1 == 6 && lamborghini == 1)
                                                                                                            readimagefile("lambo135.gif", x - 15, y - 15, x + 15, y + 15);
                                                                                                        else
                                                                                                            if (car1 == 7 && lamborghini == 1)
                                                                                                                readimagefile("lambo45.gif", x - 15, y - 15, x + 15, y + 15);
            }

    setcolor(0);
    readimagefile("Back.gif", 30, height - 110, 80, height - 50);
    ConstruireDrumAnterior();
}
void Input()
{
    tasta = getch();
    if ('a' == tasta)
    {
        v[++fr] = 31;
        Drum(x, y, x - 40, y);
        antx = x;
        x -= 40;
        car1 = 1;
        outtextxy(100, height - 110, "                                                   ");
        outtextxy(100, height - 100, "                                                   ");
        outtextxy(100, height - 90, "                                                   ");
        outtextxy(100, height - 80, "                                                   ");
        if (antx >= (Dx - R - r + Ax + 1 + R + r) / 2 - 4 && x <= (Dx - R - r + Ax + 1 + R + r) / 2 - 4 && y <= (Dy + Gy) / 2 + R && y >= (Dy + Gy) / 2)
        {
            stop++;
            score += puncte;
            arr[0]='/0';
            setcolor(WHITE);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            sprintf(arr,"Score:%d",score+ScoreLastNumePlayer);
            outtextxy(width/2-117,70,arr);
        }
    }
    else if ('d' == tasta)
    {
        v[++fr] = 10;
        antx = x;
        outtextxy(100, height - 110, "                                                   ");
        outtextxy(100, height - 100, "                                                   ");
        outtextxy(100, height - 90, "                                                   ");
        outtextxy(100, height - 80, "                                                   ");
        if (!(x <= (Dx + Ax + 1) / 2 - 4 && x + 40 >= (Dy + Gy) / 2 + R && y <= (Dx + Ax + 1) / 2 - 4 && y >= (Dy + Gy) / 2))
        {
            Drum(x, y, x + 40, y);
            x += 40;
            car1 = 2;
            if (antx <= (Dx - R - r + Ax + 1 + R + r) / 2 - 4 && x >= (Dx - R - r + Ax + 1 + R + r) / 2 - 4 && y <= (Dy + Gy) / 2 + R && y >= (Dy + Gy) / 2)
            {
                stop++;
                score += puncte;
                arr[0]='/0';
                setcolor(WHITE);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                sprintf(arr,"Score:%d",score+ScoreLastNumePlayer);
                outtextxy(width/2-117,70,arr);
            }
        }
        else
        {
            setcolor(RED);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(100, height - 110, "Nu este permisa mutarea.Trebuie sa jucati cinstit.");
            outtextxy(500, height - 80, "NU TRISA");
            setcolor(WHITE);
        }
    }
    else if ('w' == tasta)
    {
        v[++fr] = 12;
        Drum(x, y, x, y - 40);
        anty = y;
        y -= 40;
        car1 = 0;
        outtextxy(100, height - 110, "                                                   ");
        outtextxy(100, height - 100, "                                                   ");
        outtextxy(100, height - 90, "                                                   ");
        outtextxy(100, height - 80, "                                                   ");
    }
    else if ('s' == tasta)
    {
        v[++fr] = 33;
        Drum(x, y, x, y + 40);
        y += 40;
        car1 = 3;
        outtextxy(100, height - 110, "                                                   ");
        outtextxy(100, height - 100, "                                                   ");
        outtextxy(100, height - 90, "                                                   ");
        outtextxy(100, height - 80, "                                                   ");
    }
    else if ('q' == tasta)
    {
        v[++fr] = 22;
        Drum(x, y, x - 40, y - 40);
        antx = x;
        anty = y;
        x -= 40;
        y -= 40;
        car1 = 5;
        outtextxy(100, height - 110, "                                                   ");
        outtextxy(100, height - 100, "                                                   ");
        outtextxy(100, height - 90, "                                                   ");
        outtextxy(100, height - 80, "                                                   ");
        if (x <= (Dx + Ax + 1) / 2 - 4 && antx >= (Dx + Ax + 1) / 2 - 4 && y >= (Dy + Gy) / 2 && anty <= (Dy + Gy) / 2 + R)
        {
            stop++;
            score += puncte;
            arr[0]='/0';
            setcolor(WHITE);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            sprintf(arr,"Score:%d",score+ScoreLastNumePlayer);
            outtextxy(width/2-117,70,arr);
        }
    }
    else if ('e' == tasta)
    {
        v[++fr] = 11;
        antx = x;
        anty = y;
        outtextxy(100, height - 110, "                                                   ");
        outtextxy(100, height - 100, "                                                   ");
        outtextxy(100, height - 90, "                                                   ");
        outtextxy(100, height - 80, "                                                   ");
        if (!(x + 40 >= (Dx + Ax + 1) / 2 - 4 && y <= (Dy + Gy) / 2 + R && x <= (Dx + Ax + 1) / 2 - 4 && y - 40 >= (Dy + Gy) / 2))
        {
            Drum(x, y, x + 40, y - 40);
            x += 40;
            y -= 40;
            car1 = 7;
            if (x >= (Dx + Ax + 1) / 2 - 4 && antx <= (Dx + Ax + 1) / 2 - 4 && y >= (Dy + Gy) / 2 && anty <= (Dy + Gy) / 2 + R)
            {
                stop++;
                score += puncte;
                arr[0]='/0';
                setcolor(WHITE);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                sprintf(arr,"Score:%d",score+ScoreLastNumePlayer);
                outtextxy(width/2-117,70,arr);
            }
        }
        else
        {
            setcolor(RED);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(100, height - 110, "Nu este permisa mutarea.Trebuie sa jucati cinstit.");
            outtextxy(500, height - 80, "NU TRISA");
            setcolor(WHITE);
        }
    }
    else if ('x' == tasta)
    {
        v[++fr] = 42;
        antx = x;
        anty = y;
        outtextxy(100, height - 110, "                                                   ");
        outtextxy(100, height - 100, "                                                   ");
        outtextxy(100, height - 90, "                                                   ");
        outtextxy(100, height - 80, "                                                   ");
        if (!(x + 40 >= (Dx + Ax + 1) / 2 - 4 && x <= (Dx + Ax + 1) / 2 - 4 && y + 40 >= (Dy + Gy) / 2 && y <= (Dy + Gy) / 2 + R))
        {

            Drum(x, y, x + 40, y + 40);
            x += 40;
            y += 40;
            car1 = 6;
            if (x >= (Dx + Ax + 1) / 2 - 4 && antx <= (Dx + Ax + 1) / 2 - 4 && y >= (Dy + Gy) / 2 && anty <= (Dy + Gy) / 2 + R)
            {
                stop++;
                score += puncte;
                arr[0]='/0';
                setcolor(WHITE);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                sprintf(arr,"Score:%d",score+ScoreLastNumePlayer);
                outtextxy(width/2-117,70,arr);
            }
        }
        else
        {
            setcolor(RED);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(100, height - 110, "Nu este permisa mutarea.Trebuie sa jucati cinstit.");
            outtextxy(500, height - 80, "NU TRISA");
            setcolor(WHITE);
        }
    }
    else if ('z' == tasta)
    {
        v[++fr] = 32;
        antx = x;
        anty = y;
        outtextxy(100, height - 110, "                                                   ");
        outtextxy(100, height - 100, "                                                   ");
        outtextxy(100, height - 90, "                                                   ");
        outtextxy(100, height - 80, "                                                   ");
        Drum(x, y, x - 40, y + 40);
        x -= 40;
        y += 40;
        car1 = 4;
        if (x <= (Dx + Ax + 1) / 2 - 4 && antx >= (Dx + Ax + 1) / 2 - 4 && y <= (Dy + Gy) / 2 + R && anty <= (Dy + Gy) / 2 + R)
        {
            score += puncte;
            stop++;
            arr[0]='/0';
            setcolor(WHITE);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            sprintf(arr,"Score:%d",score+ScoreLastNumePlayer);
            outtextxy(width/2-117,70,arr);
        }
    }
}
struct threeNum
{
    int n1, n2, n3, n4;
};

void MeniulHowToPlay()
{
  while (meniulhowtoplay)
    {
        readimagefile("howtoplay.jpg", 0, 0, width, height);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(130, 30, "Welcome to the Car Rally! Here we will present some general information related to the game!");
            outtextxy(60, 70,  "Once you press the play button, you will have the opportunity to choose one of the 3 cars: tesla model s, ");
            outtextxy(40, 86,  "lamborghini aventator and F1.If the car is chosen, you will be able to choose one of the 6 rally maps, each");
            outtextxy(40, 102, "increasing in difficulty from the first to the last. At the beginning of a race you will be spawned at the ");
            outtextxy(40, 118, "finish line, where the race will start.The game is quite simple, all you have to do is keep the car on the ");
            outtextxy(40, 134, "car on the circuit, and as long as you don't go off the track, the score at the top of the screen will     ");
            outtextxy(40, 150, "increase every time you cross the finish line, only 3 rounds being required to complete the game.");
            readimagefile("tastatura.gif", 700,600, 1200, 1200);
            readimagefile("butoane.gif", 800, 50, 1460,900);
            readimagefile("jos.gif", 878,520,958,670);
            readimagefile("sus.gif", 888, 280,942,475);
            readimagefile("dreapta.gif", 940, 450,1140,520);
            readimagefile("stanga.gif", 750, 450,890,520);
            readimagefile("stanga-jos.gif", 800, 520,950,450);
            readimagefile("dreapta-jos.gif", 925, 525,1030,610);
            readimagefile("dreapta-sus.gif", 925, 385,1030,470);
            readimagefile("tesla45.gif", 980,320,1080,220);
            readimagefile("stanga-sus.gif", 800, 380,920,460);
            readimagefile("tesla325.gif", 730, 310,830, 430);

            readimagefile("tesla225.gif", 715, 570,835,470);
            readimagefile("tesla135.gif", 1000,580,1100,680);
            readimagefile("tesla90.gif", 1120,430,1225,530);
            readimagefile("tesla270.gif", 650, 440,750,540);
            readimagefile("tesla0.gif", 876, 180,952,290);
            readimagefile("tesla180.gif", 882, 660,957,760);
            readimagefile("Back.gif", 30, height - 110, 80, height - 50);
        while (meniulhowtoplay)
        {
            getmouseclick(WM_LBUTTONDOWN, mx, my);

            if (mx >= 30 && mx <= 80 && my >= height - 110 && my <= height - 50)
            {
                meniulprincipal = true;
                meniulhowtoplay = false;
                stopmen1 = 0;
            }
        }
    }
}
void sunet()
{
    getmouseclick(WM_LBUTTONDOWN, mx, my);
    pozitiemausx = mousex();
    pozitiemausy = mousey();
    if ((mx >= width - 80 && mx <= width - 10 && my >= 10 && my <= 80) && stopsunet == 0)
    {
        sndPlaySound("game start.wav", SND_ASYNC);
        sndPlaySound("ROCK IT.wav", SND_ASYNC);
        readimagefile("Sound on.gif", width - 80, 10, width - 10, 80);
        stopsunet = 1;
    }
    else if ((mx >= width - 80 && mx <= width - 10 && my >= 10 && my <= 80) && stopsunet == 1)
    {
        sndPlaySound("game start.wav", SND_ASYNC);
        readimagefile("Sound off.gif", width - 80, 10, width - 10, 80);
        PlaySound(0, 0, 0);
        stopsunet = 0;
    }

}
void exit()
{
    if (pozitiemausx >= width / 2 - 300 && pozitiemausx <= width / 2 - 140 && pozitiemausy >= height / 2 + 170 && pozitiemausy <= height / 2 + 270)
        readimagefile("Exit yellow.gif", width / 2 - 300, height / 2 + 170, width / 2 - 140, height / 2 + 277);
    else
        readimagefile("Exit.gif", width / 2 - 298, height / 2 + 170, width / 2 - 140, height / 2 + 275);
    if (mx >= width / 2 - 300 && mx <= width / 2 - 140 && my >= height / 2 + 170 && my <= height / 2 + 270)
    {
        sndPlaySound("game start.wav", SND_ASYNC);
        closegraph();
        PlaySound(0, 0, 0);
    }

}
void DeseneazaMeniulPrincipal()
{
    if (!stopmen1)
    {
        readimagefile("Rocket League.jpg", 0, 0, width, height);
        readimagefile("Sound on.gif", width - 80, 10, width - 10, 80);
        readimagefile("Auto Rally.gif", width / 2 - 100, height / 2 - 50, width / 2 + 150, height / 2 + 25);
        readimagefile("Emblem.gif", width / 2 - 220, height / 2 - 100, width / 2 - 70, height / 2 + 50);
        stopmen1 = 1;
    }
}
void howtoplay()
{
    if (pozitiemausx >= width / 2 + 125 && pozitiemausx <= width / 2 + 305 && pozitiemausy >= height / 2 + 170 && pozitiemausy <= height / 2 + 270)
        readimagefile("How to play yellow.gif", width / 2 + 125, height / 2 + 170, width / 2 + 305, height / 2 + 270);
    else
        readimagefile("How to play.gif", width / 2 + 125, height / 2 + 170, width / 2 + 305, height / 2 + 270);
    if (mx >= width / 2 + 125 && mx <= width / 2 + 305 && my >= height / 2 + 170 && my <= height / 2 + 270)
    {
        meniulhowtoplay = true;
        meniulprincipal = false;
        meniulsecundar = false;
    }
}
time_t rawTime;
struct tm* currentTime;
char c[100], curenttimp[100];
int charrasci(char a)
{
    int b;
    b = (int)a; b -= 48;
    return b;
}
int orefinal = 0, minutefinal = 0, secundefinal = 0, oreIneputjoc, minuteIneputjoc, secundeIneputjoc, ore, minute, secunde;
void timp()
{
    int a, b, d = 0, h1, h2, min1, min2, sec1, sec2;
    while (1)
    {
        rawTime = time(NULL);
        currentTime = localtime(&rawTime);
        strftime(c, 100, "%I:%M:%S %p", currentTime);
        strcpy(curenttimp, c);
        if (curenttimp[9] == 'A' && curenttimp[10] == 'M')
          {
              if(curenttimp[0]==1 && curenttimp[1]==2)
            {
                a = charrasci(curenttimp[0])-1; b = charrasci(curenttimp[1])-2;
                curenttimp[0] = '0' ; curenttimp[1] = '0';
                curenttimp[9] = '\0';
            }
           else
            curenttimp[9] = '\0';
          }
        else
            if (curenttimp[9] == 'P' && curenttimp[10] == 'M')
            {
                a = charrasci(curenttimp[0]); b = charrasci(curenttimp[1]);
                d = a * 10 + b + 12;
                curenttimp[0] = '0' + d / 10; curenttimp[1] = '0' + d % 10;
                curenttimp[9] = '\0';
            }

        //     h1=charrasci(curenttimp[0]); h2=charrasci(curenttimp[1]);
        //     min1=charrasci(curenttimp[3]); min2=charrasci(curenttimp[4]);
        //     sec1=charrasci(curenttimp[6]); sec2=charrasci(curenttimp[7]);
        //
        //     oreIneputjoc=h1*10+h2; minuteIneputjoc=min1*10+min2; secundeIneputjoc=sec1*10+sec2;

        setcolor(11);
        settextstyle(3, HORIZ_DIR, 4);
        outtextxy(width - 225, 20, c);


        strftime(c, 100, "%a, %d, %b, %Y,", currentTime);
        settextstyle(3, HORIZ_DIR, 3);
        outtextxy(width - 200, 50, c);

        delay(1000);
        break;
    }

}

struct valoaretabel
{
    char player[100];
    int points;
    char time[100];
};
valoaretabel tabelvalori[6];

struct clasament
{
    int loc;
    int score;
    char nume[100];
    char time[100];
};
    FILE* fptr;
  struct clasament tabelul;
void setuptabel()
{
    if ((fptr = fopen("clasament.bin", "r")) == NULL)
        printf("Error! opening file");
    /*
                   fptr = fopen("clasament.bin","w");
                   tabelul.loc = 1; strcpy(tabelul.nume,"MariaAreMere"); tabelul.score=9; strcpy(tabelul.time,"00:03:08");   //1
                   fwrite(&tabelul, sizeof(struct clasament), 1, fptr);
                   tabelul.loc=2; strcpy(tabelul.nume,"Stefan Salvatore"); tabelul.score=10000; strcpy(tabelul.time,"77:07:00");   //2
                   fwrite(&tabelul, sizeof(struct clasament), 1, fptr);
                   tabelul.loc=3; strcpy(tabelul.nume,"George O'Malley"); tabelul.score=870; strcpy(tabelul.time,"65:10:12");   //3
                   fwrite(&tabelul, sizeof(struct clasament), 1, fptr);
                   tabelul.loc=4; strcpy(tabelul.nume,"Anonymus"); tabelul.score=320; strcpy(tabelul.time,"14:02:03");   //4
                   fwrite(&tabelul, sizeof(struct clasament), 1, fptr);
     */

    for (int n = 1; n <= 4; ++n)
    {
        fread(&tabelul, sizeof(struct clasament), 1, fptr);
        strcpy(tabelvalori[tabelul.loc].player, tabelul.nume);
        tabelvalori[tabelul.loc].points = tabelul.score;
        ord[tabelul.loc] = tabelul.score;
        strcpy(tabelvalori[tabelul.loc].time, tabelul.time);

    }

}
int lungimenumar(int x)
{
    int nr = 0;
    if (x == 0)
        return 1;
    while (x)
    {
        x = x / 10;
        nr++;
    }
    return nr;
}

void Sort(int ord[])
{
    char auxc[1000];
    int aux, i, j;

    for (i = 1; i <= 4; i++)
    {
        for (j = i + 1; j <= 5; j++)
            if (ord[i] < ord[j])
            {

                aux = ord[i];
                ord[i] = ord[j];
                ord[j] = aux;
                aux = tabelvalori[i].points;
                tabelvalori[i].points = tabelvalori[j].points;
                tabelvalori[j].points = aux;

                strcpy(auxc, tabelvalori[i].player);
                strcpy(tabelvalori[i].player, tabelvalori[j].player);
                strcpy(tabelvalori[j].player, auxc);

                strcpy(auxc, tabelvalori[i].time);
                strcpy(tabelvalori[i].time, tabelvalori[j].time);
                strcpy(tabelvalori[j].time, auxc);

            }

    }
            fptr = fopen("clasament.bin","w");
            for(int i=1;i<=5;i++)
           {
               tabelul.loc = i; strcpy(tabelul.nume,tabelvalori[i].player); tabelul.score=tabelvalori[i].points; strcpy(tabelul.time,tabelvalori[i].time);   //1
                   fwrite(&tabelul, sizeof(struct clasament), 1, fptr);
           }

}
void tabel()
{
    char arr[100];
    Sort(ord);
    setcolor(WHITE);
    for (int i = 1; i <= 5; i++)
        if (i <= 3 && tabelvalori[i].points != -1)
        {
            settextstyle(3, 0, 3);
            outtextxy(width / 4 + width / 8 + 70, 260 + (i - 1) * 95, tabelvalori[i].player); //nume player

            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
            sprintf(arr, "%d", tabelvalori[i].points);  //scor
            outtextxy(width / 4 + width / 8 + 260 + (lungimenumar(tabelvalori[1].points) - lungimenumar(tabelvalori[i].points)) * 10, 263 + (i - 1) * 95, arr);

            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
            outtextxy(width / 4 + width / 8 + 370, 263 + (i - 1) * 95, tabelvalori[i].time);  //timp
        }
        else if (tabelvalori[i].points != -1)
        {
            settextstyle(3, 0, 3);
            outtextxy(width / 4 + width / 8 + 50, 468 + (i - 3) * 75, tabelvalori[i].player);


            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
            sprintf(arr, "%d", tabelvalori[i].points);
            outtextxy(width / 4 + width / 8 + 258 + (lungimenumar(tabelvalori[1].points) - lungimenumar(tabelvalori[i].points)) * 10, 473 + (i - 3) * 75, arr);

            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
            outtextxy(width / 4 + width / 8 + 368, 473 + (i - 3) * 75, tabelvalori[i].time);
        }
}

void CautareLastNamePlayerandaddscore()
{
    for (int i = 1; i <= 5; i++)
        if (tabelvalori[i].points != -1 && strcmp(tabelvalori[i].player, LastNumePLayer) == 0)
        {
            tabelvalori[i].points = ScoreLastNumePlayer;
            ord[i] = ScoreLastNumePlayer;
        }
}
void CautareLastNamePlayerandaddtime()
{
    for (int i = 1; i <= 5; i++)
        if (tabelvalori[i].points != -1 && strcmp(tabelvalori[i].player, LastNumePLayer) == 0)
        {
            strcpy(tabelvalori[i].time, curenttimp);
            //                tabelvalori[i].time[0]=orefinal/10;
            //                tabelvalori[i].time[1]=orefinal%10;
            //                tabelvalori[i].time[3]=minutefinal/10;
            //                tabelvalori[i].time[4]=minutefinal%10;
            //                tabelvalori[i].time[6]=secundefinal/10;
            //                tabelvalori[i].time[7]=secundefinal%10;
            //                  cout<<tabelvalori[i].time[0]<<" "<<orefinal/10<<endl;
            //                cout<<tabelvalori[i].time[1]<<" "<<orefinal%10<<endl;
            //                cout<<tabelvalori[i].time[3]<<" "<<minutefinal/10<<endl;
            //                cout<<tabelvalori[i].time[4]<<" "<<minutefinal%10<<endl;
            //                cout<<tabelvalori[i].time[6]<<" "<<secundefinal/10<<endl;
            //                cout<<tabelvalori[i].time[7]<<" "<<secundefinal%10<<endl;
            //                cout<<tabelvalori[i].time[0]<<" "<<orefinal/10<<endl;
            //                cout<<tabelvalori[i].time[1]<<" "<<orefinal%10<<endl;
            //                cout<<tabelvalori[i].time[3]<<" "<<minutefinal/10<<endl;
            //                cout<<tabelvalori[i].time[4]<<" "<<minutefinal%10<<endl;
            //                cout<<tabelvalori[i].time[6]<<" "<<secundefinal/10<<endl;
            //                cout<<tabelvalori[i].time[7]<<" "<<secundefinal%10<<endl;
        }
}
void level1()
{
    sndPlaySound("game start.wav", SND_ASYNC);
    cleardevice();
    SetUp();
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(width / 2, height / 2, WHITE);
    settextstyle(1, HORIZ_DIR, 60);
    readimagefile("Back.gif", 30, height - 110, 80, height - 50);
    arr[0] = '/0';
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    sprintf(arr, "Score:%d", score + ScoreLastNumePlayer);
    outtextxy(width / 2 - 120, 70, arr);
    outtextxy(100, height - 110, "                                                   ");
    outtextxy(100, height - 90, "                                                   ");
    outtextxy(100, height - 70, "                                                   ");
    if (masina == 0 && lamborghini == 0 && tesla == 0)
    {
        setcolor(RED);
        outtextxy(100, height - 95, "                                                  ");
        outtextxy(100, height - 110, " Press the back button and go to choose your car!  ");
    }
    Startul();
    while (!gameOver && (masina == 1 || lamborghini == 1 || tesla == 1))
    {
        Draw();
        Input();
    }
    int nr = 3;
    timp();
    CautareLastNamePlayerandaddtime();
    if (gameOvergreseala == 1)
        while (nr <= 20)
        {
            readimagefile("game over.gif", width / 2 - 150 - nr * 10 - (nr - 4) * 10, height / 2 - 300 - nr * 10, width / 2 + 50 + nr * 10 + (nr + 4) * 10, height / 2 + 100 + nr * 10 + (nr + 4) * 10);
            nr = nr + 10;
        }
    if(stop==3)
        while(nr<=20)
        {
            readimagefile("win.gif",width/2-220-nr*10,height/2-150-nr*10,width/2+180+nr*10,height/2+150+nr*10);
            nr=nr+7;
        }

    while (1)
    {
        getmouseclick(WM_LBUTTONDOWN, mx, my);
        if (mx >= 30 && mx <= 80 && my >= height - 110 && my <= height - 50)
        {
            meniulprincipal = false;
            meniulsecundar = true;
            meniulhowtoplay = false;
            stopranking = 1;
            break;
        }

    }
}

void conturpistalevel2()
{
    /*
    setcolor(WHITE);
    // readimagefile("finishline2.jpg", 1100, 830, 1150, 900);
    line(400, 200, 900, 200); // line 1;
    line(900, 200, 1050, 400); // line 2;
    line(1050, 400, 1400, 400); // line 3;
    line(1400, 400, 1550, 600); // line 4;
    line(1550, 600, 1800, 600); // line 5;
    line(1800, 600, 1800, 900); // line 6;
    line(1800, 900, 600, 900); // line 7;
    line(600, 900, 500, 700); // line 8;
    line(500, 700, 500, 500); // line 9;
    line(400, 200, 500, 500); // line 10;
    //marginea interioara;
    line(500, 270, 870, 270);   //line 1;
    line(500, 270, 580, 500);   //line 2;
    line(580, 500, 580, 700);   //line 3;
    line(580, 700, 650, 830);   //line 4;
    line(650, 830, 1725, 830);  //line 5;
    line(1725, 830, 1725, 680); // line 6;
    line(1500, 680, 1725, 680);  // line 7;
    line(1340, 470, 1500, 680);  // line 8;
    line(1020, 470, 1340, 470);  // line 9
    line(870, 270, 1020, 470);  // line 10;
    */

    int n;
    struct threeNum num;
    FILE* fptr;
    if ((fptr = fopen("nivel2.bin", "r")) == NULL)
        printf("Error! opening file");
    /*
                   fptr = fopen("nivel2.bin","w");
                   num.n1 = 1400; num.n2=400; num.n3=1550; num.n4=600;  //4
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1550; num.n2=600; num.n3=1800; num.n4=600;  //5
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =1800; num.n2=600; num.n3=1800; num.n4=900;   //6
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =1800; num.n2=900; num.n3=600; num.n4=900;   //7
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 600; num.n2=900; num.n3=500 ; num.n4=700;   //8
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =500; num.n2=700; num.n3=500; num.n4=500;     //9
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =400; num.n2=200; num.n3=500; num.n4=500;     //10
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);


                    num.n1 = 500; num.n2=270; num.n3=870; num.n4=270;   //1
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =500; num.n2=270; num.n3=580; num.n4=500;  //2
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =580; num.n2=500; num.n3=580; num.n4=700;  //3
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =580; num.n2=700; num.n3=650; num.n4=830;  //4
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 650; num.n2=830; num.n3=1725; num.n4=830;  //5
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =1725; num.n2=830; num.n3=1725; num.n4=680;   //6
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =1500; num.n2=680; num.n3=1725; num.n4=680;   //7
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =1340; num.n2=470; num.n3=1500 ; num.n4=680;   //8
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =1020; num.n2=470; num.n3=1340; num.n4=470;     //9
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =870; num.n2=270; num.n3=1020; num.n4=470;     //10
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 400; num.n2=200; num.n3=910; num.n4=200;   //1
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 910; num.n2=200; num.n3=1150; num.n4=400;     //2
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                    num.n1 =1150; num.n2=400; num.n3=1400; num.n4=400;     //3
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);

                   num.n1 =0; num.n2=0; num.n3=510; num.n4=271;     //3
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =411; num.n2=201; num.n3=0; num.n4=0;     //3
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);

                      num.n1 =(Dx + Ax + 1) / 2 - 3; num.n2=(Dy + Gy) / 2 + R - 7; num.n3=(Dx - R - r + Ax + 1 + R + r) / 2 - 3; num.n4=(Dy + Gy) / 2 + 20;  //startul
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = (Dx + Ax + 1) / 2 - 13; num.n2=(Dy + Gy) / 2 + R / 2; num.n3=0; num.n4=0;
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);

   */
    for (n = 1; n <= 20; ++n)
    {
        fread(&num, sizeof(struct threeNum), 1, fptr);
        line(num.n1, num.n2, num.n3, num.n4);

    }

    gameOver = false;
    dir = Stop;
    readimagefile("Back.jpg", 30, height - 110, 80, height - 50);
    fread(&num, sizeof(struct threeNum), 1, fptr);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(num.n1, num.n2, WHITE);  //  coloring the exterior of the rally
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(num.n3, num.n4, WHITE); // coloring the interior of the rally
    fread(&num, sizeof(struct threeNum), 1, fptr);
    setfillstyle(HATCH_FILL, GREEN);
    floodfill(num.n1, num.n2, WHITE); //col
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(num.n3, num.n4, WHITE);
    fread(&num, sizeof(struct threeNum), 1, fptr);
    fread(&num, sizeof(struct threeNum), 1, fptr);
          x=num.n1;
          y=num.n2;
        line(x,y-27,x,y+39);
        fread(&num, sizeof(struct threeNum), 1, fptr);
    antx = x;
    anty = y;
    score = 0;
}
void level2()
{
    cleardevice();
    sndPlaySound("game start.wav", SND_ASYNC);
    conturpistalevel2();
    arr[0] = '/0';
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    sprintf(arr, "Score:%d", score + ScoreLastNumePlayer);
    outtextxy(width / 2 - 120, 70, arr);
    outtextxy(100, height - 110, "                                                   ");
    outtextxy(100, height - 90, "                                                   ");
    outtextxy(100, height - 70, "                                                   ");
    readimagefile("Back.gif", 30, height - 110, 80, height - 50);
    if (masina == 0 && lamborghini == 0 && tesla == 0)
    {
        setcolor(RED);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(100, height - 80, "                                                   ");
        outtextxy(100, height - 95, "                                                   ");
        outtextxy(100, height - 110, "  Press the back button and go to choose your car! ");
    }
    timp();
    CautareLastNamePlayerandaddtime();

    while (!gameOver && (masina == 1 || lamborghini == 1 || tesla == 1))
    {
        Draw();
        Input();
    }

    int nr = 3;
    if (gameOvergreseala == 1)
        while (nr <= 20)
        {
            readimagefile("game over.gif", width / 2 - 150 - nr * 10 - (nr - 4) * 10, height / 2 - 300 - nr * 10, width / 2 + 50 + nr * 10 + (nr + 4) * 10, height / 2 + 100 + nr * 10 + (nr + 4) * 10);
            nr = nr + 10;
        }
    if(stop==3)
        while(nr<=20)
        {
            readimagefile("win.gif",width/2-220-nr*10,height/2-150-nr*10,width/2+180+nr*10,height/2+150+nr*10);
            nr=nr+7;
        }

    while (1)
    {
        getmouseclick(WM_LBUTTONDOWN, mx, my);
        if (mx >= 30 && mx <= 80 && my >= height - 110 && my <= height - 50)
        {
            meniulprincipal = false;
            meniulsecundar = true;
            meniulhowtoplay = false;
            stopranking = 1;
            break;
        }

    }

}
void conturpistalevel3()
{
    int n;
    struct threeNum num;
    FILE* fptr;
    if ((fptr = fopen("nivelul3.bin", "r")) == NULL)
        printf("Error! opening file");
    /*
                   fptr = fopen("nivelul3.bin","w");
                   num.n1 = 500; num.n2=500 - 70; num.n3=1200; num.n4=500 - 70;   //1
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =1200; num.n2=500 - 70; num.n3=1350; num.n4=650 - 70;  //2
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =1350; num.n2=650 - 70; num.n3=1600; num.n4=650 - 70;  //3
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1600; num.n2=650 - 70; num.n3=1600; num.n4=800 - 70;  //4
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1600; num.n2=800 - 70; num.n3=1300; num.n4=900 - 70;  //5
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1300; num.n2=900 - 70; num.n3=850; num.n4=900 - 70;   //6
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =850; num.n2=900 - 70; num.n3=700; num.n4=800 - 70;   //7
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 700; num.n2=800 - 70; num.n3=500; num.n4=800 - 70;   //8
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 500; num.n2=800 - 70; num.n3=350; num.n4=900 - 70;     //9
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 350; num.n2=900 - 70; num.n3=200; num.n4=700 - 70;     //10
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 200; num.n2=700 - 70; num.n3=500; num.n4=500 - 70;  	//11
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 830; num.n2=970 - 70; num.n3=1330; num.n4=970 - 70;		//12
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1330; num.n2=970 - 70; num.n3=1700 ; num.n4=830 - 70;  	//13
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1700; num.n2=830 - 70; num.n3=1700; num.n4=580 - 70;	//14
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1700; num.n2=580 - 70; num.n3=1580; num.n4=580 - 70;    //15
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1580; num.n2=580 - 70; num.n3=1300; num.n4=200 - 70;   //16
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1480; num.n2=580 - 70; num.n3=1380; num.n4=580 - 70;	//17
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1380; num.n2=580 - 70; num.n3=1210; num.n4=410 - 70;	//18
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1210; num.n2=410 - 70; num.n3=500; num.n4=410 - 70;		//19
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =500; num.n2=410 - 70; num.n3=150; num.n4=630 - 70;		//20
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 150; num.n2=630 - 70; num.n3=150; num.n4=280 - 70;   //21
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 150; num.n2=280 - 70; num.n3=1250; num.n4=280 - 70;   //22
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1250; num.n2=210; num.n3=1480; num.n4=580 - 70;   	//23
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1300; num.n2=200 - 70; num.n3=80; num.n4=200 - 70;	//24
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 80; num.n2=200 - 70; num.n3=80; num.n4=700 - 70;	//25
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 300; num.n2=1020 - 70; num.n3=80; num.n4=700 - 70;    //26
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 300; num.n2=1020 - 70; num.n3=500; num.n4=880 - 70;  	//27
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =500; num.n2=880 - 70; num.n3=680; num.n4=880 - 70;		//28
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =680; num.n2=810; num.n3=830; num.n4=970 - 70; 	//29
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =(Dx + Ax + 1) / 2 - 3; num.n2=(Dy + Gy) / 2 + R - 7; num.n3=(Dx - R - r + Ax + 1 + R + r) / 2 - 3; num.n4=(Dy + Gy) / 2 + 20;  //startul
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 =(Dx - R - r + Ax + 1 + R + r) / 2 - 4; num.n2=(Dy + Gy) / 2 + R - 7; num.n3=(Dx - R - r + Ax + 1 + R + r) / 2 - 4; num.n4=(Dy + Gy) / 2 + 20;  //startul
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = (Dx + Ax + 1) / 2 - 13; num.n2=(Dy + Gy) / 2 + R / 2; num.n3=0; num.n4=0;
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 0; num.n2=0; num.n3=1230; num.n4=220;
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 0; num.n2=0; num.n3=1230; num.n4=220;
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 300; num.n2=700; num.n3=690; num.n4=810;
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 300; num.n2=700; num.n3=690; num.n4=810;
   */
    for (n = 1; n <= 29; ++n)
    {
        fread(&num, sizeof(struct threeNum), 1, fptr);
        line(num.n1, num.n2, num.n3, num.n4);
    }

    fread(&num, sizeof(struct threeNum), 1, fptr);
    line(num.n1, num.n2, num.n3, num.n4);
    fread(&num, sizeof(struct threeNum), 1, fptr);
    fread(&num, sizeof(struct threeNum), 1, fptr);
    x=num.n1;
    y=num.n2;
    fread(&num, sizeof(struct threeNum), 1, fptr);
    fread(&num, sizeof(struct threeNum), 1, fptr);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(num.n1, num.n2, WHITE);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(num.n3, num.n4, WHITE);
    fread(&num, sizeof(struct threeNum), 1, fptr);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(num.n1, num.n2, WHITE);
    setfillstyle(HATCH_FILL, GREEN);
    floodfill(num.n3, num.n4, WHITE);
    fread(&num, sizeof(struct threeNum), 1, fptr);
    fread(&num, sizeof(struct threeNum), 1, fptr);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(num.n1, num.n2, WHITE);

    gameOver = false;
    dir = Stop;
    readimagefile("Back.jpg", 30, height - 110, 80, height - 50);
    setcolor(RED);

    antx = x;
    anty = y;
    score = 0;
}

void level3()
{
    cleardevice();
    sndPlaySound("game start.wav", SND_ASYNC);
    conturpistalevel3();
    arr[0] = '/0';
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    sprintf(arr, "Score:%d", score + ScoreLastNumePlayer);
    outtextxy(width / 2 - 120, 70, arr);
    outtextxy(100, height - 110, "                                                   ");
    outtextxy(100, height - 90, "                                                   ");
    outtextxy(100, height - 70, "                                                   ");
    readimagefile("Back.gif", 30, height - 110, 80, height - 50);
    if (masina == 0 && lamborghini == 0 && tesla == 0)
    {
        setcolor(RED);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(100, height - 80, "                                                   ");
        outtextxy(100, height - 95, "                                                   ");
        outtextxy(100, height - 110, "  Press the back button and go to choose your car! ");
    }
    timp();
    CautareLastNamePlayerandaddtime();
    while (!gameOver && (masina == 1 || lamborghini == 1 || tesla == 1))
    {
        Draw();
        Input();
    }
    int nr = 3;
    if (gameOvergreseala == 1)
        while (nr <= 20)
        {
            readimagefile("game over.gif", width / 2 - 150 - nr * 10 - (nr - 4) * 10, height / 2 - 300 - nr * 10, width / 2 + 50 + nr * 10 + (nr + 4) * 10, height / 2 + 100 + nr * 10 + (nr + 4) * 10);
            nr = nr + 10;
        }
    if(stop==3)
        while(nr<=20)
        {
            readimagefile("win.gif",width/2-220-nr*10,height/2-150-nr*10,width/2+180+nr*10,height/2+150+nr*10);
            nr=nr+7;
        }
    while (1)
    {
        getmouseclick(WM_LBUTTONDOWN, mx, my);
        if (mx >= 30 && mx <= 80 && my >= height - 110 && my <= height - 50)
        {
            meniulprincipal = false;
            meniulsecundar = true;
            meniulhowtoplay = false;
            stopranking = 1;
            break;
        }

    }

}
void conturpistalevel4()
{
				int n;
				struct threeNum num;
				FILE *fptr;
                if ((fptr = fopen("level4.bin","r")) == NULL)
					printf("Error! opening file");
             /*
                            fptr = fopen("level4.bin","w");
            num.n1=1400; num.n2=930; num.n3=1600; num.n4=850;    //4
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1 =1400; num.n2=850; num.n3=1650; num.n4=650;    //5
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1 =1600; num.n2=850; num.n3=1750; num.n4=650;    //6
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1650; num.n2=650; num.n3=1650; num.n4=450;    //7
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1750; num.n2=650; num.n3=1750; num.n4=430;    //8
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1650; num.n2=450; num.n3=1580; num.n4=350;    //9
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1750; num.n2=430; num.n3=1610; num.n4=250;    //10
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1580; num.n2=350; num.n3=1470; num.n4=350;    //11
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1610; num.n2=250; num.n3=1470; num.n4=250;    //12
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1470; num.n2=350; num.n3=1400; num.n4=380;    //13
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1470; num.n2=250; num.n3=1400; num.n4=280;    //14
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1400; num.n2=280; num.n3=1300; num.n4=280;    //15
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1400; num.n2=380; num.n3=1300; num.n4=380;    //16
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1300; num.n2=280; num.n3=1250; num.n4=250;    //17
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1300; num.n2=380; num.n3=1150; num.n4=250;    //18
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1250; num.n2=250; num.n3=1300; num.n4=200;    //19
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1150; num.n2=250; num.n3=1200; num.n4=200;    //20
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1300; num.n2=200; num.n3=1300; num.n4=100;    //21
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1200; num.n2=200; num.n3=1200; num.n4=170;    //22
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1300; num.n2=100; num.n3=1230; num.n4=50;    //23
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1200; num.n2=170; num.n3=1180; num.n4=130;    //24
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1230; num.n2=50; num.n3=1140; num.n4=50;    //25
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1180; num.n2=130; num.n3=1130; num.n4=130;    //26
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1140; num.n2=50; num.n3=1000; num.n4=170;    //27
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1130; num.n2=130; num.n3=1080; num.n4=170;    //28
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1080; num.n2=170; num.n3=1080; num.n4=400;    //29
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1000; num.n2=170; num.n3=1000; num.n4=430;    //30
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1080; num.n2=400; num.n3=1180; num.n4=470;    //31
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1000; num.n2=430; num.n3=1100; num.n4=500;    //32
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1180; num.n2=470; num.n3=1180; num.n4=500;    //33
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1100; num.n2=500; num.n3=1100; num.n4=530;    //34
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1180; num.n2=500; num.n3=1230; num.n4=540;    //35
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1100; num.n2=530; num.n3=1210; num.n4=610;    //36
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1230; num.n2=540; num.n3=1450; num.n4=540;    //37

            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1210; num.n2=610; num.n3=1420; num.n4=610;    //38
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1450; num.n2=540; num.n3=1530; num.n4=590;    //39
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1420; num.n2=610; num.n3=1450; num.n4=630;    //40
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1530; num.n2=590; num.n3=1530; num.n4=700;    //41
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1450; num.n2=630; num.n3=1450; num.n4=680;    //42
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1530; num.n2=700; num.n3=1400; num.n4=830;    //43
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1450; num.n2=680; num.n3=1380; num.n4=760;    //44

            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1400; num.n2=830; num.n3=1300; num.n4=790;    //45
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1380; num.n2=760; num.n3=1280; num.n4=720;    //46
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1300; num.n2=790; num.n3=1200; num.n4=790;    //47
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1280; num.n2=720; num.n3=1200; num.n4=720;    //48
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1200; num.n2=790; num.n3=1100; num.n4=730;    //49
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1200; num.n2=720; num.n3=1100; num.n4=650;    //50
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1100; num.n2=730; num.n3=860; num.n4=730;    //51
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1100; num.n2=650; num.n3=900; num.n4=650;    //52

            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=860; num.n2=730; num.n3=770; num.n4=650;    //53
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=900; num.n2=650; num.n3=860; num.n4=630;    //54
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=770; num.n2=650; num.n3=770; num.n4=250;    //55
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=860; num.n2=630; num.n3=860; num.n4=250;    //56
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=770; num.n2=250; num.n3=820; num.n4=200;    //57
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=860; num.n2=250; num.n3=930; num.n4=190;    //58
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=720; num.n2=120; num.n3=600; num.n4=120;    //63
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=720; num.n2=120; num.n3=820; num.n4=200;    //newline2
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=750; num.n2=50; num.n3=580; num.n4=50;    //64
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=750; num.n2=50; num.n3=930; num.n4=190;    //newline1
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=580; num.n2=50; num.n3=500; num.n4=100;    //65
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=600; num.n2=120; num.n3=580; num.n4=130;    //66
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=500; num.n2=100; num.n3=500; num.n4=500;    //67
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=580; num.n2=130; num.n3=580; num.n4=530;    //68
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=500; num.n2=500; num.n3=400; num.n4=600;    //69
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=580; num.n2=530; num.n3=490; num.n4=600;    //70
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=400; num.n2=600; num.n3=400; num.n4=800;    //71
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=490; num.n2=600; num.n3=490; num.n4=750;    //72
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=400; num.n2=800; num.n3=600; num.n4=905;    //73
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=490; num.n2=750; num.n3=600; num.n4=812;    //74
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1250; num.n2=905; num.n3=600; num.n4=905;    //75
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1300; num.n2=812; num.n3=600; num.n4=812;    //76
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1250; num.n2=905; num.n3=1400; num.n4=930;    //77
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
            num.n1=1300; num.n2=812; num.n3=1400; num.n4=850;    //78
            fwrite(&num, sizeof(struct threeNum), 1, fptr);

            num.n1=1300; num.n2=840; num.n3=691; num.n4=609;
            fwrite(&num, sizeof(struct threeNum), 1, fptr);
               */
				 initwindow(1920, 1080);
			for(n = 1; n <=73; ++n)
		{
              fread(&num, sizeof(struct threeNum), 1, fptr);
		     line(num.n1,num.n2,num.n3,num.n4);
		}
    gameOver = false;
    dir = Stop;
    readimagefile("Back.jpg", 30, height - 110, 80, height - 50);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(0, 0, WHITE);
      fread(&num, sizeof(struct threeNum), 1, fptr);
    setfillstyle(HATCH_FILL, GREEN);
    floodfill(num.n1, num.n2, WHITE);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(num.n3, num.n4, WHITE);

    setcolor(RED);
    line((Dx - R - r + Ax + 1 + R + r) / 2 - 3, (Dy + Gy) / 2 + R - 7, (Dx - R - r + Ax + 1 + R + r) / 2 - 3, (Dy + Gy) / 2 + 10);
    line((Dx - R - r + Ax + 1 + R + r) / 2 - 4, (Dy + Gy) / 2 + R - 7, (Dx - R - r + Ax + 1 + R + r) / 2 - 4, (Dy + Gy) / 2 + 10);
    setcolor(BLACK);
    x = (Dx + Ax + 1) / 2 - 13;
    y = (Dy + Gy) / 2 + R / 2;
    antx = x;
    anty = y;
    score = 0;
}

void level4()
{
    cleardevice();
    sndPlaySound("game start.wav", SND_ASYNC);
    conturpistalevel4();
    arr[0] = '/0';
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    sprintf(arr, "Score:%d", score + ScoreLastNumePlayer);
    outtextxy(width / 2 - 120, 70, arr);
    outtextxy(100, height - 110, "                                                   ");
    outtextxy(100, height - 90, "                                                   ");
    outtextxy(100, height - 70, "                                                   ");
    readimagefile("Back.gif", 30, height - 110, 80, height - 50);
    if (masina == 0 && lamborghini == 0 && tesla == 0)
    {
        setcolor(RED);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(100, height - 80, "                                                   ");
        outtextxy(100, height - 95, "                                                   ");
        outtextxy(100, height - 110, "  Press the back button and go to choose your car! ");
    }
    timp();
    CautareLastNamePlayerandaddtime();
    while (!gameOver && (masina == 1 || lamborghini == 1 || tesla == 1))
    {
        Draw();
        Input();
    }
    int nr = 3;
    if (gameOvergreseala == 1)
        while (nr <= 20)
        {
            readimagefile("game over.gif", width / 2 - 150 - nr * 10 - (nr - 4) * 10, height / 2 - 300 - nr * 10, width / 2 + 50 + nr * 10 + (nr + 4) * 10, height / 2 + 100 + nr * 10 + (nr + 4) * 10);
            nr = nr + 10;
        }
    if(stop==3)
        while(nr<=20)
        {
            readimagefile("win.gif",width/2-220-nr*10,height/2-150-nr*10,width/2+180+nr*10,height/2+150+nr*10);
            nr=nr+7;
        }

    while (1)
    {
        getmouseclick(WM_LBUTTONDOWN, mx, my);
        if (mx >= 30 && mx <= 80 && my >= height - 110 && my <= height - 50)
        {
            meniulprincipal = false;
            meniulsecundar = true;
            meniulhowtoplay = false;
            stopranking = 1;
            break;
        }

    }

}
void conturpistalevel5()
{
    int n;
    struct threeNum num;
    FILE* fptr;
    if ((fptr = fopen("nivelul5.bin", "r")) == NULL)
        printf("Error! opening file");
    /*
                   fptr = fopen("nivelul5.bin","w");

                   num.n1 = 400; num.n2=920; num.n3=1600; num.n4=920;   //1
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 450; num.n2=850; num.n3=800; num.n4=850;  //2
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 900; num.n2=850; num.n3=1300; num.n4=850;  //3
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1400; num.n2=850; num.n3=1550; num.n4=850;  //4
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1550; num.n2=850; num.n3=1610; num.n4=820;  //5
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1600; num.n2=920; num.n3=1670; num.n4=870;   //6
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1610; num.n2=820; num.n3=1630; num.n4=790;   //7
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1670; num.n2=870; num.n3=1720; num.n4=790;   //8
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1630; num.n2=790; num.n3=1630; num.n4=450;     //9
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1720; num.n2=790; num.n3=1720; num.n4=450;     //10
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1400; num.n2=850; num.n3=1350; num.n4=800;  	//11
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1300; num.n2=850; num.n3=1240; num.n4=790;		//12
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1350; num.n2=800; num.n3=1300; num.n4=700;  	//13
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1240; num.n2=790; num.n3=1200; num.n4=690;		//14
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1300; num.n2=700; num.n3=1300; num.n4=550;    //15
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1300; num.n2=550; num.n3=1350; num.n4=450;   //16
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1350; num.n2=450; num.n3=1400; num.n4=430;		//17
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1400; num.n2=430; num.n3=1600; num.n4=430;		//18
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1630; num.n2=450; num.n3=1600; num.n4=430;		//19
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1720; num.n2=450; num.n3=1680; num.n4=380;		//20
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1680; num.n2=380; num.n3=1640; num.n4=360;   //21
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1640; num.n2=360; num.n3=1300; num.n4=360; 	//22
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 800; num.n2=850; num.n3=850; num.n4=800;   	//23
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 900; num.n2=850; num.n3=950; num.n4=790;		//24
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 850; num.n2=800; num.n3=890; num.n4=670;		//25
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 950; num.n2=790; num.n3=970; num.n4=680;    	//26
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 970; num.n2=680; num.n3=1000; num.n4=630;  	//27
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1200; num.n2=690; num.n3=1150; num.n4=630;		//28
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1000; num.n2=630; num.n3=1150; num.n4=630; 	//29
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 890; num.n2=670; num.n3=915; num.n4=630;  //30
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 915; num.n2=630; num.n3=915; num.n4=550;	//31
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 915; num.n2=550; num.n3=880; num.n4=490;	//32
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1000; num.n2=570; num.n3=1215; num.n4=570;		//33
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1215; num.n2=570; num.n3=1230; num.n4=530;	//34
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1230; num.n2=530; num.n3=1220; num.n4=430; 	//35
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1220; num.n2=430; num.n3=950; num.n4=430;		//36
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 950; num.n2=430; num.n3=1000; num.n4=500;	//37
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1000; num.n2=500; num.n3=1000; num.n4=570;	//38
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1220; num.n2=360; num.n3=950; num.n4=360;	//39
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1220; num.n2=360; num.n3=1190; num.n4=250;  	//40
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1300; num.n2=360; num.n3=1270; num.n4=220; 	//41
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1190; num.n2=250; num.n3=1150; num.n4=220; 	//42
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1270; num.n2=220; num.n3=1190; num.n4=140; //43
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1190; num.n2=140; num.n3=900; num.n4=140;  	//44
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1150; num.n2=220; num.n3=950; num.n4=220;		//45
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 900; num.n2=140; num.n3=830; num.n4=190;   	//46
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 950; num.n2=220; num.n3=900; num.n4=250; 	//47
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 900; num.n2=250; num.n3=900; num.n4=300;  	//48
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 900; num.n2=300; num.n3=950; num.n4=360;	//49
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 830; num.n2=190; num.n3=830; num.n4=350;	//50
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 880; num.n2=490; num.n3=880; num.n4=430;	//51
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);

                   num.n1 = 880; num.n2=430; num.n3=700; num.n4=430;	//52
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 830; num.n2=350; num.n3=800; num.n4=370;		//53
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);

                   num.n1 = 800; num.n2=370; num.n3=700; num.n4=370;		//54
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);

                   num.n1 = 400; num.n2=920; num.n3=280; num.n4=860;    //55
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 280; num.n2=710; num.n3=450; num.n4=850;     //56
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 280; num.n2=860; num.n3=150; num.n4=700;   //57
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 280; num.n2=710; num.n3=280; num.n4=550;       //58
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 150; num.n2=700; num.n3=150; num.n4=550;      //59
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 280; num.n2=550; num.n3=350; num.n4=430;      //60
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 150; num.n2=550; num.n3=250; num.n4=370;       //61
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 350; num.n2=430; num.n3=700; num.n4=430;     //62
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 250; num.n2=370; num.n3=800; num.n4=370;		//63
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 932; num.n2=917; num.n3=932; num.n4=853;  //startul
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 931; num.n2=917; num.n3=931; num.n4=853;  //startul
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 360; num.n2=810; num.n3=0; num.n4=0;
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 0; num.n2=0; num.n3=285; num.n4=710;
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 905; num.n2=250; num.n3=1005; num.n4=550;
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
                   num.n1 = 1355; num.n2=450; num.n3=905; num.n4=845;
                   fwrite(&num, sizeof(struct threeNum), 1, fptr);
   */

    for (n = 1; n <= 63; ++n)
    {
        fread(&num, sizeof(struct threeNum), 1, fptr);
        line(num.n1, num.n2, num.n3, num.n4);
    }

    fread(&num, sizeof(struct threeNum), 1, fptr);
    line(num.n1, num.n2, num.n3, num.n4);
    fread(&num, sizeof(struct threeNum), 1, fptr);
    line(num.n1, num.n2, num.n3, num.n4);
    x = (num.n1 + num.n3-10) / 2; y = (num.n2 + num.n4) / 2;
    /*
    line(932,917,932,853);
line(931,917,931,853);
//931
//858
    */

    fread(&num, sizeof(struct threeNum), 1, fptr);
    setfillstyle(HATCH_FILL, GREEN);
    floodfill(num.n1, num.n2, WHITE);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(num.n3, num.n4, WHITE);
    for (n = 1; n <= 3; n++)
    {
        fread(&num, sizeof(struct threeNum), 1, fptr);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(num.n1, num.n2, WHITE);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(num.n3, num.n4, WHITE);
    }
    gameOver = false;
    dir = Stop;
    readimagefile("Back.jpg", 30, height - 110, 80, height - 50);
    score = 0;
}
void level5()
{
    cleardevice();
    sndPlaySound("game start.wav", SND_ASYNC);
    conturpistalevel5();
    arr[0] = '/0';
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    sprintf(arr, "Score:%d", score + ScoreLastNumePlayer);
    outtextxy(width / 2 - 120, 70, arr);
    outtextxy(100, height - 110, "                                                   ");
    outtextxy(100, height - 90, "                                                   ");
    outtextxy(100, height - 70, "                                                   ");
    readimagefile("Back.gif", 30, height - 110, 80, height - 50);
    if (masina == 0 && lamborghini == 0 && tesla == 0)
    {
        setcolor(RED);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(100, height - 80, "                                                   ");
        outtextxy(100, height - 95, "                                                   ");
        outtextxy(100, height - 110, "  Press the back button and go to choose your car! ");
    }
    timp();
    CautareLastNamePlayerandaddtime();
    while (!gameOver && (masina == 1 || lamborghini == 1 || tesla == 1))
    {
        Draw();
        Input();
    }
    int nr = 3;
    if (gameOvergreseala == 1)
        while (nr <= 20)
        {
            readimagefile("game over.gif", width / 2 - 150 - nr * 10 - (nr - 4) * 10, height / 2 - 300 - nr * 10, width / 2 + 50 + nr * 10 + (nr + 4) * 10, height / 2 + 100 + nr * 10 + (nr + 4) * 10);
            nr = nr + 10;
        }
     if(stop==3)
        while(nr<=20)
        {
            readimagefile("win.gif",width/2-220-nr*10,height/2-150-nr*10,width/2+180+nr*10,height/2+150+nr*10);
            nr=nr+7;
        }

    while (1)
    {

        getmouseclick(WM_LBUTTONDOWN, mx, my);
        if (mx >= 30 && mx <= 80 && my >= height - 110 && my <= height - 50)
        {
            meniulprincipal = false;
            meniulsecundar = true;
            meniulhowtoplay = false;
            stopranking = 1;
            break;
        }

    }
}
void conturpistalevel6()
{
        int n;
        struct threeNum num;
        FILE *fptr;
        fptr = fopen("level6.bin","r");

 /*
                fptr = fopen("level6.bin","w");
num.n1=650; num.n2=350; num.n3=550; num.n4=300;    //11
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1060; num.n2=320; num.n3=1170; num.n4=300;    //12
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=650; num.n2=700; num.n3=550; num.n4=700;    //13
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1050; num.n2=680; num.n3=1170; num.n4=700;    //14
num.n1=550; num.n2=300; num.n3=280; num.n4=300;    //15
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1170; num.n2=300; num.n3=1440; num.n4=300;    //16
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=550; num.n2=700; num.n3=280; num.n4=700;    //17
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1170; num.n2=700; num.n3=1440; num.n4=700;    //18
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=280; num.n2=300; num.n3=170; num.n4=400;    //19
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1440; num.n2=300; num.n3=1570; num.n4=400;    //20
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=280; num.n2=700; num.n3=170; num.n4=600;    //21
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1440; num.n2=700; num.n3=1570; num.n4=600;    //22
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=170; num.n2=400; num.n3=170; num.n4=600;    //23
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1570; num.n2=400; num.n3=1570; num.n4=600;    //24
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=750; num.n2=270; num.n3=950; num.n4=270;    //25
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=750; num.n2=820; num.n3=950; num.n4=820;    //26
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=750; num.n2=270; num.n3=720; num.n4=310;    //27
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=950; num.n2=270; num.n3=980; num.n4=310;    //28
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=750; num.n2=820; num.n3=720; num.n4=780;    //29
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=950; num.n2=820; num.n3=980; num.n4=780;    //30
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=720; num.n2=310; num.n3=720; num.n4=380;    //31
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=980; num.n2=310; num.n3=980; num.n4=380;    //32
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=720; num.n2=780; num.n3=720; num.n4=630;    //33
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=980; num.n2=780; num.n3=980; num.n4=610;    //34
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=720; num.n2=380; num.n3=690; num.n4=400;    //35
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=980; num.n2=380; num.n3=1020; num.n4=400;    //36
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=720; num.n2=630; num.n3=690; num.n4=610;    //37
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=980; num.n2=610; num.n3=1020; num.n4=600;    //38
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=690; num.n2=400; num.n3=640; num.n4=400;    //39
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1020; num.n2=400; num.n3=1070; num.n4=400;    //40
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=690; num.n2=610; num.n3=540; num.n4=640;    //41
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=640; num.n2=400; num.n3=540; num.n4=360;    //42
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=640; num.n2=400; num.n3=540; num.n4=360;    //43
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1070; num.n2=400; num.n3=1180; num.n4=350;    //44
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1020; num.n2=600; num.n3=1180; num.n4=635;    //46
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=540; num.n2=360; num.n3=330; num.n4=360;    //47
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1180; num.n2=350; num.n3=1390; num.n4=350;    //48
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=540; num.n2=640; num.n3=330; num.n4=640;    //49
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1180; num.n2=635; num.n3=1390; num.n4=635;    //50
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=330; num.n2=360; num.n3=245; num.n4=430;    //51
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1390; num.n2=350; num.n3=1500; num.n4=430;    //52
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=330; num.n2=640; num.n3=245; num.n4=580;    //53
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1390; num.n2=635; num.n3=1500; num.n4=580;    //54
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=245; num.n2=430; num.n3=245; num.n4=580;    //55
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1500; num.n2=430; num.n3=1500; num.n4=580;    //56
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=700; num.n2=190; num.n3=1000; num.n4=190;    //1
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=700; num.n2=900; num.n3=1000; num.n4=900;    //2
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=700; num.n2=190; num.n3=650; num.n4=250;    //3
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=650; num.n2=840; num.n3=700; num.n4=900;    //4
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1000; num.n2=190; num.n3=1060; num.n4=250;    //5
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=650; num.n2=250; num.n3=650; num.n4=350;    //7
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1060; num.n2=250; num.n3=1060; num.n4=320;    //8
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=650; num.n2=840; num.n3=650; num.n4=700;    //9
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1050; num.n2=840; num.n3=1050; num.n4=680;    //10
fwrite(&num, sizeof(struct threeNum), 1, fptr);
num.n1=1000; num.n2=900; num.n3=1050; num.n4=840;    //6
fwrite(&num, sizeof(struct threeNum), 1, fptr);
   */
			for(n = 1; n <=62; ++n)
		{
              fread(&num, sizeof(struct threeNum), 1, fptr);
		     line(num.n1,num.n2,num.n3,num.n4);

		}
    line(1000, 900, 1050, 840);
    line(1050, 840, 1050, 680);
    line(1050, 680, 1170, 700);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(0,0, WHITE); // coloring the interior of the rally
    setfillstyle(HATCH_FILL, GREEN);
    floodfill(900, 835, WHITE); //col
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(900,700, WHITE);

    x = 900;
    y = 835;
    gameOver = false;
    dir = Stop;
    readimagefile("Back.jpg", 30, height - 110, 80, height - 50);
    score = 0;

}
void level6()
{
    cleardevice();
    sndPlaySound("game start.wav", SND_ASYNC);
    conturpistalevel6();
    Startul();
    arr[0] = '/0';
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    sprintf(arr, "Score:%d", score + ScoreLastNumePlayer);
    outtextxy(width / 2 - 120, 70, arr);
    outtextxy(100, height - 110, "                                                   ");
    outtextxy(100, height - 90, "                                                   ");
    outtextxy(100, height - 70, "                                                   ");
    readimagefile("Back.gif", 30, height - 110, 80, height - 50);
    if (masina == 0 && lamborghini == 0 && tesla == 0)
    {
        setcolor(RED);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(100, height - 80, "                                                   ");
        outtextxy(100, height - 95, "                                                   ");
        outtextxy(100, height - 110, "  Press the back button and go to choose your car! ");
    }
    timp();
    CautareLastNamePlayerandaddtime();
    while (!gameOver && (masina == 1 || lamborghini == 1 || tesla == 1))
    {
        Draw();
        Input();
    }
    int nr = 3;
    if (gameOvergreseala == 1)
        while (nr <= 20)
        {
            readimagefile("game over.gif", width / 2 - 150 - nr * 10 - (nr - 4) * 10, height / 2 - 300 - nr * 10, width / 2 + 50 + nr * 10 + (nr + 4) * 10, height / 2 + 100 + nr * 10 + (nr + 4) * 10);
            nr = nr + 10;
        }
    if(stop==3)
        while(nr<=20)
        {
            readimagefile("win.gif",width/2-220-nr*10,height/2-150-nr*10,width/2+180+nr*10,height/2+150+nr*10);
            nr=nr+7;
        }

    while (1)
    {
        getmouseclick(WM_LBUTTONDOWN, mx, my);
        if (mx >= 30 && mx <= 80 && my >= height - 110 && my <= height - 50)
        {
            meniulprincipal = false;
            meniulsecundar = true;
            meniulhowtoplay = false;
            stopranking = 1;
            break;
        }

    }

}
void car()
{
    stopmentesla = 1;
    stopmenlamburghini = 1;
    stopmencar = 1;
    while (ok)
    {
        getmouseclick(WM_LBUTTONDOWN, mx, my);
        if (mx >= (width / 2 + width / 2 - width / 4 - 57) && my >= 150 && mx <= (width / 2 + width / 2 - width / 4 + 157) && my <= 250)
        {
            tesla = 1;
            readimagefile("meniu yellow.gif", width / 2 + width / 2 - width / 4 - 57, 150, width / 2 + width / 2 - width / 4 + 164, 253);
            readimagefile("tesla meniu.gif", width / 2 + width / 2 - width / 4 - 57, 157, width / 2 + width / 2 - width / 4 + 160, 257);
            ok = 0;
        }
        else if (stopmentesla)
        {
            tesla = 0;
            stopmentesla = 0;
            readimagefile("meniu.gif", width / 2 + width / 2 - width / 4 - 57, 150, width / 2 + width / 2 - width / 4 + 157, 250);
            readimagefile("tesla meniu.gif", width / 2 + width / 2 - width / 4 - 57, 157, width / 2 + width / 2 - width / 4 + 160, 257);
        }

        if (mx >= (width / 2 + width / 2 - width / 4 - 57) && my >= 268 && mx <= (width / 2 + width / 2 - width / 4 + 157) && my <= 378)
        {

            lamborghini = 1;
            readimagefile("meniu yellow.gif", width / 2 + width / 2 - width / 4 - 57, 264, width / 2 + width / 2 - width / 4 + 160, 363);
            readimagefile("Lamborghini meniu.gif", width / 2 + width / 2 - width / 4 - 27, 291, width / 2 + width / 2 - width / 4 + 132, 335);
            ok = 0;
        }
        else if (stopmenlamburghini)
        {
            lamborghini = 0;
            stopmenlamburghini = 0;
            readimagefile("meniu.gif", width / 2 + width / 2 - width / 4 - 57, 266, width / 2 + width / 2 - width / 4 + 157, 360);
            readimagefile("Lamborghini meniu.gif", width / 2 + width / 2 - width / 4 - 27, 291, width / 2 + width / 2 - width / 4 + 132, 335);
        }

        if (mx >= (width / 2 + width / 2 - width / 4 - 52) && my >= 386 && mx <= (width / 2 + width / 2 - width / 4 + 157) && my <= 486)
        {
            masina = 1;
            readimagefile("meniu yellow.gif", width / 2 + width / 2 - width / 4 - 52, 382, width / 2 + width / 2 - width / 4 + 162, 491);
            readimagefile("Car meniu.gif", width / 2 + width / 2 - width / 4 - 27, 401, width / 2 + width / 2 - width / 4 + 132, 476);
            ok = 0;
        }
        else if (stopmencar)
        {
            masina = 0;
            stopmencar = 0;
            readimagefile("meniu.gif", width / 2 + width / 2 - width / 4 - 52, 384, width / 2 + width / 2 - width / 4 + 160, 488);
            readimagefile("Car meniu.gif", width / 2 + width / 2 - width / 4 - 27, 401, width / 2 + width / 2 - width / 4 + 132, 476);
        }
        if (mx >= width / 2 + width / 2 - width / 4 - 50 && my >= 50 && mx <= width / 2 + width / 2 - width / 4 + 150 && my <= 140 && stopbody == 1)
        {
            stopbody = 0;
            readimagefile("Body.gif", width / 2 + width / 2 - width / 4 - 50, 48, width / 2 + width / 2 - width / 4 + 148, 142);
            readimagefile("body reparare.gif", width / 2 + width / 2 - width / 4 - 67, 140, width / 2 + width / 2 - width / 4 + 170, 498);
            ok = 0;
        }
    }
}
   int stoplevel5;
void MeniulSecundar()
{
    while (meniulsecundar)
    {
        readimagefile("meniu3.gif", 0, 0, width, height);
        readimagefile("levels.gif", width / 4 - 140, 50, width / 4 + 20, 145);
        readimagefile("Ranking.gif", width / 2 - 95, 50, width / 2 + 85, 145);
        readimagefile("Body.gif", width / 2 + width / 2 - width / 4 - 50, 48, width / 2 + width / 2 - width / 4 + 148, 142);
        ok = 0;
        readimagefile("Back.gif", 30, height - 110, 80, height - 50);
        while (meniulsecundar)
        {
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if (mx >= width / 2 + width / 2 - width / 4 - 50 && my >= 50 && mx <= width / 2 + width / 2 - width / 4 + 150 && my <= 140 && stopbody == 1)
            {
                stopbody = 0;
                readimagefile("Body.gif", width / 2 + width / 2 - width / 4 - 50, 48, width / 2 + width / 2 - width / 4 + 148, 142);
                readimagefile("body reparare.gif", width / 2 + width / 2 - width / 4 - 67, 140, width / 2 + width / 2 - width / 4 + 170, 498);
                ok = 0;

            }
            else if (mx >= width / 2 + width / 2 - width / 4 - 50 && my >= 50 && mx <= width / 2 + width / 2 - width / 4 + 150 && my <= 140 && stopbody == 0)
            {
                stopbody = 1;
                readimagefile("Body yellow.gif", width / 2 + width / 2 - width / 4 - 32, 50, width / 2 + width / 2 - width / 4 + 132, 140);
                ok = 1;
            }
            if (ok == 1)
            {
                car();
            }
            if (mx >= width / 2 - 95 && mx <= width / 2 + 85 && my >= 50 && my <= 145 && stopranking == 1)
            {
                stopranking = 0;
                readimagefile("Ranking.gif", width / 2 - 95, 50, width / 2 + 85, 145);
                readimagefile("ranking reparare.gif", width / 4 + width / 8 - 10, 165, width / 2 + width / 8 + 10, height / 2 + height / 8 + 10);
            }
            else if (mx >= width / 2 - 95 && mx <= width / 2 + 85 && my >= 50 && my <= 145 && stopranking == 0)
            {
                stopranking = 1;
                readimagefile("Ranking yellow.gif", width / 2 - 95, 48, width / 2 + 87, 150);
                readimagefile("table ranking.gif", width / 4 + width / 8, 175, width / 2 + width / 8, height / 2 + height / 8);
                CautareLastNamePlayerandaddscore();
                tabel();
            }
            if (mx >= width / 4 - 140 && mx <= width / 4 + 20 && my >= 50 && my <= 145 && stoplevels == 0)
            {
                readimagefile("Levels yellow.gif", width / 4 - 140, 48, width / 4 + 22, 149);
                readimagefile("Level1.gif", width / 4 - 260, 160, width / 4 - 200, 220);
                Level1 = 1;
                readimagefile("Level2.gif", width / 4 - 180, 158, width / 4 - 117, 222);
                readimagefile("level3.gif", width / 4 - 100, 165, width / 4 - 30, 227);
                readimagefile("backgroundblack.gif", width / 4 - 2, 167, width / 4 + 53, 215);
                readimagefile("level4.gif", width / 4 - 12, 160, width / 4 + 60, 220);
                readimagefile("level5.gif", width / 4 + 80, 160, width / 4 + 150, 220);
                readimagefile("level6.gif", width / 4 - 260, 260, width / 4 - 200, 320);
                readimagefile("level7.gif", width / 4 - 180, 260, width / 4 - 117, 320);
                readimagefile("level8.gif", width / 4 - 97, 250, width / 4 - 33, 320);
                readimagefile("level9.gif", width / 4 - 12, 260, width / 4 + 60, 320);
                readimagefile("level10.gif", width / 4 + 80, 260, width / 4 + 150, 314);
                stoplevels = 1;
            }
            else if (mx >= width / 4 - 180 && mx <= width / 4 && my >= 50 && my <= 145 && stoplevels == 1)
            {
                readimagefile("levels.gif", width / 4 - 140, 50, width / 4 + 20, 145);
                readimagefile("levels reparare.gif", width / 4 - 270, 160, width / 4 + 160, 330);
                stoplevels = 0;

            }
            if (mx >= 30 && mx <= 80 && my >= height - 110 && my <= height - 50)
            {
                meniulprincipal = true;
                meniulsecundar = false;
                meniulhowtoplay = false;
                stopmen1 = 0;
            }
            else if (mx >= width / 4 - 260 && mx <= width / 4 - 200 && my >= 160 && my <= 220 && Level1 == 1)
            {
                stoplevels = false;
                stopranking = false;
                puncte = 10; stop = 0;
                level1();
                ScoreLastNumePlayer = ScoreLastNumePlayer + score;
                break;
            }
            else if (mx >= width / 4 - 180 && my >= 158 && mx <= width / 4 - 117 && my <= 222)
            {
                stoplevels = false;
                stopranking = false;
                puncte = 20; stop = 0;
                level2();
                ScoreLastNumePlayer = ScoreLastNumePlayer + score;
                break;
            }
            else if (mx >= width / 4 - 100 && my >= 165 && mx <= width / 4 - 30 && my <= 227)
            {
                stoplevels = false;
                stopranking = false;
                puncte = 30; stop = 0; start3 = 1;
                level3();
                ScoreLastNumePlayer = ScoreLastNumePlayer + score;
                start3 = 0;
                break;
            }
            else if (mx >= width / 4 + 80 && my >= 160 && mx <= width / 4 + 150 && my <= 220 )
            {
                stoplevels = false;
                stopranking = false;
                puncte = 50; stop = 0;
                level5();
                ScoreLastNumePlayer = ScoreLastNumePlayer + score;
                break;
            }
            else if (mx >= width / 4 - 12 && my >= 160 && mx <= width / 4 + 600 && my <= 220)
            {
                stoplevels = false;
                stopranking = false;
                puncte = 40; stop = 0;
                level4();
                ScoreLastNumePlayer = ScoreLastNumePlayer + score;
                break;
            }
            else
                if (mx >= width / 4 - 260 && my >= 260 && mx <= width / 4 - 200 && my <= 320)
                {
                    stoplevels = false;
                    stopranking = false;
                    puncte = 60; stop = 0;
                    level6();
                    ScoreLastNumePlayer = ScoreLastNumePlayer + score;
                    break;
                }
        }
    }
}
void play()
{
    if (pozitiemausx >= width / 2 - 120 && pozitiemausx <= width / 2 + 100 && pozitiemausy >= height / 2 + 85 && pozitiemausy <= height / 2 + 190)
    {
        readimagefile("Play2.gif", width / 2 - 120, height / 2 + 85, width / 2 + 120, height / 2 + 200);
        if (mx >= width / 2 - 120 && mx <= width / 2 + 100 && my >= height / 2 + 85 && my <= height / 2 + 200)
        {
            meniulsecundar = true;
            meniulprincipal = false;
            meniulhowtoplay = false;
        }
    }
    else
        readimagefile("Play1.gif", width / 2 - 120, height / 2 + 85, width / 2 + 120, height / 2 + 190);
}
void MeniulPrincipal()
{
    while (meniulprincipal)
    {
        DeseneazaMeniulPrincipal();
        sunet();
        exit();
        howtoplay();
        play();
    }
}
    void rectanglerotate(int cx,int cy,int w,int h,int angle=0)
    {
        double theta=(double)(angle%180)*M_PI/180.0;
        int dx=w/2;
        int dy=h/2;
        int point[8]={
                      (-dx*cos(theta)-dy*sin(theta)+cx),
                      (-dx*sin(theta)+dy*cos(theta)+cy),
                      (dx*cos(theta)-dy*sin(theta)+cx),
                      (dx*sin(theta)+dy*cos(theta)+cy),
                      (dx*cos(theta)+dy*sin(theta)+cx),
                      (dx*sin(theta)-dy*cos(theta)+cy),
                      (-dx*cos(theta)+dy*sin(theta)+cx),
                      (-dx*sin(theta)-dy*cos(theta)+cy)
                                 };
        for(int i=0;i<8;i+=2)
        line(point[i],point[i+1],point[(i+2)%8],point[(i+3)%8]);

    }
int main()
{
    int i;
    setuptabel();

    cout << "Name Player 1: ";
    cin.getline(tabelvalori[5].player, 100);
    strcpy(LastNumePLayer, tabelvalori[5].player); //o copie a ultimului nume introdus
    ScoreLastNumePlayer = 0;
    tabelvalori[5].points = 0;
    ord[5] = 0;

    initwindow(width, height, "Raliu Auto");
        setcolor(BLUE);
         readimagefile("loading.gif",width/2-280,height/2-100,width/2+300,height/2+250);
        for(i=width/6; i<=width-width/4; i++)
        {
            line(i,100,i,300);
            line(i+1,100,i+1,300);
            line(i+2,100,i+2,300);
            line(i+3,100,i+3,300);
            line(i+4,100,i+4,300);
            line(i+5,100,i+5,300);
            line(i+6,100,i+6,300);
            line(i+7,100,i+7,300);
            line(i+8,100,i+8,300);
            line(i+9,100,i+9,300);
            line(i+10,100,i+10,300);
            line(i+11,100,i+11,300);
            line(i+12,100,i+12,300);
            rectanglerotate(width/2,height/2+100,400,400,i);
            i+=12;
            delay(25);
        }

    sndPlaySound("ROCK IT.wav",SND_ASYNC);
    stopmen1 = 0;
    stopsunet = 1;
    stopmen3 = 1;
    stoplevel5=1;
    while (1)
    {
        MeniulPrincipal();
        MeniulSecundar();
        MeniulHowToPlay();
    }

    getch();
    closegraph();
    return 0;
}


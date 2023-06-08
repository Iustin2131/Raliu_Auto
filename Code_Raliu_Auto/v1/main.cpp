#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <MMsystem.h>
  using namespace std;
   int width=GetSystemMetrics(SM_CXSCREEN);
  int height=GetSystemMetrics(SM_CYSCREEN);
  bool gameOver;
int x=100,y=100,antx,anty,viteza,score,car1=1,v[10000]={0};
enum edirectie {Stop=0,stanga,dreapta,sus,jos,stangasus,stangajos,dreaptajos,dreaptasus};
edirectie dir;
int a[1000][1000]={0};
bool input = false;
   void SetUp()
   {
       gameOver=false;
       dir=Stop;
       x=475; antx=x;
       y=675; anty=y;
        score=0;
   }
   void ConturPista()
   {
       setcolor(0);
      arc(152, 100, 90, 180,50);         arc(150, 99,90,180,49);
      line(101,100,101,650);             line(102,100,102,650);
      line(152,50,840,50);               line(152,51,840,51);
      arc(841,100,0,90,50);              arc(841,100,0,90,51);
      line(891,100,891,650);             line(892,100,892,650);
      arc(841,650,270,0,50);             arc(841,650,270,0,51);
      arc(152,650,180,270,50);           arc(152,650,180,270,49);
      line(152,700,841,700);             line(151,699,841,699);

      line(181,100,812,100);             line(181,101,812,101);
      arc(181,120,90,180,20);            arc(181,120,90,180,19);
      line(181,650,812,650);             line(181,649,812,649);
      arc(181,630,180,270,20);           arc(181,630,180,270,19);
      line(160,120,160,630);             line(159,120,159,630);      //(de revazut conturul interior la pista)
      line(825,120,825,630);             line(824,120,824,630);
      arc(810,115,350,80,16);            arc(810,115,350,80,15);
      arc(807,635,280,10,17);            arc(807,635,280,10,16);
      setcolor(15);
  }
  void Startul()
   {   setcolor(4);
       line(490,700,490,650);
       line(491,700,491,650); setcolor(15);
   }
    struct nod
  {
      int x1,y1,x2,y2,nr;
      nod *urm;
  };
  int fr=0,numar=0;
  nod *p=NULL,*u=NULL,*q;
   void Drum(int x1,int y1,int x2,int y2)
    {
        if(p==NULL)
        {
            p=new nod;
            p->x1=x1;
            p->y1=y1;
            p->x2=x2;
            p->y2=y2;
            p->nr=++numar;
            u=p;
            u->urm=NULL;
        }
        else
        {
            q=new nod;
            q->x1=x1;
            q->y1=y1;
            q->x2=x2;
            q->y2=y2;
            q->nr=++numar;
            u->urm=q;
            u=q;
            u->urm=NULL;
        }
    }
     void ConstruireDrumAnterior()
    {
            q=p; int cx,cy,bx,by,ax,ay,dx,dy,ex,ey;
          while(q!=NULL)
           {
               line(q->x1,q->y1,q->x2,q->y2);   //Dreapta(Drumul pe unde a trecut masina)

                if(v[q->nr]==11) //Sagetile
               {
                   cx=q->x1;cy=q->y1,bx=q->x2,by=q->y2;
                   line((bx+cx)/2,(by+cy)/2,(bx+cx)/2,(cy+by)/2+10);
                   line((bx+cx)/2,(by+cy)/2,(bx+cx)/2-10,(cy+by)/2);
               }
               else
                if(v[q->nr]==22)
                {
                    cx=q->x1;cy=q->y1,ax=q->x2,ay=q->y2;
                  line((ax+cx)/2,(ay+cy)/2,(ax+cx)/2,(ay+cy)/2+10);
                  line((ax+cx)/2,(ay+cy)/2,(ax+cx)/2+10,(ay+cy)/2);
                }
                else
                if(v[q->nr]==32)
                {
                    cx=q->x1;cy=q->y1,dx=q->x2,dy=q->y2;
                  line((dx+cx)/2,(dy+cy)/2,(dx+cx)/2+10,(dy+cy)/2);
                  line((dx+cx)/2,(dy+cy)/2,(dx+cx)/2,(cy+dy)/2-10);
                }
                else
                if(v[q->nr]==42)
                {
                    cx=q->x1;cy=q->y1,ex=q->x2,ey=q->y2;
                  line((ex+cx)/2,(ey+cy)/2,(ex+cx)/2-10,(ey+cy)/2);
                  line((ex+cx)/2,(ey+cy)/2,(ex+cx)/2,(cy+ey)/2-10);
                }
                 else
                if(v[q->nr]==12)
                {
                    cx=q->x1;cy=q->y1,ex=q->x2,ey=q->y2;
                  line((cx+ex)/2,(cy+ey)/2,(cx+ex)/2-7,(cy+ey)/2+7);
                  line((cx+ex)/2,(cy+ey)/2,(cx+ex)/2+7,(cy+ey)/2+7);
                }
                else
                if(v[q->nr]==33)
                {
                    cx=q->x1;cy=q->y1,ex=q->x2,ey=q->y2;
                  line((cx+ex)/2,(cy+ey)/2,(cx+ex)/2-7,(cy+ey)/2-7);
                  line((cx+ex)/2,(cy+ey)/2,(cx+ex)/2+7,(cy+ey)/2-7);
                }
                else
                if(v[q->nr]==31)
                {
                    cx=q->x1;cy=q->y1,ex=q->x2,ey=q->y2;
                  line((cx+ex)/2,(cy+ey)/2,(cx+ex)/2+7,(cy+ey)/2-7);
                  line((cx+ex)/2,(cy+ey)/2,(cx+ex)/2+7,(cy+ey)/2+7);
                }
                else
                if(v[q->nr]==10)
                {
                    cx=q->x1;cy=q->y1,ex=q->x2,ey=q->y2;
                  line((cx+ex)/2,(cy+ey)/2,(cx+ex)/2-7,(cy+ey)/2-7);
                  line((cx+ex)/2,(cy+ey)/2,(cx+ex)/2-7,(cy+ey)/2+7);
                }
                q=q->urm;
           }
    }

   void Draw()
   {
        for(int i=10;i<=1800;i++)
           for(int j=10;j<=1700;j++)
            if(i==x && j==y)
             {
                  readimagefile("stadion.jpg",0,0,width,height);
                 if(car1==1)
                     readimagefile("car1dirstanga.gif",x-20,y-20,x+20,y+20);
                   else
                 if(car1==2)
                     readimagefile("car1dirdreapta.gif",x-20,y-20,x+20,y+20);
                   else
                 if(car1==0)
                     readimagefile("car1dirinainte.gif",x-20,y-20,x+20,y+20);
                   else
                 if(car1==3)
                     readimagefile("car1dirinapoi.gif",x-20,y-20,x+20,y+20);
                   else
                 if(car1==4)
                     readimagefile("car1dirstangajos.gif",x-30,y-30,x+30,y+30);
                   else
                 if(car1==5)
                     readimagefile("car1dirstangasus.gif",x-60,y-60,x+60,y+60);
                   else
                 if(car1==6)
                     readimagefile("car1dirdreaptajos.gif",x-30,y-30,x+30,y+30);
                   else
                 if(car1==7)
                     readimagefile("car1dirdreaptasus.gif",x-30,y-30,x+30,y+30);
             }
          setcolor(0);
      //    rectangle(100,100,800,700);
        //         rectangle(200,200,700,600);
          //       floodfill(150,150,15);
            //     cleardevice();
          ConstruireDrumAnterior();
         ConturPista();
       Startul();
   }
   void Input()
   {
    while(_kbhit())
    {
        input = true;
      switch (_getch())
      {
          case 'a':
            dir=stanga;
            break;
          case 'd':
            dir=dreapta;
            break;
          case 'w':
             dir=sus;
             break;
          case 's':
             dir=jos;
             break;
          case 'q':
             dir=stangasus;
             break;
          case 'e':
            dir=dreaptasus;
            break;
          case 'x':
            dir=dreaptajos;
            break;
          case 'z':
             dir=stangajos;
             break;
        case 't':
             gameOver=true;
             break;
      }
    }
   }
   void Logic()
   {
      switch (dir)
      {

          case stanga:
            {
                v[++fr]=31;
                Drum(x,y,x-40,y);
                x-=40;
                car1=1;
                dir=Stop;
                break;
            }
          case dreapta:
            {
                v[++fr]=10;
                Drum(x,y,x+40,y);
                x+=40;
                car1=2;
                dir=Stop;
                break;
            }
          case sus:
              {
                  v[++fr]=12;
                  Drum(x,y,x,y-40);
                  y-=40;
                  car1=0;
                  dir=Stop;
                  break;
              }
          case jos:
            {
                v[++fr]=33;
                Drum(x,y,x,y+40);
                y+=40;
                car1=3;
                dir=Stop;
                break;
            }
          case stangajos:
              {
                  v[++fr]=32;
                  Drum(x,y,x-40,y+40);
                  x-=40;
                  y+=40;
                  car1=4;
                  dir=Stop;
                  break;
              }
          case stangasus:
              {
                  v[++fr]=22;
                  Drum(x,y,x-40,y-40);
                  x-=40;
                  y-=40;
                  car1=5;
                  dir=Stop;
                  break;
              }
          case dreaptajos:
              {
                  v[++fr]=42;
                  Drum(x,y,x+40,y+40);
                  x+=40;
                  y+=40;
                  car1=6;
                  dir=Stop;
                  break;
              }
          case dreaptasus:
              {

                  v[++fr]=11;
                  Drum(x,y,x+40,y-40);
                  x+=40;
                  y-=40;
                  car1=7;
                  dir=Stop;
                  break;
              }
            default:
             break;

      }
   }

   int main()
  {
    int mx,my;
    int ok=1;
    initwindow(width,height,"Raliu Auto");
    readimagefile("Rocket League.gif",0,0,width,height);
    readimagefile("Sound on.gif",width-80,10,width-10,80);
    sndPlaySound("ROCK IT.wav",SND_ASYNC);
    readimagefile("Auto Rally.gif",width/2-100,height/2-50,width/2+150,height/2+25);
    readimagefile("Emblem.gif",width/2-220,height/2-100,width/2-70,height/2+50);
   while(1)
    {
        getmouseclick(WM_LBUTTONDOWN, mx, my);
        x=mousex();
        y=mousey();
          if(x <= width-10 && x >= width-80 && y >= 10 && y <= 80 && ok==1)
                readimagefile("Sound off.gif",width-80,10,width-10,80);
            else
          if(x <= width-10 && x >= width-80 && y >= 10 && y <= 80 && ok==0)
                 readimagefile("Sound on.gif",width-80,10,width-10,80);
           if((mx >= width-80 && mx <=width-10 && my >= 10 && my <= 80) &&ok==1)
                {
                readimagefile("Sound off.gif",width-80,10,width-10,80);
                PlaySound(0,0,0);
                ok=0;
                }
            else
                if((mx >= width-80 && mx <=width-10 && my >= 10 && my <= 80) &&ok==0)
                {
                    sndPlaySound("ROCK IT.wav",SND_ASYNC);
                    readimagefile("Sound on.gif",width-80,10,width-10,0);
                    ok=1;
                }

            if(x >= width/2-300 && x <= width/2-140 && y >= height/2+170 && y <= height/2+270)
             readimagefile("Exit yellow.gif",width/2-300,height/2+170,width/2-140,height/2+277);
             else
             readimagefile("Exit.gif",width/2-300,height/2+170,width/2-140,height/2+275);
             if(mx >=  width/2-300 && mx <= width/2-140 && my >=  height/2+170 && my <=  height/2+270)
               {
                    closegraph();
                    PlaySound(0,0,0);
               }

            if(x >= width/2+125 && x <= width/2+305 && y >= height/2+170 && y <= height/2+270)
              readimagefile("How to play yellow.gif",width/2+125,height/2+170,width/2+305,height/2+270);
            else
              readimagefile("How to play.gif",width/2+125,height/2+170,width/2+305,height/2+270);
            if(mx >= width/2+125 && mx <= width/2+305 && my >= height/2+170 && my <= height/2+270)
             {
                 cleardevice();
                 ok=1;
                 while(1)
              {
                 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                 outtextxy(25,240,"Press any key to view the moving car");
                 readimagefile("Back.jpg",30,height-110,80,height-50);
                 if(mx >= 30 && mx <= 80 && my >= height-110 && my <= height-50)   // Nu este corect
                   readimagefile("How to play.gif",0,0,1000,1000);
              }
             }
            if(x>=width/2-120 && x<=width/2+100 && y>=height/2+85 && y<=height/2+190)
            {
                 readimagefile("Play2.gif",width/2-120,height/2+85,width/2+120,height/2+200);
                if(mx >= width/2-120 && mx <=width/2+100 && my >= height/2+85 && my <= height/2+200)
            {
                sndPlaySound("game start.wav",SND_ASYNC);
                // PlaySound(0,0,0); // Daca vreau sa opresc muzica cand incepe jocul
                cleardevice();
                SetUp();
                while(1)
                {
                  Draw();
                  Input();
                  Logic();
                }
            }
           }
           else
              readimagefile("Play1.gif",width/2-120,height/2+85,width/2+120,height/2+190);
    }

    getch(); closegraph();
    return 0;
}


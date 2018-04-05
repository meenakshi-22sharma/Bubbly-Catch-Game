#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<process.h>
#include<fstream.h>
union REGS in,out;



int mouse_click()
{
 in.x.ax=1;
 int86(51,&in,&out);
 return 1;
}



void mouse_position(int &xp , int &yp , int &cp)
{
 in.x.ax=3;
 int86(51,&in,&out);
 xp=out.x.cx;
 yp=out.x.dx;
 cp=out.x.bx;
}



class HighScore
{
 char Name[20];
 long Score;

public:

 void Store();
 void Display();

 void SetScore(long Points)
 {
   Score=Points;
 }

 void HName(char HTScorer[])
 {
   strcpy(HTScorer,Name);
 }

 void SetName(char FindScorer[])
 {
   strcpy(Name,FindScorer);
 }

 long High()
 {
   return Score;
 }
};



void HighScore::Store()
{
  settextstyle(7,0,3);
  outtextxy(200,150,"SCORE :");
  gotoxy(40,11);
  cout<<Score;
  outtextxy(200,200,"NAME :");
  gotoxy(40,14);
  cin>>Name;
}



void HighScore::Display()
{
  cout<<"   NAME  :"<<Name<<endl;
  cout<<"   SCORE :"<<Score<<endl;
}



void Scorer(HighScore &HTS)
{
 ifstream fin("HSCORE.TXT",ios::in);
 fin.seekg(0);
 fin.read((char*)&HTS,sizeof(HTS));
 fin.close();
}



void lines()
{

 line(106,50,106,10);
 line(106,150,106,100);
 line(106,250,106,200);
 line(106,350,106,300);
 line(106,450,106,400);
 line(206,50,206,10);
 line(206,150,206,100);
 line(206,250,206,200);
 line(206,350,206,300);
 line(206,450,206,400);
 line(306,50,306,10);
 line(306,150,306,100);
 line(306,250,306,200);
 line(306,350,306,300);
 line(306,450,306,400);
 line(406, 56,406,10);
 line(406,156,406,100);
 line(406, 256,406,200);
 line(406,356,406,300);
 line(406,456,406,406);
 rectangle(6,6,506,479);
}



void Win()
{
 setbkcolor(LIGHTBLUE);
 setcolor(5);
 delay(100);
 cleardevice();

 settextstyle(1,0,4);
 outtextxy(150,200,"!  HIGHEST  SCORE  !");
 delay(500);
 rectangle(100,400,500,420);
 setcolor(3);
 settextstyle(0,0,1);
 outtextxy(250,380,"L@ADING.....");

 for(int i=0 ; i<=380 ; ++i)
 {
   delay(10);
   circle(110+i,410,5);
 }
}



int  check1(int x , int v)
{
 if(x>v && x<(v+40))
   return 1;
 return 0;
}



int check2(int x , int v)
{
 if(x>v+50 && x<(v+100))
   return 1;
 return 0;
}



void play()
{
 setcolor(10);
 setbkcolor(9);
 setfillstyle(8,1);

 HighScore HS,HTS;
 int track=3 , radius1=4 , x1=250 , y1=0 , radius2=6 , x2=-10 , y2=-10;
 char HTScorer[10] , size='s';
 int x , y , cl , v11=300 , Score=0;
 int chance=3;
 Scorer(HTS);
 HTS.HName(HTScorer);
 ifstream fin;
 fin.open("value.txt",ios::in|ios::binary);
 fin.seekg(0);

 while(chance>0)
 {
   cleardevice();

   if(y1==240)
   {
     fin>>track;
     fin.get(size);
     radius2=radius1;
     x2=x1;
     y2=y1;
     if(size=='s')
       radius1=4;
     else
       radius1=6;
     x1=50+100*(track-1);
     y1=0;
   }

   settextstyle(2,0,6);
   outtextxy(508,20,"CHANCES LEFT :");
   gotoxy(72.5,4);
   cout<<chance;
   outtextxy(508,90,"SCORE :");
   gotoxy(72.5,8);
   cout<<Score;
   settextstyle(2,0,5);
   outtextxy(509,250,"HIGHEST SCORER :");
   outtextxy(506,255,"______________");
   gotoxy(70,19);
   cout<<HTScorer;
   gotoxy(71,20);
   cout<<HTS.High();
   lines();
   circle(x1,++y1,radius1);
   circle(x2,++y2,radius2);
   bar3d(v11,420,v11+40,470,50,1);

   if(y2==420 && radius2==6)
   {
     if(check1(x2,v11))
     {
       radius2=-1;
       Score+=50;
     }
     else
      --chance;
   }

   else if(y2==385 && radius2==4)
   {
     if(check2(x2,v11))
     {
       radius2=-1;
       Score+=50;
     }
     else
     --chance;
   }

   mouse_position(x,y,cl);
   if(cl==1 && v11>-6)
     --v11;
   else if(cl==2 && v11<478)
     ++v11;

   if(fin.eof())
     fin.seekg(0);

   delay(20);
 }

 delay(5000);
 cleardevice();
 setbkcolor(3);
 settextstyle(3,0,5);
 outtextxy(200,200,"GAME_@VER");
 settextstyle(2,0,5);
 outtextxy(400,400,"press 'ENTER' to continue");
 getch();
 cleardevice();

 if(Score>=HTS.High())
 {
   cleardevice();
   Win();
   cleardevice();
   setcolor(1);
   settextstyle(3,0,5);
   HS.SetScore(Score);
   HS.Store();
   ofstream fout("HSCORE.TXT",ios::out);
   fout.seekp(0);
   fout.write((char*)&HS,sizeof(HS));
   fout.close();
   getch();
 }
}



void instructions()
{
 setbkcolor(BLACK);
 settextstyle(2,0,5);
 int a1=0,b1=0,a2=0,b2=0,x=0,y=0;

 for(int j=0 ; ; ++j)
 {

   for(int i=0 ; ; ++i)
   {
     cleardevice();
     setcolor(12);
     outtextxy(440,10,"press  'ENTER'  to  CONTINUE");
     arc(310,200,0,90-a1,100);
     arc(290,200,90+b1,180,100);
     line(190,200,190,300);
     line(410,200,410,300);
     arc(300,300,180,360,110);
     rectangle(290,100,310,200);
     line(290-b1-y,100,290,200);
     line(310+a1+x,100,310,200);
     line(190,200,410,200);
     delay(1000);

     if(kbhit())
       break;

     a1=0;b1=0;x=0;y=0;

     if(i%4==0)
     {
       a1=5;
       x=3;
       line(350,150,450,100);
       line(430,100,450,100);
       line(440,120,450,100);
       delay(1000);
       outtextxy(450,90,"CLICK TO MOVE RIGHT");
       delay(1500);
     }

     if(kbhit())
       break;

     else if(i%4==2)
     {
       b1=5;
       y=3;
       line(250,150,150,100);
       line(170,100,150,100);
       line(160,120,150,100);
       delay(1000);
       outtextxy(10,90,"CLICK TO MOVE LEFT");
       delay(1500);
     }

     if(kbhit())
       break;
   }
   getch();

   for( ; ;)
   {
     a2=0,b2=0;

     for(i=0 ; i<=120 ; ++i)
     {
       cleardevice();
       outtextxy(420,10,"press  'ENTER'  to  CONTINUE");
       setcolor(10);
       setfillstyle(8,1);
       bar3d(200,320,300,450,100,1);
       circle(250,200+i,12);
       circle(350,125+i,8);
       setfillstyle(2,10);
       bar3d(140+4*i-a2,320,240+4*i-a2,320,0,0);
       bar3d(250,200+2*i-b2,250,230+2*i-b2,2,0);
       bar3d(240+4*i-a2,245,340+4*i-a2,245,0,0);
       bar3d(350,125+2*i-b2,350,155+2*i-b2,2,0);
       delay(20);
       if(i==30)
	 a2=120;
       else if(i==60)
	 a2=240,b2=120;
       else if(i==90)
	 a2=360;
     }

     delay(500);
     if(kbhit())
       break;
   }
 break;
 }
}



void start()
{
 int x,y,cl;

A:

 setcolor(11);
 setfillstyle(7,12);
 settextstyle(10,0,4);
 outtextxy(100,100,"_");
 delay(700);
 cleardevice();
 outtextxy(100,100,"B_");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BU_");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BUB_");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BUBB_");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BUBBL_");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BUBBLY_");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BUBBLY _");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BUBBLY  C_");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BUBBLY  CA_");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BUBBLY  CAT_");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BUBBLY  CATC_");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BUBBLY  CATCH_");
 delay(200);
 cleardevice();
 outtextxy(100,100,"BUBBLY  CATCH");
 delay(500);
 settextstyle(2,0,10);

 for(int i=0 ; i<=10 ; i++)
 {
   setbkcolor(i);
   delay(100);
 }

 delay(200);
 setbkcolor(6);
 delay(500);
 bar3d(190,230,420,280,0,0);
 outtextxy(200,230,"S T A R T");
 bar3d(170,330,440,380,0,0);
 outtextxy(180,330,"INSTRUCTION");
 settextstyle(2,0,5);
 bar3d(550,20,600,40,0,0);
 outtextxy(560,22,"EXIT");

 for(i=0 ; i<1 ;)
 {
   mouse_position(x,y,cl);
   if(x>=190 && x<=420 && y>=230 && y<=280 && cl==1)
   {
     play();
     goto A;
   }
   else if(x>=170 && x<=440 && y>=330 && y<=380 && cl==1)
   {
     instructions();
     goto A;
   }
   else if(x>=550 && x<=600 && y>=20 && y<=40 && cl==1)
   {
     exit(1);
   }
 }
}



void main()
{
 clrscr();
 int gd=DETECT,gm=0;
 initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
 mouse_click();
 start();
}
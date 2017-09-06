#include<graphics.h>
#include<dos.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

union REGS i, o;
int leftcolor[15],style=1;

int get_key()
{
   union REGS i,o;

   i.h.ah = 0;
   int86(22,&i,&o);

   return ( o.h.ah );
}
void draw_color_panel()
{
   int left, top, c, color;


   left = 100;
   top = 436;

   color = getcolor();
   setcolor(YELLOW);
   rectangle(4,433,635,457);
   setcolor(RED);
   settextstyle(TRIPLEX_FONT,0,2);
   outtextxy(10,431,"Colors : ");

   for( c = 0 ; c <= 15 ; c++ )
   {
      setfillstyle(SOLID_FILL, c);            //colour box
      bar(left, top, left+16, top+16);
      leftcolor[c-1] = left;
      left += 26;

   }

   setcolor(color);
}

void draw_shape_panel()
{
   int left, top, c, color;

   left = 529;
   top = 45;
   setcolor(RED);
   rectangle(615,1,630,21);
   setfillstyle(1,RED);
   floodfill(617,20,4);
   setcolor(WHITE);
   rectangle(614,0,631,22);
   outtextxy(618,-3,"x");
   color = getcolor();
   setcolor(GREEN);
   rectangle(525,40,635,432);

   for( c = 1 ; c <= 12 ; c++ )
   {
      rectangle(left, top, left+100, top+25);
      top += 30;
   }
   rectangle(600,255,629,280);
   rectangle(530,405,580,430);
   rectangle(585,405,630,430);
   setcolor(RED);
   settextstyle(1,0,2);
   outtextxy(530,45,"Bar");
   outtextxy(530,75,"Line");
   outtextxy(530,105,"Pixel");
   outtextxy(530,135,"Ellipse");
   outtextxy(530,165,"Freehand");
   outtextxy(530,195,"Rectangle");
   outtextxy(530,225,"Circle");
   outtextxy(530,255,"Fill     ^");
   outtextxy(530,285,"ERAISER");
   outtextxy(530,315,"Save As");
   outtextxy(530,345,"Load");
   outtextxy(530,375,"Clear");
   outtextxy(530,405,"Cont");
   outtextxy(590,405,"dis");
   setcolor(color);
}
void change_color(int x, int y)
{
   int c;

   for( c = -1 ; c <= 13 ; c++ )
   {
      if( x > leftcolor[c] && x < leftcolor[c+1] && y > 437 && y < 453 )
	 setcolor(c+1);
      if( x > leftcolor[14] && x < 505 && y > 437 && y < 453 )
	 setcolor(WHITE);
   }
}

char change_shape(int x, int y,char tempch)
{
 int a[100];

   if ( x > 529 && x < 625 && y > 45 && y < 70 )
      return 'b';
   else if ( x > 529 && x < 625 && y > 75 && y < 100 )
      return 'l';
   else if ( x > 529 && x < 625 && y > 105 && y < 130 )
      return 'p';
   else if ( x > 529 && x < 625 && y > 135 && y < 160 )
      return 'e';
   else if ( x > 529 && x < 625 && y > 165 && y < 190 )
      return 'f';
   else if ( x > 529 && x < 625 && y > 195 && y < 220 )
      return 'r';
   else if ( x > 529 && x < 625 && y > 225 && y < 250 )
      return 'd';
   else if ( x > 529 && x < 625 && y > 255 && y < 280 )
    {if(x>600&&style<11)
     style++;
     else
     style=1;
     return  'i';
    }
   else if ( x > 529 && x < 625 && y > 285 && y < 310 )
     return  'a';
   else if ( x > 529 && x < 625 && y > 315 && y < 340 )
     return  's';
   else if ( x > 529 && x < 625 && y > 345 && y < 375 )
     return  'o';
   else if ( x > 529 && x < 625 && y > 380 && y < 410 )
     return  'c';
   else if ( x > 529 && x < 580 && y > 405 && y < 430 )
     return 'n';
   else if ( x > 585 && x < 630 && y > 405 && y < 430 )
     return 't';
   else
   return(tempch);
}
void copy(char b[100],char p[100])
{
 FILE *f1,*f2;int choice;
 char ch,r[1000],h[100];
 sprintf(r,"%s.pai",b);
 sprintf(h,"%s.pai",p);
 f1=fopen(h,"r");
 rewind(f1);
 f2=fopen(r,"w");
 rewind(f2);
 fflush(f2);
 if(f1==0||f2==0)
 printf("cant save");
 else
 {
 ch=fgetc(f1);
 while(ch!=EOF)
 {
   fputc(ch,f2);
  ch=fgetc(f1);
  }
  outtext ("SAVED PRESS ENTER");
  fprintf(f2,"-1 -1 -1 -1");
  getch();
  fcloseall();
 }
}
void convert(char p[100])
{
 FILE *f;int shape,x1,y1,x2,y2,color;
   char q[100];
	    // default free-hand drawing
 sprintf(q,"%s.pai",p);
 f=fopen(q,"r");
 rewind(f);
 if(f!=0)
 {}
 else
 {printf("there is no such file exiests\n\n\n press any key");
 getch();
 closegraph();fclose(f);main();}
 while(x1!=-1)
 {
  fscanf(f,"%d %d %d %d %d %d",&shape,&color,&x1,&y1,&x2,&y2);
  setcolor(color);
  if(shape==2||shape==5)
  {
  line(x1,y1,x2,y2);
  }
  else if(shape==4||shape==7)
  ellipse(x1,y1,0,360,x2,y2);
  else if(shape==6)
  rectangle(x1,y1,x2,y2);
  else if(shape==3)
  putpixel(x1,y1,color);
  else if(shape==1||shape==9)
  {setfillstyle(SOLID_FILL,color);
	    bar(x2,y2,x1,y1);}
 else if(shape==8)
  {setfillstyle(x2,color);
	     floodfill(x1,y1,color);
	     }
 }
  getch();
 fclose(f);
}

void showmouseptr()
{
   i.x.ax = 1;
   int86(0x33,&i,&o);
}

void hidemouseptr()
{
   i.x.ax = 2;
   int86(0x33,&i,&o);
}

void restrictmouseptr( int x1, int y1, int x2, int y2)
{
   i.x.ax = 7;
   i.x.cx = x1;
   i.x.dx = x2;
   int86(0x33,&i,&o);

   i.x.ax = 8;
   i.x.cx = y1;
   i.x.dx = y2;
   int86(0x33,&i,&o);
}

void getmousepos(int *button,int *x,int *y)
{
   i.x.ax = 3;
   int86(0x33,&i,&o);

   *button = o.x.bx;
   *x = o.x.cx;
   *y = o.x.dx;
}
void gotostart(int i)
{
 int j;
 for(j=0;j<i;j++)
 printf("\b");
}
void last()
{
 setcolor(GREEN);
 outtextxy(50,50,"BY:-ROHIT ");
 outtextxy(50,200,"CHAITANYA ENGINEERING COLLEGE");
 outtextxy(50,400,"B.TECH 1st Year C.S.E");
}
int start=0;char a[100],c=0;;
main()
{  char n_1[100],n_2[100];
   int gd = DETECT,gm;int errorcode;
   int maxx,maxy,x,y,button,prevx,prevy,temp1,temp2,key,color;FILE *f,*F;int newx=-1,newy=-1;
   char co[20][20]={"   Black  ","Dark__Blue","Dark_Green","Light_blue"," Dark_red "," Dark_Pink","Dark_Orang","Light_gray"," Dark_Gray","periwinkle","Ligh_green"," sky_blue ","  Salmon  ","Light_pink","  Yellow  ","  White   "};
   char ch = 'f', tempch='f';            // default free-hand drawing
   initgraph(&gd,&gm,"C:\\TC\\BGI");
   maxx = getmaxx();
   maxy = getmaxy();
   setcolor(GREEN);
   rectangle(0,0,maxx,maxy-20);
   setcolor(15);
   rectangle(1,1,523,430);
   setcolor(WHITE);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
      printf("colour=%s shape=%c continue=%d Fill=*%d*",co[getcolor()],ch,c,style);
   settextstyle(5,0,2);
   setcolor(9);
   outtextxy(maxx/2-300,maxy-28,"                            by:-Dasamantharao Rohit");
    setcolor(WHITE);
   draw_color_panel();
   draw_shape_panel();

   setviewport(3,3,maxx-1,maxy-1,1);

   restrictmouseptr(3,3,maxx-1,maxy-1);
   showmouseptr();
   setviewport(2,2,519,427,1);
   if( start ==0 )
   f=fopen("save.pai","w");     //opening the dead file 1
 //  if(start==1)
   //{
    //convert(a); f=fopen("c:\\TC\\rohit\\save.txt","a");}
   while(1)
   {
      if(kbhit())
      {
	 key = get_key();

	 if( key == 1 )
	 {
	  cleardevice();
	    closegraph();
	    fflush(f);
	    fclose(f);
	    exit(0);
	 }
      }

      getmousepos(&button,&x,&y);

      if( button == 1 )
      {
	 if( x > 4 && x < 635 && y > 431 && y < 457 )
	   {change_color( x, y ); gotostart(50);
      printf("colour=%s shape=%c continue=%d Fill=*%d*",co[getcolor()],ch,c,style); }
	 else if( x > 615 && x < 630 && y > 1 && y < 21)
	  {
	   hidemouseptr();
	   cleardevice();
	    closegraph();
	    fflush(f);
	    fclose(f);
	    exit(0);
	  }
	 else if ( x > 529 && x < 630 && y > 40 && y < 445 )
	   {ch = change_shape( x, y,tempch );gotostart(50);
      printf("colour=%s shape=%c continue=%d Fill=*%d*",co[getcolor()],ch,c,style); }
	 temp1 = x ;
	 temp2 = y ;
	 if(ch != 's')
	 tempch = ch;
	 if(ch=='n')
	   c=1;
	 if(ch=='t')
	 c=0;
	 if ( ch == 'a' )
	  {
	   while( button == 1 )
	    {
	    setfillstyle(1,getcolor()) ;
	       bar(temp1+10,temp2+10,x-10,y-10);
	       temp1 = x;
	       temp2 = y;
	       getmousepos(&button,&x,&y);
	       if( x > 2 && x < 518 && y >2 && y < 427&&(newx!=x||newy!=y) )
	       {
	       fprintf(f,"9 %d %d %d %d %d ",getcolor(),temp1+10,temp2+10,x-10,y-10);
	       newx=x;newy=y;}
	    }
	  }
	 if ( ch == 'f' )
	 {
	    hidemouseptr();
	    while( button == 1 )
	    {
	       line(temp1,temp2,x,y);
	       temp1 = x;
	       temp2 = y;
	       getmousepos(&button,&x,&y);
	       if( x > 2 && x < 518 && y >2 && y < 427&&(newx!=x||newy!=y) )
	       {
	       fprintf(f,"5 %d %d %d %d %d ",getcolor(),x,y,temp1,temp2);
	       newx=x;newy=y;}
	    }
	    showmouseptr();
	 }
	 if(c==0)
	 while( button == 1)
	    getmousepos(&button,&x,&y);

	 /* to avoid interference of mouse while drawing */
	 hidemouseptr();

	 if( ch == 'p')
	   {
	   if(c==0)
	    {putpixel(x,y,getcolor());
	    if( x > 2 && x < 518 && y >2 && y < 427 )
	       fprintf(f,"3 %d %d %d %d %d ",ch,getcolor(),x,y,temp1,temp2);}
	   else
	   {while( button == 1 )
	    {
	     hidemouseptr();
	       putpixel(x,y,getcolor());
	       getmousepos(&button,&x,&y);
	       if( x > 2 && x < 518 && y >2 && y < 427&&(newx!=x||newy!=y) )
	       {
	       fprintf(f,"3 %d %d %d %d %d ",getcolor(),x,y,temp1,temp2);
	       }
	     newx=x;newy=y;
	     showmouseptr();
	     }
	     }
	  }
	 else if ( ch == 'b' )
	 {
	    setfillstyle(SOLID_FILL,getcolor());
	    bar(temp1,temp2,x,y);
	       if( x > 0 && x < 518 && y >2 && y < 427 )
	       fprintf(f,"1 %d %d %d %d %d ",getcolor(),x,y,temp1,temp2);
	 }
	 else if ( ch == 'l')
	 {
	    if(c==0)
	     { line(temp1,temp2,x,y);
	 if( x > 2 && x < 518 && y >2 && y < 427 )
	       fprintf(f,"2 %d %d %d %d %d ",getcolor(),x,y,temp1,temp2);}
	   else
	   {
	      hidemouseptr();
	    while( button == 1 )
	    {
	       line(temp1,temp2,x,y);
	       getmousepos(&button,&x,&y);
	       if( x > 2 && x < 518 && y >2 && y < 427&&(newx!=x||newy!=y) )
	       {
	       fprintf(f,"2 %d %d %d %d %d ",getcolor(),x,y,temp1,temp2);
	       newx=x;newy=y;}
	      }
	    }
	    showmouseptr();
	 }
	 else if ( ch == 'e')
	  {
	    if(c==0)
	    {ellipse(temp1,temp2,0,360,abs(x-temp1),abs(y-temp2));
	     if( x > 2 && x < 518 && y >2 && y < 427 )
	     fprintf(f,"4 %d %d %d %d %d ",getcolor(),temp1,temp2,abs(x-temp1),abs(y-temp2));}
	  }
	  else if( ch == 'd' )
	  {
	   if(c==0)
	   {
	   if(x>temp1)
	    {ellipse(temp1,temp2,0,360,x-temp1,x-temp1);
	    if( x > 2 && x < 518 && y >2 && y < 427 )
	    fprintf(f,"7 %d %d %d %d %d ",getcolor(),temp1,temp2,x-temp1,x-temp1);}
	   else
	    {ellipse(temp1,temp2,0,360,temp1-x,temp1-x);
	    if( x > 2 && x < 518 && y >2 && y < 427 )
	    fprintf(f,"7 %d %d %d %d %d ",getcolor(),temp1,temp2,temp1-x,temp1-x);}
	  }
	  else{
	  while(button==1){ getmousepos(&button,&x,&y);
	  if(x>temp1)
	    {ellipse(temp1,temp2,0,360,x-temp1,x-temp1);
	    if( x > 2 && x < 518 && y >2 && y < 427&&(newx!=x||newy!=y))
	    fprintf(f,"7 %d %d %d %d %d ",getcolor(),temp1,temp2,x-temp1,x-temp1);}
	   else
	    {ellipse(temp1,temp2,0,360,temp1-x,temp1-x&&(newx!=x||newy!=y));
	    if( x > 2 && x < 518 && y >2 && y < 427 )
	    fprintf(f,"7 %d %d %d %d %d ",getcolor(),temp1,temp2,temp1-x,temp1-x);}
	    newx=x;newy=y;}} }
	 else if ( ch == 'r' )
	  {
	    rectangle(temp1,temp2,x,y);
	     if( x > 2 && x < 518 && y >2 && y < 427 )
	    fprintf(f,"6 %d %d %d %d %d ",getcolor(),x,y,temp1,temp2);
	  }
	 else if ( ch == 'c' )
	 {
	    ch = 'f';          // setting to freehand drawing
	    clearviewport();
	    color = getcolor();
	    setcolor(WHITE);
	    setcolor(color);
	    fclose(f);
	    f=fopen("save.pai","w");
	 }
	 else if (ch=='i')
	 {
	 errorcode = graphresult();
if (errorcode != grOk)
/* an error occurred */
{
   printf("Graphics error cant suppourt fill: %s\n", grapherrormsg(errorcode));
   printf("Press any key to exit");
   getch();
   fcloseall();
   closegraph();
   exit(1);
   /* terminate with an error code */
}          setfillstyle(style,getcolor());
	  floodfill(x,y,getcolor());
	  if( x > 2 && x < 518 && y >2 && y < 427 )
	   fprintf(f,"8 %d %d %d %d %d ",getcolor(),x,y,style,temp2);
	  }
	 else if(ch == 's')
	  {
	   cleardevice();
	   printf("\n\n\n\n\n\n\t\t\t\tTYPE FILE NAME AND PRESS ENTER");
	   printf("\n\n\n\n\t\t\tFILE NAME:-c:\\tc\\bin\\");
	   scanf("%s",&a);
	   fclose(f);
	   copy(a,"save");
	   cleardevice();
	   main();
	   ch = tempch;
	  }
	   else if(ch == 'o')
	  {
	   cleardevice();
	   printf("ENTER THE FILE NAME :-");
	   scanf("%s",&a);
	   fclose(f);
	   cleardevice();
   setcolor(GREEN);
   setviewport(1,1,575,460,1);
   rectangle(1,1,565,455);
   rectangle(3,3,563,453);
   setfillstyle(1,GREEN);
   floodfill(2,2,GREEN);
   setcolor(WHITE);
   setviewport(20,10,getmaxx()-100,getmaxy()-30,1);
	   convert(a);
	   cleardevice();
	   main();
	   }
	}
	 showmouseptr();
   }
}


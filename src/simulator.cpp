#include "simulator.h"

Simulator::Simulator()
{
 x=y=0;
 moves=NULL;
 current_move=0;
 number_of_moves=0;
}

void Simulator::Init_pos()
{
 x=y=0;
 current_move=0;
}

void Simulator::Load_map(char *filename)
{
 FILE *in=fopen(filename,"r");
 int n;
 fscanf(in,"%d ",&n);
 MAP.resize(n);
 for(int i=0;i<n;i++)
     {
      MAP[i].resize(n);
     }
 for(int i=0;i<n;i++)
     {
      for(int j=0;j<n;j++)
          {
           int x;
           fscanf(in,"%d ",&x);
           MAP[i][j]=x;
          }
     }
 fclose(in);
}

void Simulator::Load_moves(char *filename)
{
 FILE *in=fopen(filename,"r");
 fscanf(in,"%d ",&number_of_moves);
 moves=new char[number_of_moves];
 for(int i=0;i<number_of_moves;i++)
     {
      int q;
      fscanf(in,"%d ",&q);
      moves[i]=q;
     }
}

void Simulator::Create_path_image()
{
 Init_pos();
 path_image=Create_Transparent_Texture(MAP.size()*OBSTACLE_IMAGE->w,MAP.size()*OBSTACLE_IMAGE->h);
 SDL_SetRenderTarget(RENDERER,path_image->image);
 while(current_move<number_of_moves && !(x==MAP.size()-1 && y==MAP.size()-1))
       {
        SDL_SetRenderDrawColor(RENDERER,255*current_move/number_of_moves,0,255-255*current_move/number_of_moves,255);
        SDL_Rect rct={y*OBSTACLE_IMAGE->w,x*OBSTACLE_IMAGE->h,OBSTACLE_IMAGE->w,OBSTACLE_IMAGE->h};
        SDL_RenderFillRect(RENDERER,&rct);
        Move();
       }
 SDL_SetRenderTarget(RENDERER,NULL);
 Init_pos();
}

void Simulator::Print(Texture *_screen)
{
 for(int i=0;i<MAP.size();i++)
     {
      for(int j=0;j<MAP.size();j++)
          {
           Apply_Texture(j*OBSTACLE_IMAGE->w,i*OBSTACLE_IMAGE->h,MAP[i][j]?OBSTACLE_IMAGE:FREE_IMAGE,_screen);
          }
     }
 Apply_Texture((MAP.size()-1)*OBSTACLE_IMAGE->w,(MAP.size()-1)*OBSTACLE_IMAGE->h,HIGHLIGHT_TILE,_screen);
 Apply_Texture(0,0,path_image,_screen);
 Apply_Texture(y*OBSTACLE_IMAGE->w,x*OBSTACLE_IMAGE->h,PLAYER_IMAGE,_screen);
}

void Simulator::Move()
{
 const int dirx[]={1,0,-1,0};
 const int diry[]={0,1,0,-1};
 int x1=x+dirx[moves[current_move]];
 int y1=y+diry[moves[current_move]];
 if(x1>=0 && x1<MAP.size() && y1>=0 && y1<MAP.size() && !MAP[x1][y1])
    {
     x=x1;
     y=y1;
    }
 current_move++;
}

void Simulator::Start(Texture *_screen)
{
 Texture *buff;
 buff=Create_Transparent_Texture(MAP.size()*OBSTACLE_IMAGE->w,MAP.size()*OBSTACLE_IMAGE->h);
 SDL_Event ev;
 bool quit=false;
 while(current_move<number_of_moves && !(x==MAP.size()-1 && y==MAP.size()-1) && !quit)
       {
        SDL_PollEvent(&ev);
        if(ev.type==SDL_QUIT || (ev.type==SDL_KEYDOWN && ev.key.keysym.scancode==SDL_SCANCODE_ESCAPE))
           quit=true;
        Print(buff);
        Apply_Texture({0,0,buff->w,buff->h},buff,{0,0,_screen->w,_screen->h},_screen);
        Flip_Buffers(_screen);
        Move();
        if(current_move>3*number_of_moves/4)
           SDL_Delay(200);
        else
           SDL_Delay(100);
       }
 if(!(x==MAP.size()-1 && y==MAP.size()-1))
    printf("\nDestination not reached!!");
 else
    printf("\nDestination reached!");
}

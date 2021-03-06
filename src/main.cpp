#include "settings.h"
#include "simulator.h"

#include <cstdio>
#include <ctime>
#include <cstdlib>

Texture *screen;

int main( int argc, char *args[] )
{
 char aux[100],path[100]={"output/gen_"};
 scanf("%s",aux);
 strcat(path,aux);
 strcat(path,".txt");
 ///Random
 srand((unsigned int)(time(NULL)));
 ///Random
 if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
     FILE *log_file=fopen("err/logs.txt","w");
     fprintf(log_file,"SDL_Init() failed : %s ",SDL_GetError());
     fclose(log_file);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"SDL_Init() failed : ");
     strcat(message,SDL_GetError());
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL failure",message,NULL);
     exit(-1);
    }
 if(TTF_Init()==-1)
    {
     FILE *log_file=fopen("err/logs.txt","w");
     fprintf(log_file,"TTF_Init() failed : %s ",TTF_GetError());
     fclose(log_file);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"TTF_Init() failed : ");
     strcat(message,SDL_GetError());
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL_TTF module failure",message,NULL);
     exit(-2);
    }
 Load_Settings();
 Open_Window_and_Renderer(RESOLUTION_W,RESOLUTION_H,DISPLAY_MODE);
 last_frame=Create_Transparent_Texture(RESOLUTION_W,RESOLUTION_H);
 screen=new Texture;
 screen->w=RESOLUTION_W;
 screen->h=RESOLUTION_H;
 screen->image=NULL;
 SCREEN=screen;
 if(screen==NULL)
    {
     FILE *log_file=fopen("err/logs.txt","w");
     fprintf(log_file,"Open_Window_and_Renderer failed : %s ",SDL_GetError());
     fclose(log_file);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"Open_Window_and_Renderer failed : ");
     strcat(message,SDL_GetError());
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL video module failure",message,NULL);
     exit(-1);
    }
 Flip_Buffers(screen);
 //static_screen=screen;
 Simulator test;
 test.Load_map("map.txt");
 test.Load_moves(path);
 Load_images();
 test.Create_path_image();
 test.Start(screen);
 return 0;
}

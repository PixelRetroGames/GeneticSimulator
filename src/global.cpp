#include "global.h"

Texture *OBSTACLE_IMAGE,*FREE_IMAGE,*PLAYER_IMAGE,*HIGHLIGHT_TILE;
bool LOADED_IMAGES=false;

void Load_images()
{
 if(LOADED_IMAGES)
    return;
 OBSTACLE_IMAGE=Load_Transparent_Texture("res/img/obstacle.png");
 FREE_IMAGE=Load_Transparent_Texture("res/img/free.png");
 PLAYER_IMAGE=Load_Transparent_Texture("res/img/player.png");
 HIGHLIGHT_TILE=Load_Transparent_Texture("res/img/highlight.png");
 LOADED_IMAGES=true;
}

void Clear_images()
{
 if(!LOADED_IMAGES)
    return;
 Destroy_Texture(OBSTACLE_IMAGE);
 Destroy_Texture(FREE_IMAGE);
 Destroy_Texture(PLAYER_IMAGE);
 Destroy_Texture(HIGHLIGHT_TILE);
 LOADED_IMAGES=false;
}

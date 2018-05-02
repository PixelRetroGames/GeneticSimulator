#ifndef GLOBAL_H
#define GLOBAL_H

#include "texture.h"

extern Texture *OBSTACLE_IMAGE,*FREE_IMAGE,*PLAYER_IMAGE,*HIGHLIGHT_TILE;
extern bool LOADED_IMAGES;

void Load_images();
void Clear_images();

#endif // GLOBAL_H

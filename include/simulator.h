#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "texture.h"
#include "global.h"
#include <vector>

class Simulator
{
 private:
 int x,y;
 char *moves;
 int current_move=0,number_of_moves=0;
 std::vector<std::vector<bool>> MAP;
 Texture *path_image;

 public:
 Simulator();
 void Init_pos();
 void Load_map(char *filename);
 void Load_moves(char *filename);
 void Create_path_image();
 void Print(Texture *_screen);
 void Move();
 void Start(Texture *_screen);
};

#endif // SIMULATOR_H

#include <ncurses.h>

//Structure to hold properties of food
struct Obstacle {
  int x;
  int y;
  int xsize;
  int ysize;
  struct Obstacle* next;
};

typedef struct Obstacle Obstacle; 

//Function prototypes 
void add_new_obstacle(Obstacle* obstacles, Obstacle* new_obstacle);
bool obstacle_exists(Obstacle* obstacles, int x, int y);
Obstacle* create_obstacle(int x, int y, int xsize, int ysize);
void draw_obstacles(Obstacle *Obstacle);
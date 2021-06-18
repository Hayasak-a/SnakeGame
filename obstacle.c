

#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "obstacle.h"


//Create new food
Obstacle* create_obstacle(int x, int y, int xsize, int ysize){
    Obstacle* new_obstacle = malloc(sizeof(Obstacle));
     
    new_obstacle->x = x;
    new_obstacle->y = y;
    new_obstacle->xsize = xsize;
    new_obstacle->ysize = ysize;
    new_obstacle->next = NULL;

    return new_obstacle;
}

//Check if food exists at coordinates
bool obstacle_exists(Obstacle* obst, int x, int y){
    Obstacle* temp = obst;
    while(temp){
        if((temp->x <= x && temp->x + temp->xsize >=x) && (temp->y <= y && temp->y+temp->ysize>=y))
            return true;
        temp = temp->next;
    }
    return false;
}

//Add new food to end of food list
void add_new_obstacle(Obstacle* obst, Obstacle* new_obst){
    Obstacle* temp = obst;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = new_obst;
}

// Display all the food
void draw_obstacles (Obstacle *obst)
{   Obstacle* temp = obst;
    while(temp) {
      int i;
      int j;
       for( i = temp->x; i <= temp ->x+temp->xsize; i++)
        {
          for(j = temp->y; j <= temp -> y+temp->ysize; j++)
          {
            mvprintw(j, i, "V");
          }
        }
        
        temp = temp->next;
    }
}

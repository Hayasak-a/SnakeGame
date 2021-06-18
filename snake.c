/* snake.c -------
 *
 * Filename: snake.c
 * Description:
 * Author: Rishabh Agrawal
 * Maintainer:
 * Created: Sun Sep 13 9:12:30 2020
 * Last-Updated: September 13 22:40 2020
 *           By: Rishabh Agrawal
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 *
 *
 */

/* Copyright (c) 2016 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */


#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "snake.h"
#include "key.h"
#include "obstacle.h"
#include <ncurses.h>

int TOP_EDGE;
int BOTTOM_EDGE;
int LEFT_EDGE;
int RIGHT_EDGE;


// Initialize snake
Snake* init_snake(int x, int y){
  Snake* head = create_tail(x, y);
  Snake* tail1 = create_tail(x-1, y);
  Snake* tail2 = create_tail(x-2, y);
  tail1->next = tail2;
  head->next = tail1;
  LEFT_EDGE = x-34;
  RIGHT_EDGE = x+34;
  TOP_EDGE = y-15;
  BOTTOM_EDGE = y+15;
  return head;
}

Snake* reduced_snake(Snake* snake) {
  if(snake-> next == NULL)
  {
    return NULL;
  }
  else{
    return snake->next;
  }

}
// Creates one tail
Snake* create_tail(int x, int y){
  Snake* snake = malloc(sizeof(snake));
  snake->color[0] = 0;
  snake->color[1] = 0;
  snake->color[2] = 0;
  /* snake->color = {0, 0, 255}; */
  snake->symbol = '#';
  snake->next = NULL;
  snake->x = x;
  snake->y = y;
  return snake;
}

// Moves the snake in the input direction
Snake* move_snake(Snake* snake, int direction){
    // TODO
  Snake* new_head = malloc(sizeof(new_head));

  // Set the new head to have the x and y coordinates as the existing head of the snake
  new_head->x = snake->x;
  new_head->y = snake->y;
  
  switch(direction) { 
    case UP:
        //Write code to make the new head go up by 1 cell
        if(snake->next) { if((snake->next->y) == (snake->y -1))
        {
          return snake;
        }}
        new_head->y -=1;
      break;
    case DOWN:
    if(snake->next) { if((snake->next->y) == (snake->y +1))
        {
          return snake;
        }}
        //Write code to make the new head go down by 1 cell
        new_head->y +=1;
      break;
    case RIGHT:
    if(snake->next) {if((snake->next->x) == (snake->x +1))
        {
          return snake;
        }}
        //Write code to make the new head go right by 1 cell
        new_head->x+=1;
      break;
    case LEFT:
    if(snake->next) {if((snake->next->x) == (snake->x -1))
        {
          return snake;
        }}
        //Write code to make the new head go left by 1 cell
        new_head->x-=1;
      break;
  }

  //Move head to opposite edge if it hits an edge
  if(new_head->x == RIGHT_EDGE+1)
  {
    new_head->x = LEFT_EDGE;
  }
  if(new_head->x == LEFT_EDGE-1)
  {
    new_head->x = RIGHT_EDGE;
  }
  if(new_head->y == TOP_EDGE - 1)
  {
    new_head-> y = BOTTOM_EDGE;
  }
  if(new_head->y==BOTTOM_EDGE+1)
  {
    new_head->y = TOP_EDGE;
  }


  
  //Set new head as the new head of the entire snake
  //Add all the features (color and symbol) to the new cell
  // Delete the tail from the snake: HINT - there is a remove tail function below
  new_head->next = snake;
  strcpy(new_head->color, snake->color);
  new_head->symbol = snake->symbol;
  remove_tail(new_head);


  

  return new_head;
}

Snake* reverse_snake(Snake* snake){
  if(snake->next==NULL) { return NULL; }
  struct Snake* prev = NULL;
  struct Snake* curr = snake;
  struct Snake* next = NULL;

  while(curr != NULL)
  {
    next = curr -> next;
    curr -> next = prev;
    prev = curr;
    curr = next;

  }
  Snake* temp = prev;
  int k = 0;
  while(temp->next)
  {
    temp = temp-> next;
    k++;

  }
  mvprintw(20, 20, "%d", k);
  return prev;

}

Snake* remove_tail(Snake* snake){
  if(!snake->next) { return NULL; }
    Snake* end = snake;
    while(end->next->next)
        end = end->next;
    free(end->next);
    end->next = NULL;
    return snake;
}

// draws the snake on the board
void draw_snake(Snake* snake){
  while(snake){
    mvprintw(snake->y, snake->x, "%c", snake->symbol);
    snake = snake->next;
  }
}

// checks if it eats itself, if it does, then return true
bool eat_itself(Snake* snake){
    // TODO for Milestone 2 only
}
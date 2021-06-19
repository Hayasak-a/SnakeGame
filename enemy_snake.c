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
#include "enemy_snake.h"
#include "key.h"
#include "obstacle.h"
#include <ncurses.h>

int TOP_EDGE;
int BOTTOM_EDGE;
int LEFT_EDGE;
int RIGHT_EDGE;


// Initialize snake
eSnake* init_esnake(int x, int y){
  eSnake* head = create_etail(x, y);
  eSnake* tail1 = create_etail(x-1, y);
  eSnake* tail2 = create_etail(x-2, y);
  eSnake* tail3 = create_etail(x-3, y);
  eSnake* tail4 = create_etail(x-4, y);
  tail1->next = tail2;
  head->next = tail1;
  tail2->next = tail3;
  tail3->next = tail4;
  LEFT_EDGE = x-34;
  RIGHT_EDGE = x+34;
  TOP_EDGE = y-15;
  BOTTOM_EDGE = y+15;
  return head;
}

eSnake* reduced_esnake(eSnake* snake) {
  if(snake-> next == NULL)
  {
    return NULL;
  }
  else{
    return snake->next;
  }

}
// Creates one tail
eSnake* create_etail(int x, int y){
  eSnake* snake = malloc(sizeof(snake));
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
eSnake* move_esnake(eSnake* snake, int direction){
    // TODO
  eSnake* new_head = malloc(sizeof(new_head));

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
  remove_etail(new_head);
  if(e_eat_itself(new_head)==true) { remove_etail(new_head); }


  

  return new_head;
}

eSnake* reverse_esnake(eSnake* snake){
  if(snake->next==NULL) { return NULL; }
  struct eSnake* prev = NULL;
  struct eSnake* curr = snake;
  struct eSnake* next = NULL;

  while(curr != NULL)
  {
    next = curr -> next;
    curr -> next = prev;
    prev = curr;
    curr = next;

  }
  eSnake* temp = prev;
  int k = 0;
  while(temp->next)
  {
    temp = temp-> next;
    k++;

  }
  mvprintw(20, 20, "%d", k);
  return prev;

}

eSnake* remove_etail(eSnake* snake){
  if(!snake->next) { return NULL; }
    eSnake* end = snake;
    while(end->next->next)
        end = end->next;
    free(end->next);
    end->next = NULL;
    return snake;
}

// draws the snake on the board
void draw_esnake(eSnake* snake){
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK); 
  attron(COLOR_PAIR(1));
  while(snake){
    mvprintw(snake->y, snake->x, "%c", snake->symbol);
    snake = snake->next;
  }
  attroff(COLOR_PAIR(1));
}

// checks if it eats itself, if it does, then return true
bool e_eat_itself(eSnake* snake){
  eSnake* temp = snake;
    // TODO for Milestone 2 only
    while(temp->next)
    {
      temp = temp->next;
      if((snake->x==temp->x) && (snake->y == temp->y))
      { 
        return true;
      }

    }
    return false;
}
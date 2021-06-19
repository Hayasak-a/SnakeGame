/* snake.h -------
 *
 * Filename: snake.h
 * Description:
 * Author: Rishabh Agrawal
 * Maintainer:
 * Created: Sun Sep 13 21:01:02 2020
 * Last-Updated: September 13 22:43 2020
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


#include <stdbool.h>

struct eSnake {
  int x;
  int y;
  int speed;
  char color[3];
  char symbol;
  bool enemy;
  struct eSnake* next;
};

typedef struct eSnake eSnake;

eSnake* init_esnake(int x, int y);
eSnake* create_etail(int x, int y);
eSnake* reduced_esnake(eSnake* snake);
eSnake* move_esnake(eSnake* snake, int direction);
eSnake* reverse_esnake(eSnake* snake);
void draw_esnake(eSnake* snake);
bool e_eat_itself(eSnake* snake);
eSnake* remove_etail(eSnake* snake);
int elen(eSnake* snake);
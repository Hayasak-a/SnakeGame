#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "food.h"
#include "game_window.h"
#include "key.h"
#include "game.h"
#include "obstacle.h"

void generate_points(int *food_x, int *food_y, int width, int height, int x_offset, int y_offset){
    *food_x = rand() % width + x_offset;
    *food_y = rand() % height + y_offset;
}

void saveGame(Obstacle * obst, Food * foods, Snake * snek, int score, int lives) {
  endwin();
  clear();
  int inp;
  while(inp!=99) {
    printf("Input filename: ");
    char file[99];
    scanf("%s", file);
    char fullfile[106];
    sprintf(fullfile, "saves/%s.dat", file);
    FILE * outfile = fopen(fullfile, "w");
    if( outfile == NULL ) {
    fprintf(stderr, "Couldn't open %s\n", fullfile);
    exit(1);
}
    int tracko = 0;
    Obstacle* tempo = obst;
    while(tempo -> next)
    {
      tempo = tempo -> next;
      tracko++;
    }
    fwrite(&tracko, sizeof(int), 1, outfile);
    fwrite(&obst, sizeof(struct Obstacle), 1, outfile);
    tempo = obst;
    while(tempo -> next)
    {
      tempo = tempo -> next;
      fwrite(&tempo, sizeof(struct Obstacle), 1, outfile);
    }

    int trackf = 0;
    Food* tempf = foods;
    while(tempf -> next)
    {
      tempf = tempf -> next;
      trackf++;
    }
    fwrite(&trackf, sizeof(int), 1, outfile);
    fwrite(&foods, sizeof(struct Food), 1, outfile);
    tempf = foods;
    while(tempf -> next)
    {
      tempf = tempf -> next;
      fwrite(&tempf, sizeof(struct Food), 1, outfile);
    }
    
    int tracks = 0;
    Snake* temps = snek;
    while(temps -> next)
    {
      temps = temps -> next;
      tracks++;
    }
    fwrite(&tracks, sizeof(int), 1, outfile);
    fwrite(&snek, sizeof(struct Snake), 1, outfile);
    temps = snek;
    while(temps -> next)
    {
      temps = temps -> next;
      fwrite(&temps, sizeof(struct Snake), 1, outfile);
    }

    fwrite(&score, sizeof(int), 1, outfile);
    fwrite(&lives, sizeof(int), 1, outfile);

    
    fclose(outfile);
    inp = 99;

  }
}

void updateBestScores(int score) {
  int found = 0;
  int i = 0;
  int j;
  for(i = 0; i < 5; i++)
  {
    if(score > best_scores[i] && found == 0)
    {
      found = 1;
      for(j = 4; j > i; j--)
      {
        best_scores[j] = best_scores[j-1];
      }
      best_scores[i] = score;
    }
  }

  FILE * scorefile = fopen("saves/best_5.game", "w");
  for(i = 0; i < 5; i++)
  {
    fwrite(best_scores+i, sizeof(int), 1, scorefile);
  }
  fclose(scorefile);
}

void game(int lives, int s){
    FILE * scorefile = fopen("saves/best_5.game", "r");
    if(scorefile!= NULL) {
    int i = 0;
      while(fread(best_scores+i, sizeof(int), 1, scorefile))
      {
        i++;
      }
    fclose(scorefile);}
    int score = s;
    score += rand()%100;
    enum State state = INIT; // Set the initial state
    static int x_max, y_max; //Max screen size variables
    static int x_offset, y_offset; // distance between the top left corner of your screen and the start of the board
    gamewindow_t *window; // Name of the board
    Snake *snake; // The snake
    Food *foods,*new_food; // List of foods (Not an array)
    Obstacle *obst, *new_obst;

    const int height = 30; 
    const int width = 70;
    char ch;

    struct timespec timeret;
    timeret.tv_sec = 0;
    timeret.tv_nsec = 999999999/4;

    while(state != EXIT){
        switch(state){
        case INIT:
            initscr();
            start_color();
            nodelay(stdscr, TRUE); //Dont wait for char
            noecho(); // Don't echo input chars
            getmaxyx(stdscr, y_max, x_max);
            keypad(stdscr, TRUE); // making keys work
            curs_set(0); // hide cursor
            timeout(100);

            // Setting height and width of the board
            x_offset = (x_max / 2) - (width / 2);
            y_offset = (y_max / 2) - (height / 2);
            
            //Init board
            window = init_GameWindow(x_offset, y_offset, width, height);
            draw_Gamewindow(window);

            // Init snake
            snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));
            
            // Init foods
            int food_x, food_y, i;
            enum Type type;

            //Generate 10 foods
            generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
            type = (rand() > RAND_MAX/2) ? Increase : Decrease; // Randomly deciding type of food
            foods = create_food(food_x, food_y, type);
            for(i = 1; i < 10; i++){
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                while (food_exists(foods,food_x, food_y))
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                type = (rand() > RAND_MAX/2) ? Increase : Decrease;
                new_food = create_food(food_x, food_y, type);
                add_new_food(foods, new_food);
            }

            int obst_num = rand()%5+3;
            int obst_xsize = rand()%4;
            int obst_ysize = rand()%4;
            int obst_x, obst_y, j;
            generate_points(&obst_x, &obst_y, width-4, height-4, x_offset, y_offset);
            obst = create_obstacle(obst_x, obst_y, obst_xsize, obst_ysize);

            for(j = 1; j < obst_num; j++)
            {
              generate_points(&obst_x, &obst_y, width-4, height-4, x_offset, y_offset);
              obst_xsize = rand()%4;
              obst_ysize = rand()%4;
              while (obstacle_exists(obst, obst_x, obst_y))
              {
                generate_points(&obst_x, &obst_y, width-4, height-4, x_offset, y_offset);
              }
              new_obst = create_obstacle(obst_x, obst_y, obst_xsize, obst_ysize);
              add_new_obstacle(obst, new_obst);
            }
            state = ALIVE;
            break;

        case ALIVE:
            ch = get_char(); 
            Snake* temp = snake;
            switch(ch) {
              
              case LEFT:
              temp = move_snake(snake, LEFT);
              break;
              case RIGHT:
              temp = move_snake(snake, RIGHT);
              break;
              case DOWN:
              temp = move_snake(snake, DOWN);
              break;
              case UP:
              temp = move_snake(snake, UP);
              break;
              case ',':
              //Since milestone 2 has no way to reduce snake's size (without Milestone 1 elements)
              // I'm adding this case to manually reduce its size
              snake = remove_tail(snake);
              
              break;
              case 'p':
              case 'P':
              //Implement pause menu
              clear();
              int currLine = 0;
             
              ch = 'a';
              while(ch != 'p' && ch != 'P')
              {
                ch = get_char();
                switch(ch) {
                case UP:
                if(currLine<=0) { currLine = 2; }
                else { currLine--;}
                break;
                case DOWN:
                if(currLine>=2) { currLine = 0; }
                else { currLine++; }
                break;
                case 10:
                //Value of ENTER key
                {
                  if(currLine ==0) { ch = 'p'; }
                  else if(currLine==1) { saveGame(obst, foods, snake, score, lives); 
                  }
                  else if(currLine==2) {
                    endwin();
                    clear();
                    state = EXIT;
                    ch = 'p';
                  }
                }
                break;
                }
                mvprintw(20, 20, "Game paused");
                mvprintw(21, 18, "%c Unpause game", currLine==0 ? '>' : ' ');
                mvprintw(22, 18, "%c Save game", currLine==1 ? '>' : ' ');
                mvprintw(23, 18, "%c Quit game", currLine==2 ? '>' : ' ');
                
              }
              break;


            }
            if(obstacle_exists(obst, temp->x, temp->y))
            {
              snake = reverse_snake(snake);
            }
            else
            {
              snake = temp;
            }

            if(snake==NULL)
            {
              // If snake is gone, snake is dead
              state = DEAD;
            }

            
            /* Write your code here */

			// Draw everything on the screen
            clear();
            mvprintw(20,20, "Key entered: %c", ch);
            mvprintw(21, 20, "Lives remaining: %d", lives);
            mvprintw(22, 20, "Score: %d", score);
            draw_Gamewindow(window);
            draw_snake(snake);
            draw_food(foods);
            draw_obstacles(obst);
            break;

        case DEAD:
          endwin();
          clear();
          
            if(lives>1)
            {
              mvprintw(20, 20, "Press s to continue game");
              mvprintw(21, 20, "Lives remaining: %d", lives-1);
              mvprintw(22, 20, "Score: %d", score);
              char input = 'a';
              while(input != 's')
              {
                input = get_char();
              }
              game(lives-1, score);
            }
            else 
            {
              lives = 0;
              mvprintw(20, 20, "Press s to restart game");
              mvprintw(21, 20, "Your score: %d", score);
              updateBestScores(score);
              mvprintw(22, 20, "High scores:");
	      int z;
              for(z = 0; i < 5; i++)
              {
                mvprintw(23+z, 20, "%d. %d\n", z+1, best_scores[z]);
              }
              char input = 'a';
              while(input != 's')
              {
                input = get_char();
              }
              game(3, 0);
            }        
            break;
        case EXIT:
          clear();
          break;
        }
        if(state!=EXIT) {refresh();}
        nanosleep(&timeret, NULL);
    }
}


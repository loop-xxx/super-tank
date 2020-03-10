#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_UP 0
#define PLAYER_DOWN 1
#define PLAYER_LEFT 2
#define PLAYER_RIGHT 3

#include <time.h>
#include <stdbool.h>
#include "map.h"
extern void player_init(unsigned int blood, clock_t move_speed, clock_t fire_speed) ;
extern void player_draw(void) ;
extern void player_move(unsigned int direction) ;
extern bool player_isover(void) ;
extern void player_position(short *x_pointer, short *y_pointer) ;
extern bool player_move_isok(void) ;
extern void player_hp_1(void) ;
extern bool player_fire_isok(void) ;
extern void player_fire(void) ;
extern void player_bomb(void) ;

#endif // PLAYER_H

#ifndef BULLET_H
#define BULLET_H

#include <time.h>
#include <stdbool.h>

#define BULLET_UP 0x1
#define BULLET_DOWN 0x2
#define BULLET_LEFT 0x4
#define BULLET_RIGHT 0x8
#define BULLET_DEFAULT_SPEED 0x20


extern void bullet_list_init(void) ;
extern void bullet_list_add(short x, short y, unsigned char sign,\
                            unsigned int life, unsigned int direction, clock_t speed, void(*effect)(void*)) ;
extern void bullet_list_move(void) ;
extern void bullet_laser_effect(void *pointer) ;
extern void bullet_bomb_effect(void *pointer) ;
extern void bullet_mid_laser_effect(void *pointer) ;
#endif // BULLET_H

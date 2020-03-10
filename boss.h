#ifndef BOSS_H
#define BOSS_H

#include <time.h>
#include <stdbool.h>

extern void boss_draw(void) ;
extern void boss_init(unsigned int max_blood, short tank_init_offset, clock_t move_speed,\
                      clock_t skill_speed, clock_t tank_move_speed) ;
extern void boss_move(short x, short y) ;
extern bool boss_move_isok(void) ;
extern bool boss_tank_move_isok(void) ;
extern void boss_tank_move(short x, short y) ;
extern void boss_skill(void) ;
extern bool boss_skill_isok(void) ;
extern bool boss_fire_isok(void) ;
extern void boss_fire(void) ;
extern void boss_hp_1(void) ;
extern void boss_tank_hp_1(unsigned char tank_sign) ;
extern bool boss_isover(void) ;
#endif // BOSS_H

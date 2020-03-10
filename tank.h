#ifndef TANK_H
#define TANK_H

#include <time.h>
#include <stdbool.h>
#include "map.h"
#include "link.h"

#define TANK_UP 0
#define TANK_DOWN 1
#define TANK_LEFT 2
#define TANK_RIGHT 3


typedef struct _tank{
    struct{
        short x , y ;
    }m_position ;
    unsigned int m_blood ;
    link_node m_link ;
    unsigned char m_sign ;
}tank ;


extern void tank_flush(tank *tank_pointer) ;
extern void tank_draw(tank *tank_pointer) ;
extern void tank_clear(tank *tank_pointer) ;
extern bool tank_position_check(tank *tank_pointer) ;
extern bool tank_move_check(tank *tank_pointer, unsigned int direction ) ;
#endif // TANK_H

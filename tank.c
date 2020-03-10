#include "tank.h"

/**
 * @brief _tank_iscrash_object 判断是否与其他物体相撞
 * @param tank_pointer
 * @return
 */
bool _tank_iscrash_object(tank *tank_pointer)
{
    bool iscrash = false ;
    if(
            IS_CRASH_OBJECT(tank_pointer->m_position.x-1, tank_pointer->m_position.y-1, tank_pointer->m_sign) ||\
            IS_CRASH_OBJECT(tank_pointer->m_position.x, tank_pointer->m_position.y-1, tank_pointer->m_sign) || \
            IS_CRASH_OBJECT(tank_pointer->m_position.x+1, tank_pointer->m_position.y-1, tank_pointer->m_sign) ||\

            IS_CRASH_OBJECT(tank_pointer->m_position.x-1, tank_pointer->m_position.y, tank_pointer->m_sign) ||\
            IS_CRASH_OBJECT(tank_pointer->m_position.x, tank_pointer->m_position.y, tank_pointer->m_sign) || \
            IS_CRASH_OBJECT(tank_pointer->m_position.x+1, tank_pointer->m_position.y, tank_pointer->m_sign) ||\

            IS_CRASH_OBJECT(tank_pointer->m_position.x-1, tank_pointer->m_position.y+1, tank_pointer->m_sign) ||\
            IS_CRASH_OBJECT(tank_pointer->m_position.x, tank_pointer->m_position.y+1, tank_pointer->m_sign) || \
            IS_CRASH_OBJECT(tank_pointer->m_position.x+1, tank_pointer->m_position.y+1, tank_pointer->m_sign)
            )
    {
           iscrash = true ;
    }

    return iscrash ;
}
/**
 * @brief _tank_iscrash_sence 检测是否与环境相撞
 * @param tank_pointer
 * @return
 */
bool _tank_iscrash_sence(tank *tank_pointer)
{
    bool iscrash = false ;

    if(
            IS_CRASH_SCENE(tank_pointer->m_position.x-1, tank_pointer->m_position.y-1) || \
            IS_CRASH_SCENE(tank_pointer->m_position.x, tank_pointer->m_position.y-1) || \
            IS_CRASH_SCENE(tank_pointer->m_position.x+1, tank_pointer->m_position.y-1) || \

            IS_CRASH_SCENE(tank_pointer->m_position.x-1, tank_pointer->m_position.y) || \
            IS_CRASH_SCENE(tank_pointer->m_position.x, tank_pointer->m_position.y) || \
            IS_CRASH_SCENE(tank_pointer->m_position.x+1, tank_pointer->m_position.y) || \

            IS_CRASH_SCENE(tank_pointer->m_position.x-1, tank_pointer->m_position.y+1) || \
            IS_CRASH_SCENE(tank_pointer->m_position.x, tank_pointer->m_position.y+1) || \
            IS_CRASH_SCENE(tank_pointer->m_position.x+1, tank_pointer->m_position.y+1)
            )
    {
           iscrash = true ;
    }

    return iscrash ;
}


//在物理地图上放置tank
static inline void _put_tank(tank *tank_pointer)
{
    PUT_OBJECT(tank_pointer->m_position.x-1, tank_pointer->m_position.y-1, tank_pointer->m_sign) ;
    PUT_OBJECT(tank_pointer->m_position.x, tank_pointer->m_position.y-1, tank_pointer->m_sign) ;
    PUT_OBJECT(tank_pointer->m_position.x+1, tank_pointer->m_position.y-1, tank_pointer->m_sign) ;

    PUT_OBJECT(tank_pointer->m_position.x-1, tank_pointer->m_position.y, tank_pointer->m_sign) ;
    PUT_OBJECT(tank_pointer->m_position.x, tank_pointer->m_position.y, tank_pointer->m_sign) ;
    PUT_OBJECT(tank_pointer->m_position.x+1, tank_pointer->m_position.y, tank_pointer->m_sign) ;

    PUT_OBJECT(tank_pointer->m_position.x-1, tank_pointer->m_position.y+1, tank_pointer->m_sign) ;
    PUT_OBJECT(tank_pointer->m_position.x, tank_pointer->m_position.y+1, tank_pointer->m_sign) ;
    PUT_OBJECT(tank_pointer->m_position.x+1, tank_pointer->m_position.y+1, tank_pointer->m_sign) ;
}
//在物理地图上拿起tank
static inline void _take_tank(tank *tank_pointer)
{
    TAKE_OBJECT(tank_pointer->m_position.x-1, tank_pointer->m_position.y-1) ;
    TAKE_OBJECT(tank_pointer->m_position.x, tank_pointer->m_position.y-1) ;
    TAKE_OBJECT(tank_pointer->m_position.x+1, tank_pointer->m_position.y-1) ;

    TAKE_OBJECT(tank_pointer->m_position.x-1, tank_pointer->m_position.y) ;
    TAKE_OBJECT(tank_pointer->m_position.x, tank_pointer->m_position.y) ;
    TAKE_OBJECT(tank_pointer->m_position.x+1, tank_pointer->m_position.y) ;

    TAKE_OBJECT(tank_pointer->m_position.x-1, tank_pointer->m_position.y+1) ;
    TAKE_OBJECT(tank_pointer->m_position.x, tank_pointer->m_position.y+1) ;
    TAKE_OBJECT(tank_pointer->m_position.x+1, tank_pointer->m_position.y+1) ;
}

//在console上画出tank
static inline void _tank_draw(tank *player_pointer)
{
    write_char(player_pointer->m_position.x-1, player_pointer->m_position.y-1, tank_pic[0], F_H_BLUE) ;
    write_char(player_pointer->m_position.x, player_pointer->m_position.y-1, tank_pic[1], F_H_BLUE) ;
    write_char(player_pointer->m_position.x+1, player_pointer->m_position.y-1, tank_pic[0], F_H_BLUE) ;


    write_char(player_pointer->m_position.x-1, player_pointer->m_position.y, tank_pic[1], F_H_BLUE) ;
    write_char(player_pointer->m_position.x, player_pointer->m_position.y, num_pic[player_pointer->m_blood], F_H_BLUE) ;
    write_char(player_pointer->m_position.x+1, player_pointer->m_position.y, tank_pic[1], F_H_BLUE) ;


    write_char(player_pointer->m_position.x-1, player_pointer->m_position.y+1, tank_pic[0], F_H_BLUE) ;
    write_char(player_pointer->m_position.x, player_pointer->m_position.y+1, tank_pic[1], F_H_BLUE) ;
    write_char(player_pointer->m_position.x+1, player_pointer->m_position.y+1, tank_pic[0], F_H_BLUE) ;
}
//在console上清除tank
static inline void _tank_clear(tank *player_pointer)
{
    CLEAR_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y-1) ;
    CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1) ;
    CLEAR_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y-1) ;

    CLEAR_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y) ;
    CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y) ;
    CLEAR_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y) ;

    CLEAR_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y+1) ;
    CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1) ;
    CLEAR_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y+1) ;
}

bool tank_position_check(tank *tank_pointer)
{
    bool result = false ;

    if(!_tank_iscrash_object(tank_pointer) && !_tank_iscrash_sence(tank_pointer))
    {
        result = true ;
    }

    return result ;
}

bool tank_move_check(tank *tank_pointer, unsigned int direction )
{
    bool result = false ;

    switch (direction)
    {
    case TANK_UP:
        tank_pointer->m_position.y -= 1;
        if(!_tank_iscrash_object(tank_pointer) && !_tank_iscrash_sence(tank_pointer))
        {
            result = true ;
        }
        tank_pointer->m_position.y +=1 ;

        break ;
    case TANK_DOWN:
        tank_pointer->m_position.y += 1;
        if(!_tank_iscrash_object(tank_pointer) && !_tank_iscrash_sence(tank_pointer))
        {
            result = true ;
        }
        tank_pointer->m_position.y -= 1;
        break ;
    case TANK_LEFT:
        tank_pointer->m_position.x -=1 ;
        if(!_tank_iscrash_object(tank_pointer) && !_tank_iscrash_sence(tank_pointer))
        {
            result = true ;
        }
        tank_pointer->m_position.x += 1;
        break ;
    case TANK_RIGHT:
        tank_pointer->m_position.x +=1 ;
        if(!_tank_iscrash_object(tank_pointer) && !_tank_iscrash_sence(tank_pointer))
        {
            result = true ;
        }
        tank_pointer->m_position.x -= 1;
        break ;
    }

    return result ;
}

void tank_draw(tank *tank_pointer)
{
    _put_tank(tank_pointer) ;
    _tank_draw(tank_pointer) ;
}
void tank_flush(tank *tank_pointer)
{
    _tank_draw(tank_pointer) ;
}

void tank_clear(tank *tank_pointer)
{
    _take_tank(tank_pointer) ;
    _tank_clear(tank_pointer) ;
}

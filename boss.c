#include <stdlib.h>
#include "boss.h"
#include "tank.h"
#include "bullet.h"


typedef struct _boss{
    struct{
        short x , y ;
    }m_position ;
    unsigned int m_direction ;
    unsigned int m_blood ;
    unsigned int m_max_blood ;


    clock_t m_move_speed ;
    clock_t m_skill_speed;
    clock_t m_tank_move_speed ;

    unsigned int m_skill_number ;
    void (*m_skill_arr[0x5])(void) ;

    link_node m_tank_link_head ;
    short m_tank_init_offset ;
    unsigned char m_sign ;
    unsigned char m_sign_seed ;
    unsigned char m_bullet_sign ;
    bool m_body[0x7][0xc] ;
}boss ;

static boss b1 ;

//将boss放置在物理地图
static inline void _put_boss(boss *boss_pointer)
{
    switch (boss_pointer->m_direction)
    {
    case TANK_UP:
        for(short row = 0 ; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    PUT_OBJECT(boss_pointer->m_position.x + col, boss_pointer->m_position.y+((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) - 1) - row), boss_pointer->m_sign) ;
                }
            }
        }
        break;
    case TANK_DOWN:
        for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    PUT_OBJECT(boss_pointer->m_position.x + col, boss_pointer->m_position.y+row, boss_pointer->m_sign) ;
                }
            }
        }
        break;
    case TANK_LEFT:
        for(short col = 0 ; col < (short)((sizeof boss_pointer->m_body[0])/sizeof( boss_pointer->m_body[0][0])) ; col++)
        {
            for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    PUT_OBJECT(boss_pointer->m_position.x + ((short)((sizeof boss_pointer->m_body)/ sizeof(boss_pointer->m_body[0]) -1)- row), boss_pointer->m_position.y+col, boss_pointer->m_sign) ;
                }
            }
        }

        break ;
    case TANK_RIGHT:
        for(short col = 0 ; col < (short)((sizeof boss_pointer->m_body[0])/sizeof( boss_pointer->m_body[0][0])) ; col++)
        {
            for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    PUT_OBJECT(boss_pointer->m_position.x + row, boss_pointer->m_position.y+col, boss_pointer->m_sign) ;
                }
            }
        }
        break ;
    }
}
//将boss从物理地图上拿起
static inline void _take_boss(boss *boss_pointer)
{
    switch (boss_pointer->m_direction)
    {
    case TANK_UP:
        for(short row = 0 ; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    TAKE_OBJECT(boss_pointer->m_position.x + col, boss_pointer->m_position.y+((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) - 1) - row)) ;
                }
            }
        }
        break;
    case TANK_DOWN:
        for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof(boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    TAKE_OBJECT(boss_pointer->m_position.x + col, boss_pointer->m_position.y+row) ;
                }
            }
        }
        break;
    case TANK_LEFT:
        for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
        {
            for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    TAKE_OBJECT(boss_pointer->m_position.x + ((short)((sizeof boss_pointer->m_body)/ sizeof(boss_pointer->m_body[0]) -1)- row), boss_pointer->m_position.y+col) ;
                }
            }
        }

        break ;
    case TANK_RIGHT:
        for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
        {
            for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    TAKE_OBJECT(boss_pointer->m_position.x + row, boss_pointer->m_position.y+col) ;
                }
            }
        }
        break ;
    }
}

//将boss画在控制台上
static inline void _boss_draw(boss *boss_pointer)
{
    switch (boss_pointer->m_direction)
    {
    case TANK_UP:
        for(short row = 0 ; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    write_char(boss_pointer->m_position.x + col, boss_pointer->m_position.y+((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) - 1) - row), tank_pic[0], F_H_BLUE) ;
                    write_char(boss_pointer->m_position.x + col, boss_pointer->m_position.y+((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) - 1) - row), num_pic[boss_pointer->m_blood/0x10], B_H_GREEN) ;
                }
            }
        }
        break;
    case TANK_DOWN:
        for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    write_char(boss_pointer->m_position.x + col, boss_pointer->m_position.y+row, tank_pic[0], F_H_BLUE) ;
                    write_char(boss_pointer->m_position.x + col, boss_pointer->m_position.y+row, num_pic[boss_pointer->m_blood/0x10], B_H_GREEN) ;
                }
            }
        }
        break;
    case TANK_LEFT:
        for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
        {
            for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    write_char(boss_pointer->m_position.x + ((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) - 1) - row), boss_pointer->m_position.y+col, tank_pic[0], F_H_BLUE) ;
                    write_char(boss_pointer->m_position.x + ((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) - 1) - row), boss_pointer->m_position.y+col, num_pic[boss_pointer->m_blood/0x10], B_H_GREEN) ;
                }
            }
        }
        break;
    case TANK_RIGHT:
        for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
        {
            for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    write_char(boss_pointer->m_position.x + row, boss_pointer->m_position.y+col, tank_pic[0], F_H_BLUE) ;
                    write_char(boss_pointer->m_position.x + row, boss_pointer->m_position.y+col, num_pic[boss_pointer->m_blood/0x10], B_H_GREEN) ;
                }
            }
        }
        break;
    }
}
//将boss从控制台上清除
static inline void _boss_clear(boss *boss_pointer)
{
    switch (boss_pointer->m_direction)
    {
    case TANK_UP:
        for(short row = 0 ; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    CLEAR_OBJECT(boss_pointer->m_position.x + col, boss_pointer->m_position.y+((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) - 1) - row)) ;
                }
            }
        }
        break;
    case TANK_DOWN:
        for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    CLEAR_OBJECT(boss_pointer->m_position.x + col, boss_pointer->m_position.y+row) ;
                }
            }
        }
        break;
    case TANK_LEFT:
        for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
        {
            for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    CLEAR_OBJECT(boss_pointer->m_position.x + ((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) -1) - row), boss_pointer->m_position.y+col) ;
                }
            }
        }

        break ;
    case TANK_RIGHT:
        for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
        {
            for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    CLEAR_OBJECT(boss_pointer->m_position.x + row, boss_pointer->m_position.y+col) ;
                }
            }
        }
        break ;
    }
}

/**
 * @brief _boss_iscrash_object 判断是否有其他对象
 * @param boss_pointer
 * @return
 */
static inline bool _boss_iscrash_object(boss *boss_pointer)
{
    bool result = false;

    switch (boss_pointer->m_direction)
    {
    case TANK_UP:
        for(short row = 0 ; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    if(IS_CRASH_OBJECT(boss_pointer->m_position.x + col, boss_pointer->m_position.y+((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) - 1) - row), boss_pointer->m_sign))
                    {
                        result = true ;
                        break ;
                    }
                }
            }
        }
        break;
    case TANK_DOWN:
        for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    if(IS_CRASH_OBJECT(boss_pointer->m_position.x + col, boss_pointer->m_position.y+row, boss_pointer->m_sign))
                    {
                        result = true ;
                        break ;
                    }
                }
            }
        }
        break;
    case TANK_LEFT:
        for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
        {
            for(short row = 0 ; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    if(IS_CRASH_OBJECT(boss_pointer->m_position.x + ((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) -1) - row), boss_pointer->m_position.y+col, boss_pointer->m_sign))
                    {
                        result = true ;
                        break ;
                    }
                }
            }
        }
        break;
    case TANK_RIGHT:
        for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
        {
            for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    if(IS_CRASH_OBJECT(boss_pointer->m_position.x + row, boss_pointer->m_position.y+col,  boss_pointer->m_sign))
                    {
                        result = true ;
                        break ;
                    }
                }
            }
        }
        break;
    }
    return  result ;
}
/**
 * @brief _boss_iscrash_sence 判断是否有障碍物
 * @param boss_pointer
 * @return
 */
static inline bool _boss_iscrash_sence(boss *boss_pointer)
{
    bool result = false;

    switch (boss_pointer->m_direction)
    {
    case TANK_UP:
        for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    if(IS_CRASH_SCENE(boss_pointer->m_position.x + col, boss_pointer->m_position.y+((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) - 1) - row)))
                    {
                        result = true ;
                        break ;
                    }
                }
            }
        }
        break;
    case TANK_DOWN:
        for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
        {
            for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    if(IS_CRASH_SCENE(boss_pointer->m_position.x + col, boss_pointer->m_position.y+row))
                    {
                        result = true ;
                        break ;
                    }
                }
            }
        }
        break;
    case TANK_LEFT:
        for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
        {
            for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    if(IS_CRASH_SCENE(boss_pointer->m_position.x + ((short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0]) -1) - row), boss_pointer->m_position.y+col))
                    {
                        result = true ;
                        break ;
                    }
                }
            }
        }
        break;
    case TANK_RIGHT:
        for(short col = 0; col < (short)((sizeof boss_pointer->m_body[0])/ sizeof( boss_pointer->m_body[0][0])); col++)
        {
            for(short row = 0; row < (short)((sizeof boss_pointer->m_body)/ sizeof( boss_pointer->m_body[0])); row++)
            {
                if(boss_pointer->m_body[row][col])
                {
                    if(IS_CRASH_SCENE(boss_pointer->m_position.x + row, boss_pointer->m_position.y+col))
                    {
                        result = true ;
                        break ;
                    }
                }
            }
        }
        break;
    }
    return  result ;
}

/**
 * @brief _boss_move_check 判断boss是否可以移动
 * @param boss_pointer
 * @return
 */
static inline bool _boss_move_check(boss *boss_pointer, unsigned int direction)
{
    bool result ;

    result = false ;
    switch (direction)
    {
    case TANK_UP:
        boss_pointer->m_position.y -= 1;
        if(!_boss_iscrash_object(boss_pointer) && !_boss_iscrash_sence(boss_pointer))
        {
            result = true ;
        }
        boss_pointer->m_position.y += 1;
        break ;
    case TANK_DOWN:
        boss_pointer->m_position.y += 1;
        if(!_boss_iscrash_object(boss_pointer) && !_boss_iscrash_sence(boss_pointer))
        {
            result = true ;
        }
        boss_pointer->m_position.y -= 1;
        break ;
    case TANK_LEFT:
        boss_pointer->m_position.x -= 1;
        if(!_boss_iscrash_object(boss_pointer) && !_boss_iscrash_sence(boss_pointer))
        {
            result = true ;
        }
        boss_pointer->m_position.x += 1;
        break ;
    case TANK_RIGHT:
        boss_pointer->m_position.x += 1;
        if(!_boss_iscrash_object(boss_pointer) && !_boss_iscrash_sence(boss_pointer))
        {
            result = true ;
        }
        boss_pointer->m_position.x -= 1;
        break ;
    }
    return  result ;
}
/**
 * @brief _boss_turn_check 判断boss是否可以转头
 * @param boss_pointer
 * @param direction
 * @return
 */
static inline bool _boss_turn_check(boss *boss_pointer, unsigned int direction)
{
    bool result;

    result = false ;
    //转头
    direction =  direction ^  boss_pointer->m_direction  ;
    boss_pointer->m_direction = direction ^ boss_pointer->m_direction ;
    direction = direction ^ boss_pointer->m_direction ;
    if(!_boss_iscrash_object(boss_pointer) && !_boss_iscrash_sence(boss_pointer))
    {
        result = true ;
    }
    //回头
    direction =  direction ^  boss_pointer->m_direction  ;
    boss_pointer->m_direction = direction ^ boss_pointer->m_direction ;
    direction = direction ^ boss_pointer->m_direction ;

    return result ;
}

static inline void _boss_turn(boss *boss_pointer, unsigned int direction)
{
    if(_boss_turn_check(boss_pointer, direction))
    {
        _boss_clear(boss_pointer) ;
        _take_boss(boss_pointer) ;
        boss_pointer->m_direction = direction ;
        _put_boss(boss_pointer) ;
        _boss_draw(boss_pointer) ;
    }
}
static inline void _boss_move(boss *boss_pointer, unsigned int direction)
{
    if(_boss_move_check(boss_pointer, direction))
    {
        _boss_clear(boss_pointer) ;
        _take_boss(boss_pointer) ;
        switch(direction)
        {
        case TANK_UP:
            boss_pointer->m_position.y -= 1;
            break;
        case TANK_DOWN:
            boss_pointer->m_position.y += 1;
            break ;
        case TANK_LEFT:
            boss_pointer->m_position.x -= 1;
            break ;
        case TANK_RIGHT:
            boss_pointer->m_position.x += 1;
            break ;
        }
        _put_boss(boss_pointer) ;
        _boss_draw(boss_pointer) ;
    }
}

bool boss_move_isok()
{
    bool result ;
    clock_t current_clock ;
    static clock_t move_last_clock = 0 ;

    result = false ;
    current_clock = clock() ;
    if(current_clock - move_last_clock >= b1.m_move_speed * (clock_t)(b1.m_blood/10))
    {
        move_last_clock = current_clock ;
        result = true ;
    }

    return result ;
}

bool boss_tank_move_isok()
{
    bool result ;
    clock_t current_clock ;
    static clock_t tank_move_last_clock = 0 ;

    result = false ;
    current_clock = clock() ;
    if(current_clock - tank_move_last_clock >= b1.m_tank_move_speed)
    {
        tank_move_last_clock = current_clock ;
        result = true ;
    }

    return result ;
}

void boss_tank_move(short x, short y)
{
    link_node *node_pointer ;
    tank *tank_pointer ;
    short row, col ;

    node_pointer = &b1.m_tank_link_head ;
    while((node_pointer = node_pointer->next) != &b1.m_tank_link_head)
    {
        tank_pointer = ADDR_LINK2DATA(node_pointer, tank, m_link) ;
        row = tank_pointer->m_position.y - y ;
        col = tank_pointer->m_position.x - x ;
        if((col>=0 ? col:0-col) > (row >= 0?row : 0-row) )
        {
            if(col < 0)
            {
                if(tank_move_check(tank_pointer, TANK_RIGHT))
                {
                    tank_clear(tank_pointer) ;
                    tank_pointer->m_position.x += 1;
                    tank_draw(tank_pointer) ;
                }else {

                    if(row < 0)
                    {
                        if(tank_move_check(tank_pointer, TANK_DOWN))
                        {
                            tank_clear(tank_pointer) ;
                            tank_pointer->m_position.y += 1;
                            tank_draw(tank_pointer) ;
                        }
                    }else {
                        if(tank_move_check(tank_pointer, TANK_UP))
                        {
                            tank_clear(tank_pointer) ;
                            tank_pointer->m_position.y -= 1;
                            tank_draw(tank_pointer) ;
                        }
                    }
                }
            }
            else
            {
                if(tank_move_check(tank_pointer, TANK_LEFT))
                {
                    tank_clear(tank_pointer) ;
                    tank_pointer->m_position.x -= 1;
                    tank_draw(tank_pointer) ;
                }else {

                    if(row < 0)
                    {
                        if(tank_move_check(tank_pointer, TANK_DOWN))
                        {
                            tank_clear(tank_pointer) ;
                            tank_pointer->m_position.y += 1;
                            tank_draw(tank_pointer) ;
                        }
                    }else {
                        if(tank_move_check(tank_pointer, TANK_UP))
                        {
                            tank_clear(tank_pointer) ;
                            tank_pointer->m_position.y -= 1;
                            tank_draw(tank_pointer) ;
                        }
                    }
                }
            }
        }
        else
        {
            if(row < 0)
            {
                if(tank_move_check(tank_pointer, TANK_DOWN))
                {
                    tank_clear(tank_pointer) ;
                    tank_pointer->m_position.y += 1;
                    tank_draw(tank_pointer) ;
                }else {
                    if(col < 0)
                    {
                        if(tank_move_check(tank_pointer, TANK_RIGHT))
                        {
                            tank_clear(tank_pointer) ;
                            tank_pointer->m_position.x += 1;
                            tank_draw(tank_pointer) ;
                        }
                    }
                    else
                    {
                        if(tank_move_check(tank_pointer, TANK_LEFT))
                        {
                            tank_clear(tank_pointer) ;
                            tank_pointer->m_position.x -= 1;
                            tank_draw(tank_pointer) ;
                        }
                    }
                }
            }else {
                if(tank_move_check(tank_pointer, TANK_UP))
                {
                    tank_clear(tank_pointer) ;
                    tank_pointer->m_position.y -= 1;
                    tank_draw(tank_pointer) ;
                }else {
                    if(col < 0)
                    {
                        if(tank_move_check(tank_pointer, TANK_RIGHT))
                        {
                            tank_clear(tank_pointer) ;
                            tank_pointer->m_position.x += 1;
                            tank_draw(tank_pointer) ;
                        }
                    }
                    else
                    {
                        if(tank_move_check(tank_pointer, TANK_LEFT))
                        {
                            tank_clear(tank_pointer) ;
                            tank_pointer->m_position.x -= 1;
                            tank_draw(tank_pointer) ;
                        }
                    }

                }
            }
        }

    }
}

void boss_move(short x, short y)
{
    short row, col ;
    if(b1.m_direction < TANK_LEFT)
    {
        row = b1.m_position.y + (short)(sizeof b1.m_body/sizeof b1.m_body[0]/2) - y  ;
        col = b1.m_position.x + (short)(sizeof b1.m_body[0]/sizeof b1.m_body[0][0]/2) - x ;
    }else {
        row = b1.m_position.y + (short)(sizeof b1.m_body[0]/sizeof b1.m_body[0][0]/2) - y  ;
        col = b1.m_position.x + (short)(sizeof b1.m_body/sizeof b1.m_body[0]/2) - x ;
    }

    if((col>=0 ? col:0-col) > (row >= 0?row : 0-row) )
    {
        if(col < 0)
        {
            if(b1.m_direction ==  TANK_RIGHT)
            {
                if(row > 0)
                {
                    _boss_move(&b1, TANK_UP) ;
                }else {
                    _boss_move(&b1, TANK_DOWN) ;
                }
            }else {
                _boss_turn(&b1, TANK_RIGHT) ;
            }

        }
        else
        {
            if(b1.m_direction ==  TANK_LEFT)
            {
                if(row > 0)
                {
                    _boss_move(&b1, TANK_UP ) ;
                }else {
                    _boss_move(&b1, TANK_DOWN ) ;
                }
            }else{
                _boss_turn(&b1, TANK_LEFT) ;
            }

        }
    }
    else
    {
        if(row < 0)
        {
            if(b1.m_direction == TANK_DOWN)
            {
                if(col > 0)
                {
                    _boss_move(&b1, TANK_LEFT) ;

                }else{
                    _boss_move(&b1, TANK_RIGHT) ;
                }
            }else {
                _boss_turn(&b1, TANK_DOWN) ;
            }
        }
        else
        {
            if(b1.m_direction == TANK_UP)
            {
                if(col > 0)
                {
                    _boss_move(&b1, TANK_LEFT) ;
                }else{
                    _boss_move(&b1, TANK_RIGHT) ;

                }
            }else {
                _boss_turn(&b1, TANK_UP) ;
            }
        }
    }
}

static inline void _boss_tank_list_add(boss *boss_pointer)
{
    tank *tank_pointer;


    if(boss_pointer->m_direction < TANK_LEFT)
    {
        {//tank1
            boss_pointer->m_sign_seed += boss_pointer->m_sign ;
            tank_pointer = malloc(sizeof(tank)) ;
            tank_pointer->m_sign = boss_pointer->m_sign_seed ;
            tank_pointer->m_blood = (boss_pointer->m_max_blood - boss_pointer->m_blood)/0x10*0x2 + 0x1;

            tank_pointer->m_position.x =  boss_pointer->m_position.x - boss_pointer->m_tank_init_offset ;
            tank_pointer->m_position.y = boss_pointer->m_position.y + (short)(sizeof boss_pointer->m_body/sizeof boss_pointer->m_body[0]/2) ;
            if(tank_pointer->m_position.x < 0 || tank_pointer->m_position.x >= MAP_WIDTH ||\
                    tank_pointer->m_position.y < 0 || tank_pointer->m_position.y >= MAP_HEIGHT ||\
                    !tank_position_check(tank_pointer))//如果boss的两边无法创建tank,则在随机位置创建
            {
                do{
                    tank_pointer->m_position.x = (short)rand()%(MAP_WIDTH-1) + 1 ;
                    tank_pointer->m_position.y = (short)rand()%(MAP_HEIGHT-1) + 1;
                }while(!tank_position_check(tank_pointer)) ;
            }
            link_add(&boss_pointer->m_tank_link_head, &tank_pointer->m_link) ;
            tank_draw(tank_pointer) ;
        }
        {//tank2

            boss_pointer->m_sign_seed += boss_pointer->m_sign ;
            tank_pointer = malloc(sizeof(tank)) ;
            tank_pointer->m_sign = boss_pointer->m_sign_seed ;
            tank_pointer->m_blood = (boss_pointer->m_max_blood - boss_pointer->m_blood)/0x10*0x2 + 0x1;

            tank_pointer->m_position.x =  boss_pointer->m_position.x +(short)(sizeof boss_pointer->m_body[0]/sizeof boss_pointer->m_body[0][0]) + boss_pointer->m_tank_init_offset ;
            tank_pointer->m_position.y = boss_pointer->m_position.y + (short)(sizeof boss_pointer->m_body/sizeof boss_pointer->m_body[0]/2) ;
            if(tank_pointer->m_position.x < 0 || tank_pointer->m_position.x >= MAP_WIDTH ||\
                    tank_pointer->m_position.y < 0 || tank_pointer->m_position.y >= MAP_HEIGHT ||\
                    !tank_position_check(tank_pointer))//如果boss的两边无法创建tank,则在随机位置创建
            {
                do{
                    tank_pointer->m_position.x = (short)rand()%(MAP_WIDTH-1) + 1 ;
                    tank_pointer->m_position.y = (short)rand()%(MAP_HEIGHT-1) + 1;
                }while(!tank_position_check(tank_pointer)) ;
            }
            link_add(&boss_pointer->m_tank_link_head, &tank_pointer->m_link) ;
            tank_draw(tank_pointer) ;
        }
    }else {

        {//tank1
            boss_pointer->m_sign_seed += boss_pointer->m_sign ;
            tank_pointer = malloc(sizeof (tank)) ;
            tank_pointer->m_sign = boss_pointer->m_sign_seed ;
            tank_pointer->m_blood = (boss_pointer->m_max_blood - boss_pointer->m_blood)/0x10*0x2 + 0x1;

            tank_pointer->m_position.x = boss_pointer->m_position.x + (short)(sizeof boss_pointer->m_body/sizeof boss_pointer->m_body[0]/2) ;
            tank_pointer->m_position.y = boss_pointer->m_position.y - boss_pointer->m_tank_init_offset ;
            if(tank_pointer->m_position.x < 0 || tank_pointer->m_position.x >= MAP_WIDTH ||\
                    tank_pointer->m_position.y < 0 || tank_pointer->m_position.y >= MAP_HEIGHT ||\
                    !tank_position_check(tank_pointer))//如果boss的两边无法创建tank,则在随机位置创建
            {
                do{
                    tank_pointer->m_position.x = (short)rand()%(MAP_WIDTH-1) + 1 ;
                    tank_pointer->m_position.y = (short)rand()%(MAP_HEIGHT-1) + 1;
                }while(!tank_position_check(tank_pointer)) ;
            }
            link_add(&boss_pointer->m_tank_link_head, &tank_pointer->m_link) ;
            tank_draw(tank_pointer) ;
        }
        {//tank2
            boss_pointer->m_sign_seed += boss_pointer->m_sign ;
            tank_pointer = malloc(sizeof (tank)) ;
            tank_pointer->m_sign = boss_pointer->m_sign_seed ;
            tank_pointer->m_blood = (boss_pointer->m_max_blood - boss_pointer->m_blood)/0x10*0x2 + 0x1;

            tank_pointer->m_position.x = boss_pointer->m_position.x + (short)(sizeof boss_pointer->m_body/sizeof boss_pointer->m_body[0]/2) ;
            tank_pointer->m_position.y = boss_pointer->m_position.y + (short)(sizeof b1.m_body[0]/sizeof b1.m_body[0][0]) + boss_pointer->m_tank_init_offset ;

            if(tank_pointer->m_position.x < 0 || tank_pointer->m_position.x >= MAP_WIDTH ||\
                    tank_pointer->m_position.y < 0 || tank_pointer->m_position.y >= MAP_HEIGHT ||\
                    !tank_position_check(tank_pointer))//如果boss的两边无法创建tank,则在随机位置创建
            {
                do{
                    tank_pointer->m_position.x = (short)rand()%(MAP_WIDTH-1) + 1 ;
                    tank_pointer->m_position.y = (short)rand()%(MAP_HEIGHT-1) + 1;
                }while(!tank_position_check(tank_pointer)) ;
            }
            link_add(&boss_pointer->m_tank_link_head, &tank_pointer->m_link) ;
            tank_draw(tank_pointer) ;
        }
    }
}

void boss_tank_list_add()
{
    _boss_tank_list_add(&b1) ;
}

void boss_hp_1()
{
    if(b1.m_blood)
    {
        b1.m_blood -= 1;
        _boss_draw(&b1) ;
    }
}

void boss_tank_hp_1(unsigned char tank_sign)
{
    link_node *node_pointer ;
    tank *tank_pointer;

    node_pointer = b1.m_tank_link_head.next ;
    while(node_pointer != &b1.m_tank_link_head)
    {
        tank_pointer = ADDR_LINK2DATA(node_pointer, tank, m_link) ;
        node_pointer = node_pointer->next ;

        if(tank_pointer->m_sign == tank_sign)
        {
            tank_pointer->m_blood -= 1;
            tank_flush(tank_pointer) ;
            if(!tank_pointer->m_blood)//如果hp为0则死亡
            {
                tank_clear(tank_pointer) ;
                _link_remove(&tank_pointer->m_link) ;
                free(tank_pointer) ;
            }
        }
    }
}

bool boss_skill_isok()
{
    bool result ;
    clock_t current_clock ;
    static clock_t first_clock = 0 ;

    result = false ;
    current_clock = clock() ;
    if(current_clock - first_clock >= b1.m_skill_speed)
    {
        first_clock = current_clock ;
        result = true ;
    }

    return result ;
}

void boss_skill()
{
    b1.m_skill_arr[b1.m_skill_number]() ;
    b1.m_skill_number = (b1.m_skill_number + 0x1)% (sizeof(b1.m_skill_arr)/sizeof (b1.m_skill_arr[0])) ;
}



static inline void _boss_laser(boss* boss_pointer)
{
    switch (boss_pointer->m_direction) {
    case TANK_UP:
        bullet_list_add(boss_pointer->m_position.x, boss_pointer->m_position.y-1, boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_UP, BULLET_DEFAULT_SPEED, &bullet_laser_effect) ;
        bullet_list_add(boss_pointer->m_position.x + (short)(sizeof(boss_pointer->m_body[0]) /sizeof(boss_pointer->m_body[0][0])) -1, boss_pointer->m_position.y-1, boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_UP, BULLET_DEFAULT_SPEED, &bullet_laser_effect) ;
        break ;
    case TANK_DOWN:
        bullet_list_add(boss_pointer->m_position.x, boss_pointer->m_position.y+(short)(sizeof(boss_pointer->m_body)/sizeof (boss_pointer->m_body[0]))+1, boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_DOWN, BULLET_DEFAULT_SPEED, &bullet_laser_effect) ;
        bullet_list_add(boss_pointer->m_position.x + (short)(sizeof(boss_pointer->m_body[0]) /sizeof(boss_pointer->m_body[0][0])) -1, boss_pointer->m_position.y+(short)(sizeof(boss_pointer->m_body)/sizeof (boss_pointer->m_body[0]))+1, boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_DOWN, BULLET_DEFAULT_SPEED, &bullet_laser_effect) ;
        break ;
    case TANK_LEFT:
        bullet_list_add(boss_pointer->m_position.x-1, boss_pointer->m_position.y, boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_LEFT, BULLET_DEFAULT_SPEED, &bullet_laser_effect) ;
        bullet_list_add(boss_pointer->m_position.x-1, boss_pointer->m_position.y + (short)(sizeof(boss_pointer->m_body[0]) /sizeof(boss_pointer->m_body[0][0])) - 1, boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_LEFT, BULLET_DEFAULT_SPEED, &bullet_laser_effect) ;
        break ;
    case TANK_RIGHT:
        bullet_list_add(boss_pointer->m_position.x + (short)(sizeof(boss_pointer->m_body) /sizeof(boss_pointer->m_body[0])), boss_pointer->m_position.y, boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_RIGHT, BULLET_DEFAULT_SPEED, &bullet_laser_effect) ;
        bullet_list_add(boss_pointer->m_position.x + (short)(sizeof(boss_pointer->m_body) /sizeof(boss_pointer->m_body[0])),boss_pointer->m_position.y + (short)(sizeof(boss_pointer->m_body[0]) /sizeof(boss_pointer->m_body[0][0])) -1 , boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_RIGHT, BULLET_DEFAULT_SPEED, &bullet_laser_effect) ;
        break ;
    }
}


void boss_laser()
{
    _boss_laser(&b1) ;
}

static inline void _boss_mid_laser(boss *boss_pointer)
{
    short random_offset = (short)(rand()%0x5 - 0x2) ;

    switch (boss_pointer->m_direction) {
    case TANK_UP:
        bullet_list_add(boss_pointer->m_position.x + (short)(sizeof boss_pointer->m_body[0] / sizeof boss_pointer->m_body[0][0]) / 2 + random_offset, boss_pointer->m_position.y-1, boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_UP, 0x10, &bullet_mid_laser_effect) ;
        break ;
    case TANK_DOWN:
        bullet_list_add(boss_pointer->m_position.x + (short)(sizeof boss_pointer->m_body[0] / sizeof boss_pointer->m_body[0][0]) / 2 + random_offset, boss_pointer->m_position.y+(short)(sizeof(boss_pointer->m_body)/sizeof (boss_pointer->m_body[0]))+1, boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_DOWN, 0x10, &bullet_mid_laser_effect) ;
        break ;
    case TANK_LEFT:
        bullet_list_add(boss_pointer->m_position.x-1, boss_pointer->m_position.y + (short)(sizeof boss_pointer->m_body[0] / sizeof boss_pointer->m_body[0][0]) / 2 + random_offset,boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_LEFT, 0x10, &bullet_mid_laser_effect) ;
        break ;
    case TANK_RIGHT:
        bullet_list_add(boss_pointer->m_position.x + (short)(sizeof(boss_pointer->m_body) /sizeof(boss_pointer->m_body[0])), boss_pointer->m_position.y+ (short)(sizeof boss_pointer->m_body[0] / sizeof boss_pointer->m_body[0][0]) / 2 + random_offset, boss_pointer->m_bullet_sign,\
                         0xffffffff, BULLET_RIGHT, 0x10, &bullet_mid_laser_effect) ;
        break ;
    }
}

bool boss_isover()
{
    return b1.m_blood == 0 ;
}

void boss_mid_laser()
{
    _boss_mid_laser(&b1) ;
}

static inline void _boss_fire(boss *boss_pointer, unsigned int life, void(*effect)(void*))
{
    if(boss_pointer->m_direction < TANK_LEFT)
    {
        for(short height = 0; height < (short)(sizeof boss_pointer->m_body / sizeof boss_pointer->m_body[0]) ; height++)
        {
            if(height < (short)(sizeof boss_pointer->m_body / sizeof boss_pointer->m_body[0])/3)
            {
                bullet_list_add(boss_pointer->m_position.x - 1,boss_pointer->m_position.y+height,\
                                boss_pointer->m_bullet_sign, life, BULLET_UP|BULLET_LEFT, BULLET_DEFAULT_SPEED, effect) ;
                bullet_list_add(boss_pointer->m_position.x + (short)(sizeof boss_pointer->m_body[0]/ sizeof boss_pointer->m_body[0][0]), boss_pointer->m_position.y+height,\
                        boss_pointer->m_bullet_sign, life, BULLET_UP|BULLET_RIGHT, BULLET_DEFAULT_SPEED, effect) ;
            }
            else if(height > (((short)(sizeof boss_pointer->m_body / sizeof boss_pointer->m_body[0]) - 1) - (short)(sizeof boss_pointer->m_body / sizeof boss_pointer->m_body[0])/3))
            {
                bullet_list_add(boss_pointer->m_position.x - 1,boss_pointer->m_position.y+height,\
                                boss_pointer->m_bullet_sign, life, BULLET_DOWN|BULLET_LEFT, BULLET_DEFAULT_SPEED, effect) ;
                bullet_list_add(boss_pointer->m_position.x + (short)(sizeof boss_pointer->m_body[0]/ sizeof boss_pointer->m_body[0][0]), boss_pointer->m_position.y+height,\
                        boss_pointer->m_bullet_sign, life, BULLET_DOWN|BULLET_RIGHT, BULLET_DEFAULT_SPEED, effect) ;
            }else {
                bullet_list_add(boss_pointer->m_position.x - 1,boss_pointer->m_position.y+height,\
                                boss_pointer->m_bullet_sign, life, BULLET_LEFT, BULLET_DEFAULT_SPEED, effect) ;
                bullet_list_add(boss_pointer->m_position.x + (short)(sizeof boss_pointer->m_body[0]/ sizeof boss_pointer->m_body[0][0]), boss_pointer->m_position.y+height,\
                        boss_pointer->m_bullet_sign, life, BULLET_RIGHT, BULLET_DEFAULT_SPEED, effect) ;
            }
        }
    }
    else
    {
        for(short width = 0; width < (short)(sizeof boss_pointer->m_body / sizeof boss_pointer->m_body[0]) ; width++)
        {
            if(width < (short)(sizeof boss_pointer->m_body / sizeof boss_pointer->m_body[0])/3)
            {
                bullet_list_add(boss_pointer->m_position.x+width, boss_pointer->m_position.y -1, boss_pointer->m_bullet_sign,\
                                 life, BULLET_LEFT |BULLET_UP, BULLET_DEFAULT_SPEED, effect) ;
                bullet_list_add(boss_pointer->m_position.x+width, boss_pointer->m_position.y + (short)(sizeof (boss_pointer->m_body[0])/ sizeof(boss_pointer->m_body[0][0])), boss_pointer->m_bullet_sign,\
                                 life, BULLET_LEFT |BULLET_DOWN, BULLET_DEFAULT_SPEED, effect) ;
            }
            else if(width > ((short)(sizeof boss_pointer->m_body / sizeof boss_pointer->m_body[0]) - 1) - (short)(sizeof boss_pointer->m_body / sizeof boss_pointer->m_body[0])/3)
            {
                bullet_list_add(boss_pointer->m_position.x+width, boss_pointer->m_position.y -1, boss_pointer->m_bullet_sign,\
                                 life, BULLET_RIGHT|BULLET_UP, BULLET_DEFAULT_SPEED, effect) ;
                bullet_list_add(boss_pointer->m_position.x+width, boss_pointer->m_position.y + (short)(sizeof (boss_pointer->m_body[0])/ sizeof(boss_pointer->m_body[0][0])), boss_pointer->m_bullet_sign,\
                                 life, BULLET_RIGHT|BULLET_DOWN, BULLET_DEFAULT_SPEED, effect) ;

            }else
            {
                bullet_list_add(boss_pointer->m_position.x+width, boss_pointer->m_position.y -1, boss_pointer->m_bullet_sign,\
                                 life, BULLET_UP, BULLET_DEFAULT_SPEED, effect) ;
                bullet_list_add(boss_pointer->m_position.x+width, boss_pointer->m_position.y + (short)(sizeof (boss_pointer->m_body[0])/ sizeof(boss_pointer->m_body[0][0])), boss_pointer->m_bullet_sign,\
                                 life, BULLET_DOWN, BULLET_DEFAULT_SPEED, effect) ;
            }
        }
    }
}

static inline void _boss_tank_fire(boss *boss_pointer, unsigned int life, void(*effect)(void*))
{
    link_node *node_pointer ;

    node_pointer = &boss_pointer->m_tank_link_head ;
    while((node_pointer = node_pointer->next) != &boss_pointer->m_tank_link_head)
    {
        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x+2,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y-1,\
                        boss_pointer->m_bullet_sign, life, BULLET_RIGHT|BULLET_UP, BULLET_DEFAULT_SPEED, effect) ;
        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x+2,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y,\
                        boss_pointer->m_bullet_sign, life, BULLET_RIGHT, BULLET_DEFAULT_SPEED, effect) ;
        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x+2,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y+1,\
                        boss_pointer->m_bullet_sign, life, BULLET_RIGHT|BULLET_DOWN, BULLET_DEFAULT_SPEED, effect) ;

        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x-2,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y-1,\
                        boss_pointer->m_bullet_sign, life, BULLET_LEFT|BULLET_UP, BULLET_DEFAULT_SPEED, effect) ;
        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x-2,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y,\
                        boss_pointer->m_bullet_sign, life, BULLET_LEFT, BULLET_DEFAULT_SPEED, effect) ;
        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x-2,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y+1,\
                        boss_pointer->m_bullet_sign, life, BULLET_LEFT|BULLET_DOWN, BULLET_DEFAULT_SPEED, effect) ;

        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x-1,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y-2,\
                        boss_pointer->m_bullet_sign, life, BULLET_UP|BULLET_LEFT, BULLET_DEFAULT_SPEED, effect) ;
        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y-2,\
                        boss_pointer->m_bullet_sign, life, BULLET_UP, BULLET_DEFAULT_SPEED, effect) ;
        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x+1,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y-2,\
                        boss_pointer->m_bullet_sign, life, BULLET_UP|BULLET_RIGHT, BULLET_DEFAULT_SPEED, effect) ;

        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x-1,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y+2,\
                        boss_pointer->m_bullet_sign, life, BULLET_DOWN|BULLET_LEFT, BULLET_DEFAULT_SPEED, effect) ;
        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y+2,\
                        boss_pointer->m_bullet_sign, life, BULLET_DOWN, BULLET_DEFAULT_SPEED, effect) ;
        bullet_list_add(ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.x+1,ADDR_LINK2DATA(node_pointer, tank, m_link)->m_position.y+2,\
                        boss_pointer->m_bullet_sign, life, BULLET_DOWN|BULLET_RIGHT, BULLET_DEFAULT_SPEED, effect) ;
    }
}
void boss_fire()
{
    _boss_fire(&b1, 0x6, NULL) ;
    _boss_tank_fire(&b1, 0x6, NULL) ;
}

void boss_bomb()
{
    _boss_fire(&b1, 0xc, NULL) ;
    _boss_tank_fire(&b1, 0xc, &bullet_bomb_effect);
}



void boss_init(unsigned int max_blood, short tank_init_offset, clock_t move_speed,\
               clock_t skill_speed, clock_t tank_move_speed)
{
    srand((unsigned int)time(NULL)) ;
    b1.m_direction = TANK_DOWN ;
    b1.m_position.x = ((short)(MAP_WIDTH - sizeof(b1.m_body[0])/sizeof(b1.m_body[0][0])))/2 ;
    b1.m_position.y = 0x1 ;
    for(short row = 0; row < (short)((sizeof b1.m_body)/ sizeof( b1.m_body[0])) ; row++)
    {
        for(short col = 0; col < (short)((sizeof b1.m_body[0])/ sizeof( b1.m_body[0][0]))/2 ; col++)
        {
            if(rand()%2)
            {
                b1.m_body[row][col] = true ;
                b1.m_body[row][(short)((sizeof b1.m_body[0])/ sizeof( b1.m_body[0][0]) - 1) - col] = true ;
            }
        }
    }
    b1.m_blood = max_blood ;
    b1.m_max_blood = max_blood ;
    b1.m_move_speed = move_speed ;

    INIT_LINK_HEAD(&b1.m_tank_link_head) ;
    b1.m_tank_init_offset = tank_init_offset ;

    b1.m_tank_move_speed = tank_move_speed ;

    b1.m_skill_number = 0 ;
    b1.m_skill_speed = skill_speed ;
    b1.m_skill_arr[0] = &boss_tank_list_add ;
    b1.m_skill_arr[1] = &boss_fire ;
    b1.m_skill_arr[2] = &boss_laser ;
    b1.m_skill_arr[3] = &boss_mid_laser ;
    b1.m_skill_arr[4] = &boss_bomb ;

    b1.m_sign = '\x4';
    b1.m_sign_seed = b1.m_sign ;
    b1.m_bullet_sign = (unsigned char)'\xfc' ;
}


void boss_draw()
{
    _put_boss(&b1) ;
    _boss_draw(&b1) ;
}

#include "player.h"
#include "bullet.h"


typedef struct _player{
    struct{
        short x , y ;
    }m_position ;
    unsigned int m_direction ;

    clock_t m_move_speed ;
    clock_t m_fire_speed ;
    unsigned int m_blood ;
    unsigned int m_score ;
    unsigned char m_sign ;
    unsigned char m_bullet_sign ;
}player ;

static player p1 ;

//在物理地图上放置player
static inline void _put_palyer(player *player_pointer)
{
    switch (player_pointer->m_direction)
    {
    case PLAYER_UP:
        PUT_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y+1, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y+1, player_pointer->m_sign) ;
        break;
    case PLAYER_DOWN:
        PUT_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y-1, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y-1, player_pointer->m_sign) ;
        break ;
    case PLAYER_LEFT:
        PUT_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y-1, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y+1, player_pointer->m_sign) ;
        break ;
    case PLAYER_RIGHT:
        PUT_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y-1, player_pointer->m_sign) ;
        PUT_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y+1, player_pointer->m_sign) ;
        break ;
    }

}
//在物理地图上拿起player
static inline void _take_player(player *player_pointer)
{
    switch (player_pointer->m_direction)
    {
    case PLAYER_UP:
        TAKE_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y) ;
        TAKE_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1) ;
        TAKE_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y) ;
        TAKE_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y) ;
        TAKE_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y+1) ;
        TAKE_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y+1) ;
        break;
    case PLAYER_DOWN:
        TAKE_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y) ;
        TAKE_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1) ;
        TAKE_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y) ;
        TAKE_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y) ;
        TAKE_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y-1) ;
        TAKE_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y-1) ;
        break ;
    case PLAYER_LEFT:
        TAKE_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y) ;
        TAKE_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y) ;
        TAKE_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1) ;
        TAKE_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1) ;
        TAKE_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y-1) ;
        TAKE_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y+1) ;
        break ;
    case PLAYER_RIGHT:
        TAKE_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y) ;
        TAKE_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y) ;
        TAKE_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1) ;
        TAKE_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1) ;
        TAKE_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y-1) ;
        TAKE_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y+1) ;
        break ;
    }
}
//在console上画出player
static inline void _player_draw(player *player_pointer)
{
    switch (player_pointer->m_direction)
    {
    case PLAYER_UP:
        write_char(player_pointer->m_position.x, player_pointer->m_position.y, num_pic[player_pointer->m_blood], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x, player_pointer->m_position.y-1, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x-1, player_pointer->m_position.y, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x+1, player_pointer->m_position.y, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x-1, player_pointer->m_position.y+1, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x+1, player_pointer->m_position.y+1, tank_pic[0], F_H_YELLOW) ;
        break;
    case PLAYER_DOWN:
        write_char(player_pointer->m_position.x, player_pointer->m_position.y, num_pic[player_pointer->m_blood], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x, player_pointer->m_position.y+1, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x-1, player_pointer->m_position.y, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x+1, player_pointer->m_position.y, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x-1, player_pointer->m_position.y-1, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x+1, player_pointer->m_position.y-1, tank_pic[0], F_H_YELLOW) ;
        break ;
    case PLAYER_LEFT:
        write_char(player_pointer->m_position.x, player_pointer->m_position.y, num_pic[player_pointer->m_blood], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x-1, player_pointer->m_position.y, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x, player_pointer->m_position.y-1, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x, player_pointer->m_position.y+1, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x+1, player_pointer->m_position.y-1, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x+1, player_pointer->m_position.y+1, tank_pic[0], F_H_YELLOW) ;
        break ;
    case PLAYER_RIGHT:
        write_char(player_pointer->m_position.x, player_pointer->m_position.y, num_pic[player_pointer->m_blood], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x+1, player_pointer->m_position.y, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x, player_pointer->m_position.y-1, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x, player_pointer->m_position.y+1, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x-1, player_pointer->m_position.y-1, tank_pic[0], F_H_YELLOW) ;
        write_char(player_pointer->m_position.x-1, player_pointer->m_position.y+1, tank_pic[0], F_H_YELLOW) ;
        break ;
    }
}
//在console上清除player
static inline void _player_clear(player *player_pointer)
{

    switch (player_pointer->m_direction)
    {
    case PLAYER_UP:
        CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y) ;
        CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1) ;
        CLEAR_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y) ;
        CLEAR_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y) ;
        CLEAR_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y+1) ;
        CLEAR_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y+1) ;
        break;
    case PLAYER_DOWN:
        CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y) ;
        CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1) ;
        CLEAR_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y) ;
        CLEAR_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y) ;
        CLEAR_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y-1) ;
        CLEAR_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y-1) ;
        break ;
    case PLAYER_LEFT:
        CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y) ;
        CLEAR_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y) ;
        CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1) ;
        CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1) ;
        CLEAR_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y-1) ;
        CLEAR_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y+1) ;
        break ;
    case PLAYER_RIGHT:
        CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y) ;
        CLEAR_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y) ;
        CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1) ;
        CLEAR_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1) ;
        CLEAR_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y-1) ;
        CLEAR_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y+1) ;
        break ;
    }
}

void player_init(unsigned int blood, clock_t move_speed, clock_t fire_speed)
{
    p1.m_direction = PLAYER_UP ;
    p1.m_position.x = MAP_WIDTH/2 ;
    p1.m_position.y = MAP_HEIGHT - 3 ;

    p1.m_blood = blood ;
    p1.m_move_speed = move_speed ;

    p1.m_sign = '\x1' ;
    p1.m_bullet_sign = '\x3' ;
    p1.m_score = 0 ;
    p1.m_fire_speed = fire_speed ;
}

void player_hp_1()
{
    if(p1.m_blood)
    {
        p1.m_blood -= 1;
        _player_draw(&p1) ;
    }


}

void player_draw()
{
    _put_palyer(&p1) ;
    _player_draw(&p1) ;
}

/**
 * @brief _player_iscrash_object 检测是否与其他物体相撞
 * @param player_pointer
 * @return
 */
static inline bool _player_iscrash_object(player *player_pointer)
{
    bool iscrash = false ;
    switch (player_pointer->m_direction)
    {
    case PLAYER_UP:
        if(
                IS_CRASH_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y, player_pointer->m_sign) || \
                IS_CRASH_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1, player_pointer->m_sign) || \
                IS_CRASH_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y, player_pointer->m_sign) || \
                IS_CRASH_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y, player_pointer->m_sign) || \
                IS_CRASH_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y+1, player_pointer->m_sign) || \
                IS_CRASH_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y+1, player_pointer->m_sign)
                )
        {
               iscrash = true ;
        }
        break;
    case PLAYER_DOWN:
        if(
        IS_CRASH_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y, player_pointer->m_sign) ||\
        IS_CRASH_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1, player_pointer->m_sign) || \
        IS_CRASH_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y, player_pointer->m_sign) || \
        IS_CRASH_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y, player_pointer->m_sign) || \
        IS_CRASH_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y-1, player_pointer->m_sign) || \
        IS_CRASH_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y-1, player_pointer->m_sign)
                )
        {
            iscrash = true ;
        }
        break ;
    case PLAYER_LEFT:
        if(
        IS_CRASH_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y, player_pointer->m_sign) ||\
        IS_CRASH_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y, player_pointer->m_sign) ||\
        IS_CRASH_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1, player_pointer->m_sign) ||\
        IS_CRASH_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1, player_pointer->m_sign) ||\
        IS_CRASH_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y-1, player_pointer->m_sign) ||\
        IS_CRASH_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y+1, player_pointer->m_sign)
                )
        {
            iscrash = true ;
        }
        break ;
    case PLAYER_RIGHT:
        if(
        IS_CRASH_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y, player_pointer->m_sign) ||\
        IS_CRASH_OBJECT(player_pointer->m_position.x+1, player_pointer->m_position.y, player_pointer->m_sign) ||\
        IS_CRASH_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y-1, player_pointer->m_sign) ||\
        IS_CRASH_OBJECT(player_pointer->m_position.x, player_pointer->m_position.y+1, player_pointer->m_sign) ||\
        IS_CRASH_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y-1, player_pointer->m_sign) ||\
        IS_CRASH_OBJECT(player_pointer->m_position.x-1, player_pointer->m_position.y+1, player_pointer->m_sign)
                )
        {
            iscrash = true ;
        }
        break ;
    }

    return iscrash ;
}
/**
 * @brief _player_iscrash_sence 检测是否与环境相撞
 * @param player_pointer
 * @return
 */
static inline bool _player_iscrash_sence(player *player_pointer)
{
    bool iscrash = false ;
    switch (player_pointer->m_direction)
    {
    case PLAYER_UP:
        if(
                IS_CRASH_SCENE(player_pointer->m_position.x, player_pointer->m_position.y) || \
                IS_CRASH_SCENE(player_pointer->m_position.x, player_pointer->m_position.y-1) || \
                IS_CRASH_SCENE(player_pointer->m_position.x-1, player_pointer->m_position.y) || \
                IS_CRASH_SCENE(player_pointer->m_position.x+1, player_pointer->m_position.y) || \
                IS_CRASH_SCENE(player_pointer->m_position.x-1, player_pointer->m_position.y+1) || \
                IS_CRASH_SCENE(player_pointer->m_position.x+1, player_pointer->m_position.y+1)
                )
        {
               iscrash = true ;
        }
        break;
    case PLAYER_DOWN:
        if(
        IS_CRASH_SCENE(player_pointer->m_position.x, player_pointer->m_position.y) ||\
        IS_CRASH_SCENE(player_pointer->m_position.x, player_pointer->m_position.y+1) || \
        IS_CRASH_SCENE(player_pointer->m_position.x-1, player_pointer->m_position.y) || \
        IS_CRASH_SCENE(player_pointer->m_position.x+1, player_pointer->m_position.y) || \
        IS_CRASH_SCENE(player_pointer->m_position.x-1, player_pointer->m_position.y-1) || \
        IS_CRASH_SCENE(player_pointer->m_position.x+1, player_pointer->m_position.y-1)
                )
        {
            iscrash = true ;
        }
        break ;
    case PLAYER_LEFT:
        if(
        IS_CRASH_SCENE(player_pointer->m_position.x, player_pointer->m_position.y) ||\
        IS_CRASH_SCENE(player_pointer->m_position.x-1, player_pointer->m_position.y) ||\
        IS_CRASH_SCENE(player_pointer->m_position.x, player_pointer->m_position.y-1) ||\
        IS_CRASH_SCENE(player_pointer->m_position.x, player_pointer->m_position.y+1) ||\
        IS_CRASH_SCENE(player_pointer->m_position.x+1, player_pointer->m_position.y-1) ||\
        IS_CRASH_SCENE(player_pointer->m_position.x+1, player_pointer->m_position.y+1)
                )
        {
            iscrash = true ;
        }
        break ;
    case PLAYER_RIGHT:
        if(
        IS_CRASH_SCENE(player_pointer->m_position.x, player_pointer->m_position.y) ||\
        IS_CRASH_SCENE(player_pointer->m_position.x+1, player_pointer->m_position.y) ||\
        IS_CRASH_SCENE(player_pointer->m_position.x, player_pointer->m_position.y-1) ||\
        IS_CRASH_SCENE(player_pointer->m_position.x, player_pointer->m_position.y+1) ||\
        IS_CRASH_SCENE(player_pointer->m_position.x-1, player_pointer->m_position.y-1) ||\
        IS_CRASH_SCENE(player_pointer->m_position.x-1, player_pointer->m_position.y+1)
                )
        {
            iscrash = true ;
        }
        break ;
    }

    return iscrash ;
}
/**
 * @brief _player_move_check 检查坦克是否可以移动
 * @param player_pointer
 * @return
 */
static inline bool _player_move_check(player *player_pointer, unsigned int direction)
{
    bool result ;

    result = false ;
    switch (direction)
    {
    case PLAYER_UP:
        player_pointer->m_position.y -= 1;
        if(!_player_iscrash_object(player_pointer) && !_player_iscrash_sence(player_pointer))
        {
            result = true ;
        }
        player_pointer->m_position.y += 1;
        break ;
    case PLAYER_DOWN:
        player_pointer->m_position.y += 1;
        if(!_player_iscrash_object(player_pointer) && !_player_iscrash_sence(player_pointer))
        {
            result = true ;
        }
        player_pointer->m_position.y -= 1;
        break ;
    case PLAYER_LEFT:
        player_pointer->m_position.x -= 1;
        if(!_player_iscrash_object(player_pointer) && !_player_iscrash_sence(player_pointer))
        {
            result = true ;
        }
        player_pointer->m_position.x += 1;
        break ;
    case PLAYER_RIGHT:
        player_pointer->m_position.x += 1;
        if(!_player_iscrash_object(player_pointer) && !_player_iscrash_sence(player_pointer))
        {
            result = true ;
        }
        player_pointer->m_position.x -= 1;
        break ;
    }

    return  result ;
}
/**
 * @brief _player_turn_check 检查坦克是否可以转头
 * @param player_pointer
 * @param direction
 * @return
 */
static inline bool _player_turn_check(player *player_pointer, unsigned int direction)
{
    bool result;

    result = false ;
    //转头
    direction =  direction ^  player_pointer->m_direction  ;
    player_pointer->m_direction = direction ^ player_pointer->m_direction ;
    direction = direction ^ player_pointer->m_direction ;
    if(!_player_iscrash_object(player_pointer) && !_player_iscrash_sence(player_pointer))
    {
        result = true ;
    }
    //回头
    direction =  direction ^  player_pointer->m_direction  ;
    player_pointer->m_direction = direction ^ player_pointer->m_direction ;
    direction = direction ^ player_pointer->m_direction ;

    return result ;
}

bool player_move_isok()
{
    bool result ;
    clock_t current_clock ;
    static clock_t move_last_clock = 0 ;

    result = false ;
    current_clock = clock() ;
    if(current_clock - move_last_clock >= p1.m_move_speed)
    {
        result = true ;
        move_last_clock = current_clock ;
    }

    return result ;
}

bool player_fire_isok()
{
    bool result ;
    clock_t current_clock ;
    static clock_t fire_last_clock = 0 ;

    result = false ;
    current_clock = clock() ;
    if(current_clock - fire_last_clock >= p1.m_fire_speed)
    {
        result = true ;
        fire_last_clock = current_clock ;
    }

    return result ;
}

void _player_trun(player *player_pointer, unsigned int direction)
{
    _player_clear(player_pointer) ;
    _take_player(player_pointer) ;
    if(_player_turn_check(player_pointer, direction)) //无法转向则倒车
    {
        player_pointer->m_direction = direction ;
    }
    else
    {
        switch (player_pointer->m_direction)
        {
        case PLAYER_UP:
            if(_player_move_check(player_pointer, PLAYER_DOWN))
            {
                player_pointer->m_position.y += 1;
            }
            break;
        case PLAYER_DOWN:
            if(_player_move_check(player_pointer, PLAYER_UP))
            {
                player_pointer->m_position.y -= 1;
            }
            break ;
        case PLAYER_LEFT:
            if(_player_move_check(player_pointer, PLAYER_RIGHT))
            {
                player_pointer->m_position.x += 1;
            }
            break ;
        case PLAYER_RIGHT:
            if(_player_move_check(player_pointer, PLAYER_LEFT))
            {
                player_pointer->m_position.x -= 1;
            }
            break ;
        }
    }
    _put_palyer(player_pointer) ;
    _player_draw(player_pointer) ;
}
void _player_move(player *player_pointer, unsigned int direction)
{
    if(_player_move_check(player_pointer, direction))
    {
        _player_clear(player_pointer) ;
        _take_player(player_pointer) ;
        switch(direction)
        {
        case PLAYER_UP:
            player_pointer->m_position.y -= 1;
            break;
        case PLAYER_DOWN:
            player_pointer->m_position.y += 1;
            break ;
        case PLAYER_LEFT:
            player_pointer->m_position.x -= 1;
            break ;
        case PLAYER_RIGHT:
            player_pointer->m_position.x += 1;
            break ;
        }
        _put_palyer(player_pointer) ;
        _player_draw(player_pointer) ;
    }
}

void player_move(unsigned int direction)
{
    if(direction == p1.m_direction)
    {
        _player_move(&p1, direction) ;
    }else
    {
        _player_trun(&p1,direction) ;
    }

}


void player_fire()
{
    switch (p1.m_direction) {
    case PLAYER_UP:
        bullet_list_add(p1.m_position.x, p1.m_position.y - 2, p1.m_bullet_sign,  0x16, BULLET_UP, BULLET_DEFAULT_SPEED, NULL) ;
        break ;
    case PLAYER_DOWN:
        bullet_list_add(p1.m_position.x, p1.m_position.y + 2, p1.m_bullet_sign,  0x16, BULLET_DOWN, BULLET_DEFAULT_SPEED, NULL) ;
        break ;
    case PLAYER_LEFT:
        bullet_list_add(p1.m_position.x-2, p1.m_position.y, p1.m_bullet_sign,  0x16, BULLET_LEFT, BULLET_DEFAULT_SPEED, NULL) ;
        break ;
    case PLAYER_RIGHT:
        bullet_list_add(p1.m_position.x+2, p1.m_position.y, p1.m_bullet_sign,  0x16, BULLET_RIGHT, BULLET_DEFAULT_SPEED, NULL) ;
        break ;
    }
}

void player_bomb()
{
    bullet_list_add(p1.m_position.x+2,p1.m_position.y-1,\
                    p1.m_bullet_sign, 0x4, BULLET_RIGHT|BULLET_UP, BULLET_DEFAULT_SPEED, NULL) ;
    bullet_list_add(p1.m_position.x+2,p1.m_position.y,\
                    p1.m_bullet_sign, 0x4, BULLET_RIGHT, BULLET_DEFAULT_SPEED, NULL) ;
    bullet_list_add(p1.m_position.x+2,p1.m_position.y+1,\
                    p1.m_bullet_sign, 0x4, BULLET_RIGHT|BULLET_DOWN, BULLET_DEFAULT_SPEED, NULL) ;

    bullet_list_add(p1.m_position.x-2,p1.m_position.y-1,\
                    p1.m_bullet_sign, 0x4, BULLET_LEFT|BULLET_UP, BULLET_DEFAULT_SPEED, NULL) ;
    bullet_list_add(p1.m_position.x-2,p1.m_position.y,\
                    p1.m_bullet_sign, 0x4, BULLET_LEFT, BULLET_DEFAULT_SPEED, NULL) ;
    bullet_list_add(p1.m_position.x-2,p1.m_position.y+1,\
                    p1.m_bullet_sign, 0x4, BULLET_LEFT|BULLET_DOWN, BULLET_DEFAULT_SPEED, NULL) ;

    bullet_list_add(p1.m_position.x-1,p1.m_position.y-2,\
                    p1.m_bullet_sign, 0x4, BULLET_UP|BULLET_LEFT, BULLET_DEFAULT_SPEED, NULL) ;
    bullet_list_add(p1.m_position.x,p1.m_position.y-2,\
                    p1.m_bullet_sign, 0x4, BULLET_UP, BULLET_DEFAULT_SPEED, NULL) ;
    bullet_list_add(p1.m_position.x+1,p1.m_position.y-2,\
                    p1.m_bullet_sign, 0x4, BULLET_UP|BULLET_RIGHT, BULLET_DEFAULT_SPEED, NULL) ;

    bullet_list_add(p1.m_position.x-1,p1.m_position.y+2,\
                    p1.m_bullet_sign, 0x4, BULLET_DOWN|BULLET_LEFT, BULLET_DEFAULT_SPEED, NULL) ;
    bullet_list_add(p1.m_position.x,p1.m_position.y+2,\
                    p1.m_bullet_sign, 0x4, BULLET_DOWN, BULLET_DEFAULT_SPEED, NULL) ;
    bullet_list_add(p1.m_position.x+1,p1.m_position.y+2,\
                    p1.m_bullet_sign, 0x4, BULLET_DOWN|BULLET_RIGHT, BULLET_DEFAULT_SPEED, NULL) ;

}

void player_position(short *x_pointer, short *y_pointer)
{
    *x_pointer = p1.m_position.x ;
    *y_pointer = p1.m_position.y ;
}

bool player_isover()
{
    return p1.m_blood == 0 ;
}

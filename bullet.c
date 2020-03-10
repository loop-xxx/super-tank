#include <malloc.h>
#include "bullet.h"
#include "link.h"
#include "map.h"
#include "player.h"
#include "boss.h"


typedef struct _bullet{
    unsigned int m_life ;
    unsigned int m_direction ;
    clock_t m_last_clock ;
    clock_t m_speed;

    struct{
        short x;
        short y ;
    }m_position ;
    void (*m_effect)(void *) ;
    link_node m_link ;
    unsigned char m_sign ;
    bool m_is_vaild ;
}bullet ;

static link_node bullet_list_head ;

void bullet_list_init()
{
    INIT_LINK_HEAD(&bullet_list_head) ;
}

static inline bool _bullet_check(bullet *bullet_pointer)
{
    bool result ;
    link_node *node_pointer ;
    bullet *b_pointer;

    result = true ;
    if(IS_HIT_BULLET(bullet_pointer->m_position.x, bullet_pointer->m_position.y))
    {
        result = false ;
        node_pointer = &bullet_list_head ;
        while((node_pointer = node_pointer->next) == &bullet_list_head) //单纯的遍历
        {
            b_pointer = ADDR_LINK2DATA(node_pointer, bullet, m_link) ;
            //检测撞到的子弹是否已经失效
            if( b_pointer != bullet_pointer && b_pointer->m_is_vaild)
            {
                if(b_pointer->m_position.x == bullet_pointer->m_position.x && b_pointer->m_position.y == bullet_pointer->m_position.y)
                {
                    b_pointer->m_is_vaild = false ;
                }
            }
        }
    }
    else if(IS_HIT_OBJECT(bullet_pointer->m_position.x, bullet_pointer->m_position.y))
    {
        result = false ;
        if(!OBJECT_ISFRIEND(bullet_pointer->m_position.x, bullet_pointer->m_position.y, bullet_pointer->m_sign))
        {
            if(OBJECT_SIGN(bullet_pointer->m_position.x, bullet_pointer->m_position.y) == '\x1') //击中player
            {
                player_hp_1() ;
            }
            else if(OBJECT_SIGN(bullet_pointer->m_position.x, bullet_pointer->m_position.y) == '\x4') //击中boss
            {
                boss_hp_1() ;
            }else //击中小怪
            {
                boss_tank_hp_1(OBJECT_SIGN(bullet_pointer->m_position.x, bullet_pointer->m_position.y)) ;
            }
        }

    }
    else if(IS_HIT_SCENE(bullet_pointer->m_position.x, bullet_pointer->m_position.y))
    {
        result = false ;
    }

    return result ;
}


void bullet_list_add(short x, short y, unsigned char sign,\
                     unsigned int life, unsigned int direction, clock_t speed, void(*effect)(void*))
{
    bullet *bullet_pointer = malloc(sizeof(bullet)) ;
    bullet_pointer->m_life = life ;
    bullet_pointer->m_direction = direction ;
    bullet_pointer->m_sign = sign ;
    bullet_pointer->m_speed = speed ;
    bullet_pointer->m_last_clock = 0x0;
    bullet_pointer->m_position.x = x ;
    bullet_pointer->m_position.y = y ;
    bullet_pointer->m_is_vaild = true ;
    bullet_pointer->m_effect = effect ;
    if(_bullet_check(bullet_pointer))
    {
        PUT_BULLET(bullet_pointer->m_position.x, bullet_pointer->m_position.y, bullet_pointer->m_sign) ;
        write_char(bullet_pointer->m_position.x, bullet_pointer->m_position.y, bullet_pic[0], F_H_WHITE) ;
        link_add(&bullet_list_head, &bullet_pointer->m_link) ;
    }
    else
    {
        free(bullet_pointer) ;
    }
}

void bullet_list_move()
{
    clock_t current_clock = 0 ;

    bullet * bullet_pointer ;
    link_node *node_pointer = bullet_list_head.next ;

    current_clock = clock() ;
    while(node_pointer != &bullet_list_head){
        bullet_pointer = ADDR_LINK2DATA(node_pointer, bullet, m_link) ;
        node_pointer = node_pointer->next ;

        if(current_clock - bullet_pointer->m_last_clock >= bullet_pointer->m_speed)
        {

            bullet_pointer->m_last_clock = current_clock ;

            bullet_pointer->m_life -= 0x1 ;
            if(bullet_pointer->m_effect)
                (*bullet_pointer->m_effect)(bullet_pointer) ;


            if(!IS_HIT_OBJECT(bullet_pointer->m_position.x, bullet_pointer->m_position.y))
            {
                CLEAR_BULLET(bullet_pointer->m_position.x, bullet_pointer->m_position.y) ;
            }
            TAKE_BULLET(bullet_pointer->m_position.x, bullet_pointer->m_position.y) ;

            if(bullet_pointer->m_is_vaild && bullet_pointer->m_life != 0)
            {

                if(bullet_pointer->m_direction & BULLET_UP)
                {
                    bullet_pointer->m_position.y -= 1 ;
                }
                if(bullet_pointer->m_direction & BULLET_DOWN)
                {
                    bullet_pointer->m_position.y += 1;
                }
                if(bullet_pointer->m_direction & BULLET_LEFT)
                {
                    bullet_pointer->m_position.x -= 1;
                }
                if(bullet_pointer->m_direction & BULLET_RIGHT)
                {
                    bullet_pointer->m_position.x += 1;
                }

                if(_bullet_check(bullet_pointer))
                {
                    PUT_BULLET(bullet_pointer->m_position.x, bullet_pointer->m_position.y, bullet_pointer->m_sign) ;
                    write_char(bullet_pointer->m_position.x, bullet_pointer->m_position.y, bullet_pic[0], F_H_WHITE) ;
                }else { //有撞击则摧毁
                    _link_remove(&bullet_pointer->m_link) ;
                    free(bullet_pointer) ;
                }
            }else { //已经被摧毁或生命周期已到的子弹
                _link_remove(&bullet_pointer->m_link) ;
                free(bullet_pointer) ;
            }
        }
    }
}

void bullet_laser_effect(void *pointer)
{
    bullet *bullet_pointer;

    bullet_pointer= pointer ;
    switch (bullet_pointer->m_direction)
    {
    case BULLET_UP:
    case BULLET_DOWN:
        bullet_list_add(bullet_pointer->m_position.x - 1 , bullet_pointer->m_position.y, bullet_pointer->m_sign,\
                        0x2, BULLET_LEFT, BULLET_DEFAULT_SPEED, NULL ) ;
        bullet_list_add(bullet_pointer->m_position.x + 1 , bullet_pointer->m_position.y, bullet_pointer->m_sign,\
                        0x2, BULLET_RIGHT, BULLET_DEFAULT_SPEED, NULL ) ;
        break ;
    case BULLET_LEFT:
    case BULLET_RIGHT:
        bullet_list_add(bullet_pointer->m_position.x , bullet_pointer->m_position.y - 1, bullet_pointer->m_sign,\
                        0x2, BULLET_UP, BULLET_DEFAULT_SPEED, NULL ) ;
        bullet_list_add(bullet_pointer->m_position.x , bullet_pointer->m_position.y + 1, bullet_pointer->m_sign,\
                        0x2, BULLET_DOWN, BULLET_DEFAULT_SPEED, NULL ) ;
        break ;
    }
}

void bullet_mid_laser_effect(void *pointer)
{
    bullet *bullet_pointer;

    bullet_pointer= pointer ;
    switch (bullet_pointer->m_direction)
    {
    case BULLET_UP:
    case BULLET_DOWN:
        bullet_list_add(bullet_pointer->m_position.x - 1 , bullet_pointer->m_position.y, bullet_pointer->m_sign,\
                        0x6, BULLET_LEFT, 0x10, NULL ) ;
        bullet_list_add(bullet_pointer->m_position.x + 1 , bullet_pointer->m_position.y, bullet_pointer->m_sign,\
                        0x6, BULLET_RIGHT, 0x10, NULL ) ;
        break ;
    case BULLET_LEFT:
    case BULLET_RIGHT:
        bullet_list_add(bullet_pointer->m_position.x , bullet_pointer->m_position.y - 1, bullet_pointer->m_sign,\
                        0x6, BULLET_UP, 0x10, NULL ) ;
        bullet_list_add(bullet_pointer->m_position.x , bullet_pointer->m_position.y + 1, bullet_pointer->m_sign,\
                        0x6, BULLET_DOWN, 0x10, NULL ) ;
        break ;
    }
}

void bullet_bomb_effect(void *pointer)
{
    bullet *bullet_pointer;

    bullet_pointer= pointer ;
    if(!bullet_pointer->m_life)
    {
        bullet_list_add(bullet_pointer->m_position.x - 1 , bullet_pointer->m_position.y, bullet_pointer->m_sign,\
                        0x6, BULLET_LEFT, BULLET_DEFAULT_SPEED, NULL ) ;
        bullet_list_add(bullet_pointer->m_position.x + 1 , bullet_pointer->m_position.y, bullet_pointer->m_sign,\
                        0x6, BULLET_RIGHT, BULLET_DEFAULT_SPEED, NULL ) ;
        bullet_list_add(bullet_pointer->m_position.x , bullet_pointer->m_position.y - 1, bullet_pointer->m_sign,\
                        0x6, BULLET_UP, BULLET_DEFAULT_SPEED, NULL ) ;
        bullet_list_add(bullet_pointer->m_position.x , bullet_pointer->m_position.y + 1, bullet_pointer->m_sign,\
                        0x6, BULLET_DOWN, BULLET_DEFAULT_SPEED, NULL ) ;
        bullet_list_add(bullet_pointer->m_position.x-1 , bullet_pointer->m_position.y - 1, bullet_pointer->m_sign,\
                        0x6, BULLET_LEFT|BULLET_UP, BULLET_DEFAULT_SPEED, NULL ) ;
        bullet_list_add(bullet_pointer->m_position.x+1 , bullet_pointer->m_position.y - 1, bullet_pointer->m_sign,\
                        0x6, BULLET_RIGHT|BULLET_UP, BULLET_DEFAULT_SPEED, NULL ) ;
        bullet_list_add(bullet_pointer->m_position.x -1 , bullet_pointer->m_position.y + 1, bullet_pointer->m_sign,\
                        0x6, BULLET_LEFT|BULLET_DOWN, BULLET_DEFAULT_SPEED, NULL ) ;
        bullet_list_add(bullet_pointer->m_position.x + 1 , bullet_pointer->m_position.y + 1, bullet_pointer->m_sign,\
                        0x6, BULLET_RIGHT|BULLET_DOWN, BULLET_DEFAULT_SPEED, NULL ) ;
    }
}

#include <stdio.h>
#include <windows.h>
#include "player.h"
#include "boss.h"
#include "bullet.h"

#define PLAYER_BLOOD 0x9
#define PLAYER_MOVE_SPEED 0x20
#define PLAYER_FIRE_SPEED 0x100

#define BOSS_BLOOD 0x60
#define BOSS_MOVE_SPEED 0x40
#define BOSS_SKILL_SPEED 0x800
#define BOSS_TANK_MOVE_SPEED 0xd0
#define BOSS_TANK_INIT_OFFSET 0x4
#define BOSS_MAX_BLOOD 0x9f

#define KEY_DOWN(key) (GetAsyncKeyState(key)&0x8000  ?1:0)

int engin_init()
{
    int retcode ;

    retcode = -1;
    if(0 == init_console())
    {
        retcode = 0 ;
        map_init(NULL) ;
        map_darw() ;
        player_init(PLAYER_BLOOD, PLAYER_MOVE_SPEED, PLAYER_FIRE_SPEED) ;
        player_draw() ;
        boss_init(BOSS_MAX_BLOOD, BOSS_TANK_INIT_OFFSET,BOSS_MOVE_SPEED,BOSS_SKILL_SPEED, BOSS_TANK_MOVE_SPEED) ;
        boss_draw();
        bullet_list_init() ;
    }

    return  retcode ;
}

void engin_run()
{
    short x, y ;
    while(!player_isover() && !boss_isover())
    {
        if (KEY_DOWN(VK_UP))    {
            if(player_move_isok())
            {
                player_move( PLAYER_UP);
            }

        }
        if (KEY_DOWN(VK_DOWN))  {
            if(player_move_isok())
            {
                player_move( PLAYER_DOWN);
            }
        }
        if (KEY_DOWN(VK_LEFT))  {
            if(player_move_isok())
            {
                player_move( PLAYER_LEFT);
            }
        }
        if (KEY_DOWN(VK_RIGHT))
        {
            if(player_move_isok())
            {
                player_move( PLAYER_RIGHT);
            }
        }
        if (KEY_DOWN('X'))
        {
            if(player_fire_isok())
            {
                player_fire() ;
            }
        }
        if (KEY_DOWN('C'))
        {
            if(player_fire_isok())
            {
                player_bomb() ;
            }
        }

        if(boss_move_isok())
        {
            player_position(&x, &y) ;
            boss_move(x, y) ;
        }
        if(boss_skill_isok())
        {
            boss_skill() ;
        }
        if(boss_tank_move_isok())
        {
            player_position(&x, &y) ;
            boss_tank_move(x, y) ;
        }


        bullet_list_move() ;
    }
    if(boss_isover())
    {
        write_char(0, 0, "", F_H_WHITE) ;
        system("cls") ;
        write_char(MAP_WIDTH/2, MAP_HEIGHT/2, "win!\n", F_H_WHITE) ;
    }
    if(player_isover())
    {
        system("cls") ;
        write_char(0, 0, "", F_H_WHITE) ;
        write_char(MAP_WIDTH/2, MAP_HEIGHT/2, "lose!\n", F_H_WHITE) ;
    }
}

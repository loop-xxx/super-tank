#ifndef MAP_H
#define MAP_H
#include "graphics.h"

#define MAP_HEIGHT 40
#define MAP_WIDTH 40

//对象地图
extern unsigned char g_map_object[MAP_HEIGHT][MAP_WIDTH] ;
//环境地图
extern unsigned char g_map_scene[MAP_HEIGHT][MAP_WIDTH] ;
//子弹地图
extern unsigned char g_map_bullet[MAP_HEIGHT][MAP_WIDTH] ;

//是否有撞其他子弹
#define IS_HIT_BULLET(x, y) (g_map_bullet[(y)][(x)])
//是否有撞其他对象
#define IS_HIT_OBJECT(x,y) (g_map_object[(y)][(x)])
//是否是友方
#define OBJECT_ISFRIEND(x,y, sign) (g_map_object[(y)][(x)] & sign)
//是否有撞环境
#define IS_HIT_SCENE(x,y)(g_map_scene[(y)][(x)] > 1)
//获取对象sign
#define OBJECT_SIGN(x, y) (g_map_object[(y)][(x)])

//放置子弹
#define PUT_BULLET(x,y, sign) (g_map_bullet[(y)][(x)] = (sign))
//拿起子弹
#define TAKE_BULLET(x,y) (g_map_bullet[(y)][(x)] = 0)
//清楚控制台上的子弹
#define CLEAR_BULLET(x,y) write_char((x), (y), wall_pic[g_map_scene[(y)][(x)]], F_H_WHITE)



//判断环境地图该坐标是否已有物体
#define IS_CRASH_SCENE(x, y) (g_map_scene[(y)][(x)])
//判断物理地图该左边是否已有物体
#define IS_CRASH_OBJECT(x, y, sign) ((g_map_object[(y)][(x)]) && g_map_object[(y)][(x)] != (sign))

//在物理地图的对应坐标放置对象
#define PUT_OBJECT(x, y, sign) (g_map_object[(y)][(x)] = (sign))
//将对象从物理地图上拿起
#define TAKE_OBJECT(x, y) (g_map_object[(y)][(x)] = 0)

//清楚cosole上显示的对象
#define CLEAR_OBJECT(x, y) write_char((x), (y), wall_pic[g_map_scene[(y)][(x)]], F_H_WHITE)

extern void map_init(void *data_pointer);
extern void map_darw(void) ;
#endif // MAP_H

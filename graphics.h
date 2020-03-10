#ifndef GRAPHICS_H
#define GRAPHICS_H


// 前景 颜色
#define F_H_BLUE   0x0001|0x0008        // 亮蓝
#define F_H_YELLOW 0x0002|0x0004|0x0008 // 亮黄
#define F_H_WHITE  0x0004|0x0002|0x0001|0x0008
//背景　颜色
#define B_H_GREEN  0x0020|0x0080        // 亮绿

#define CODE_BLANK '\x0'
#define CODE_RIVER '\x1'
#define CODE_WALL '\x2'

extern char const * wall_pic[] ;
extern char const * tank_pic[] ;
extern char const * num_pic[] ;
extern char const * bullet_pic[] ;
extern int init_console(void) ;
extern void write_char(short col, short row,  char const* pic, unsigned short color) ;


#endif // GRAPHICS_H

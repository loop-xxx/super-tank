#include <stdio.h>
#include "stdbool.h"
#include <windows.h>


static HANDLE s_stdout_handle ;
//墙图片库
char const * wall_pic[] = {"  ","≈", "〓"};
//tank图片库
char const * tank_pic[] = {"■", "◇"};// 身体
//数字图片库
char const * num_pic[] = {"◎","①", "②", "③", "④", "⑤", "⑥", "⑦", "⑧", "⑨", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎", "◎"};
//子弹图片库
char const * bullet_pic[] = {"●", "○"};

#define WINDOWS_WIDTH 66*2
#define WINDOWS_HEIGHT  42

/**
 * @brief init_console
 * @return -1 failed
 * @return 0 succcess
 */
int init_console()
{
    int retcode;
    s_stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置console大小
    retcode = -1 ;
    SMALL_RECT window_size = { 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT };
    if(SetConsoleWindowInfo(s_stdout_handle, true, &window_size))
    {
        retcode= 0 ;
    }
    return retcode ;
}

/**
 * @brief write_char 在控制台固定坐标画一个宽字符
 * @param col
 * @param row
 * @param pic
 * @param color
 */
void write_char(short col, short row, char const* pic, unsigned short color)
{


    // 设置光标属性
    CONSOLE_CURSOR_INFO cci;                    //控制台光标信息结构类型
    cci.dwSize = 1;                             //光标大小
    cci.bVisible = FALSE;                       //是否显示光标
    COORD loc;                                  //坐标结构类型
    loc.X = col * 2;                            //宽度必须*2
    loc.Y = row;                                //高度
    SetConsoleCursorInfo(s_stdout_handle, &cci);      //设置指定控制台屏幕缓冲区光标大小和可见性
    SetConsoleCursorPosition(s_stdout_handle, loc);   //设置指定控制台屏幕缓冲区中光标的位置
    SetConsoleTextAttribute(s_stdout_handle, color);   //设置颜色
    //函数对函数调用后输出的文本产生影响
    fputs(pic, stdout);                            //打印特殊字符占两个字节
}

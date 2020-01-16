#include <gb/gb.h>
#include <stdio.h>
#include "BoyAndGirl.h"
#include "RewardCard.h"
#include "Background.h"
#include "Ground.h"

#include "GameRole.h"

//开始界面
#include "ourworld_data.c"
#include "ourworld_map.c"

struct GameRole role1;
struct GameRole role2;
//设置展示日期
UINT16 year = 1982;
UINT8 month = 12;
UINT8 count = 0;

UINT8 screen_position_x = 0;

/**
 * 日历计算方法，并进行展示.
 */
void calendardisplay(){
        //处理日期
        count++;
        if(count>=8){
            count=0;
            month++;
            if(month>=13){
                year++;
                month =1;
            }
            rcmap[27]=month/10;
            rcmap[28]=month%10==0?0x0a:month%10;
            rcmap[25]=year%10==0?0x0a:year%10;
            rcmap[24] = year/10%10==0?0x0a:year/10%10;
            rcmap[23] = year/100%10==0?0x0a:year/100%10;
            rcmap[22] = year/1000%10==0?0x0a:year/1000%10;
            set_win_tiles(0,0,20,3,rcmap);
        }
}



/**
 * 初始化role1，
 */
void initRole1(UINT8 x, UINT8 y) 
{
    role1.x = 0;
    role1.y = 0;
    role1.width = 16;
    role1.height = 16;
    role1.spritrun[0] = 4;
    role1.spritrun[1] = 8;
    role1.spite_run_status = 0;
    set_sprite_tile(0, role1.spritrun[role1.spite_run_status]);
    role1.spritids[0] = 0;
    set_sprite_tile(1, role1.spritrun[role1.spite_run_status]+2);
    role1.spritids[1] = 1;
    // set_sprite_prop(0,S_FLIPX);
    // set_sprite_prop(1,S_FLIPX);
    role1.direction = 4;
    movegamecharacter(&role1,x,y);
    role1.x = x;
    role1.y = y;
}

/**
 * 初始化角色2
 */
void initRole2(UINT8 x,UINT8 y)
{
    role2.x = 0;
    role2.y = 0;
    role2.width = 16;
    role2.height = 16;
    role2.spritrun[0] = 12;
    role2.spritrun[1] = 16;
    role2.spite_run_status = 0;
    set_sprite_tile(0, role2.spritrun[role2.spite_run_status]);
    role1.spritids[0] = 0;
    set_sprite_tile(1, role2.spritrun[role2.spite_run_status]+2);
    role1.spritids[1] = 1;
    role1.direction = 4;
    movegamecharacter(&role2,x,y);
    role1.x = x;
    role1.y = y;
}

/**
 * 初始化数据
 */
void initscreen()
{
    //设置瓦块图案
    set_sprite_data(0, 16, BoyGirl);
    //初始化精灵
    initRole1(28,112);

    //设置背景瓦块
    set_bkg_data(0,23,BGTile);
    set_bkg_tiles(0,0,32,18,Ground);

    set_win_tiles(0,0,20,3,rcmap);
    move_win(7,120);
}

/**
 * 休眠指定次数
 */
void performantdelay(UINT8 numloops)
{
    UINT8 i=0;
    for (   ; i < numloops; i++)
    {
        wait_vbl_done();
    }
    
}

/**
 * @brief 开始界面
 * 
 */
void start_inteface()
{
    UINT8 i=18;
    set_bkg_data(0,226,ourworld_data);
    set_bkg_tiles(0,0,20,18,ourworld_map);
    SHOW_BKG;
    // while (i>0)
    // {
    //     scroll_bkg(0,-2);
    //     i-=2;
    //     performantdelay(5);
    // }
    
    waitpad(J_START);
    HIDE_BKG;
}
void main()
{

    SPRITES_8x16;
    start_inteface();
    initscreen();

    SHOW_SPRITES;
    SHOW_WIN;
    SHOW_BKG;
    DISPLAY_ON;
    
    while(1){
        
        //处理1985年2号主角出现的平台问题
        if(year>=1983 && Ground[0x100+(screen_position_x-8)/8]==0x00)
        {
            Ground[0x100+(screen_position_x-8)/8]=screen_position_x/8%4+0x13;
            set_bkg_tiles(0,0,32,18,Ground);
        }
        //延迟1000毫秒
        performantdelay(5);
        //根据方向键来移动精灵
        switch (joypad())
        {
            case J_LEFT:  
                if(role1.x>16){
                    movegamecharacter(&role1,role1.x-2,role1.y);
                    role1.x -= 2 ;
                }
                break;
            case J_RIGHT:
                if(role1.x >= 80) {
                    movegamecharacter(&role1,role1.x,role1.y);
                    scroll_bkg(1,0);
                    screen_position_x++;
                    // screen_position_x = screen_position_x%32;
                }
                else {
                    movegamecharacter(&role1,role1.x+2,role1.y);
                    role1.x +=2;
                }
                calendardisplay();
                break;

            default:

                break;
        }
        
    }
}

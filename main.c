#include <gb/gb.h>
#include <stdio.h>
#include "BoyAndGirl.h"

void main()
{

    UINT8 currentspriteindex = 0;
    //设置精灵的方向
    INT8 spritediretion=1;
    SPRITES_8x16;
    //设置图块图案
    set_sprite_data(0, 8, BoyGirl);
    //在子画面上0上，显示 精灵索引
    set_sprite_tile(0, currentspriteindex);
    move_sprite(0, 28, 108);
    set_sprite_tile(1, currentspriteindex+2);
    move_sprite(1, 28-8, 108);
    set_sprite_prop(0,S_FLIPX);
    set_sprite_prop(1,S_FLIPX);
    SHOW_SPRITES;

    while(1){
        //延迟1000毫秒
        delay(100);
        //根据方向键来移动精灵
        switch (joypad())
        {

            case J_LEFT:
                if(spritediretion==1){
                    scroll_sprite(0,-8,0);
                    scroll_sprite(1,8,0);
                    spritediretion = 2;
                }
                scroll_sprite(0,-1,0);
                scroll_sprite(1,-1,0);
                currentspriteindex = currentspriteindex == 0?4:0;
                set_sprite_tile(0, currentspriteindex);
                set_sprite_tile(1, currentspriteindex+2);
                set_sprite_prop(0,0);
                set_sprite_prop(1,0);
                break;
            case J_RIGHT:
                if(spritediretion==2){
                    scroll_sprite(0,8,0);
                    scroll_sprite(1,-8,0);
                    spritediretion = 1;
                }
                set_sprite_prop(0,S_FLIPX);
                set_sprite_prop(1,S_FLIPX);
                currentspriteindex = currentspriteindex == 0?4:0;
                set_sprite_tile(0, currentspriteindex);
                set_sprite_tile(1, currentspriteindex+2);
                scroll_sprite(0,1,0);
                scroll_sprite(1,1,0);

                break;
            case J_UP:
                scroll_sprite(0, 0,-1);
                break;
            case J_DOWN:
                scroll_sprite(0,0,1);
                break;
            case J_LEFT ^ J_UP:
                scroll_sprite(0,-1,-1);
                break;
            case J_LEFT ^ J_DOWN:
                scroll_sprite(0, -1, 1);
                break;
            case J_RIGHT ^ J_DOWN:
                scroll_sprite(0, 1,1);
                break;
            case J_RIGHT ^ J_UP:
                scroll_sprite(0,1,-1);
                break;
            default:
                currentspriteindex = 0;
                set_sprite_tile(0, currentspriteindex);
                set_sprite_tile(1, currentspriteindex+2);
                break;
        }
        
    }
}

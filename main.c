#include <gb/gb.h>
#include <stdio.h>
#include "SmileSprites.h"

void main()
{
    UINT8 currentspriteindex = 0;

    printf("TEST");
    //设置图块图案
    set_sprite_data(0, 2, Smiler);
    //在子画面上0上，显示 精灵索引
    set_sprite_tile(0, currentspriteindex);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;

    while(1){
        //延迟1000毫秒
        delay(100);
        //根据方向键来移动精灵
        switch (joypad())
        {
            case J_A:
                currentspriteindex = currentspriteindex == 0?1:0;
                set_sprite_tile(0, currentspriteindex);
                break;
            case J_LEFT:
                scroll_sprite(0,-1,0);
                break;
            case J_RIGHT:
                scroll_sprite(0,1,0);
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
                break;
        }
        
    }
}

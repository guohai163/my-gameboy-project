#include <gb/gb.h>
#include <stdio.h>
#include "SmileSprites.c"

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
        if(currentspriteindex == 0){
            currentspriteindex = 1;
        }
        else{
            currentspriteindex =0;
        }
        set_sprite_tile(0, currentspriteindex);
        //延迟1000毫秒
        delay(1000);
        //相对于当前位置移动精灵
        scroll_sprite(0,10,0);
    }
}

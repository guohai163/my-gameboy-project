#include <gb/gb.h>
#include <stdio.h>
#include "BoyAndGirl.h"
#include "RewardCard.h"
#include "Background.h"
#include "Ground.h"

//设置展示日期
UINT16 year = 1982;
UINT8 month = 12;
UINT8 count = 0;
UINT8 roleposition = 28;

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
void interruptLCD(){
    HIDE_WIN;
}
void main()
{

    UINT8 currentspriteindex = 4;
    //设置精灵的方向
    INT8 spritediretion=1;

    // STAT_REG = 0x45;
    // LYC_REG = 0x08;  //  Fire LCD Interupt on the 8th scan line (just first row)
    // disable_interrupts();
    SPRITES_8x16;
    //设置图块图案
    set_sprite_data(0, 16, BoyGirl);
    //在子画面上0上，显示 精灵索引
    set_sprite_tile(0, currentspriteindex);
    move_sprite(0, 28, 112);
    set_sprite_tile(1, currentspriteindex+2);
    move_sprite(1, 28-8, 112);
    set_sprite_prop(0,S_FLIPX);
    set_sprite_prop(1,S_FLIPX);
    SHOW_SPRITES;

    set_bkg_data(0,23,BGTile);
    set_bkg_tiles(0,0,32,18,Ground);

    set_win_tiles(0,0,20,3,rcmap);
    move_win(7,120);
    SHOW_WIN;
    SHOW_BKG;
    DISPLAY_ON;
    
    // add_LCD(interruptLCD);
    // enable_interrupts();
    // set_interrupts(VBL_IFLAG | LCD_IFLAG); 
    while(1){
        
        // SHOW_WIN;
        
        // wait_vbl_done();
        
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

                currentspriteindex = currentspriteindex == 4?8:4;
                set_sprite_tile(0, currentspriteindex);
                set_sprite_tile(1, currentspriteindex+2);
                set_sprite_prop(0,0);
                set_sprite_prop(1,0);
                
                if(roleposition>16){
                    scroll_sprite(0,-2,0);
                    scroll_sprite(1,-2,0);
                    roleposition-=2;
                }
                break;
            case J_RIGHT:
                if(spritediretion==2){
                    scroll_sprite(0,8,0);
                    scroll_sprite(1,-8,0);
                    spritediretion = 1;
                }
                set_sprite_prop(0,S_FLIPX);
                set_sprite_prop(1,S_FLIPX);
                currentspriteindex = currentspriteindex == 4?8:4;
                set_sprite_tile(0, currentspriteindex);
                set_sprite_tile(1, currentspriteindex+2);

                
                if(roleposition>= 80 ){
                    scroll_bkg(1,0);
                }
                else{
                    scroll_sprite(0,2,0);
                    scroll_sprite(1,2,0);
                    roleposition+=2;
                }
                calendardisplay();
                break;
            // case J_UP:
            //     scroll_sprite(0, 0,-1);
            //     break;
            // case J_DOWN:
            //     scroll_sprite(0,0,1);
            //     break;
            // case J_LEFT ^ J_UP:
            //     scroll_sprite(0,-1,-1);
            //     break;
            // case J_LEFT ^ J_DOWN:
            //     scroll_sprite(0, -1, 1);
            //     break;
            // case J_RIGHT ^ J_DOWN:
            //     scroll_sprite(0, 1,1);
            //     break;
            // case J_RIGHT ^ J_UP:
            //     scroll_sprite(0,1,-1);
            //     break;
            default:
                if(currentspriteindex != 4){
                    currentspriteindex = 4;
                    set_sprite_tile(0, currentspriteindex);
                    set_sprite_tile(1, currentspriteindex+2);
                }

                break;
        }
        
    }
}

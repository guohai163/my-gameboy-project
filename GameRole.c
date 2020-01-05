#include "GameRole.h"
/**
 * 移动精灵
 */
void movegamecharacter(struct GameRole* character, UINT8 x, UINT8 y)
{
    character->spite_run_status = character->spite_run_status == 0 ? 1:0;
    set_sprite_tile(character->spritids[0], character->spritrun[character->spite_run_status]);
    set_sprite_tile(character->spritids[1], character->spritrun[character->spite_run_status]+2);
    if(x<character->x && character->direction==2) {
        //向左移动
        set_sprite_prop(character->spritids[0],0x00u);
        set_sprite_prop(character->spritids[1],0x00u);
        character->direction = 4;
    }
    if(x>character->x && character->direction == 4) {
        //向右移动
        set_sprite_prop(character->spritids[0],S_FLIPX);
        set_sprite_prop(character->spritids[1],S_FLIPX);
        character->direction = 2;
    }
    if(character->x!=x || character->y!=y) {
        if(character->direction ==2){
            move_sprite(character->spritids[0], x, y);
            move_sprite(character->spritids[1], x - spritesize, y);
        }
        else if (character->direction == 4)
        {
            move_sprite(character->spritids[0], x-4, y);
            move_sprite(character->spritids[1], x + spritesize-4, y);
        }
    }
}

#include <gb/gb.h>
#include <stdio.h>
/**
 * 游戏内角色的结构体,因为GB的机能限制，最大只支持8x16像素的sprit，
 * 因为我们每个角色使用32x32才能表示，所以一个数组来存储精灵的索引
 */
struct GameRole
{
    //精灵两个下标
	UBYTE spritids[2]; // all characters use 4 sprites
    //精灵运动起来时的动画针索引，0为静止，1为动态
    UBYTE spritrun[2];
    //精灵的运动状态
    UINT8 spite_run_status;
	UINT8 x;
	UINT8 y;
	UINT8 width;
	UINT8 height;
    //精灵的面部朝向
    //1上，2右，3下，4左
    UINT8 direction;
};

UINT8 spritesize = 8;

/**
 * 移动精灵
 */
void movegamecharacter(struct GameRole* character, UINT8 x, UINT8 y);

#include "modules/dungeon_resource07_slot0.h"

void func_80171EFC(void *effect, s32 *position, void *sprite, void *source)
{
    s32 direction;
    s16 *direction_x;

    direction = (*(u16 *)((s8 *)source + 0x2A) >> 9) & 7;
    *((s8 *)effect + 0x9A) = 0x10;
    *((s8 *)effect + 0x9B) = 0;
    *(u8 **)((s8 *)sprite + 0x2C) = ((u8 *)D_80174158);
    func_80047784(sprite,(s16)(((u8 *)D_80174158)[((gameWork.view.viewAngle +
                               *(s16 *)((s8 *)source + 0x2A) + 0x100) >> 9) & 7]),(s16)(0));
    direction_x = dirStepX;
    direction *= 2;
    position[0] -= *(s16 *)((u8 *)direction_x + direction) << 19;
    position[1] -= *(s16 *)((u8 *)dirStepY + direction) << 19;
}

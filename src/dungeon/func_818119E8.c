#include "modules/dungeon_ovl_1831370.h"

s32 dungeonGetAndPositionObjectHandle(void *object)
{
    ovl_1831370_818119E8_Vec3 *initial_pos;
    s32 success = 0;

    if ((*(s32 *)((s8 *)object + 0x70) = func_80048EE4((s8 *)object + 0x74, 4)) != 0) {
        initial_pos = &D_8002E5E8;
        *(s32 *)((s8 *)object + 0x54) = initial_pos->x;
        *(s32 *)((s8 *)object + 0x58) = initial_pos->y;
        *(s32 *)((s8 *)object + 0x5C) = initial_pos->z;
        textureSetTheFieldOffsetHex8InEachEntryPointerArray(*(s32 *)((s8 *)object + 0x70), (s8 *)object + 0x54, 4);
        success = 1;
    }
    return success;
}

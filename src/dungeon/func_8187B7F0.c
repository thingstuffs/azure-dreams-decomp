#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"

extern s16 D_8002694C[5];

/* Conditionally advances the position and decrements a counter, setting flags when it expires. */
void func_80024FF0(void *object, s16 *position)
{
    s16 *object_fields = object;
    s16 counter;

    s16 minimum_height = position[5] + 2;
    u16 query_x = (u16)position[1];
    u16 query_y = (u16)position[3];

    *(s16 *)D_8002694C = 1;
    if (position[5] < (s16)func_800BCB04(query_x, query_y, minimum_height)) {
        ((s32 *)position)[2] += *(s32 *)((u8 *)object + 0xB4);
    }

    counter = (u16)object_fields[8] - 4;
    object_fields[8] = counter;
    if ((counter << 16) <= 0) {
        ((u16 *)object_fields)[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

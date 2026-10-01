#include "common.h"
#include "shared/entity_objects.h"

typedef struct S_800C1F8C_0 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
} S_800C1F8C_0;   /* arg0 in func_800C1F8C */


typedef struct Position {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
} Position;

extern void SD_Call(s32);
extern s32 abs(s32);
extern u8 D_800C1EA4[];


/* Trigger an action and update the object state when either position limit is exceeded. */
void func_800C1F8C(S_800C1F8C_0 *object)
{
    s32 x_offset;
    s32 y_offset;
    s32 x_distance;
    s32 y_distance;

    x_offset = object->unk_04 - D_80083780.x.w.i;
    x_distance = abs(x_offset);
    y_offset = object->unk_06 - D_80083780.y.w.i;
    y_distance = abs(y_offset);
    if (object->unk_0C >= (s16)x_distance && object->unk_0E >= (s16)y_distance) {
        return;
    }
    SD_Call(object->unk_10 | 0x1000);
    object->unk_00 = D_800C1EA4;
}

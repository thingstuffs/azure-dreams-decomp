#include "common.h"

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

extern void func_80053DA8(s32);
extern Position D_80083780;
extern u8 D_800C1EA4[];


/* Trigger an action and update the object state when either position limit is exceeded. */
void func_800C1F8C(S_800C1F8C_0 *object)
{
    s32 y_distance;
    register s32 axis_distance ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 axis_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    axis_distance = object->unk_04;
    axis_offset = D_80083780.x;
    y_distance = D_80083780.y;
    axis_distance -= axis_offset;
    if (axis_distance < 0) {
        axis_distance = -axis_distance;
    }
    axis_distance <<= 16;

    axis_offset = object->unk_06 - y_distance;
    y_distance = axis_offset;
    if (axis_offset < 0) {
        y_distance = -y_distance;
    }

    if (object->unk_0C < (axis_distance >> 16)) {
        goto trigger;
    }
    axis_distance = (s16)y_distance;
    if (object->unk_0E >= axis_distance) {
        return;
    }

trigger:
    func_80053DA8(object->unk_10 | 0x1000);
    object->unk_00 = D_800C1EA4;
}

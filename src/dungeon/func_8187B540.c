#include "common.h"

typedef struct S_8187B540_0 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_8187B540_0;   /* arg2 in func_8187B540 */

typedef struct S_8187B540_1 {
    u8 pad_00[0x10];
    u16 unk_10;
    u8 pad_12[0x8E];
    u16 unk_A0;
} S_8187B540_1;   /* obj in func_8187B540 */



extern s16 D_8002694C;
extern s32 D_800814A0;

void func_8187B540(void *arg0, s32 arg1, void *arg2) {
    u8 *obj = arg0;
    u8 *page = (u8 *)&D_8002694C - 0x694C;
    u16 value;

    ((S_8187B540_0 *)arg2)->unk_1A += ((S_8187B540_1 *)obj)->unk_A0;
    value = ((S_8187B540_1 *)obj)->unk_10 - 0x20;
    *(s16 *)(page + 0x694C) = 1;
    ((S_8187B540_1 *)obj)->unk_10 = value;
    if ((s16)value <= 0) {
        (*(u16 *)((u8 *)obj + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

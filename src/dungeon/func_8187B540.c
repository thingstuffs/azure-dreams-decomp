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

/* Add the object increment to the target and flag completion when its countdown expires. */
void func_8187B540(void *object, s32 unused, void *target) {
    u8 *object_data = object;
    u8 *global_base = (u8 *)&D_8002694C - 0x694C;
    u16 remaining;

    ((S_8187B540_0 *)target)->unk_1A += ((S_8187B540_1 *)object_data)->unk_A0;
    remaining = ((S_8187B540_1 *)object_data)->unk_10 - 0x20;
    *(s16 *)(global_base + 0x694C) = 1;
    ((S_8187B540_1 *)object_data)->unk_10 = remaining;
    if ((s16)remaining <= 0) {
        (*(u16 *)((u8 *)object_data + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

#include "shared/entity_objects.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 D_800D0428[];

/* Copy the global position to the output with an offset on the third component. */
void func_800C5C3C(s32 unused, void *position_out) {
    *(s32 *)position_out = D_80083780.x.v;
    *(s32 *)((u8 *)position_out + 4) = D_80083780.y.v;
    *(s32 *)((u8 *)position_out + 8) = D_80083780.z.v + D_800D0428[0];
}

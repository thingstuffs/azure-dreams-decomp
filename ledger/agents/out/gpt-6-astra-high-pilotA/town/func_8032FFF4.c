#include "common.h"

typedef struct S_8001A7F4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    void * unk_1C;
} S_8001A7F4_0;   /* base in func_8001A7F4 */

typedef struct S_8001A7F4_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001A7F4_1;   /* dst in func_8001A7F4 */

extern s8 D_80016000[];

/* Scale and offset the coordinates stored in the current position object. */
void func_8001A7F4(s32 unused, s32 x, s32 y)
{
    register void *base ASM_REG("$4");
    register void *position ASM_REG("$7");

    (void)unused;
    base = *(void **)D_80016000;
    position = ((S_8001A7F4_0 *)base)->unk_1C;
    ASM_KEEP(position);
    x <<= 6;
    ((S_8001A7F4_1 *)position)->unk_04 = x / 10 + 0x220;
    base = ((S_8001A7F4_0 *)base)->unk_1C;
    ASM_KEEP(base);
    y <<= 6;
    ((S_8001A7F4_0 *)base)->unk_08 = y / 10 + 0x220;
}

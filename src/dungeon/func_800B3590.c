#include "common.h"

typedef struct S_800B8CF0_0_pre {
    u16 unk_00;
} S_800B8CF0_0_pre;   /* the 0x2 bytes before arg0 in func_800B8CF0, addressed as arg0[-1] */

typedef struct S_800B8CF0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800B8CF0_0;   /* arg0 in func_800B8CF0 */

typedef struct S_800B8CF0_1 {
    u8 pad_00[0xC];
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_800B8CF0_1;   /* arg2 in func_800B8CF0 */



extern void func_800B8D5C(void);
extern s32 D_800814A0; /* overlays/dungeon/first_pass_matched/func_800AB5D4.c */

void func_800B8CF0(void *arg0, s32 arg1, void *arg2) {
    s32 temp;

    temp = ((S_800B8CF0_0 *)arg0)->unk_02 - 1;
    ((S_800B8CF0_0 *)arg0)->unk_02 = (u16) temp;
    if (((temp << 16) >> 16) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_800B8CF0_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
        func_800B8D5C();
        return;
    }
    if (temp & 1) {
        s8 val = (s8) ((((temp << 16) >> 16) << 3) | 0x20);
        ((S_800B8CF0_1 *)arg2)->unk_0C.at00.v = val;
        ((S_800B8CF0_1 *)arg2)->unk_0C.at02.v = val;
        ((S_800B8CF0_1 *)arg2)->unk_0C.at01.v = val;
        func_800B8D5C();
        return;
    }
    ((S_800B8CF0_1 *)arg2)->unk_0C.at00u.v = 0x00101010;
}

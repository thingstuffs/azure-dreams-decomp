#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_800C30A4_0_pre {
    u16 unk_00;
} S_800C30A4_0_pre;   /* the 0x2 bytes before arg0 in func_800C30A4, addressed as arg0[-1] */



extern s32 D_800814A0;
extern u8 D_80082660[];

void func_800C30A4(void *arg0) {
    s32 offset;
    u8 *base;

    base = D_80082660;
    offset = ((Rec_func_80094268_arg0 *)arg0)->unk_60 * 8;
    (*(s32 *)((u8 *)(base + offset) + 4)) = 0;
    (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_800C30A4_0_pre *)arg0)[-1].unk_00 | 0x8000);
    D_800814A0 |= 0x8000;
}

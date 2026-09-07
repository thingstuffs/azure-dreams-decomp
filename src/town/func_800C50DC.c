#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800C2864;
extern void *D_800FE4A0;

typedef struct S_800C283C_0 {
    u8 pad_00[0x14];
    s8 unk_14;
    u8 pad_15[0x3B];
    M2C_UNK * unk_50;
} S_800C283C_0;   /* v1 in func_800C283C */

void func_800C283C(s32 arg0) {
    S_800C283C_0 *v1 = D_800FE4A0;
    if (v1 == (void *)arg0) {
        v1->unk_14 = 0;
        v1->unk_50 = &D_800C2864;
    }
}

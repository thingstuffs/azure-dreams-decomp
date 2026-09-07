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


void func_800C1F8C(S_800C1F8C_0 *arg0)
{
    s32 temp_a0;
    register s32 temp_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 temp_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    temp_v0 = arg0->unk_04;
    temp_v1 = D_80083780.x;
    temp_a0 = D_80083780.y;
    temp_v0 -= temp_v1;
    if (temp_v0 < 0) {
        temp_v0 = -temp_v0;
    }
    temp_v0 <<= 16;

    temp_v1 = arg0->unk_06 - temp_a0;
    temp_a0 = temp_v1;
    if (temp_v1 < 0) {
        temp_a0 = -temp_a0;
    }

    if (arg0->unk_0C < (temp_v0 >> 16)) {
        goto trigger;
    }
    temp_v0 = (s16)temp_a0;
    if (arg0->unk_0E >= temp_v0) {
        return;
    }

trigger:
    func_80053DA8(arg0->unk_10 | 0x1000);
    arg0->unk_00 = D_800C1EA4;
}

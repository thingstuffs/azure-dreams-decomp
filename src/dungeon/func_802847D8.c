#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800E2970[];
extern M2C_UNK D_800E2C40[];

typedef struct S_800177D8_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    void * unk_10;
} S_800177D8_0;   /* temp_t0 in func_800177D8 */

typedef struct S_800177D8_1 {
    s8 unk_00;
    s8 unk_01;
    s16 unk_02;
} S_800177D8_1;   /* temp_v0_2 in func_800177D8 */

void func_800177D8(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    register s32 temp_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 temp_v0;
    void *base_2970;
    void *base_2c40;
    S_800177D8_0 *temp_t0;
    S_800177D8_1 *temp_v0_2;

    base_2970 = (void *)D_800E2970;
    temp_t0 = (arg0 * 0x14) + base_2970;
    if (temp_t0->unk_0A != 0) {
        temp_a1 = arg0 << 6;
        base_2c40 = (void *)D_800E2C40;
        do { temp_v0 = temp_t0->unk_0E; } while (0);
        temp_t0->unk_10 = temp_a1 + base_2c40;
        temp_v0_2 = ((s32)(temp_v0 << 0x10) >> 0xE) + temp_a1 + base_2c40;
        temp_t0->unk_0E = (u16)(temp_v0 + 1);
        temp_v0_2->unk_02 = arg3;
        temp_v0_2->unk_00 = arg1;
        temp_v0_2->unk_01 = arg2;
    }
}

/* MECHANISM: Frameless leaf under the true-space name, with named bases hoisting both global address pairs.
   The row offset is guarded in $a1 immediately after definition, before the lhu temporary is born.
   This preserves retail's $a0/$a1 and $v0/$v1 roles while keeping the 29-word schedule exact. */

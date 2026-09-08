#include "common.h"
#include "m2c_compat.h"

extern struct S_8003E2D8 D_80083160;
extern u8 D_80089660[];
extern void *memcpy(void *dst, const void *src, u32 n);

typedef struct S_800BDC98_0 {
    u8 pad_00[0x1DC];
    s8 * unk_1DC;
} S_800BDC98_0;   /* base in func_800BDC98 */

typedef struct S_800BDC98_1 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    s16 unk_1A;
} S_800BDC98_1;   /* temp_t2 in func_800BDC98 */

void func_800BDC98(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    u16 sp[8];
    s32 var_t1;
    register s32 arg3_hold ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 temp_t5;
    s32 var_t7;
    s32 var_a2;
    s32 var_a3;
    s32 temp_v1;
    register s32 zero_test ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 arg1_shift;
    s32 outer_end;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 mode_offset;
    s8 *base;
    s8 *row_src;
    s8 *temp_t2;
    s8 *dst;

    arg3_hold = arg3;
    var_t1 = arg3_hold;
    M2C_MEMCPY_UNALIGNED(sp, D_80089660, 0x10);
    base = (s8 *)&D_80083160;
    temp_t2 = base + 0x1DC;
    dst = ((S_800BDC98_0 *)base)->unk_1DC;
    var_t7 = 1;
    if ((arg2 == 2) || (var_t1 = 3, zero_test = arg3_hold << 0x10, (zero_test == 0))) {
        var_a3 = arg0;
        temp_v1 = var_a3;
        temp_v1 += 2;
        if (var_a3 < temp_v1) {
            arg1_shift = arg1 << 0x10;
            mode_offset = ((s32)(var_t1 << 0x10) >> 0xE);
            row_src = (s8 *)((long)mode_offset + (long)sp);
            temp_t5 = var_a3;
            outer_end = temp_v1;
            while (var_a3 < outer_end) {
                var_a2 = arg1_shift >> 0x10;
                temp_v1_2 = var_a2 + var_t7;
                if (var_a2 < temp_v1_2) {
                    s8 *pixel_src;
                    s32 inner_end;
                    pixel_src = (s8 *)((long)((var_a3 - temp_t5) * 2) + (long)row_src);
                    inner_end = temp_v1_2;
                    do {
                        temp_v1_3 = var_a2 & ((S_800BDC98_1 *)temp_t2)->unk_1A;
                        var_a2 += 1;
                        *(u16 *)((long)((s32) (((((S_800BDC98_1 *)temp_t2)->unk_18 & var_a3) + (temp_v1_3 << ((S_800BDC98_1 *)temp_t2)->unk_14)) << 0x10) >> 0xF) + (long)dst) = *(u16 *)pixel_src;
                    } while (var_a2 < inner_end);
                }
                var_a3 += 1;
            }
        }
    }
}

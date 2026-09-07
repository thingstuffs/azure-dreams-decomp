#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

typedef struct {
    u32 word[2];
} __attribute__((packed)) Copy8;

extern u8 D_800E50A8[];
extern u8 D_80083160[];
M2C_UNK func_800672D8(Copy8 *);
extern Copy8 D_80088CB0;
extern u8 D_800EA000[];

void func_8009D6F4(void) {
    Copy8 sp10;
    Copy8 *copy;
    register u8 *base;
    register u8 *cursor ASM_REG("$7");
    register u8 *state ASM_REG("$2");
    register u8 *temp_t1 ASM_REG("$9");
    register u8 *table;
    register s32 var_t6 ASM_REG("$14");
    register s32 var_t4 ASM_REG("$12");
    s16 temp_v0_3;
    register s16 var_t3 ASM_REG("$11");
    register s32 row ASM_REG("$10");
    u8 temp_a0;
    register u8 var_t0 ASM_REG("$8");

    copy = &D_80088CB0;
    sp10 = *copy;
    var_t0 = 0;
    base = D_800E50A8;
    cursor = base;
    ASM_KEEP(cursor);
    ASM_KEEP(base);
    state = D_80083160;
    temp_t1 = state + 0x1DC;
    if ((1 << M2C_FIELD(temp_t1, s16 *, 0x16)) > 0) {
        register s32 var_a2 ASM_REG("$6");
        register s32 var_v0_2 ASM_REG("$2");
        register s32 row_wide ASM_REG("$2");
        register s32 next_a2 ASM_REG("$2");

        var_t3 = 0;
        var_t6 = 0;
        var_t4 = 1;
        table = D_800EA000;
loop_2:
        ASM_KEEP(base);
        var_a2 = 0;
        if (var_t6 < (var_t4 << M2C_FIELD(temp_t1, s16 *, 0x14))) {
            row_wide = var_t3 << 16;
            ASM_KEEP(row_wide);
            row = row_wide >> 16;
loop_4:
            var_v0_2 = var_a2 & 1;
            if (var_v0_2 == 0) {
                var_t0 = *cursor;
                *cursor = 0;
                var_v0_2 = var_t0 & 0xF;
            } else {
                var_v0_2 = var_t0 & 0xF0;
            }
            if (var_v0_2 != 0) {
                register s32 temp_v0 ASM_REG("$2");
                register s32 temp_v1 ASM_REG("$3");
                register s32 clamp ASM_REG("$4");
                register s32 col ASM_REG("$2");
                register s16 shift;

                col = (s16) var_a2;
                shift = M2C_FIELD(temp_t1, s16 *, 0x14);
                temp_v0 = (s16) (M2C_FIELD(((((row << shift) + col) * 6) + table), u16 *, 2) + 0x200) / 64;
                clamp = temp_v0;
                ASM_KEEP(temp_v0);
                temp_v1 = temp_v0;
                if (temp_v1 >= 0x10) {
                    clamp = 15;
                    goto clamp_value;
                }
                if (temp_v1 <= 0) {
                    clamp = 1;
                }
clamp_value:
                temp_v0 = clamp << 0x10;
                temp_v1 = temp_v0 >> 0x10;
                temp_a0 = *cursor;
                if (var_a2 & 1) {
                    temp_v0 = temp_a0 | (temp_v1 << 4);
                    goto store_value;
                }
                temp_v0 = temp_a0 | temp_v1;
store_value:
                *cursor = temp_v0;
                goto block_16;
            }
block_16:
            if (var_a2 & 1) {
                next_a2 = var_a2 + 1;
                cursor += 1;
            } else {
                next_a2 = var_a2 + 1;
            }
            var_a2 = next_a2;
            ASM_KEEP_NV(next_a2);
            if ((s16) next_a2 >= (var_t4 << M2C_FIELD(temp_t1, s16 *, 0x14))) {
                goto block_19;
            }
            goto loop_4;
        }
block_19:
        temp_v0_3 = var_t3 + 1;
        var_t3 = temp_v0_3;
        if (temp_v0_3 >= (var_t4 << M2C_FIELD(temp_t1, s16 *, 0x16))) {
            goto done;
        }
        goto loop_2;
    }
done:
    func_800672D8(&sp10);
}

#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009D6F4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8009D6F4_1;   /* ((((row << shift) + col) * 6) + table) in func_8009D6F4 */




typedef struct {
    u32 word[2];
} __attribute__((packed)) Copy8;

extern u8 D_800E50A8[];
extern u8 D_80083160[];
M2C_UNK func_800672D8(Copy8 *);
extern Copy8 D_80088CB0;
extern u8 D_800EA000[];

typedef struct S_8009D6F4_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
} S_8009D6F4_0;   /* temp_t1 in func_8009D6F4 */

void func_8009D6F4(void) {
    Copy8 sp10;
    Copy8 *copy;
    register u8 *base;
    register u8 *cursor ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *state;
    u8 *temp_t1;
    register u8 *table;
    s32 var_t6;
    s32 var_t4;
    s16 temp_v0_3;
    register s16 var_t3 ASM_REG("$11");   /* MATCH pin: retail register colouring depends on it */
    register s32 row ASM_REG("$10");   /* MATCH pin: retail register colouring depends on it */
    u8 temp_a0;
    u8 var_t0;

    copy = &D_80088CB0;
    sp10 = *copy;
    var_t0 = 0;
    base = D_800E50A8;
    cursor = base;
    ASM_KEEP(base);   /* MATCH pin: keeps a statement from moving across a call/branch */
    state = D_80083160;
    temp_t1 = state + 0x1DC;
    if ((1 << ((S_8009D6F4_0 *)temp_t1)->unk_16) > 0) {
        register s32 var_a2 ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
        s32 var_v0_2;
        register s32 row_wide ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 next_a2 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

        var_t3 = 0;
        var_t6 = 0;
        var_t4 = 1;
        table = D_800EA000;
loop_2:
        ASM_KEEP(base);   /* MATCH pin: keeps a statement from moving across a call/branch */
        var_a2 = 0;
        if (var_t6 < (var_t4 << ((S_8009D6F4_0 *)temp_t1)->unk_14)) {
            row_wide = var_t3 << 16;
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
                register s32 temp_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
                s32 temp_v1;
                register s32 clamp ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                s32 col;
                register s16 shift;

                col = (s16) var_a2;
                shift = ((S_8009D6F4_0 *)temp_t1)->unk_14;
                temp_v0 = (s16) (((S_8009D6F4_1 *)(((((row << shift) + col) * 6) + table)))->unk_02 + 0x200) / 64;
                clamp = temp_v0;
                ASM_KEEP(temp_v0);   /* MATCH pin: retail register colouring depends on it */
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
            ASM_KEEP_NV(next_a2);   /* MATCH pin: retail register colouring depends on it */
            if ((s16) next_a2 >= (var_t4 << ((S_8009D6F4_0 *)temp_t1)->unk_14)) {
                goto block_19;
            }
            goto loop_4;
        }
block_19:
        temp_v0_3 = var_t3 + 1;
        var_t3 = temp_v0_3;
        if (temp_v0_3 >= (var_t4 << ((S_8009D6F4_0 *)temp_t1)->unk_16)) {
            goto done;
        }
        goto loop_2;
    }
done:
    func_800672D8(&sp10);
}

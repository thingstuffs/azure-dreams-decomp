#include "common.h"

extern s16 func_800ABEEC(s16, s32, s32);
extern s32 func_800AC348(void);
extern s8 D_8006CCD8[9];
extern s8 D_8006CCE8[9];

typedef struct {
    u8 *field0;
    u8 unk04[0x10];
    s16 field14;
    s16 field16;
} Config;

extern Config D_8008333C;

s32 func_800AC1B0(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    u16 *sp10;
    register u16 *loaded ASM_REG("$2");
    register Config *config ASM_REG("$16");
    register s32 var_a3 ASM_REG("$7");
    s16 temp_v0;
    s16 temp_v0_2;
    register s16 var_s2 ASM_REG("$18");
    register s16 var_s3 ASM_REG("$19");
    s32 temp_a1;
    register s32 temp_s5 ASM_REG("$21");
    register s32 var_s1 ASM_REG("$17");
    register s16 var_s4 ASM_REG("$20");
    s32 var_v0;
    s32 var_v0_2;
    register s32 arg0_shift ASM_REG("$22");
    register s32 var_s7 ASM_REG("$23");
    u16 *temp_s8;
    u8 *table_base;

    var_a3 = arg3;
    var_s3 = arg1;
    var_s2 = arg2;
    var_s1 = 0xA;
    var_s4 = 0;
    config = &D_8008333C;
    loaded = *(u16 **)&D_8008333C;
    sp10 = loaded;
    if (arg1 < 0) {
        goto block_bad;
    }
    var_a3 = 1;
    if (arg1 >= (var_a3 << config->field14)) {
        goto block_bad;
    }
    if (arg2 < 0) {
        return 0;
    }
    if (arg2 < (var_a3 << config->field16)) {
        goto block_8;
    }
block_bad:
    func_800AC348();
    return 0;
block_8:
            arg0_shift = arg0 << 0x10;
            table_base = (u8 *)&D_8006CCD8;
            temp_s5 = arg0_shift >> 0xF;
            temp_s8 = (u16 *)(table_base + temp_s5);
            ASM_KEEP(var_a3);
            var_s7 = 1;
loop_7:
            var_v0_2 = var_s3 << 0x10;
            temp_a1 = var_v0_2 >> 0x10;
            if (!(*(u16 *)((u8 *)sp10 +
                          ((temp_a1 + (var_s2 << config->field14)) << 1)) & 0x8000) ||
                (var_s4 += 1,
                 (func_800ABEEC((s16)(arg0_shift >> 0x10), temp_a1, var_s2) < 2))) {
                temp_v0 = var_s3 + *temp_s8;
                var_s3 = temp_v0;
                if (temp_v0 >= 0) {
                    if (temp_v0 < (var_s7 << config->field14)) {
                        temp_v0_2 = var_s2 + *(u16 *)((u8 *)&D_8006CCE8 + temp_s5);
                        var_s2 = temp_v0_2;
                        if (temp_v0_2 >= 0) {
                            if (temp_v0_2 < (var_s7 << config->field16)) {
                                var_s1 -= 1;
                                if (var_s1 <= 0) {
                                    goto block_14;
                                }
                                goto loop_7;
                            }
                        }
                    } else {
block_14:
                        ;
                    }
                }
            }
            var_v0 = var_s4;
            return var_v0;
}

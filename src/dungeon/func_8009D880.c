#include "common.h"
#include "m2c_compat.h"

s32 func_8003AD08();                        /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_80099734();                     /* extern */
s32 func_800A2DB8();                          /* extern */
M2C_UNK func_800A319C();                   /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern void *D_8007359C;
extern M2C_UNK D_80089000;
extern M2C_UNK D_800E09CD;
extern M2C_UNK D_800E09D9;
extern M2C_UNK D_800E09E6;
extern M2C_UNK D_800E09EE;
extern M2C_UNK D_800E09FB;

typedef struct S_800A2FE0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x48];
    void * unk_60;
} S_800A2FE0_0;   /* arg0 in func_800A2FE0 */

typedef struct S_800A2FE0_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A2FE0_1;   /* temp_v0 in func_800A2FE0 */

typedef struct S_800A2FE0_2 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_800A2FE0_2;   /* temp_v0_2 in func_800A2FE0 */

typedef struct S_800A2FE0_3 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
} S_800A2FE0_3;   /* temp_v1_2 in func_800A2FE0 */

typedef struct S_800A2FE0_4 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800A2FE0_4;   /* temp_global in func_800A2FE0 */

void func_800A2FE0(S_800A2FE0_0 *arg0) {
    s32 temp_v0_3;
    s32 temp_v0_4;
    register s32 temp_v0_5 ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    s32 temp_v0_raw;
    s32 temp_a;
    s32 temp_v1;
    s32 var_s2;
    s32 var_v1;
    S_800A2FE0_4 *temp_global;
    S_800A2FE0_1 *temp_v0;
    S_800A2FE0_2 *temp_v0_2;
    S_800A2FE0_3 *temp_v1_2;

    var_s2 = 0;
    temp_v0 = arg0->unk_60;
    var_v1 = 0;
    if ((temp_v0 != NULL) && (temp_v0->unk_14 & 0x4000)) {
        temp_a = arg0->unk_14 & 0x4000;
        var_v1 = temp_a != 0;
    }
    if (var_v1 == 0) {
        var_s2 = func_800A2DB8(arg0);
    }
    temp_v1 = arg0->unk_14;
    if (!(temp_v1 & 0x20000000)) {
        if (!(temp_v1 & 0x4000)) {
            temp_v0_2 = arg0->unk_60;
            if ((temp_v0_2 != NULL) && (temp_v0_2->unk_13 >= 0)) {
                do { temp_v0_3 = func_800990FC(); } while (0);
                func_80099290(func_80099194(&D_80089000, func_80099734(arg0, func_80099194(&D_800E09CD, temp_v0_3))));
                func_800A5720(temp_v0_3);
            }
        }
        if ((var_s2 != 0) && (temp_v1_2 = arg0->unk_60, (temp_v1_2 != NULL))) {
            if (temp_v1_2->unk_14 & 0x4000) {
                if (!(arg0->unk_14 & 0x4000)) {
                    do { temp_v0_raw = func_800990FC(); } while (0);
                    temp_global = D_8007359C;
                    ASM_KEEP(temp_v0_raw);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                    temp_v0_5 = temp_v0_raw;
                    ASM_KEEP(temp_v0_5);   /* MATCH pin: load-bearing for the whole function shape */
                    func_8003AD08(var_s2, func_80099194(&D_800E09D9, func_80099194(temp_global->unk_04, temp_v0_5)));
                    func_800A319C(&D_800E09E6);
                }
            } else if (temp_v1_2->unk_13 >= 0) {
                do { temp_v0_4 = func_800990FC(); } while (0);
                func_80099290(func_80099194(&D_800E09FB, func_8003AD08(var_s2, func_80099194(&D_800E09EE, func_80099734(arg0->unk_60, temp_v0_4)))));
                func_800A5720(temp_v0_4);
            }
        }
    }
}

/* MECHANISM: The seed's 0x20 frame, s1/s2/s0 roles, CFG, and 124-word shape were already exact.
   The middle func_800990FC result stays guarded in v0 through the D_8007359C load, then copies
   to guarded s0 in that load-delay slot; this fixes both equal-length register substitutions. */

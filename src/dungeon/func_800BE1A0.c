#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80094E34();                            /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
s32 func_800C3AB0();                                /* extern */
s32 func_800C3AC4();                                /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083780;
extern u8 D_800DDE84[];
extern M2C_UNK D_800E17C6;
extern M2C_UNK D_800E17EF;
extern M2C_UNK D_800E180E;
extern s32 D_800E3D7C;

typedef struct S_800C3900_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x4];
    s16 unk_24;
    u8 pad_26[0xEA];
    s32 unk_110;
} S_800C3900_0;   /* arg0 in func_800C3900 */

typedef struct S_800C3900_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C3900_1;   /* var_v1 in func_800C3900 */

typedef struct S_800C3900_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C3900_2;   /* counter_base in func_800C3900 */

s32 func_800C3900(S_800C3900_0 *arg0, s32 arg1, s16 arg2) {
    register M2C_UNK *var_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    M2C_UNK *counter_base;
    s32 temp_s1;
    s32 temp_v0;
    u32 temp_v1;

    if (arg0 == D_800E3D7C) {
        arg0->unk_110 = arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        return 0;
    }
    if (((u32) (arg0->unk_13 - 1) < 0x2EU) && ((u32) arg0 <= 0x9FFFFFFFU)) {
        func_800A63B8(arg0, arg1, arg2);
        temp_s1 = ((u32) arg0->unk_1C >> 3) & 1;
        if (func_800AD6FC(arg0, (((u16 *) D_800DDE84)[arg0->unk_13] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
        temp_v0 = temp_s1;
        if (temp_v0 != 0) {
            arg0->unk_1C = (u32) (arg0->unk_1C | 8);
        }
        temp_v1 = arg0->unk_1C;
        arg0->unk_24 = 0;
        if (!(temp_v1 & 8)) {
            temp_v0 = temp_v1 & 0x80000;
            var_v1 = (M2C_UNK *)0x80080000;
            if (temp_v0 != 0) {
                func_80094E34();
                var_v1 = (M2C_UNK *)0x80080000;
            }
            var_v1 = (M2C_UNK *)((u8 *)var_v1 + 0x3460);
            ((S_800C3900_1 *)var_v1)->unk_0A = (u16) (((S_800C3900_1 *)var_v1)->unk_0A + 1);
        }
        func_800A56E0(0x51E);
        if (arg0->unk_14 & 0x4000) {
            func_80099844(arg0, &D_800E17C6);
        }
        func_80098B38(arg1);
        goto decrement_counter;
    }
    if (arg0->unk_13 == 0) {
        func_800997FC(&D_800E17EF);
        func_800A56E0(0x506);
        goto decrement_counter;
    }
    func_80098B38(arg1);
    func_800997FC(&D_800E180E);
decrement_counter:
    counter_base = &D_80083460;
    ((S_800C3900_2 *)counter_base)->unk_0A = (u16) (((S_800C3900_2 *)counter_base)->unk_0A - 1);
    return 1;
}
/* MECHANISM: The 0x20 frame holds arg0/arg1 in s0/s2 and the pre-call flag in s1.
   Four-arg ABI, u16 table indexing, and guarded v0/v1 live ranges close the head.
   Local shared exits plus held page bases preserve both merged low-half addiu words. */

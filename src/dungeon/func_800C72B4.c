#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CCA14_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x1];
    s8 unk_27;
} S_800CCA14_0;   /* temp_v0 in func_800CCA14 */

typedef struct S_800CCA14_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CCA14_1;   /* count_base in func_800CCA14 */

typedef struct S_800CCA14_2 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    s8 unk_26;
    s8 unk_27;
} S_800CCA14_2;   /* temp_v0_2 in func_800CCA14 */

typedef struct S_800CCA14_3 {
    u8 pad_00[0x11];
    u8 unk_11;
} S_800CCA14_3;   /* D_800E3D7C in func_800CCA14 */


void *func_8003FE78();      /* extern */
s32 func_8009B390();                   /* extern */
M2C_UNK func_8009CE1C(); /* extern */
M2C_UNK func_800CC5F0(); /* extern */
M2C_UNK func_800CC88C();     /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_800CC370;
extern M2C_UNK D_800CC9BC;
extern S_800CCA14_3 *D_800E3D7C;
extern u8 D_800E5908;
extern M2C_UNK D_8014A000;

void func_800CCA14(u16 arg0, u16 arg1, u16 arg2) {
    s32 temp_a1;
    s32 first_a3;
    s32 temp_a3;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0_3;
    s32 var_s4;
    u16 temp_x;
    u16 temp_y;
    u16 temp_z;
    u8 *count_base;
    S_800CCA14_0 *temp_v0;
    S_800CCA14_2 *temp_v0_2;

    temp_v0 = func_8003FE78(0, (D_800E5908 * 0xC8) + (u8 *)&D_8014A000, 0xA);
    temp_v0->unk_10 = &D_800CC9BC;
    temp_v0->unk_20 = arg0;
    temp_v0->unk_22 = arg1;
    temp_v0->unk_24 = arg2;
    temp_v0->unk_27 = 8;
    count_base = (u8 *)&D_80083460;
    ((S_800CCA14_1 *)count_base)->unk_0A = (u16) (((S_800CCA14_1 *)count_base)->unk_0A + 1);
    var_s4 = 3;
    do {
        temp_v0_2 = func_8003FE78(0, (((D_800E5908 * 5) + var_s4) * 0x28) + ((u8 *)&D_8014A000 + 0x28), 0xA);
        temp_v0_2->unk_10 = &D_800CC370;
        temp_x = (u16) temp_v0->unk_20;
        temp_a1 = var_s4 * 2;
        temp_v0_2->unk_20 = temp_x;
        temp_y = (u16) temp_v0->unk_22;
        var_s4 -= 1;
        temp_v0_2->unk_22 = temp_y;
        temp_z = (u16) temp_v0->unk_24;
        temp_v0_2->unk_27 = 8;
        temp_v0_2->unk_26 = temp_a1;
        temp_v0_2->unk_24 = temp_z;
    } while (var_s4 >= 0);
    temp_s0 = (var_s4 << 0x1A) >> 0x10;
    first_a3 = temp_s0;
    ASM_KEEP(first_a3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    var_s4 = 3;
    func_800CC88C((s16) temp_v0->unk_20, (s16) temp_v0->unk_22, (s16) temp_v0->unk_24, first_a3, 0);
    func_800CC88C((s16) temp_v0->unk_20, (s16) temp_v0->unk_22, (s16) temp_v0->unk_24, temp_s0, 1);
    do {
        temp_s0_2 = (var_s4 << 0x1A) >> 0x10;
        temp_a3 = temp_s0_2;
        ASM_KEEP(temp_a3);   /* MATCH pin: retail schedule: same instructions, different order without it */
        var_s4 -= 1;
        func_800CC5F0((s16) temp_v0->unk_20, (s16) temp_v0->unk_22, (s16) temp_v0->unk_24, temp_a3, 0, 0);
        func_800CC5F0((s16) temp_v0->unk_20, (s16) temp_v0->unk_22, (s16) temp_v0->unk_24, temp_s0_2, 1, 1);
    } while (var_s4 >= 0);
    temp_v0_3 = func_8009B390(temp_v0->unk_20, temp_v0->unk_22, (s16) temp_v0->unk_24);
    if (temp_v0_3 != 0) {
        func_8009CE1C(temp_v0_3, 0xC, D_800E3D7C->unk_11, 9, 0x400, 0, 3);
    }
}
/* MECHANISM: Byte-scaled table arithmetic and a held D_80083460 base fixed addressing/prologue.
   One-read x/y/z locals plus the a1 pin/barrier reproduced the first-loop load-delay schedule.
   One counter name, explicit signed shifts, and short-lived a3 pins closed both call seams. */

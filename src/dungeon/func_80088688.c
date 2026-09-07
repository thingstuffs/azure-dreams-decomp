#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80048A44(void *, u8, s32, s32); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
M2C_UNK func_8008CAA0(); /* extern */
M2C_UNK func_8008CBD4(); /* extern */
M2C_UNK func_8008E0A4();                            /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800AD4D0();                      /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8008ACDC;
extern u8 D_800DCFB0[8];
extern u8 D_800DCFE0[8];
extern s32 D_800E296C;


typedef struct S_8008DDE8_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x70];
    u16 unk_10C;
} S_8008DDE8_0;   /* arg0 in func_8008DDE8 */

typedef struct S_8008DDE8_1 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    u32 unk_0C;
    s32 unk_10;
} S_8008DDE8_1;   /* arg1 in func_8008DDE8 */

typedef struct S_8008DDE8_2 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    s16 unk_6A;
} S_8008DDE8_2;   /* arg3 in func_8008DDE8 */

typedef struct S_8008DDE8_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8008DDE8_3;   /* arg2 in func_8008DDE8 */

typedef struct S_8008DDE8_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8008DDE8_4;   /* temp_global in func_8008DDE8 */

void func_8008DDE8(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_a0;
    s32 temp_a1;
    s32 temp_v1;
    u16 temp_v0;
    u16 temp_v0_3;
    u16 temp_timer;
    u32 temp_v0_2;
    u32 temp_page;   /* MATCH pin: load-bearing for the whole function shape */
    u8 *temp_table;
    s32 *temp_global;

    if (((S_8008DDE8_0 *)arg0)->unk_9B == 0) {
        func_800AD4D0(arg3);
        ((S_8008DDE8_0 *)arg0)->unk_9B = (u8) (((S_8008DDE8_0 *)arg0)->unk_9B + 1);
        ((S_8008DDE8_1 *)arg1)->unk_0C = (u32) (func_80064584(((S_8008DDE8_2 *)arg3)->unk_6A) << 9);
        ((S_8008DDE8_1 *)arg1)->unk_10 = (s32) (func_800644B8(((S_8008DDE8_2 *)arg3)->unk_6A) << 9);
        ((S_8008DDE8_0 *)arg0)->unk_96 = 0xCU;
    }
    if (((S_8008DDE8_0 *)arg0)->unk_10C & 1) {
        func_8008CAA0(arg0, arg1, arg2, arg3);
        func_8008E0A4();
        return;
    }
    if ((((S_8008DDE8_3 *)arg2)->unk_2C == D_800DCFE0) && (((S_8008DDE8_3 *)arg2)->unk_14 & 0x6000)) {
        temp_v0 = ((S_8008DDE8_0 *)arg0)->unk_96 - 1;
        ((S_8008DDE8_0 *)arg0)->unk_96 = temp_v0;
        if ((temp_v0 << 0x10) > 0) {
            func_80048A44(arg2, ((S_8008DDE8_3 *)arg2)->unk_2C[((s32) (D_80083228 + ((S_8008DDE8_2 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
        }
    }
    temp_a0 = (s16) ((S_8008DDE8_0 *)arg0)->unk_96;
    if (temp_a0 > 0) {
        temp_v1 = ((S_8008DDE8_1 *)arg1)->unk_00;
        temp_a1 = ((S_8008DDE8_1 *)arg1)->unk_04;
        ((S_8008DDE8_1 *)arg1)->unk_00 = (s32) (temp_v1 + ((s32) ((((((S_8008DDE8_3 *)arg2)->unk_24 << 6) + 0x20) << 0x10) - temp_v1) / temp_a0));
        ((S_8008DDE8_1 *)arg1)->unk_04 = (s32) (temp_a1 + ((s32) ((((((S_8008DDE8_3 *)arg2)->unk_25 << 6) + 0x20) << 0x10) - temp_a1) / (s16) ((S_8008DDE8_0 *)arg0)->unk_96));
        temp_v0_2 = ((S_8008DDE8_1 *)arg1)->unk_0C;
        ((S_8008DDE8_1 *)arg1)->unk_0C = (u32) ((s32) (temp_v0_2 + (temp_v0_2 >> 0x1F)) >> 1);
        ((S_8008DDE8_1 *)arg1)->unk_10 = (s32) ((s32) ((S_8008DDE8_1 *)arg1)->unk_10 / 2);
        temp_v0_3 = ((S_8008DDE8_0 *)arg0)->unk_96 - 1;
        ((S_8008DDE8_0 *)arg0)->unk_96 = temp_v0_3;
        if ((temp_v0_3 << 0x10) == 0) {
            ((S_8008DDE8_1 *)arg1)->unk_10 = 0;
            ((S_8008DDE8_1 *)arg1)->unk_0C = 0U;
            func_800A2B04(arg1, ((S_8008DDE8_3 *)arg2)->unk_24, ((S_8008DDE8_3 *)arg2)->unk_25);
        }
    }
    if (((S_8008DDE8_3 *)arg2)->unk_14 & 0xE000) {
        temp_table = D_800DCFB0;
        (*(u8 **)((u8 *)arg2 + (0x2C))) = temp_table;
        func_80048A44(arg2, temp_table[((s32) (D_80083228 + ((S_8008DDE8_2 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
        temp_page = 0x80080000;
        ASM_KEEP(temp_page);   /* MATCH pin: load-bearing for the whole function shape */
        temp_global = (s32 *)(temp_page + 0x3460);
        if (((S_8008DDE8_4 *)temp_global)->unk_10 == (arg3 - 0x20)) {
            ((S_8008DDE8_4 *)temp_global)->unk_10 = (s32) (((S_8008DDE8_4 *)temp_global)->unk_10 & 0x7FFFFFFF);
        }
        if (((S_8008DDE8_2 *)arg3)->unk_28 == 0) {
            if (D_800E296C & 0x08000000) {
                ((S_8008DDE8_2 *)arg3)->unk_28 = 1U;
                goto assign_timer;
            }
            ((S_8008DDE8_2 *)arg3)->unk_28 = 0U;
            func_8008CBD4(arg0, arg1, arg2, arg3);
            func_8008E0A4();
            return;
        }
        temp_timer = 8U;
        goto store_timer;
assign_timer:
        temp_timer = 8U;
store_timer:
        ((S_8008DDE8_0 *)arg0)->unk_96 = temp_timer;
        ((S_8008DDE8_0 *)arg0)->unk_8C = &D_8008ACDC;
    }
}

/* MECHANISM: Byte-table typing plus X/Y-before-scale statement order aligns the body.
   The true-space 0x8008E090 edge is a local two-predecessor timer join, not a callee.
   Held $v0 page and $a0 base reconstruct D_80083460; cdk closes the final lui reorder. */

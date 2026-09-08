#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_80048A44(void *, u8, s32, s32); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
M2C_UNK func_8008CAA0(); /* extern */
M2C_UNK func_8008CBD4(); /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800AD4D0();                      /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8008ACDC;
extern u8 D_800DCFB0[8];
extern u8 D_800DCFE0[8];
extern s32 D_800E296C;






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
    u32 temp_page;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *temp_table;
    s32 *temp_global;

    if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8 == 0) {
        func_800AD4D0(arg3);
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8 = (u8) (((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8 + 1);
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_u32 = (u32) (func_80064584(((Rec_D_800E3D7C *)arg3)->unk_6A.as_s16) << 9);
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = (s32) (func_800644B8(((Rec_D_800E3D7C *)arg3)->unk_6A.as_s16) << 9);
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_u16 = 0xCU;
    }
    if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_10C & 1) {
        func_8008CAA0(arg0, arg1, arg2, arg3);
        return;
    }
    if ((((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 == D_800DCFE0) && (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000)) {
        temp_v0 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_u16 - 1;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_u16 = temp_v0;
        if ((temp_v0 << 0x10) > 0) {
            func_80048A44(arg2, ((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8[((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
        }
    }
    temp_a0 = (s16) ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_u16;
    if (temp_a0 > 0) {
        temp_v1 = ((Rec_D_800E3D7C *)arg1)->unk_00.at00_s32.v;
        temp_a1 = ((Rec_D_800E3D7C *)arg1)->unk_04.at00_s32.v;
        ((Rec_D_800E3D7C *)arg1)->unk_00.at00_s32.v = (s32) (temp_v1 + ((s32) ((((((Rec_D_80082E80 *)arg2)->unk_24 << 6) + 0x20) << 0x10) - temp_v1) / temp_a0));
        ((Rec_D_800E3D7C *)arg1)->unk_04.at00_s32.v = (s32) (temp_a1 + ((s32) ((((((Rec_D_80082E80 *)arg2)->unk_25 << 6) + 0x20) << 0x10) - temp_a1) / (s16) ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_u16));
        temp_v0_2 = ((Rec_D_800E3D7C *)arg1)->unk_0C.as_u32;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_u32 = (u32) ((s32) (temp_v0_2 + (temp_v0_2 >> 0x1F)) >> 1);
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = (s32) ((s32) ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v / 2);
        temp_v0_3 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_u16 - 1;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_u16 = temp_v0_3;
        if ((temp_v0_3 << 0x10) == 0) {
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_u32 = 0U;
            func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        }
    }
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        temp_table = D_800DCFB0;
        (*(u8 **)((u8 *)arg2 + (0x2C))) = temp_table;
        func_80048A44(arg2, temp_table[((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
        temp_page = 0x80080000;
        ASM_KEEP(temp_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_global = (s32 *)(temp_page + 0x3460);
        if (((S_8008DDE8_4 *)temp_global)->unk_10 == (arg3 - 0x20)) {
            ((S_8008DDE8_4 *)temp_global)->unk_10 = (s32) (((S_8008DDE8_4 *)temp_global)->unk_10 & 0x7FFFFFFF);
        }
        if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
            if (D_800E296C & 0x08000000) {
                ((Rec_D_800E3D7C *)arg3)->unk_28 = 1U;
                goto assign_timer;
            }
            ((Rec_D_800E3D7C *)arg3)->unk_28 = 0U;
            func_8008CBD4(arg0, arg1, arg2, arg3);
            return;
        }
        temp_timer = 8U;
        goto store_timer;
assign_timer:
        temp_timer = 8U;
store_timer:
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_u16 = temp_timer;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_pm = &D_8008ACDC;
    }
}

/* MECHANISM: Byte-table typing plus X/Y-before-scale statement order aligns the body.
   The true-space 0x8008E090 edge is a local two-predecessor timer join, not a callee.
   Held $v0 page and $a0 base reconstruct D_80083460; cdk closes the final lui reorder. */

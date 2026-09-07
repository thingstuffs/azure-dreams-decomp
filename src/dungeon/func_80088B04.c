#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"





typedef struct S_8008E264_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8008E264_4;   /* state_base0 in func_8008E264 */

typedef struct S_8008E264_5 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_8008E264_5;   /* state_base1 in func_8008E264 */


M2C_UNK func_80048A44(); /* extern */
s32 func_80094F74();  /* extern */
M2C_UNK func_80099F04();                         /* extern */
M2C_UNK func_80099F70();                         /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s16 D_80083464;
extern void *D_80088810[];
extern M2C_UNK D_8008ACDC;
extern u8 D_800DD040[];
extern u8 D_800DD058[];

void func_8008E264(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const sw_keep[13] = {
        &&case_0, &&case_1, &&case_default, &&case_default,
        &&case_default, &&case_default, &&case_default, &&case_default,
        &&case_0, &&case_1, &&case_0, &&case_1, &&case_12
    };
    s16 temp_v0;
    s32 delta_v1;
    s32 var_v0;
    u32 swi;
    u8 *state_base0;
    u8 *state_base1;
    u8 temp_v1;
    s32 temp_v1_2;

    temp_v1 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8;
    swi = temp_v1;
    if (swi >= 13) {
        goto case_default;
    }
    (void)sw_keep;
    goto *D_80088810[swi];
case_0:
        if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
            temp_v1_2 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8;
            if (temp_v1_2 != 0) {
                goto temp_nonzero;
            }
            ASM_KEEP(temp_v1_2);   /* MATCH pin: retail branch polarity depends on it */
            var_v0 = 0xFFF00000;
            goto temp_join;
temp_nonzero:
            var_v0 = 8;
            if (temp_v1_2 != var_v0) {
                var_v0 = 0xFFEC0000;
                goto temp_join;
            }
            var_v0 = 0xFFF80000;
temp_join:
            ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = var_v0;
            func_80099F70(((Rec_D_800E3D7C *)arg3)->unk_5C);
            func_80099F04(((Rec_D_800E3D7C *)arg3)->unk_5C);
            state_base0 = (u8 *)&D_80083460;
            ((S_8008E264_4 *)state_base0)->unk_02 = (u16) (((S_8008E264_4 *)state_base0)->unk_02 | 0x812);
            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_98 = (u16) (((Rec_func_8008ACDC_arg0 *)arg0)->unk_98 & 0xFFF3);
            (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD040;
            func_80048A44(arg2, D_800DD040[((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8 = (u8) (((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8 + 1);
            func_800A56E0(0x50A);
            return;
        }
case_default:
        return;
case_1:
        state_base1 = (u8 *)&D_80083460;
        if (((S_8008E264_5 *)state_base1)->unk_04 != 0) {
            var_v0 = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
            delta_v1 = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v;
            delta_v1 -= 0x20;
            var_v0 = (var_v0 - delta_v1) << 0x10;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = var_v0 / ((S_8008E264_5 *)state_base1)->unk_04;
            delta_v1 = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v;
            var_v0 = ((Rec_D_80082E80 *)arg2)->unk_25;
            delta_v1 -= 0x20;
            var_v0 <<= 6;
            var_v0 -= delta_v1;
            delta_v1 = ((S_8008E264_5 *)state_base1)->unk_04;
            var_v0 <<= 0x10;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = var_v0 / delta_v1;
        }
        temp_v0 = (u16) ((S_8008E264_5 *)state_base1)->unk_04 - 1;
        ((S_8008E264_5 *)state_base1)->unk_04 = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            ((S_8008E264_5 *)state_base1)->unk_04 = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
            func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
            if ((u8) ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8 >= 0xAU) {
                (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD058;
                func_80048A44(arg2, D_800DD058[((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
                ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8 = (u8) (((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8 + 1);
                ((S_8008E264_5 *)state_base1)->unk_04 = 1;
                return;
            }
            goto block_15;
        }
        return;
case_12:
        if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
            D_80083464 = 0;
            goto block_15;
        }
        return;
block_15:
        if ((func_80094F74(arg0, arg1, arg2, arg3) << 0x10) > 0) {
            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_pm = &D_8008ACDC;
        }
}

/* MECHANISM: External jump-table dispatch and two distinct D_80083460 base live ranges fixed layout.
   A widened selector fence plus guarded v0/v1 pins preserved the retail inner CFG and divide roles.
   Moving case 12 before the shared join and fencing the divisor reload closed the final schedule. */

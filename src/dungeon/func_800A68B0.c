#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80083460[3];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_8009B164();             /* extern */
s32 func_8009B88C();      /* extern */
void *func_8009C93C(); /* extern */
M2C_UNK func_8009CE1C(); /* extern */
u8 func_8009FB34();                           /* extern */
M2C_UNK func_800A19E4(); /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800AA5E4(); /* extern */
s16 func_800BCB04();                   /* extern */





typedef struct S_800AC010_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AC010_4;   /* counter1 in func_800AC010 */

typedef struct S_800AC010_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AC010_5;   /* counter2 in func_800AC010 */

s32 func_800AC010(void *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    u16 sp20;
    u16 sp22;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    M2C_UNK move_flags1;
    M2C_UNK move_flags2;
    u8 move_x1;
    u8 move_y1;
    u8 move_x2;
    u8 move_y2;
    s32 *counter1;
    s32 *counter2;
    s16 temp_a0;
    s32 temp_v0_5;
    s32 temp_v1;
    s16 temp_v0;
    s16 temp_v0_4;
    u16 temp_v0_3;
    void *temp_v0_2;

    temp_a0 = ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16;
    if (temp_a0 != 0) {
        temp_v0_5 = arg2->unk_24;
        temp_v1 = arg1->unk_00.at02_s16.v;
        temp_v0_5 <<= 6;
        temp_v1 -= 0x20;
        arg1->unk_0C.as_s32 = (s32) ((s32) ((temp_v0_5 - temp_v1) << 0x10) / temp_a0);
        temp_v1 = arg1->unk_04.at02_s16.v - 0x20;
        arg1->unk_10.at00_s32.v = (s32) ((s32) (((arg2->unk_25 << 6) - temp_v1) << 0x10) / (s16) ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16);
    }
    temp_v0 = (u16) ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16 - 1;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        temp_v0_2 = func_8009C93C(arg3, arg2, arg3->unk_6A.as_s16, 0, 0);
        if (temp_v0_2 != NULL) {
            func_8009CE1C(arg3, 4, 1, 8, (s32) (s16) ((u16) arg3->unk_6A.as_s16 + 0x800), 0, 1);
            func_8009CE1C(temp_v0_2, 8, 1, 8, (s32) arg3->unk_6A.as_s16, 0, 1);
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)arg0)->unk_98 & 0xFFF7);
            arg1->unk_14.as_s32 = 0;
            arg1->unk_10.at00_s32.v = 0;
            arg1->unk_0C.as_s32 = 0;
            arg3->unk_1C.as_s32 = (s32) (arg3->unk_1C.as_s32 | 0x40000000);
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9C.as_u8 = (u8) arg2->unk_26.as_u8;
            arg2->unk_26.as_u8 = func_8009FB34(arg2->unk_24, arg2->unk_25);
            func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
            if ((func_8009B88C(arg3, arg2->unk_24, arg2->unk_25, &sp20, &sp22) << 0x10) != 0) {
                goto object_move_ok;
            }
common_fail:
            func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
            func_800AA5E4(arg0, arg1, arg2, arg3);
            return 0;
object_move_ok:
            arg2->unk_24 = sp20;
            arg2->unk_25 = sp22;
            func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
            move_flags1 = arg3->unk_1C.as_s32;
            move_x1 = arg2->unk_24;
            move_y1 = arg2->unk_25;
            var_a2 = 0x3000;
            if (move_flags1 & 0x2000) {
                var_a2 = 0x300;
            }
            func_8009A21C(move_x1, move_y1, var_a2);
            counter1 = D_80083460;
            arg3->unk_1C.as_s32 = (s32) (arg3->unk_1C.as_s32 & 0xFFDFFFFF);
            ((S_800AC010_4 *)counter1)->unk_0A = (u16) (((S_800AC010_4 *)counter1)->unk_0A - 1);
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16 = 0;
            arg3->unk_71.as_s8 = 0;
            return 1;
        }
        if ((func_8009B164(arg3->unk_6A.as_s16, arg1, arg2) << 0x10) != 0) {
            temp_v0_3 = arg3->unk_8A.as_u16 - 1;
            arg3->unk_8A.as_u16 = temp_v0_3;
            if ((temp_v0_3 << 0x10) > 0) {
                arg2->unk_24 = (u8) (arg2->unk_24 + *(((u16) arg3->unk_6A.as_s16 >> 9 & 7) + D_8006CCD8));
                arg2->unk_25 = (u8) (arg2->unk_25 + *(((u16) arg3->unk_6A.as_s16 >> 9 & 7) + D_8006CCE8));
                ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16 = 2;
                goto movement_return;
            }
        }
        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)arg0)->unk_98 & 0xFFF7);
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_9C.as_u8 = (u8) arg2->unk_26.as_u8;
        arg2->unk_26.as_u8 = func_8009FB34(arg2->unk_24, arg2->unk_25);
        func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
        temp_v0_4 = func_800BCB04((arg2->unk_24 << 6) | 0x20, (arg2->unk_25 << 6) | 0x20, (s16) (arg1->unk_08.at02_u16.v - 0x20));
        if (temp_v0_4 < 0x200) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_90.at02_s16.v = 0;
            arg3->unk_88.as_s16 = temp_v0_4;
        }
        counter2 = D_80083460;
        ((S_800AC010_5 *)counter2)->unk_0A = (u16) (((S_800AC010_5 *)counter2)->unk_0A - 1);
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16 = 0;
        arg3->unk_1C.as_s32 = (s32) ((arg3->unk_1C.as_s32 | 0x40000000) & 0xFFDFFFFF);
        if ((func_8009B88C(arg3, arg2->unk_24, arg2->unk_25, &sp20, &sp22) << 0x10) != 0) {
            arg2->unk_24 = sp20;
            arg2->unk_25 = sp22;
            func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
            move_flags2 = arg3->unk_1C.as_s32;
            move_x2 = arg2->unk_24;
            move_y2 = arg2->unk_25;
            var_a2_2 = 0x3000;
            if (move_flags2 & 0x2000) {
                var_a2_2 = 0x300;
            }
            func_8009A21C(move_x2, move_y2, var_a2_2);
            arg3->unk_71.as_s8 = 0;
            return 1;
        }
        goto common_fail;
    }
movement_return:
    return 0;
}

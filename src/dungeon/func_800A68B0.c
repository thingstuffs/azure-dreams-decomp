#include "common.h"
#include "m2c_compat.h"

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

typedef struct S_800AC010_0 {
    u8 pad_00[0x92];
    s16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x2];
    u8 unk_9C;
} S_800AC010_0;   /* arg0 in func_800AC010 */

typedef struct S_800AC010_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 unk_26;
} S_800AC010_1;   /* arg2 in func_800AC010 */

typedef struct S_800AC010_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800AC010_2;   /* arg1 in func_800AC010 */

typedef struct S_800AC010_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4A];
    s16 unk_6A;
    u8 pad_6C[0x5];
    s8 unk_71;
    u8 pad_72[0x16];
    s16 unk_88;
    u16 unk_8A;
} S_800AC010_3;   /* arg3 in func_800AC010 */

typedef struct S_800AC010_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AC010_4;   /* counter1 in func_800AC010 */

typedef struct S_800AC010_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AC010_5;   /* counter2 in func_800AC010 */

s32 func_800AC010(void *arg0, S_800AC010_2 *arg1, S_800AC010_1 *arg2, S_800AC010_3 *arg3) {
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

    temp_a0 = ((S_800AC010_0 *)arg0)->unk_96;
    if (temp_a0 != 0) {
        temp_v0_5 = arg2->unk_24;
        temp_v1 = arg1->unk_02;
        temp_v0_5 <<= 6;
        temp_v1 -= 0x20;
        arg1->unk_0C = (s32) ((s32) ((temp_v0_5 - temp_v1) << 0x10) / temp_a0);
        temp_v1 = arg1->unk_06 - 0x20;
        arg1->unk_10 = (s32) ((s32) (((arg2->unk_25 << 6) - temp_v1) << 0x10) / (s16) ((S_800AC010_0 *)arg0)->unk_96);
    }
    temp_v0 = (u16) ((S_800AC010_0 *)arg0)->unk_96 - 1;
    ((S_800AC010_0 *)arg0)->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        temp_v0_2 = func_8009C93C(arg3, arg2, arg3->unk_6A, 0, 0);
        if (temp_v0_2 != NULL) {
            func_8009CE1C(arg3, 4, 1, 8, (s32) (s16) ((u16) arg3->unk_6A + 0x800), 0, 1);
            func_8009CE1C(temp_v0_2, 8, 1, 8, (s32) arg3->unk_6A, 0, 1);
            ((S_800AC010_0 *)arg0)->unk_98 = (u16) (((S_800AC010_0 *)arg0)->unk_98 & 0xFFF7);
            arg1->unk_14 = 0;
            arg1->unk_10 = 0;
            arg1->unk_0C = 0;
            arg3->unk_1C = (s32) (arg3->unk_1C | 0x40000000);
            ((S_800AC010_0 *)arg0)->unk_9C = (u8) arg2->unk_26;
            arg2->unk_26 = func_8009FB34(arg2->unk_24, arg2->unk_25);
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
            move_flags1 = arg3->unk_1C;
            move_x1 = arg2->unk_24;
            move_y1 = arg2->unk_25;
            var_a2 = 0x3000;
            if (move_flags1 & 0x2000) {
                var_a2 = 0x300;
            }
            func_8009A21C(move_x1, move_y1, var_a2);
            counter1 = D_80083460;
            arg3->unk_1C = (s32) (arg3->unk_1C & 0xFFDFFFFF);
            ((S_800AC010_4 *)counter1)->unk_0A = (u16) (((S_800AC010_4 *)counter1)->unk_0A - 1);
            ((S_800AC010_0 *)arg0)->unk_96 = 0;
            arg3->unk_71 = 0;
            return 1;
        }
        if ((func_8009B164(arg3->unk_6A, arg1, arg2) << 0x10) != 0) {
            temp_v0_3 = arg3->unk_8A - 1;
            arg3->unk_8A = temp_v0_3;
            if ((temp_v0_3 << 0x10) > 0) {
                arg2->unk_24 = (u8) (arg2->unk_24 + *(((u16) arg3->unk_6A >> 9 & 7) + D_8006CCD8));
                arg2->unk_25 = (u8) (arg2->unk_25 + *(((u16) arg3->unk_6A >> 9 & 7) + D_8006CCE8));
                ((S_800AC010_0 *)arg0)->unk_96 = 2;
                goto movement_return;
            }
        }
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        ((S_800AC010_0 *)arg0)->unk_98 = (u16) (((S_800AC010_0 *)arg0)->unk_98 & 0xFFF7);
        ((S_800AC010_0 *)arg0)->unk_9C = (u8) arg2->unk_26;
        arg2->unk_26 = func_8009FB34(arg2->unk_24, arg2->unk_25);
        func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
        temp_v0_4 = func_800BCB04((arg2->unk_24 << 6) | 0x20, (arg2->unk_25 << 6) | 0x20, (s16) (arg1->unk_0A - 0x20));
        if (temp_v0_4 < 0x200) {
            ((S_800AC010_0 *)arg0)->unk_92 = 0;
            arg3->unk_88 = temp_v0_4;
        }
        counter2 = D_80083460;
        ((S_800AC010_5 *)counter2)->unk_0A = (u16) (((S_800AC010_5 *)counter2)->unk_0A - 1);
        ((S_800AC010_0 *)arg0)->unk_96 = 0;
        arg3->unk_1C = (s32) ((arg3->unk_1C | 0x40000000) & 0xFFDFFFFF);
        if ((func_8009B88C(arg3, arg2->unk_24, arg2->unk_25, &sp20, &sp22) << 0x10) != 0) {
            arg2->unk_24 = sp20;
            arg2->unk_25 = sp22;
            func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
            move_flags2 = arg3->unk_1C;
            move_x2 = arg2->unk_24;
            move_y2 = arg2->unk_25;
            var_a2_2 = 0x3000;
            if (move_flags2 & 0x2000) {
                var_a2_2 = 0x300;
            }
            func_8009A21C(move_x2, move_y2, var_a2_2);
            arg3->unk_71 = 0;
            return 1;
        }
        goto common_fail;
    }
movement_return:
    return 0;
}

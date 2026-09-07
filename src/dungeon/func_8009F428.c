#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800A4B88_0_pre {
    s32 unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_800A4B88_0_pre;   /* the 0x18 bytes before arg0 in func_800A4B88, addressed as arg0[-1] */


typedef struct S_800A4B88_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A4B88_1;   /* temp_s0 in func_800A4B88 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80089008[];
void func_8003DB94();     /* extern */
M2C_UNK func_8003E188();            /* extern */
void func_80041E70();                      /* extern */
M2C_UNK func_80096088();              /* extern */
void func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */
M2C_UNK func_800ACB98(); /* extern */
M2C_UNK func_800D8590();                      /* extern */
extern M2C_UNK D_80082E80;
extern s32 D_80083110[];
extern s16 D_80083228;
extern u8 D_800DD274[];

void func_800A4B88(void *arg0, s32 arg1) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20, &&jt_c21, &&jt_c22, &&jt_c23, &&jt_c24, &&jt_c25, &&jt_c26 };
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    M2C_UNK var_a2_3;
    M2C_UNK var_a2_4;
    s32 temp_a1;
    s32 *var_v0;
    s32 temp_v0;
    s32 var_v1;
    M2C_UNK *temp_a0;
    u8 var_a0;
    u8 var_a1;
    void *temp_s0;

    temp_a1 = (s16) (arg1 - 1);
    if ((u32) temp_a1 >= 0x1BU) {
        goto block_26;
    }
    (void)jt_keep; goto *D_80089008[(u32)(temp_a1)];
jt_c0:
    ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 | 0x200);
    goto block_26;
jt_c1:
    ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 | 0x400);
    goto block_26;
jt_c2:
    ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = (s32) ((((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 & 0xFFFDFFFF) | 0x10);
    goto block_26;
jt_c3:
    ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 | 0x20);
    goto block_26;
jt_c4:
    ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 | 0x40);
    goto block_26;
jt_c5:
    ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 | 0x80);
    goto block_26;
jt_c7:
    ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 | 0x800);
    goto block_26;
jt_c8:
    ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 | 0x1000);
    goto block_26;
jt_c26:
    temp_s0 = ((S_800A4B88_0_pre *)arg0)[-1].unk_04;
    var_a0 = ((S_800A4B88_1 *)temp_s0)->unk_24;
    var_a1 = ((S_800A4B88_1 *)temp_s0)->unk_25;
    var_a2 = 0x3000;
    if (!(((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 & 0x2000)) {
        goto block_12;
    }
    var_a2 = 0x300;
block_12:
    func_8009A3D0(var_a0, var_a1, var_a2);
    goto block_26;
jt_c10:
    temp_s0 = ((S_800A4B88_0_pre *)arg0)[-1].unk_04;
    var_a0 = ((S_800A4B88_1 *)temp_s0)->unk_24;
    var_a1 = ((S_800A4B88_1 *)temp_s0)->unk_25;
    var_a2_2 = 0x3000;
    if (!(((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 & 0x2000)) {
        goto block_15;
    }
    var_a2_2 = 0x300;
block_15:
    func_8009A3D0(var_a0, var_a1, var_a2_2);
    temp_v0 = ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 | 0x2000;
    ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = temp_v0;
    var_a0 = ((S_800A4B88_1 *)temp_s0)->unk_24;
    var_a1 = ((S_800A4B88_1 *)temp_s0)->unk_25;
    var_a2_3 = 0x3000;
    if (!(temp_v0 & 0x2000)) {
        goto block_20;
    }
    var_a2_3 = 0x300;
    goto block_20;
jt_c11:
    temp_s0 = ((S_800A4B88_0_pre *)arg0)[-1].unk_04;
    var_a0 = ((S_800A4B88_1 *)temp_s0)->unk_24;
    var_a1 = ((S_800A4B88_1 *)temp_s0)->unk_25;
    var_a2_4 = 0x3000;
    if (!(((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 & 0x2000)) {
        goto block_19;
    }
    var_a2_4 = 0x300;
block_19:
    func_8009A3D0(var_a0, var_a1, var_a2_4);
    ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 & ~0x2000);
    var_a0 = ((S_800A4B88_1 *)temp_s0)->unk_24;
    var_a1 = ((S_800A4B88_1 *)temp_s0)->unk_25;
    do {
        var_a2_3 = 0x3000;
    } while (0);
block_20:
    func_8009A21C(var_a0, var_a1, var_a2_3);
    goto block_26;
jt_c9:
    func_8003E188(0x2E, 0);
    if (!(((Rec_D_800E3D7C *)arg0)->unk_14.as_s32 & 0x20000000)) {
        goto block_23;
    }
    func_800ACB98(arg0, ((S_800A4B88_0_pre *)arg0)[-1].unk_00, ((S_800A4B88_0_pre *)arg0)[-1].unk_04, arg0);
    return;
block_23:
    func_800D8590(arg0);
    if (((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v != 0) {
        goto block_26;
    }
    func_80096088(arg0, arg0);
    temp_a0 = &D_80082E80;
    (*(M2C_UNK **)((u8 *)temp_a0 + 0x2C)) = D_800DD274;
    func_8003DB94(temp_a0, *(s32 *)(D_800DD274 + ((((s32) (D_80083228 + (*(s16 *)((u8 *)arg0 + 0x2A)) + 0x100) >> 7) & 0x1C))), 0);
    var_v1 = 3;
    var_v0 = D_80083110;
    var_v0 += 3;
loop_25:
    *var_v0 = 0;
    var_v1 -= 1;
    var_v0 -= 1;
    if (var_v1 >= 0) {
        goto loop_25;
    }
jt_c6:
jt_c12:
jt_c13:
jt_c14:
jt_c15:
jt_c16:
jt_c17:
jt_c18:
jt_c19:
jt_c20:
jt_c21:
jt_c22:
jt_c23:
jt_c24:
jt_c25:
block_26:
    func_80041E70(arg0);
    return;
}

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8017364C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_8017364C_0;   /* arg0 in func_8017364C */

typedef struct S_8017364C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_8017364C_1;   /* arg3 in func_8017364C */

typedef struct S_8017364C_2 {
    u8 * unk_00;
} S_8017364C_2;   /* (u8 *)var_v0 - 0x14 in func_8017364C */




typedef struct S_8017364C_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8017364C_6;   /* global_state in func_8017364C */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80170858[];
s32 func_8003F270(void);                 /* extern */
void func_80047784();         /* extern */
s32 func_80069EF8();                                /* extern */
void *func_800A05A4();      /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800A94A0();       /* extern */
void func_80171020(); /* extern */
extern M2C_UNK D_8006DE24;
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[16];
extern s32 D_8008346C;
extern M2C_UNK D_80171760;
extern u8 D_80174E88[9];

void func_8017364C(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    s16 temp_v0_3;
    s16 var_s0;
    s32 temp_v0;
    s32 temp_v1_2;
    register s32 var_s4 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s8 var_v0_2;
    s8 var_v1;
    u16 temp_v0_2;
    u16 temp_v0_4;
    u8 *global_state;
    u8 *var_s1;
    s32 temp_v1;
    void *temp_v1_3;
    void *var_v0;

    temp_v1 = ((S_8017364C_0 *)arg0)->unk_9B;
    var_s4 = 0;
    if (temp_v1 == 1) {
        goto block_37;
    }
    if ((s32) temp_v1 >= 2) {
        goto block_4;
    }
    if (temp_v1 == 0) {
        goto block_7;
    }
    return;
block_4:
    if (temp_v1 == 2) {
        goto block_40;
    }
    if (temp_v1 == 3) {
        goto block_46;
    }
    return;
block_7:
    if (!(((S_8017364C_1 *)arg3)->unk_1C & 0x2000)) {
        goto block_13;
    }
    temp_v0 = ((S_8017364C_1 *)arg3)->unk_46 & 0x3FFF;
    if ((u32) (temp_v0 - 1) >= 7U) {
        goto block_21;
    }
    (void)jt_keep; goto *D_80170858[(u32)((temp_v0) - 1)];
jt_c7:
    var_s4 = 1;
    goto block_18;
jt_c6:
    var_s4 = 1;
    goto block_19;
jt_c5:
    var_s4 = 1;
    goto block_20;
block_13:
    temp_v1_2 = ((S_8017364C_1 *)arg3)->unk_46 & 0x3FFF;
    if (temp_v1_2 == 2) {
        goto block_19;
    }
    if (temp_v1_2 >= 3) {
        goto block_17;
    }
    var_s1 = NULL;
    if (temp_v1_2 == 1) {
        goto block_20;
    }
    goto block_22;
block_17:
    var_s1 = NULL;
    if (temp_v1_2 != 3) {
        goto block_22;
    }
jt_c3:
block_18:
    var_s1 = arg3 + 0xE;
    goto block_22;
jt_c2:
block_19:
    var_s1 = arg3 + 0xB;
    goto block_22;
jt_c1:
block_20:
    var_s1 = arg3 + 8;
    goto block_22;
jt_c4:
block_21:
    var_s1 = NULL;
block_22:
    if (*var_s1 == 0) {
        goto block_36;
    }
    *(volatile u16 *)((u8 *)arg0 + 0x98) =
        ((S_8017364C_0 *)arg0)->unk_98 & 0xFF7F;
    {
        s32 use_mode = var_s4;
        ASM_KEEP(use_mode);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (use_mode) {
            var_v0 = D_800814A8;
            ((S_8017364C_1 *)arg3)->unk_60 = var_v0;
            goto block_27;
        }
    }
block_25:
    {
        u8 *base;
        u8 kind;
        u32 entry;

        base = (u8 *)0x80070000;
        ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        kind = *var_s1;
        base -= 0x21DC;
        entry = kind * 20;
        entry += (u32)base;
        ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (((u8 *)entry)[0x12] != 2) {
            goto block_28;
        }
    }
    var_v0 = ((S_8017364C_1 *)arg3)->unk_60;
    if (var_v0 == NULL) {
        goto block_34;
    }
block_27:
    {
        register u8 *other ASM_REG("$3") =
            ((S_8017364C_2 *)((u8 *)var_v0 - 0x14))->unk_00;
        ((S_8017364C_1 *)arg3)->unk_72.s = other[0x24];
        ((S_8017364C_1 *)arg3)->unk_73.s = other[0x25];
    }
    goto block_33;
block_28:
    *(void * volatile *)((u8 *)arg3 + 0x60) =
        func_800A05A4(arg3, ((Rec_D_80082E80 *)arg2)->unk_24,
                      ((Rec_D_80082E80 *)arg2)->unk_25,
                      ((S_8017364C_1 *)arg3)->unk_2A, 0x10);
    ASM_KEEP(var_s4);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    {
        s32 x = ((S_8017364C_1 *)arg3)->unk_72.u;
        s32 y = ((S_8017364C_1 *)arg3)->unk_73.u;

        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        ((S_8017364C_1 *)arg3)->unk_72.s = x;
        ((S_8017364C_1 *)arg3)->unk_73.s = y;
    }
block_33:
block_34:
    if (func_800A94A0(arg3, var_s1, var_s4, arg0 + 0x98) == 0) {
        goto block_55;
    }
    ((S_8017364C_0 *)arg0)->unk_96 = 0x13U;
    ((S_8017364C_0 *)arg0)->unk_9B = (u8) (((S_8017364C_0 *)arg0)->unk_9B + 1);
    return;
block_36:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    D_8008346C = 0;
    ((Rec_D_800814A8 *)D_800814A8)->unk_A6 = (u16) ((*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1);
    func_800A4ACC(arg3);
    ((S_8017364C_1 *)arg3)->unk_6D = (u8) (((S_8017364C_1 *)arg3)->unk_6D - 1);
    ((S_8017364C_0 *)arg0)->unk_8C = &D_80171760;
    ((S_8017364C_1 *)arg3)->unk_73.u = 0;
    ((S_8017364C_1 *)arg3)->unk_72.u = 0;
    ((S_8017364C_1 *)arg3)->unk_46 = (u16) (((S_8017364C_1 *)arg3)->unk_46 & 0x7FFF);
    return;
block_37:
    if (func_8003F270() == 0) {
        goto block_39;
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v | 0x800);
    return;
block_39:
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
    ((S_8017364C_0 *)arg0)->unk_9B = (u8) (((S_8017364C_0 *)arg0)->unk_9B + 1);
    func_800A56E0(0x703);
block_40:
    temp_v0_2 = ((S_8017364C_0 *)arg0)->unk_96 - 1;
    ((S_8017364C_0 *)arg0)->unk_96 = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        goto block_42;
    }
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_43;
    }
block_42:
    ((S_8017364C_0 *)arg0)->unk_98 = (u16) (((S_8017364C_0 *)arg0)->unk_98 | 0x80);
    ((S_8017364C_0 *)arg0)->unk_9B = (u8) (((S_8017364C_0 *)arg0)->unk_9B + 1);
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v | 0x800);
    ((S_8017364C_0 *)arg0)->unk_96 = 0xFU;
block_43:
    if ((u32) (((S_8017364C_0 *)arg0)->unk_96 - 9) >= 6U) {
        goto block_55;
    }
    var_s0 = 0;
loop_44:
    func_80171020(arg0 - 0x20, 0, 0xC0C0, (func_80069EF8() & 0xFF) | 0x80, 0, 0, 0);
    temp_v0_3 = var_s0 + 1;
    var_s0 = temp_v0_3;
    if (temp_v0_3 >= 0xA) {
        return;
    }
    goto loop_44;
block_46:
    global_state = D_80083460;
    if (((S_8017364C_6 *)global_state)->unk_0C != 0) {
        goto block_48;
    }
    ((S_8017364C_0 *)arg0)->unk_96 = 0U;
block_48:
    temp_v0_4 = ((S_8017364C_0 *)arg0)->unk_96 - 1;
    ((S_8017364C_0 *)arg0)->unk_96 = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        goto block_50;
    }
    ((S_8017364C_0 *)arg0)->unk_96 = 0U;
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
block_50:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_55;
    }
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pm == D_80174E88) {
        goto block_53;
    }
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = D_80174E88;
    func_80047784(arg2, D_80174E88[((s32) (D_80083228 + ((S_8017364C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
block_53:
    if (((S_8017364C_6 *)global_state)->unk_0C != 0) {
        goto block_55;
    }
    ((S_8017364C_6 *)global_state)->unk_0A = (u16) (((S_8017364C_6 *)global_state)->unk_0A - 1);
    ((S_8017364C_0 *)arg0)->unk_8C = &D_80171760;
    func_800A4ACC(arg3);
    ((S_8017364C_1 *)arg3)->unk_73.u = 0;
    ((S_8017364C_1 *)arg3)->unk_72.u = 0;
    ((S_8017364C_1 *)arg3)->unk_6D = (u8) (((S_8017364C_1 *)arg3)->unk_6D - 1);
    ((S_8017364C_1 *)arg3)->unk_46 = (u16) (((S_8017364C_1 *)arg3)->unk_46 & 0x7FFF);
    func_800A56E0(0xB4);
block_55:
    return;
}

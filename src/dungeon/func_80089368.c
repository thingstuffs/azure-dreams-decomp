#include "common.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_8002534C(); /* extern */
M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_8008C13C(); /* extern */
M2C_UNK func_8008C468(); /* extern */
M2C_UNK func_8008C7B4(); /* extern */
M2C_UNK func_8008CAA0(); /* extern */
M2C_UNK func_8008CBA0(); /* extern */
M2C_UNK func_8008CF6C(); /* extern */
s32 func_8008D024(); /* extern */
s32 func_8008D1D0();  /* extern */
M2C_UNK func_8008D94C();                            /* extern */
M2C_UNK func_8008F6EC(); /* extern */
M2C_UNK func_8008FA14(); /* extern */
M2C_UNK func_80090200(); /* extern */
s16 func_8009074C();             /* extern */
M2C_UNK func_80094270(void *, void *, void *, s32, u32); /* extern */
M2C_UNK func_80094548();                    /* extern */
M2C_UNK func_8009456C();                    /* extern */
M2C_UNK func_8009458C();                    /* extern */
M2C_UNK func_800945C4();                    /* extern */
s16 func_80095538();                /* extern */
M2C_UNK func_800956B8(); /* extern */
M2C_UNK func_80095854(); /* extern */
s32 func_80098920();   /* extern */
void *func_8009F868();                        /* extern */
M2C_UNK func_8009F988();                    /* extern */
M2C_UNK func_8009FAAC();                            /* extern */
void *func_8009FADC();                      /* extern */
s32 func_800A1C58();                  /* extern */
M2C_UNK func_800A2B04();              /* extern */
s32 func_800A2C34();                          /* extern */
M2C_UNK func_800A4300();              /* extern */
s32 func_800A4474();                          /* extern */
s32 func_800A6D30();                          /* extern */
extern M2C_UNK D_800245A8;
extern M2C_UNK D_8004F5F4;
extern M2C_UNK D_80050CAC;
extern M2C_UNK D_8008ACDC;
extern M2C_UNK D_800DCFB0;
extern u8 D_800DD0B8[];
extern M2C_UNK (*D_800DD830[])(s32, u16);
extern M2C_UNK D_800E3544;
extern s32 D_800E4940;


typedef struct S_8008EAC8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x24];
    s16 unk_8A;
} S_8008EAC8_1;   /* arg3 in func_8008EAC8 */


typedef struct S_8008EAC8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8008EAC8_4;   /* held_D_80083460 in func_8008EAC8 */

typedef struct S_8008EAC8_5 {
    u8 pad_00[0x8];
    u32 unk_08;
} S_8008EAC8_5;   /* held_D_80083160 in func_8008EAC8 */

typedef struct S_8008EAC8_6 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_8008EAC8_6;   /* temp_v0 in func_8008EAC8 */

typedef struct S_8008EAC8_7 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8008EAC8_7;   /* ((((u32) temp_v0) * 4) + arg0) in func_8008EAC8 */

typedef struct S_8008EAC8_8 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_8008EAC8_8;   /* ((temp_v1_7 * 4) + arg0) in func_8008EAC8 */

typedef struct S_8008EAC8_9 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_8008EAC8_9;   /* temp_v0_2 in func_8008EAC8 */

typedef struct S_8008EAC8_10 {
    s8 unk_00;
} S_8008EAC8_10;   /* &D_800E3544 in func_8008EAC8 */

void func_8008EAC8(void *arg0, void *arg1, void *arg2, void *arg3) {
    GameWork *held_D_80083160 = &gameWork;
    s16 temp_v0_3;
    s16 temp_v1;
    s16 var_v0_2;
    s32 temp_a0;
    s32 temp_code;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0_3;
    u16 temp_a1;
    u16 temp_v1_4;
    s32 temp_v1_5;
    u16 temp_v1_6;
    u16 var_v0;
    u16 var_v0_4;
    u32 temp_v1_7;
    u8 temp_a0_2;
    u8 temp_a1_2;
    u8 temp_a1_3;
    u8 temp_a1_4;
    u8 temp_a1_5;
    s32 temp_angle;
    void *code8_a0;
    s32 tail_data_flags;
    void *call_arg;
    void *temp_v0;
    void *temp_v0_2;

    if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_u8 != 0xE) {
        if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0x100) {
            func_8008D94C(arg0, arg1, arg2, arg3);
            return;
        }
    }
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_u8 = 0xEU;
    if (!(((S_8008EAC8_1 *)arg3)->unk_14 & 0x100000)) {
        func_800A4300(arg2, arg3);
        ((EntityRec *)arg1)->unk_10 = 0;
        ((EntityRec *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_s8 = 0;
    dungeonStatus.flags = (u16) (dungeonStatus.flags & 0xFF7F);
    temp_v1 = ((S_8008EAC8_1 *)arg3)->unk_64;
    if ((temp_v1 < 0) || (((Rec_func_8008ACDC_arg0 *)arg0)->unk_10C & 1)) {
        func_8008CAA0(arg0, arg1, arg2, arg3);
        return;
    }
    if (temp_v1 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }
    temp_v1_2 = ((S_8008EAC8_1 *)arg3)->unk_14;
    if (temp_v1_2 & 0x20000) {
        ((S_8008EAC8_1 *)arg3)->unk_14 = (s32) (temp_v1_2 & 0xFFFDFFFF);
    }
    if (!(((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0x10)) {
        func_8008C468(arg0, arg1, arg2, arg3);
        return;
    }
    temp_v1_3 = ((S_8008EAC8_1 *)arg3)->unk_1C;
    if (temp_v1_3 & 0x200) {
        func_80090200(arg0, arg1, arg2, arg3);
        return;
    }
    if (!(temp_v1_3 & 0x100000)) {
        call_arg = arg2;
        {
            void *callback = &D_8008ACDC;
            u8 *table = (u8 *) &D_800DCFB0;
            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_pv = callback;
            (*(u8 **)((u8 *)call_arg + (0x2C))) = table;
            func_80048A44(call_arg, *((u8 *) (((s32) (gameWork.view.viewAngle + (s16) ((S_8008EAC8_1 *)arg3)->unk_2A.u
                + 0x100) >> 9) & 7) + (u32) table), 0, 1);
        }
        return;
    }
    if ((((Rec_func_8008ACDC_arg0 *)arg0)->unk_124 != 0) && (((func_800A1C58(arg3) << 0x10) == 0)
        || (func_8008D1D0(arg0, arg1, arg2, arg3) == 0))) {
        if (!(dungeonStatus.flags & 4)) {
            if (((S_8008EAC8_1 *)arg3)->unk_1C & 0x20) {
                if (!((*(u16 *)0x80013714) & 1) && (((u32)held_D_80083160->buttons) & 0x80)) {
                    ((S_8008EAC8_1 *)arg3)->unk_8A = 2;
                    D_800E4940 = 2;
                    func_8008CF6C(arg0, arg1, arg2, &D_8004F5F4);
                    D_80082E80.unk_030 = 0;
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_C8 = 0;
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_104 = 0;
                    return;
                }
                func_8008C7B4(arg0, arg1, arg2, arg3);
                return;
            }
            if ((*(u16 *)0x80013714) & 1) {
                temp_v1_4 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2;
                ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = (u16) (temp_v1_4 & 0xFFFE);
                if (temp_v1_4 & 0x200) {
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = (u16) (temp_v1_4 & 0xFDFE);
                }
                temp_v0 = func_8009F868();
                if (temp_v0 != NULL) {
                    temp_angle = ((S_8008EAC8_6 *)temp_v0)->unk_01 & 7;
                    temp_a1 = ((S_8008EAC8_1 *)arg3)->unk_2A.u;
                    ASM_KEEP(temp_angle);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    temp_angle = (u8) temp_angle;
                    temp_a0 = temp_angle << 9;
                    temp_v1_5 = temp_a1 & 0xFFF;
                    temp_angle = temp_a0;
                    ASM_KEEP(temp_angle);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    ((S_8008EAC8_1 *)arg3)->unk_2A.u = temp_v1_5;
                    if (temp_v1_5 != temp_angle) {
                        s32 signed_target;
                        s32 diff;
                        {
                            s32 normalized;
                            if (temp_a1 & 0x800) {
                                normalized = temp_v1_5 | 0xF800;
                            } else {
                                normalized = temp_a1 & 0x7FF;
                            }
                            ((S_8008EAC8_1 *)arg3)->unk_2A.u = normalized;
                        }
                        {
                            if (temp_a0 & 0x800) {
                                diff = temp_a0 | 0xF800;
                            } else {
                                diff = temp_a0 & 0x7FF;
                            }
                            temp_a0 = diff;
                        }
                        temp_v1_5 = (u32) temp_a0 << 16;
                        signed_target = temp_v1_5 >> 16;
                        diff = ((S_8008EAC8_1 *)arg3)->unk_2A.s;
                        temp_v1_5 = ((S_8008EAC8_1 *)arg3)->unk_2A.u;
                        diff -= signed_target;
                        if (diff < 0) {
                            diff = 0 - diff;
                        }
                        if (diff >= 0x801) {
                            ((S_8008EAC8_1 *)arg3)->unk_2A.u = (u16) ((temp_a0 & ~0xFFF) | (temp_v1_5 & 0xFFF));
                        }
                        {
                            s32 step;
                            step = ((S_8008EAC8_1 *)arg3)->unk_2A.s;
                            temp_v1_5 = ((S_8008EAC8_1 *)arg3)->unk_2A.u;
                            step = signed_target < step;
                            if (step) {
                                step = temp_v1_5 - 0x200;
                            } else {
                                step = temp_v1_5 + 0x200;
                            }
                            ((S_8008EAC8_1 *)arg3)->unk_2A.u = step;
                        }
                        func_8009F988(temp_a0);
                        call_arg = arg2;
                        (*(u8 **)((u8 *)call_arg + (0x2C))) = D_800DD0B8;
                        func_80048A44(call_arg, *((u8 *) (((s32) (gameWork.view.viewAngle
                            + (s16) ((S_8008EAC8_1 *)arg3)->unk_2A.u + 0x100) >> 9) & 7) + (u32) D_800DD0B8), 0, 1);
                        return;
                    }
                    ((S_8008EAC8_10 *)(&D_800E3544))->unk_00 = (s8) (((S_8008EAC8_6 *)temp_v0)->unk_01 & 0xF8);
                    temp_code = *(u8 *) &D_800E3544;
                    switch (temp_code) {
                    case 0x10:
                        func_8008C7B4(arg0, arg1, arg2, arg3);
                        return;
                    case 0x48:
                        if (func_80095538(arg0, ((S_8008EAC8_6 *)temp_v0)->unk_00 & 0x1F,
                            ((S_8008EAC8_6 *)temp_v0)->unk_02 & 0x1F) >= 0) {
                            func_8009FAAC();
                            return;
                        }
                        func_8009F988();
                        return;
                    case 0x50:
                        temp_a0_2 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                        temp_v0 = (void *) ((u32) (temp_a0_2 & 0x60) >> 5);
                        temp_v0_2 = func_8009FADC(temp_a0_2 & 0x1F, temp_a1);
                        if (func_80098920(((S_8008EAC8_7 *)(((((u32) temp_v0) * 4) + arg0)))->unk_AC, temp_v0_2, 0x15,
                            0) < 0) {
                            func_8009F988();
                            return;
                        }
                        return;
                    case 0x68:
                        temp_v0_2 = func_8009FADC(((S_8008EAC8_6 *)temp_v0)->unk_00 & 0x1F, temp_a1);
                        temp_v1_7 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                        temp_v1_7 &= 0x60;
                        temp_v1_7 >>= 5;
                        func_80094270(arg0, arg1, arg2, (s32) temp_v0_2, temp_v1_7);
                        return;
                    case 0x88:
                        temp_v1_7 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                        temp_v1_7 &= 0x60;
                        temp_v1_7 >>= 5;
                        {
                            s32 fourth;
                            fourth = ((S_8008EAC8_8 *)(((temp_v1_7 * 4) + (u8 *)arg0)))->unk_D0;
                            func_80094270(arg0, arg1, arg2, fourth, temp_v1_7);
                        }
                        return;
                    case 0x70:
                        temp_a1_5 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                        func_80094548((u32) (temp_a1_5 & 0x60) >> 5, temp_a1_5 & 7);
                        return;
                    case 0x78:
                        temp_a1_2 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                        func_8009458C((u32) (temp_a1_2 & 0x60) >> 5, temp_a1_2 & 0x1F);
                        return;
                    case 0x80:
                        temp_a1_3 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                        func_800945C4((u32) (temp_a1_3 & 0x60) >> 5, temp_a1_3 & 0x1F);
                        return;
                    case 0x90:
                        temp_a1_4 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                        func_8009456C((u32) (temp_a1_4 & 0x60) >> 5, temp_a1_4 & 7);
                        return;
                    case 0x98:
                        temp_v0_2 = func_8009FADC(((S_8008EAC8_6 *)temp_v0)->unk_00 & 0x1F, temp_a1);
                        if (((S_8008EAC8_9 *)temp_v0_2)->unk_03 & 0x20) {
                            func_800956B8(arg0, arg1, arg2, temp_v0_2);
                            return;
                        }
                        func_80095854(arg0, arg1, arg2, temp_v0_2);
                        return;
                    case 0xA0:
                        func_8002534C(arg0, arg1, arg2, arg3);
                        return;
                    case 0xD8:
                        D_800DD830[((S_8008EAC8_6 *)temp_v0)->unk_00 & 0x7F](temp_a0, temp_a1);
                        return;
                    case 8:
                        code8_a0 = arg0;
                        func_8008C13C(code8_a0, arg1, arg2, arg3);
                        return;
                    case 0x28:
                        func_8008F6EC(arg0, arg1, arg2, arg3);
                        return;
                    case 0x30:
                        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_s16 = 6;
                        func_8008FA14(arg0, arg1, arg2, arg3);
                        return;
                    default:
                        return;
                    }
                }
            } else {
                s32 flag_200;

                flag_200 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0x200;
                ((S_8008EAC8_10 *)(&D_800E3544))->unk_00 = 0;
                if (flag_200 && ((func_800A2C34(arg3) << 0x10) == 0) && !(dungeonStatus.flags & 4)) {
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 =
                        (u16) (((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0xFDFF);
                    if ((func_800A4474(((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25) << 0x10)
                        != 0) {
                        func_8008CF6C(arg0, arg1, arg2, &D_800245A8);
                        return;
                        return;
                    }
                }
                if (((u32)held_D_80083160->buttons) & 0x80) {
                    func_8008CF6C(arg0, arg1, arg2, &D_80050CAC);
                    return;
                }
                if ((((u32)held_D_80083160->buttons) & 0x10) || !(((u32)held_D_80083160->buttons) & 3)
                    || (func_8008D024(arg0, arg1, arg2, (((u32) ((u32)held_D_80083160->buttons) >> 1) ^ 1) & 1, 0)
                    == 0)) {
                    temp_v0_3 = func_8009074C(((Rec_func_8008ACDC_arg0 *)arg0)->unk_9E, arg0 + 0xA2, arg3 + 0x2A);
                    if (temp_v0_3 != 0xFFF) {
                        ((S_8008EAC8_1 *)arg3)->unk_2A.u = (u16) temp_v0_3;
                        if (!(((u32)held_D_80083160->buttons) & 0x10)) {
                            temp_v1_6 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2;
                            if (!(temp_v1_6 & 0x400)) {
                                ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = (u16) (temp_v1_6 & 0xFFFE);
                                code8_a0 = arg0;
                                if (((S_8008EAC8_1 *)arg3)->unk_1C & 0x400) {
                                    ((S_8008EAC8_1 *)arg3)->unk_2A.u =
                                        (u16) (((S_8008EAC8_1 *)arg3)->unk_2A.u + (func_800A6D30(code8_a0) & 0xE00));
                                    do {
                                        code8_a0 = arg0;
                                    } while (0);
                                }
                                func_8008C13C(code8_a0, arg1, arg2, arg3);
                                return;
                            }
                        }
                    }
                    tail_data_flags = ((u32)held_D_80083160->buttons);
                    if ((tail_data_flags & 0x30) == 0x30) {
                        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 =
                            (u16) (((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0xFFFE);
                        func_8008C7B4(arg0, arg1, arg2, arg3);
                        return;
                    }
                    {
                        s32 flag40;

                        temp_v1_6 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2;
                        flag40 = temp_v1_6 & 0x40;
                        if (flag40) {
                            flag40 = tail_data_flags & 0x40;
                            if (flag40 == 0) {
                                ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = (u16) (temp_v1_6 & 0xFFBF);
                            }
                        } else if (tail_data_flags & 0x40) {
                            if (!(tail_data_flags & 0x20)) {
                                func_8008F6EC(arg0, arg1, arg2, arg3);
                                return;
                            }
                            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_s16 = 6;
                            func_8008FA14(arg0, arg1, arg2, arg3);
                            return;
                        }
                    }
                    call_arg = arg2;
                    (*(u8 **)((u8 *)call_arg + (0x2C))) = D_800DD0B8;
                    func_80048A44(call_arg, *((u8 *) (((s32) (gameWork.view.viewAngle
                        + (s16) ((S_8008EAC8_1 *)arg3)->unk_2A.u + 0x100) >> 9) & 7) + (u32) D_800DD0B8), 0, 1);
                }
            }
        } else {
            call_arg = arg2;
            (*(u8 **)((u8 *)call_arg + (0x2C))) = D_800DD0B8;
            func_80048A44(call_arg, *((u8 *) (((s32) (gameWork.view.viewAngle + (s16) ((S_8008EAC8_1 *)arg3)->unk_2A.u
                + 0x100) >> 9) & 7) + (u32) D_800DD0B8), 0, 1);
        }
    }
}

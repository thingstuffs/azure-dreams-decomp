#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

void func_80048A44(void *, u8, s32, s32);
s32 func_8004CAE8(s32, s32);
void func_80091934(void *, s32, void *, void *);
s32 func_800990FC(void);
s32 func_80099194(void *, s32);
void func_80099290(s32);
s32 func_8009929C(s32, s32);
s32 func_80099368(s32, s32);
s32 func_8009965C(s32, s32);
s32 func_80099734(void *, s32);
void func_800A56E0(s32);
void func_800A5720(s32);
void *func_800A8608(void *, s32, s32, s32, s32);
extern s32 D_80081484;
extern s16 D_80083160[];
extern s32 D_8008ACDC;
extern s32 D_8008D470;
extern u8 D_800DD100[];
extern u8 D_800E06E3[];
extern u8 D_800E06EB[];


typedef struct S_8009255C_1 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_8009255C_1;   /* base in func_8009255C */


typedef struct S_8009255C_3 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8009255C_3;   /* call_arg in func_8009255C */


typedef struct S_8009255C_5 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_8009255C_5;   /* temp_v0 in func_8009255C */

typedef struct S_8009255C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8009255C_6;   /* temp_v1_2 in func_8009255C */

typedef struct S_8009255C_7 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    void * unk_90;
    u8 pad_94[0x8];
    void * unk_9C;
    u8 pad_A0[0x8];
    s16 unk_A8;
    s16 unk_AA;
} S_8009255C_7;   /* temp_v1_3 in func_8009255C */

void func_8009255C(void *arg0, s32 arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    s32 temp_s0;
    s32 temp_v0_2;
    s32 temp_v1;
    void *temp_v0;
    S_8009255C_6 *temp_v1_2;
    S_8009255C_7 *temp_v1_3;
    void *page;
    volatile s16 *base;
    S_8009255C_3 *call_arg;
    u8 *entry;
    u8 *table;

    temp_v1 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8;
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state_0;
        }
        goto end;
    }
    if (temp_v1 == 2) {
        goto state_2;
    }
    goto end;

state_0:
    page = (void *)0x80080000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    base = (volatile s16 *)(page + 0x3160);
    if ((((((S_8009255C_1 *)base)->unk_C8 +
             arg3->unk_2A.as_s16 + 0x100) >> 9) & 7) == 2) {
        call_arg = arg2;
        ASM_KEEP(call_arg);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        table = D_800DD100;
        call_arg->unk_2C = table;
        entry = (u8 *)((s32)(((((S_8009255C_1 *)base)->unk_C8 +
                                arg3->unk_2A.as_s16 + 0x100) >> 9) &
                              7) +
                       (s32)table);
        func_80048A44(
            call_arg,
            *entry,
            0,
            1);
        goto increment;
    }
    arg3->unk_2A.as_s16 =
        (u16)arg3->unk_2A.as_s16 + 0x200;
    goto end;

state_1:
    if (func_8004CAE8(arg2->unk_08, 0) == 0) {
        goto end;
    }
    if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_110 == (s32)&D_80081484) {
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_124 = 0;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_1C &= 0xFFEFFFFF;
    }
    temp_v0 = func_800A8608(
        arg0 - 0x20, ((Rec_func_8008ACDC_arg0 *)arg0)->unk_110, 0, 0, 0);
    if (temp_v0 != NULL) {
        ((S_8009255C_5 *)temp_v0)->unk_10 = (s32)&D_8008D470;
        temp_v1_2 = ((S_8009255C_5 *)temp_v0)->unk_08;
        temp_v1_2->unk_02 =
            (arg2->unk_24 << 6) + 0x20;
        temp_v1_2->unk_06 =
            (arg2->unk_25 << 6) + 0x20;
        temp_v1_2->unk_0A =
            arg3->unk_88.as_u16 - 0x30;
        temp_v1_3 = temp_v0 + 0x20;
        temp_v1_3->unk_A8 = 0x1E;
        temp_v1_3->unk_AA = 2;
        temp_v1_3->unk_90 = arg2;
        temp_v1_3->unk_8C = arg1;
        temp_v1_3->unk_9C = arg0 + 0x108;
        temp_v0_2 = func_800990FC();
        temp_s0 = temp_v0_2;
        temp_v0_2 = func_8009929C(8, temp_v0_2);
        temp_v0_2 = func_80099734(arg3, temp_v0_2);
        temp_v0_2 = func_80099194(D_800E06E3, temp_v0_2);
        temp_v0_2 = func_80099368(
            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_110, temp_v0_2);
        temp_v0_2 = func_80099194(D_800E06EB, temp_v0_2);
        temp_v0_2 = func_8009965C(
            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_110, temp_v0_2);
        func_80099290(temp_v0_2);
        func_800A5720(temp_s0);
        func_800A56E0(0x509);
    }

increment:
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8++;
    goto end;

state_2:
    if ((arg2->unk_14.at00_u16.v & 0xE000) == 0) {
        goto end;
    }
    if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_110 != 0) {
        func_80091934(arg0, arg1, arg2, arg3);
        goto end;
    }
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_s32 = (s32)&D_8008ACDC;

end:
    return;
}

/* MECHANISM: True-space local joins restore retail block order and the increment path.
   A volatile held 0x80083160 base reproduces both loads; short-lived a0/v1 roles
   plus index-first entry arithmetic preserve the final addu destination. */

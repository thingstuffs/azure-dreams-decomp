#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8015C3C4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
} S_8015C3C4_0;   /* arg0 in func_8015C3C4 */

typedef struct S_8015C3C4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8015C3C4_1;   /* arg1 in func_8015C3C4 */





extern void *D_80158838[];

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_8015921C(void *, void *, void *, void *);
extern void func_801594FC(void *, void *, void *, void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_8015A4BC[];
extern u8 D_8015DDDC[8];
extern u8 D_8015DDE4[8];
extern u8 D_8015DDEC[8];

void func_8015C3C4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5
    };
    s16 timer;
    u8 state;

    state = ((S_8015C3C4_0 *)arg0)->unk_9B;
    if (state >= 6) {
        goto jt_c4;
    }
    (void)jt_keep;
    goto *D_80158838[state];

jt_c0:
    ((S_8015C3C4_1 *)arg1)->unk_14 = 0;
    ((S_8015C3C4_1 *)arg1)->unk_10 = 0;
    ((S_8015C3C4_1 *)arg1)->unk_0C = 0;
    ((S_8015C3C4_0 *)arg0)->unk_96.s = 0;
    ((S_8015C3C4_0 *)arg0)->unk_9B++;
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        goto jt_c4;
    }

jt_c1:
    timer = ((S_8015C3C4_0 *)arg0)->unk_96.s + 1;
    ((S_8015C3C4_0 *)arg0)->unk_96.s = timer;
    if ((timer != 4) && !(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        goto jt_c4;
    }
    ((S_8015C3C4_0 *)arg0)->unk_96.s = 0;
    ((S_8015C3C4_0 *)arg0)->unk_9B++;
    switch (((Rec_D_800E3D7C *)arg3)->unk_48.at00_u8.v) {
    case 13:
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8015DDDC;
        func_80047784(arg2,
            D_8015DDDC[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        goto jt_c4;
    case 14:
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8015DDE4;
        func_80047784(arg2,
            D_8015DDE4[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        goto jt_c4;
    case 15:
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8015DDEC;
        func_80047784(arg2,
            D_8015DDEC[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_8015C3C4_0 *)arg0)->unk_9B = 5;
        func_800A56E0(0x60C);
        goto jt_c4;
    default:
        goto jt_c4;
    }

jt_c2:
    timer = ((S_8015C3C4_0 *)arg0)->unk_96.s + 1;
    ((S_8015C3C4_0 *)arg0)->unk_96.s = timer;
    if ((timer == 5) || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
        ((S_8015C3C4_0 *)arg0)->unk_96.s = 0;
        ((S_8015C3C4_0 *)arg0)->unk_9B++;
    }
    if (((S_8015C3C4_0 *)arg0)->unk_96.u == 3) {
        func_800A56E0(0x804);
        goto jt_c4;
    }
    goto jt_c4;

jt_c3:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(arg3, 0x100);
        ((S_8015C3C4_0 *)arg0)->unk_8C = D_8015A4BC;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
    }
    goto jt_c4;

jt_c5:
    timer = ((S_8015C3C4_0 *)arg0)->unk_96.s + 1;
    ((S_8015C3C4_0 *)arg0)->unk_96.s = timer;
    if ((timer == 10) || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x0800;
        func_800A56E0(0x804);
        func_8015921C(arg0, arg1, arg2, arg3);
        func_801594FC(arg0, arg1, arg2, arg3);
    }
    if ((((S_8015C3C4_0 *)arg0)->unk_96.u == 12) ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16,
            ((S_8015C3C4_0 *)arg0)->unk_AA);
    }
    if ((((S_8015C3C4_0 *)arg0)->unk_96.u != 20) &&
        !(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        goto jt_c4;
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_8015C3C4_0 *)arg0)->unk_96.s = 0;
    ((S_8015C3C4_0 *)arg0)->unk_9B = 3;

jt_c4:
    return;
}

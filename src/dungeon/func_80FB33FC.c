#include "common.h"

typedef struct S_80172BFC_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172BFC_0;   /* arg0 in func_80172BFC */

typedef struct S_80172BFC_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172BFC_1;   /* arg2 in func_80172BFC */

typedef struct S_80172BFC_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172BFC_2;   /* arg3 in func_80172BFC */



extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(s32, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern s32 D_80170F6C;
extern u8 D_80175288[];

void func_80172BFC(void *arg0, s32 arg1, void *arg2, void *arg3) {
    s32 state;

    state = ((S_80172BFC_0 *)arg0)->unk_9B;
    ((S_80172BFC_0 *)arg0)->unk_96--;
    switch (state) {
        case 0:
            if (((S_80172BFC_1 *)arg2)->unk_14 & 0x8000) {
                ((S_80172BFC_0 *)arg0)->unk_9B = 0xFF;
                ((S_80172BFC_1 *)arg2)->unk_14 |= 0x6000;
                func_8009C12C(arg3, arg2, ((S_80172BFC_2 *)arg3)->unk_2A, 1);
                return;
            }
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80175288;
            func_80047784(arg2,
                D_80175288[((D_80083228 + ((S_80172BFC_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_80172BFC_0 *)arg0)->unk_9B++;
            return;

        case 1:
            if (((((S_80172BFC_1 *)arg2)->unk_04 == 3) &&
                 (((S_80172BFC_1 *)arg2)->unk_14 & 0x1000)) ||
                (((S_80172BFC_1 *)arg2)->unk_14 & 0x8000)) {
                func_800A56E0(0x804);
                func_8009C12C(arg3, arg2, ((S_80172BFC_2 *)arg3)->unk_2A, 1);
                ((S_80172BFC_0 *)arg0)->unk_9B = 0xFF;
            }
            return;

        case 0xFF:
            if (((S_80172BFC_1 *)arg2)->unk_14 & 0xE000) {
                func_800A2B04(arg1, ((S_80172BFC_1 *)arg2)->unk_24, ((S_80172BFC_1 *)arg2)->unk_25);
                func_800AD594(arg3, 0x100);
                ((S_80172BFC_0 *)arg0)->unk_8C = &D_80170F6C;
                D_8008346C = 0;
                func_800A4ACC(arg3);
                if (((S_80172BFC_2 *)arg3)->unk_6D == 0) {
                    ((S_80172BFC_2 *)arg3)->unk_46 &= 0x7FFF;
                    return;
                }
                D_800E3DE8 = (u8 *)arg3 - 0x20;
            }
            return;
    }
}

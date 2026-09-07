#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801727EC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801727EC_0;   /* arg0 in func_801727EC */





extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(s32, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern u8 D_80170EA8;
extern u8 D_80174060[];

void func_801727EC(void *arg0, s32 arg1, void *arg2, void *arg3) {
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = ((S_801727EC_0 *)arg0)->unk_9B;
    switch (temp_v1) {
    case 0:
        if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
            ((S_801727EC_0 *)arg0)->unk_9B = 1;
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
            ((S_801727EC_0 *)arg0)->unk_96 = 1;
            break;
        }
        ((S_801727EC_0 *)arg0)->unk_96 = 7;
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174060;
        func_80047784(arg2,
                     D_80174060[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                     0);
        ((S_801727EC_0 *)arg0)->unk_9B++;
        break;

    case 1:
        temp_v0 = ((S_801727EC_0 *)arg0)->unk_96 - 1;
        ((S_801727EC_0 *)arg0)->unk_96 = temp_v0;
        if (((temp_v0 << 16) == 0) || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
            func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
            func_800A56E0(0x804);
        }
        if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
            func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
            func_800AD594(arg3, 0x100);
            ((S_801727EC_0 *)arg0)->unk_8C = &D_80170EA8;
            D_8008346C = 0;
            func_800A4ACC(arg3);
            if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 == 0) {
                ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
            } else {
                D_800E3DE8 = (u8 *)arg3 - 0x20;
            }
        }
        break;
    }
}

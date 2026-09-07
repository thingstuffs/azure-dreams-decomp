#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801724F4_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_801724F4_0;   /* arg3 in func_801724F4 */

typedef struct S_801724F4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801724F4_1;   /* arg0 in func_801724F4 */





extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern s32 D_801711A4;
extern u8 D_8017419C[];
extern u8 D_801741A4[];

void func_801724F4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v1;
    s32 temp_a0;
    s32 state;

    temp_v1 = ((u16)((S_801724F4_0 *)arg3)->unk_2A.s >> 8) & 0xE;
    temp_s3 = *(s16 *)((u8 *)&D_8006CCD8 + temp_v1);
    temp_s4 = *(s16 *)((u8 *)&D_8006CCE8 + temp_v1);
    state = ((S_801724F4_1 *)arg0)->unk_9B;
    temp_a0 = ((S_801724F4_1 *)arg0)->unk_96 - 1;
    ((S_801724F4_1 *)arg0)->unk_96 = temp_a0;

    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto done;

state_zero:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_801724F4_1 *)arg0)->unk_9B = 0xFF;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(arg3, arg2, ((S_801724F4_0 *)arg3)->unk_2A.u, 1);
        goto done;
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_8017419C;
    func_80047784(arg2,
        D_8017419C[((D_80083228 + ((S_801724F4_0 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    goto increment_state;

state_one:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_801741A4;
        func_80047784(arg2,
            D_801741A4[((D_80083228 + ((S_801724F4_0 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
            0);
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = (temp_s3 << 18) + (temp_s3 << 17);
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = (temp_s4 << 18) + (temp_s4 << 17);
        ((S_801724F4_1 *)arg0)->unk_96 = 8;
        func_800A56E0(0x607);
increment_state:
        ((S_801724F4_1 *)arg0)->unk_9B++;
    }
    goto done;

state_two:
    if ((temp_a0 << 16) <= 0) {
        func_8009C12C(arg3, arg2, ((S_801724F4_0 *)arg3)->unk_2A.u, 1);
        ((S_801724F4_1 *)arg0)->unk_9B = 0xFF;
    }
    goto done;

state_ff:
    {
        s32 coord = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
        s32 current = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = ((coord - current) << 0xF) >> 1;
    }
    {
        s32 coord = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
        s32 current = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = ((coord - current) << 0xF) >> 1;
    }
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        ((S_801724F4_0 *)arg3)->unk_1C |= 0x40000;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        func_800AD594(arg3, 0x100);
        ((S_801724F4_1 *)arg0)->unk_8C = &D_801711A4;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        if (((S_801724F4_0 *)arg3)->unk_6D == 0) {
            ((S_801724F4_0 *)arg3)->unk_46 &= 0x7FFF;
        } else {
            D_800E3DE8 = (u8 *)arg3 - 0x20;
        }
    }

done:
    return;
}

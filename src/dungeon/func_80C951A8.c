#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801729A8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801729A8_0;   /* arg0 in func_801729A8 */



typedef struct S_801729A8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801729A8_3;   /* arg1 in func_801729A8 */



extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_8017102C[];
extern u8 D_801752DC[];

void func_801729A8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 next_state;
    s32 one;
    u16 timer;

    state = ((S_801729A8_0 *)arg0)->unk_9B;
    one = 1;
    if (state == one) {
        goto state_1;
    }
    if (!(state < 2)) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    goto end;

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    ((S_801729A8_0 *)arg0)->unk_9B = one;

state_1:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_801729A8_0 *)arg0)->unk_9B = 3;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
        goto end;
    }

    ((S_801729A8_3 *)arg1)->unk_14 = 0;
    ((S_801729A8_3 *)arg1)->unk_10 = 0;
    ((S_801729A8_3 *)arg1)->unk_0C = 0;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801752DC;
    func_80047784(arg2,
        D_801752DC[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    next_state = ((S_801729A8_0 *)arg0)->unk_9B;
    ((S_801729A8_0 *)arg0)->unk_96.s = 0;
    goto bump_state;

state_2:
    timer = ((S_801729A8_0 *)arg0)->unk_96.s + 1;
    ((S_801729A8_0 *)arg0)->unk_96.s = timer;
    if ((s16)timer == 7 || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
    }
    if (((S_801729A8_0 *)arg0)->unk_96.u == 6) {
        func_800A56E0(0x808);
    }
    if (((S_801729A8_0 *)arg0)->unk_96.u == 8) {
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x0800;
    }
    if (((S_801729A8_0 *)arg0)->unk_96.u == 15 ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
        next_state = ((S_801729A8_0 *)arg0)->unk_9B;
        goto bump_state;
    }
    goto end;

bump_state:
    next_state++;
    ((S_801729A8_0 *)arg0)->unk_9B = next_state;
    goto end;

state_3:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(arg3, 0x100);
        ((S_801729A8_0 *)arg0)->unk_8C = D_8017102C;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
    }

end:
    return;
}

#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern s32 D_80171728;
extern u8 D_80174E1C[];


typedef struct S_80172FD8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172FD8_0;   /* arg0 in func_80172FD8 */



typedef struct S_80172FD8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172FD8_3;   /* arg1 in func_80172FD8 */

/* Advances an actor's timed animation sequence and performs its final cleanup. */
void func_80172FD8(void *sequence, void *motion, void *sprite, void *actor)
{
    u8 state;
    static void *const state_labels[] = { &&initialize, &&wait_animation, &&wait_transition, &&wait_effect, &&finish };

    state = ((S_80172FD8_0 *)sequence)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    goto *(((void **)D_80170838)[state]);

initialize:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172FD8_0 *)sequence)->unk_9B = 4;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
        return;
    }
    ((S_80172FD8_3 *)motion)->unk_14 = 0;
    ((S_80172FD8_3 *)motion)->unk_10 = 0;
    ((S_80172FD8_3 *)motion)->unk_0C = 0;
    goto advance_state;
    return;

wait_animation:
    if ((s16)++((S_80172FD8_0 *)sequence)->unk_96.u == 4 ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        (*(u8 **)((u8 *)sprite + 0x2C)) = D_80174E1C;
        func_80047784(sprite,
            D_80174E1C[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        goto advance_state;
    }
    return;

wait_transition:
    if ((s16)++((S_80172FD8_0 *)sequence)->unk_96.u == 9 ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
        ((S_80172FD8_0 *)sequence)->unk_96.u = 0;
        ((S_80172FD8_0 *)sequence)->unk_9B++;
    }
    if (((S_80172FD8_0 *)sequence)->unk_96.s == 6) {
        func_800A56E0(0x808);
        return;
    }
    return;

wait_effect:
    if ((s16)++((S_80172FD8_0 *)sequence)->unk_96.u == 6) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
    }
    if (((S_80172FD8_0 *)sequence)->unk_96.s == 15 ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
advance_state:
        ((S_80172FD8_0 *)sequence)->unk_96.u = 0;
        ((S_80172FD8_0 *)sequence)->unk_9B++;
        return;
    }
    return;

finish:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(actor, 0x100);
        ((S_80172FD8_0 *)sequence)->unk_8C = &D_80171728;
        D_8008346C = 0;
        func_800A4ACC(actor);
        ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
    }
}

#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801623C4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
} S_801623C4_0;   /* arg0 in func_801623C4 */

typedef struct S_801623C4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801623C4_1;   /* arg1 in func_801623C4 */





extern void *D_8015E838[];

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_8015F21C(void *, void *, void *, void *);
extern void func_8015F4FC(void *, void *, void *, void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_801604BC[];
extern u8 D_80163DDC[8];
extern u8 D_80163DE4[8];
extern u8 D_80163DEC[8];

/* Advance the actor's timed action sequence and update its animation and effects. */
void func_801623C4(void *action, void *motion, void *animation, void *actor)
{
    static void *const state_labels[] = {
        &&initialize, &&select_animation, &&wait_action, &&finish_action, &&done, &&special_action
    };
    s16 timer;
    u8 state;

    state = ((S_801623C4_0 *)action)->unk_9B;
    if (state >= 6) {
        goto done;
    }
    (void)state_labels;
    goto *D_8015E838[state];

initialize:
    ((S_801623C4_1 *)motion)->unk_14 = 0;
    ((S_801623C4_1 *)motion)->unk_10 = 0;
    ((S_801623C4_1 *)motion)->unk_0C = 0;
    ((S_801623C4_0 *)action)->unk_96.s = 0;
    ((S_801623C4_0 *)action)->unk_9B++;
    if (!(((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
        goto done;
    }

select_animation:
    timer = ((S_801623C4_0 *)action)->unk_96.s + 1;
    ((S_801623C4_0 *)action)->unk_96.s = timer;
    if ((timer != 4) && !(((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
        goto done;
    }
    ((S_801623C4_0 *)action)->unk_96.s = 0;
    ((S_801623C4_0 *)action)->unk_9B++;
    switch (((Rec_D_800E3D7C *)actor)->unk_48.at00_u8.v) {
    case 13:
        (*(u8 * *)((u8 *)animation + 0x2C)) = D_80163DDC;
        func_80047784(animation,
            D_80163DDC[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        goto done;
    case 14:
        (*(u8 * *)((u8 *)animation + 0x2C)) = D_80163DE4;
        func_80047784(animation,
            D_80163DE4[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        goto done;
    case 15:
        (*(u8 * *)((u8 *)animation + 0x2C)) = D_80163DEC;
        func_80047784(animation,
            D_80163DEC[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_801623C4_0 *)action)->unk_9B = 5;
        func_800A56E0(0x60C);
        goto done;
    default:
        goto done;
    }

wait_action:
    timer = ((S_801623C4_0 *)action)->unk_96.s + 1;
    ((S_801623C4_0 *)action)->unk_96.s = timer;
    if ((timer == 5) || (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, animation, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
        ((S_801623C4_0 *)action)->unk_96.s = 0;
        ((S_801623C4_0 *)action)->unk_9B++;
    }
    if (((S_801623C4_0 *)action)->unk_96.u == 3) {
        func_800A56E0(0x804);
        goto done;
    }
    goto done;

finish_action:
    if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(actor, 0x100);
        ((S_801623C4_0 *)action)->unk_8C = D_801604BC;
        D_8008346C = 0;
        func_800A4ACC(actor);
        ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
    }
    goto done;

special_action:
    timer = ((S_801623C4_0 *)action)->unk_96.s + 1;
    ((S_801623C4_0 *)action)->unk_96.s = timer;
    if ((timer == 10) || (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
        ((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v |= 0x0800;
        func_800A56E0(0x804);
        func_8015F21C(action, motion, animation, actor);
        func_8015F4FC(action, motion, animation, actor);
    }
    if ((((S_801623C4_0 *)action)->unk_96.u == 12) ||
        (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, animation, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16,
            ((S_801623C4_0 *)action)->unk_AA);
    }
    if ((((S_801623C4_0 *)action)->unk_96.u != 20) &&
        !(((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
        goto done;
    }
    ((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_801623C4_0 *)action)->unk_96.s = 0;
    ((S_801623C4_0 *)action)->unk_9B = 3;

done:
    return;
}

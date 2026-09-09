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
extern u8 D_80170870[20];
extern s32 D_80171CE8;
extern u8 D_80174EE0[];


typedef struct S_80173514_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173514_0;   /* arg0 in func_80173514 */


typedef struct S_80173514_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173514_2;   /* arg1 in func_80173514 */


/* Advance a timed sprite flashing sequence and clean up the actor when it finishes. */
void func_80173514(void *action, void *motion, void *sprite, void *actor)
{
    u8 state;
    void *call_actor;
    void *call_sprite;
    static void *const state_labels[] = { &&init, &&wait_start, &&first_flash, &&second_flash, &&finish };

    state = ((S_80173514_0 *)action)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    goto *(((void **)D_80170870)[state]);

init:
    {
        call_actor = actor;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80173514_0 *)action)->unk_9B = 4;
            call_sprite = sprite;
            ((Rec_D_80082E80 *)call_sprite)->unk_14.at00_u16.v |= 0x6000;
            goto call_tail;
        }
        ((S_80173514_2 *)motion)->unk_14 = 0;
        ((S_80173514_2 *)motion)->unk_10 = 0;
        ((S_80173514_2 *)motion)->unk_0C = 0;
        (*(u8 **)((u8 *)sprite + 0x2C)) = D_80174EE0;
        func_80047784(sprite,
            D_80174EE0[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_80173514_0 *)action)->unk_96.u = 0;
        ((S_80173514_0 *)action)->unk_9B++;
        return;
    }

wait_start:
    if ((s16)++((S_80173514_0 *)action)->unk_96.u == 5) {
        ((S_80173514_0 *)action)->unk_96.u = 0;
        ((S_80173514_0 *)action)->unk_9B++;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
        return;
    }
    return;

first_flash:
    if ((s16)++((S_80173514_0 *)action)->unk_96.u == 6 ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        ((S_80173514_0 *)action)->unk_96.u = 0;
        ((S_80173514_0 *)action)->unk_9B++;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        func_800A56E0(0x804);
        return;
    }
    return;

second_flash:
    if ((s16)++((S_80173514_0 *)action)->unk_96.u == 5 ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
    }
    if (((S_80173514_0 *)action)->unk_96.s == 12 ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        ((S_80173514_0 *)action)->unk_96.u = 0;
        ((S_80173514_0 *)action)->unk_9B++;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
    }
    call_actor = actor;
    if (((S_80173514_0 *)action)->unk_96.s == 1 ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        call_sprite = sprite;
call_tail:
        func_8009C12C(call_actor, call_sprite, ((Rec_D_800E3D7C *)call_actor)->unk_2A.as_s16, 1);
        return;
    }
    return;

finish:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(actor, 0x100);
        ((S_80173514_0 *)action)->unk_8C = &D_80171CE8;
        D_8008346C = 0;
        func_800A4ACC(actor);
        ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
    }
}

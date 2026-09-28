#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801503C4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
} S_801503C4_0;   /* arg0 in func_801503C4 */

typedef struct S_801503C4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801503C4_1;   /* arg1 in func_801503C4 */





extern void *D_8014C838[];

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_8014D21C(void *, void *, void *, void *);
extern void func_8014D4FC(void *, void *, void *, void *);

extern u8 D_8014E4BC[];
extern u8 D_80151DDC[8];
extern u8 D_80151DE4[8];
extern u8 D_80151DEC[8];

/* Advance the timed action sequence, updating animation and playing sounds. */
void func_801503C4(void *action, void *motion, void *sprite, void *actor)
{
    static void *const state_labels[] = {
        &&init_action, &&start_animation, &&wait_action, &&finish_action, &&done, &&special_action
    };
    s16 timer;
    u8 state;

    state = ((S_801503C4_0 *)action)->unk_9B;
    if (state >= 6) {
        goto done;
    }
    (void)state_labels;
    goto *D_8014C838[state];

init_action:
    ((S_801503C4_1 *)motion)->unk_14 = 0;
    ((S_801503C4_1 *)motion)->unk_10 = 0;
    ((S_801503C4_1 *)motion)->unk_0C = 0;
    ((S_801503C4_0 *)action)->unk_96.s = 0;
    ((S_801503C4_0 *)action)->unk_9B++;
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        goto done;
    }

start_animation:
    timer = ((S_801503C4_0 *)action)->unk_96.s + 1;
    ((S_801503C4_0 *)action)->unk_96.s = timer;
    if ((timer != 4) && !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        goto done;
    }
    ((S_801503C4_0 *)action)->unk_96.s = 0;
    ((S_801503C4_0 *)action)->unk_9B++;
    switch (((EntityRec *)actor)->unk_48) {
    case 13:
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80151DDC;
        func_80047784(sprite,
            D_80151DDC[((gameWork.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        goto done;
    case 14:
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80151DE4;
        func_80047784(sprite,
            D_80151DE4[((gameWork.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        goto done;
    case 15:
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80151DEC;
        func_80047784(sprite,
            D_80151DEC[((gameWork.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((S_801503C4_0 *)action)->unk_9B = 5;
        func_800A56E0(0x60C);
        goto done;
    default:
        goto done;
    }

wait_action:
    timer = ((S_801503C4_0 *)action)->unk_96.s + 1;
    ((S_801503C4_0 *)action)->unk_96.s = timer;
    if ((timer == 5) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
        ((S_801503C4_0 *)action)->unk_96.s = 0;
        ((S_801503C4_0 *)action)->unk_9B++;
    }
    if (((S_801503C4_0 *)action)->unk_96.u == 3) {
        func_800A56E0(0x804);
        goto done;
    }
    goto done;

finish_action:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(actor, 0x100);
        ((S_801503C4_0 *)action)->unk_8C = D_8014E4BC;
        dungeonStatus.unk_0C = 0;
        func_800A4ACC(actor);
        ((EntityRec *)actor)->unk_46 &= 0x7FFF;
    }
    goto done;

special_action:
    timer = ((S_801503C4_0 *)action)->unk_96.s + 1;
    ((S_801503C4_0 *)action)->unk_96.s = timer;
    if ((timer == 10) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
        func_800A56E0(0x804);
        func_8014D21C(action, motion, sprite, actor);
        func_8014D4FC(action, motion, sprite, actor);
    }
    if ((((S_801503C4_0 *)action)->unk_96.u == 12) ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing,
            ((S_801503C4_0 *)action)->unk_AA);
    }
    if ((((S_801503C4_0 *)action)->unk_96.u != 20) &&
        !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        goto done;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_801503C4_0 *)action)->unk_96.s = 0;
    ((S_801503C4_0 *)action)->unk_9B = 3;

done:
    return;
}

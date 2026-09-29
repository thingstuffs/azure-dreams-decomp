#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern u8 D_80170838[16];
extern u8 D_801716F4[];
extern u8 D_80175584[];


typedef struct S_80172F94_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F94_0;   /* arg0 in func_80172F94 */



typedef struct S_80172F94_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172F94_3;   /* arg1 in func_80172F94 */

/* Advances an actor's timed animation sequence and handles its completion. */
void func_80172F94(void *action, void *motion, void *sprite, EntityRec *actor)
{
    u8 state;
    static void *const state_labels[] = { &&start_action, &&wait_animation, &&start_followup, &&wait_followup, &&finish_action };

    state = ((S_80172F94_0 *)action)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    goto *(((void **)D_80170838)[state]);

start_action:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172F94_0 *)action)->unk_9B = 4;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(actor, sprite, actor->facing, 1);
        return;
    }
    ((S_80172F94_3 *)motion)->unk_14 = 0;
    ((S_80172F94_3 *)motion)->unk_10 = 0;
    ((S_80172F94_3 *)motion)->unk_0C = 0;
    goto advance_state;

wait_animation:
    if ((s16)++((S_80172F94_0 *)action)->unk_96.u == 4 ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80175584;
        func_80047784(sprite,
            D_80175584[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
    }
    if (((S_80172F94_0 *)action)->unk_96.s == 7 ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
advance_state:
        ((S_80172F94_0 *)action)->unk_96.u = 0;
        ((S_80172F94_0 *)action)->unk_9B++;
        return;
    }
    return;

start_followup:
    ((S_80172F94_0 *)action)->unk_96.u = 0;
    ((S_80172F94_0 *)action)->unk_9B++;

wait_followup:
    if ((s16)++((S_80172F94_0 *)action)->unk_96.u == 7 ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, sprite, actor->facing, 1);
    }

finish_action:
    if (((S_80172F94_0 *)action)->unk_96.s == 3) {
        func_800A56E0(0x814);
    }
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(actor, 0x100);
        ((S_80172F94_0 *)action)->unk_8C = D_801716F4;
        dungeonStatus.unk_0C = 0;
        func_800A4ACC(actor);
        actor->unk_46 &= 0x7FFF;
    }
    return;
}

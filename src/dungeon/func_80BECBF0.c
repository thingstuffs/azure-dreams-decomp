#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801723F0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801723F0_0;   /* arg0 in func_801723F0 */


typedef struct S_801723F0_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801723F0_3;   /* arg1 in func_801723F0 */


extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern u8 D_80171014[];
extern u8 D_8017423C[];

/* Advance the actor action animation and restore actor state when it finishes. */
void func_801723F0(void *action, void *motion, void *anim, void *actor) {
    s32 state;
    u16 ticks;

    state = ((S_801723F0_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        ((S_801723F0_0 *)action)->unk_9B = 1;
    case 1:
        if (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0x8000) {
            ((S_801723F0_0 *)action)->unk_9B = 3;
            ((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, anim, ((EntityRec *)actor)->facing, 1);
            return;
        }
        ((S_801723F0_3 *)motion)->unk_14 = 0;
        ((S_801723F0_3 *)motion)->unk_10 = 0;
        ((S_801723F0_3 *)motion)->unk_0C = 0;
        (*(u8 * *)((u8 *)anim + 0x2C)) = D_8017423C;
        func_80047784(anim,
            D_8017423C[((s32)(gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((S_801723F0_0 *)action)->unk_96 = 0;
        ((S_801723F0_0 *)action)->unk_9B++;
        func_800A56E0(0x804);
        return;
    case 2:
        ticks = ((S_801723F0_0 *)action)->unk_96 + 1;
        ((S_801723F0_0 *)action)->unk_96 = ticks;
        if (((s16)ticks == 8) || (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0x8000)) {
            func_8009C12C(actor, anim, ((EntityRec *)actor)->facing, 1);
        }
    case 3:
        if (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0xE000) {
            func_800AD594(actor, 0x100);
            ((S_801723F0_0 *)action)->unk_8C = D_80171014;
            dungeonStatus.unk_0C = 0;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            func_800A4ACC(actor);
        }
    default:
        break;
    }
}

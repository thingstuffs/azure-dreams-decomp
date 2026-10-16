#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801727EC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801727EC_0;   /* arg0 in dungeonAdvanceTimedDirectionalAnimation */


extern void func_80047784(void *, u8, s32);
extern void dungeonResolveAttackDamageAndEffects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void dungeonSetRecordIntegerTileCenter(s32, u8, u8);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(void *, s32);

extern void *D_800E3DE8;
extern u8 D_80170EA8;
extern u8 D_80174060[];

/* Advances a timed directional animation and updates the actor when it completes. */
void dungeonAdvanceTimedDirectionalAnimation(void *action_state, s32 actor_id, void *animation, EntityRec *actor) {
    u16 ticks_left;
    u8 phase;

    phase = ((S_801727EC_0 *)action_state)->unk_9B;
    switch (phase) {
    case 0:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000) {
            ((S_801727EC_0 *)action_state)->unk_9B = 1;
            ((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v |= 0x6000;
            ((S_801727EC_0 *)action_state)->unk_96 = 1;
            break;
        }
        ((S_801727EC_0 *)action_state)->unk_96 = 7;
        (*(u8 * *)((u8 *)animation + 0x2C)) = D_80174060;
        func_80047784(animation,
                      D_80174060[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        ((S_801727EC_0 *)action_state)->unk_9B++;
        break;

    case 1:
        ticks_left = ((S_801727EC_0 *)action_state)->unk_96 - 1;
        ((S_801727EC_0 *)action_state)->unk_96 = ticks_left;
        if (((ticks_left << 16) == 0) || (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
            dungeonResolveAttackDamageAndEffects(actor, animation, actor->facing, 1);
            func_800A56E0(0x804);
        }
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
            dungeonSetRecordIntegerTileCenter(actor_id, ((Rec_D_80082E80 *)animation)->unk_24, ((Rec_D_80082E80 *)animation)->unk_25);
            dungeonReduceActorFoodMeter(actor, 0x100);
            ((S_801727EC_0 *)action_state)->unk_8C = &D_80170EA8;
            dungeonStatus.unk_0C = 0;
            dungeonAdvanceStatusTimers(actor);
            if (actor->unk_6D == 0) {
                actor->unk_46 &= 0x7FFF;
            } else {
                D_800E3DE8 = (u8 *)actor - 0x20;
            }
        }
        break;
    }
}

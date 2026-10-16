/* Relink of matched dungeon/func_80CC1C80; every changed retail word is a paired relocation. */
#define D_80173B98 D_80167B98
#define D_80176320 D_8016A320
#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/object_node.h"

#ifndef DUNGEON_ACTOR_ITEM_SLOTS_VIEW
#define DUNGEON_ACTOR_ITEM_SLOTS_VIEW
/* Three adjacent 3-byte action records begin at +0x08. */
typedef struct ActorItemSlotsView {
    u8 pad_00[8];
    u8 slots[3][3];
} ActorItemSlotsView;
#endif

#ifndef DUNGEON_ACTOR_ACTION_BYTES_VIEW
#define DUNGEON_ACTOR_ACTION_BYTES_VIEW
typedef struct ActorActionBytesView {
    u8 pad_00[0x1C];
    u32 flags;
    u8 pad_20[0xA];
    s16 facing;
    u8 pad_2C[0x1A];
    u16 actionFlags;
    u8 pad_48[0x18];
    void *target;
    u8 pad_64[0x9];
    u8 remainingActions;
    u8 pad_6E[4];
    u8 targetX;
    u8 targetY;
} ActorActionBytesView;
#endif

#ifndef DUNGEON_PLAYER_ACTION_COUNT_VIEW
#define DUNGEON_PLAYER_ACTION_COUNT_VIEW
typedef struct PlayerActionCountView {
    u8 pad_00[0xA6];
    u16 remainingActions;
} PlayerActionCountView;
#endif

extern int abs(int);
extern s32 getCdCommandQueueDepth(void);
extern void func_80047784(void *, s32, s32);
extern void *dungeonScanMonsterAlongHeading(void *, u8, u8, s16, s32);
extern void dungeonSetRecordIntegerTileCenter(void *, u8, u8);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A56E0(s32);
extern s32 dungeonCreateActorSpellEffect(void *, u8 *, s32, void *);
extern void dungeonCreateActorLinkedEffect(void *);

extern u8 D_80167B98[];
extern u8 D_8016A320[];

typedef struct ItemActionState {
    u8 pad_00[0x8C];
    void * nextBehavior;
    u8 pad_90[0x6];
    u16 timer;
    u16 flags;
    u8 pad_9A[0x1];
    u8 phase;
} ItemActionState;

typedef struct TargetTileView {
    u8 pad_00[0x24];
    u8 tileX;
    u8 tileY;
} TargetTileView;

typedef struct DungeonActionStatusView {
    u8 pad_00[0xA];
    u16 activeActions;
    s32 actionBusy;
} DungeonActionStatusView;

void func_80169480(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 special;
    u8 *item_slot;
    u8 phase;
    void *target;
    u8 *target_sprite;

    special = 0;
    phase = ((ItemActionState *)action)->phase;
    switch (phase) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch ((actor->unk_46 & 0x3FFF)) {
            case 7:
                special = 1;
                /* fallthrough */
            case 3:
                item_slot = ((ActorItemSlotsView *)actor)->slots[2];
                break;
            case 6:
                special = 1;
                /* fallthrough */
            case 2:
                item_slot = ((ActorItemSlotsView *)actor)->slots[1];
                break;
            case 5:
                special = 1;
                /* fallthrough */
            case 1:
                item_slot = ((ActorItemSlotsView *)actor)->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                item_slot = ((ActorItemSlotsView *)actor)->slots[2];
                break;
            case 2:
                item_slot = ((ActorItemSlotsView *)actor)->slots[1];
                break;
            case 1:
                item_slot = ((ActorItemSlotsView *)actor)->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            ((ItemActionState *)action)->flags &= 0xFF7F;
            {
                s16 special_test;

                special_test = special;
                if (special_test != 0) {
                    target = D_800814A8;
                    actor->target = target;
                    target_sprite = ((ObjectNodeHeader *)((u8 *)target - 0x20))->unk_0C;
                    ((ActorActionBytesView *)actor)->targetX = ((TargetTileView *)target_sprite)->tileX;
                    ((ActorActionBytesView *)actor)->targetY = ((TargetTileView *)target_sprite)->tileY;
                } else {
                    u8 item_id;

                    item_id = *item_slot;
                    if (D_8006DE24[item_id].kind == 2) {
                        target = actor->target;
                        if (target != 0) {
                            target_sprite = ((ObjectNodeHeader *)((u8 *)target - 0x20))->unk_0C;
                            ((ActorActionBytesView *)actor)->targetX = ((TargetTileView *)target_sprite)->tileX;
                            ((ActorActionBytesView *)actor)->targetY = ((TargetTileView *)target_sprite)->tileY;
                        }
                    } else {

                        actor->target = dungeonScanMonsterAlongHeading(
                            actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                            actor->facing, 0x10);
                        actor->unk_72 = abs(actor->unk_72);
                        actor->unk_73 = abs(actor->unk_73);
                    }
                }
            }

            if (dungeonCreateActorSpellEffect(actor, item_slot, special,
                              &((ItemActionState *)action)->flags) == 0) {
                return;
            }
            dungeonCreateActorLinkedEffect(actor);
            ((ItemActionState *)action)->phase++;
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        ((PlayerActionCountView *)D_800814A8)->remainingActions--;
        dungeonAdvanceStatusTimers(actor);
        ((ActorActionBytesView *)actor)->remainingActions--;
        ((ItemActionState *)action)->nextBehavior = D_80167B98;
        ((ActorActionBytesView *)actor)->targetY = 0;
        ((ActorActionBytesView *)actor)->targetX = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (getCdCommandQueueDepth()) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((ItemActionState *)action)->phase++;

    case 2:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 7 &&
             (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((ItemActionState *)action)->timer = 1;
            ((ItemActionState *)action)->flags |= 0x80;
        }
        {
            s16 timer;

            timer = ((ItemActionState *)action)->timer - 1;
            ((ItemActionState *)action)->timer = timer;
            if (timer <= 0) {
                ((ItemActionState *)action)->timer = 0;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            }
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_8016A320) {
            u8 *anim_table;
            s32 direction;

            anim_table = D_8016A320;
            ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 = anim_table;
            direction = ((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7;
            func_80047784(sprite, anim_table[direction], 0);
        }
        {
            target_sprite = (u8 *)&dungeonStatus.unk_00;
            if (((DungeonActionStatusView *)target_sprite)->actionBusy != 0) {
                return;
            }
            ((DungeonActionStatusView *)target_sprite)->activeActions--;
            ((ItemActionState *)action)->nextBehavior = D_80167B98;
            dungeonAdvanceStatusTimers(actor);
            ((ActorActionBytesView *)actor)->targetY = 0;
            ((ActorActionBytesView *)actor)->targetX = 0;
            ((ActorActionBytesView *)actor)->remainingActions--;
            actor->unk_46 &= 0x7FFF;
            func_800A56E0(0xB4);
        }

        return;
    default:
        return;
    }
}

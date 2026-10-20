#include "common.h"
#include "shared/sprite_frame_state.h"
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
extern s32 get_cd_command_queue_depth(void);
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, u8 *, s32, void *);
extern void create_actor_linked_effect(void *);

extern u8 D_80173B98[];
extern u8 D_80176320[];

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

void func_80175480(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
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

                        actor->target = scan_monster_along_heading(
                            actor, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                            actor->facing, 0x10);
                        actor->unk_72 = abs(actor->unk_72);
                        actor->unk_73 = abs(actor->unk_73);
                    }
                }
            }

            if (create_actor_spell_effect(actor, item_slot, special,
                              &((ItemActionState *)action)->flags) == 0) {
                return;
            }
            create_actor_linked_effect(actor);
            ((ItemActionState *)action)->phase++;
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        g_dungeon_status.active_actor = 0;
        ((PlayerActionCountView *)D_800814A8)->remainingActions--;
        advance_status_timers(actor);
        ((ActorActionBytesView *)actor)->remainingActions--;
        ((ItemActionState *)action)->nextBehavior = D_80173B98;
        ((ActorActionBytesView *)actor)->targetY = 0;
        ((ActorActionBytesView *)actor)->targetX = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            return;
        }
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((ItemActionState *)action)->phase++;

    case 2:
        if ((((SpriteFrameState *)sprite)->unk_04 == 7 &&
             (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0xE000)) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            ((ItemActionState *)action)->timer = 1;
            ((ItemActionState *)action)->flags |= 0x80;
        }
        {
            s16 timer;

            timer = ((ItemActionState *)action)->timer - 1;
            ((ItemActionState *)action)->timer = timer;
            if (timer <= 0) {
                ((ItemActionState *)action)->timer = 0;
                ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            }
        }
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != D_80176320) {
            u8 *anim_table;
            s32 direction;

            anim_table = D_80176320;
            ((SpriteFrameState *)sprite)->frameTable = anim_table;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, anim_table[direction], 0);
        }
        {
            target_sprite = (u8 *)&g_dungeon_status.turn_scale;
            if (((DungeonActionStatusView *)target_sprite)->actionBusy != 0) {
                return;
            }
            ((DungeonActionStatusView *)target_sprite)->activeActions--;
            ((ItemActionState *)action)->nextBehavior = D_80173B98;
            advance_status_timers(actor);
            ((ActorActionBytesView *)actor)->targetY = 0;
            ((ActorActionBytesView *)actor)->targetX = 0;
            ((ActorActionBytesView *)actor)->remainingActions--;
            actor->unk_46 &= 0x7FFF;
            play_sound_if_enabled(0xB4);
        }

        return;
    default:
        return;
    }
}

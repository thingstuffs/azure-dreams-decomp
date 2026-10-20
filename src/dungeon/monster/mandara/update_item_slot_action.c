#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
extern int abs(int);

typedef struct ItemSlots {
    u8 pad_00[8];
    u8 first;
    u8 pad_09[2];
    u8 second;
    u8 pad_0C[2];
    u8 third;
} ItemSlots;

typedef struct PlayerActionCounter {
    u8 pad_00[0xA6];
    u16 pendingActions;
} PlayerActionCounter;



typedef struct ActionState {
    u8 pad_00[0x8C];
    void * handler;
    u8 pad_90[0x6];
    u16 ticks;
    u16 flags;
    u8 pad_9A[0x1];
    u8 phase;
} ActionState;

typedef struct ObjectHeaderTail {
    void * sprite;
    u8 pad_04[0x10];
} ObjectHeaderTail;   /* the 0x14 bytes before obj in update_item_slot_action, addressed as obj[-1] */

typedef struct TilePosition {
    u8 pad_00[0x24];
    u8 tileX;
    u8 tileY;
} TilePosition;

extern s32 get_cd_command_queue_depth(void);
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_two_effect_groups(void *, void *, void *, s32);

extern u8 D_80158F6C[];
extern u8 D_8015D258[];

/* Advances an actor action through item_slot selection, execution, and recovery. */
void update_item_slot_action(ActionState *action_state, EntityRec *transform, SpriteAnimationTableView *sprite, EntityRec *actor)
{
    u16 saved_position[3];
    u8 *item_slot;
    s32 use_global_target;
    void *target;
        s32 abs_x;
    s32 abs_y;
    TilePosition *target_sprite;
    s32 ticks_left;

    use_global_target = 0;
    switch (action_state->phase) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                use_global_target = 1;
                /* fall through */
            case 3:
                item_slot = &((ItemSlots *)actor)->third;
                break;
            case 6:
                use_global_target = 1;
                /* fall through */
            case 2:
                item_slot = &((ItemSlots *)actor)->second;
                break;
            case 5:
                use_global_target = 1;
                /* fall through */
            case 1:
                item_slot = &((ItemSlots *)actor)->first;
                break;
            default:
                item_slot = (u8 *)0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                item_slot = &((ItemSlots *)actor)->third;
                break;
            case 2:
                item_slot = &((ItemSlots *)actor)->second;
                break;
            case 1:
                item_slot = &((ItemSlots *)actor)->first;
                break;
            default:
                item_slot = (u8 *)0;
                break;
            }
        }
        if (*item_slot != 0) {
            action_state->flags &= 0xFF7F;
            {
                s16 global_target_flag = use_global_target;

                if (global_target_flag != 0) {
                    target = D_800814A8;
                    actor->target = target;
                    target_sprite = ((ObjectHeaderTail *)target)[-1].sprite;
                    actor->unk_72 = target_sprite->tileX;
                    actor->unk_73 = target_sprite->tileY;
                } else if (D_8006DE24[*item_slot].kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        target_sprite = ((ObjectHeaderTail *)target)[-1].sprite;
                        actor->unk_72 = target_sprite->tileX;
                        actor->unk_73 = target_sprite->tileY;
                    }
                } else {
                    actor->target =
                        scan_monster_along_heading(actor, sprite->unk_24, sprite->unk_25,
                                      actor->facing, 0x10);
                    abs_x = abs(actor->unk_72);
                    abs_y = abs(actor->unk_73);
                    actor->unk_72 = abs_x;
                    actor->unk_73 = abs_y;
                }
            }
            saved_position[0] = ((u16)transform->x.w.i);
            saved_position[1] = ((u16)transform->y.w.i);
            saved_position[2] = ((u16)transform->z.w.i);
            if (create_actor_spell_effect(actor, item_slot, use_global_target, &action_state->flags) == 0) {
                return;
            }
            sprite->unk_14 &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_effect_groups(transform, sprite, actor, 0x10);
            action_state->phase = action_state->phase + 1;
            return;
        }

        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        set_record_integer_tile_center(transform, sprite->unk_24, sprite->unk_25);
        g_dungeon_status.active_actor = 0;
        ((PlayerActionCounter *)D_800814A8)->pendingActions = ((PlayerActionCounter *)D_800814A8)->pendingActions - 1;
        advance_status_timers(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        action_state->handler = D_80158F6C;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->unk_14 |= 0x800;
            return;
        }
        sprite->unk_14 &= 0xF7FF;
        action_state->phase = action_state->phase + 1;
        /* fall through */
    case 2:
        if ((sprite->unk_04 == 3 && (sprite->unk_14 & 0x1000))
            ||
            (sprite->unk_14 & 0xE000)) {
            sprite->unk_14 |= 0x800;
            action_state->ticks = 0xE;
            action_state->flags |= 0x80;
        }
        ticks_left = action_state->ticks - 1;
        action_state->ticks = ticks_left;
        if ((s16)ticks_left <= 0) {
            action_state->ticks = 0;
            sprite->unk_14 &= 0xF7FF;
        }
        if ((sprite->unk_14 & 0xE000) == 0) {
            return;
        }
        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        set_record_integer_tile_center(transform, sprite->unk_24, sprite->unk_25);
        {
            u8 *direction_table = D_8015D258;

            if (sprite->unk_2C != direction_table) {
                sprite->unk_2C = direction_table;
                select_sprite_entry(sprite,
                    direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        if (((s32)g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
        sprite->unk_14 &= 0xF7FF;
        action_state->handler = D_80158F6C;
        advance_status_timers(actor);
        if (actor->unk_6D > 0) {
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;
    }
}

#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_links.h"
#include "shared/dungeon_moving_views.h"
#include "engine/cd.h"
#include "engine/graphics.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2C];
    s32 *field_2C;
} EffectSpriteFieldView_80EB6FC8;

typedef struct {
    u8 pad_00[0xA6];
    u16 field_A6;
} D800814A8FieldView_80EB6FC8;

extern int abs(int);

typedef struct S_801727C8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    s16 unk_A8;
} S_801727C8_0;   /* arg0 in update_actor_action_target_and_animation */

   /* the 0x14 bytes before owner in update_actor_action_target_and_animation, addressed as owner[-1] */

typedef struct S_801727C8_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_801727C8_5;

extern void *D_80170838[];
void *scan_actor_along_heading();
void set_record_integer_tile_center();
s32 advance_status_timers();
s32 play_sound_if_enabled();
s32 create_actor_spell_effect();
void create_two_effect_groups();
void update_actor_animation_and_dispatch(void *actor, s32 context, void *sprite, ActorRecord *status);
extern u8 kraken_frame_set_1;
extern u8 D_801741B4;
extern u8 kraken_frame_set_5;

/* Updates an actor's action state, target selection, and animation. */
/* Starts a targeted Kraken spell with two effect groups, waits for loading and animation, then restores
 * vertical idle state. */
void update_actor_action_target_and_animation(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 *anim_table;
    s32 visual_base;
    s32 special_slot;
    s32 slot;
    s16 is_special;
    s32 target_x;
    s32 abs_x;
    s32 abs_y;
    s32 target_y;
    u16 ticks_left;
    u8 *entry;
    s32 current_state;
    s32 state;
    void *visual_flags;
    SpriteFrameState *effect_sprite;
    void *target_owner;

    is_special = 0;
    visual_base = ((S_801727C8_0 *)action)->unk_A4;
    state = ((S_801727C8_0 *)action)->unk_9B;
    visual_flags = visual_base + 0x20;
    effect_sprite = visual_base + 0x28;
    switch (state) {
    case 0:
        if (actor->flags1C & ACTOR_PLAYER_SIDE) {
            special_slot = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (special_slot) {
            case 7:
                is_special = 1;
                /* fallthrough */
            case 3:
                entry = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
                /* fallthrough */
            case 2:
                entry = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
                /* fallthrough */
            case 1:
                entry = (u8 *)actor + 8;
                break;
            default:
                entry = 0;
                break;
            }
        } else {
            slot = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (slot) {
            case 3:
                entry = (u8 *)actor + 0xE;
                break;
            case 2:
                entry = (u8 *)actor + 0xB;
                break;
            case 1:
                entry = (u8 *)actor + 8;
                break;
            default:
                entry = 0;
                break;
            }
        }
        if (*entry != 0) {
            ((S_801727C8_0 *)action)->unk_98 = (u16) (((S_801727C8_0 *)action)->unk_98 & 0xFF7F);
            {
                s32 special_check;

                special_check = is_special;
                if (special_check != 0) {
                    target_owner = primary_actor_record;
                    actor->target = target_owner;
                    {
                        void *owner = target_owner;

                        slot = (s32)(((ObjectNodeHeader *)((u8 *)owner - 0x20))->sprite);
                        actor->target_tile_x = (s8) ((MovingTile *)((void *)slot))->tile_x;
                        actor->target_tile_y = (s8) ((MovingTile *)((void *)slot))->tile_y;
                    }
                } else if (item_action_definitions[*entry].kind == 2) {
                    target_owner = actor->target;
                    if (target_owner != 0) {
                        void *owner = target_owner;

                        slot = (s32)(((ObjectNodeHeader *)((u8 *)owner - 0x20))->sprite);
                        actor->target_tile_x = (s8) ((MovingTile *)((void *)slot))->tile_x;
                        actor->target_tile_y = (s8) ((MovingTile *)((void *)slot))->tile_y;
                    }
                } else {
                    void *spawned_owner;

                    spawned_owner = scan_actor_along_heading(actor, sprite->tile_x, sprite->tile_y,
                        actor->facing, 0x10);
                    actor->target = spawned_owner;
                    abs_x = abs(actor->target_tile_x);
                    abs_y = abs(actor->target_tile_y);
                    actor->target_tile_x = abs_x;
                    actor->target_tile_y = abs_y;
                }
            }
            anim_table = &D_801741B4;
            ((S_801727C8_5 *)visual_flags)->unk_04 = (u16) (((S_801727C8_5 *)visual_flags)->unk_04 & 0x7FFF);
            (effect_sprite->frameTable) = anim_table;
            select_sprite_entry(effect_sprite, *((u8 *) ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + (s32) anim_table)), 0);
            if (create_actor_spell_effect(actor, entry, is_special, action + 0x98) == 0) {
                return;
            }
            sprite->flags = (u16) (sprite->flags & 0xF7FF);
            create_two_effect_groups(motion, sprite, actor, 0xA);
            play_sound_if_enabled(0x703);
            current_state = ((S_801727C8_0 *)action)->unk_9B;
            {
                state = 6;

                ((S_801727C8_0 *)action)->unk_96 = (u16)state;
            }
            ((S_801727C8_0 *)action)->unk_9B = (u8) (current_state + 1);
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)&primary_actor_record->unk_A4 + 2)) = (u16) ((((D800814A8FieldView_80EB6FC8 *)primary_actor_record)->field_A6) - 1);
        advance_status_timers(actor);
        actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
        ((S_801727C8_0 *)action)->unk_8C = &update_actor_animation_and_dispatch;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags = (u16) (sprite->flags | 0x800);
            return;
        }
        sprite->flags = (u16) (sprite->flags & 0xF7FF);
        ((S_801727C8_0 *)action)->unk_9B = (u8) (((S_801727C8_0 *)action)->unk_9B + 1);

    case 2:
        ticks_left = ((S_801727C8_0 *)action)->unk_96 - 1;
        ((S_801727C8_0 *)action)->unk_96 = ticks_left;
        if ((ticks_left << 0x10) > 0) {
            if (!(sprite->flags & 0xE000)) {
                return;
            }
        }
        ((S_801727C8_0 *)action)->unk_98 = (u16) (((S_801727C8_0 *)action)->unk_98 | 0x80);
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = &kraken_frame_set_5;
        select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + &kraken_frame_set_5), 0);
        current_state = ((S_801727C8_0 *)action)->unk_9B;
        ((S_801727C8_0 *)action)->unk_9B = (u8) (current_state + 1);
        return;

    case 3:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if ((*(M2C_UNK * *)&sprite->frameTable) != &kraken_frame_set_1) {
            if (sprite->flags & 0x6000) {
                ((S_801727C8_5 *)visual_flags)->unk_04 = (u16) (((S_801727C8_5 *)visual_flags)->unk_04 | 0x8000);
                ((S_801727C8_0 *)action)->unk_A8 = 0;
                sprite->frameTable = &kraken_frame_set_1;
                select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                    + &kraken_frame_set_1), 0);
            }
        }
        if ((g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        sprite->flags = (u16) (sprite->flags & 0xF7FF);
        ((S_801727C8_0 *)action)->unk_8C = &update_actor_animation_and_dispatch;
        advance_status_timers(actor);
        if ((s8) ((u8)actor->pending_turn_updates) > 0) {
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;
    default:
        return;
    }
}

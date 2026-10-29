#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "shared/sprite_frame_state.h"
#include "engine/graphics.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/troll.h"
#include "dungeon/item.h"

typedef struct S_8017472C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x12];
    union { s16 s; u16 u; } unk_AE;   /* accessed as both */
} S_8017472C_0;   /* arg0 in advance_actor_targeted_action */

typedef struct S_8017472C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017472C_3;   /* record in advance_actor_targeted_action */
typedef struct S_8017472C_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8017472C_6;   /* control in advance_actor_targeted_action */


extern int abs(int);
extern void *create_actor_spell_effect(void *actor, void *record_data, s16 mode, void *context);
extern void spawn_random_color_burst_particle();


extern s32 D_8008346C;
extern u8 troll_action_dispatch_address[];
extern u8 troll_frame_set_1[];
extern u8 troll_frame_set_2[];
extern u8 troll_frame_set_3[];

/* Updates an actor's action state, target coordinates, animation, and completion. */
/* Starts a targeted Troll spell, emits ten particles per casting tick and a flash, then restores the
 * current item's idle frames. */
void advance_actor_targeted_action(ActorRecord *action, ObjectPosition *transform, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 state;
    register s32 use_player_target;
    s32 kind;
    u8 *move;
    void *target;
    s32 target_x;
    s32 target_y;
    u16 ticks_left;
    s32 step;
    u8 *anim_table;
    void *current_anim;
    s32 delay_slot;
    S_8017472C_6 *control;

    state = action->action_phase.u;
    use_player_target = 0;
    switch (state) {
    case 0:
        if (((u32)actor->flags1C) & ACTOR_PLAYER_SIDE) {
            kind = (actor->action_flags & ACTOR_ACTION_CODE_MASK) - 1;
            switch (kind) {
            case 6:
                use_player_target = 1;
                /* fall through */
            case 2:
                move = (u8 *)actor + 0xE;
                break;
            case 5:
                use_player_target = 1;
                /* fall through */
            case 1:
                move = (u8 *)actor + 0xB;
                break;
            case 4:
                use_player_target = 1;
                /* fall through */
            case 0:
                move = (u8 *)actor + 8;
                break;
            default:
                move = 0;
                break;
            }
        } else {
            kind = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (kind) {
            case 3:
                move = (u8 *)actor + 0xE;
                break;
            case 2:
                move = (u8 *)actor + 0xB;
                break;
            case 1:
                move = (u8 *)actor + 8;
                break;
            default:
                move = 0;
                break;
            }
        }
        if (*move != 0) {
            action->action_state_flags &= 0xFF7F;
            if (use_player_target != 0) {
                target = primary_actor_record;
                actor->target = target;
                state = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                actor->target_tile_x = ((S_8017472C_3 *)state)->unk_24;
                actor->target_tile_y = ((S_8017472C_3 *)state)->unk_25;
            } else if (item_action_definitions[*move].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    state = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                    actor->target_tile_x = ((S_8017472C_3 *)state)->unk_24;
                    actor->target_tile_y = ((S_8017472C_3 *)state)->unk_25;
                }
            } else {
                target = scan_actor_along_heading(
                    actor,
                    sprite->tile_x,
                    sprite->tile_y,
                    actor->facing,
                    0x10);
                actor->target = target;
                actor->target_tile_x =
                abs(actor->target_tile_x);
                actor->target_tile_y =
                abs(actor->target_tile_y);

            }

            if (create_actor_spell_effect(actor, move, use_player_target,
                (u8 *)action + 0x98) == 0) {
                return;
            }
            action->action_timer.u = 0x16;
            ((S_8017472C_0 *)action)->unk_AE.s = 0xE;
            action->action_phase.u++;
            return;
        }

        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, sprite->tile_x, sprite->tile_y);
        D_8008346C = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(actor);
        (*(u8 *)&actor->pending_turn_updates)--;
        action->unk_8C.address = troll_action_dispatch_address;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        action->action_phase.u++;
        play_sound_if_enabled(0x703);

    case 2:
        step = 0;
        if (!(action->action_timer.u & 1) &&
            ((S_8017472C_0 *)action)->unk_AE.s != 0) {
            ((S_8017472C_0 *)action)->unk_AE.u--;
        }
        for (step = 0; step < 10; step++) {
            spawn_random_color_burst_particle(action, transform, sprite, actor);
        }

        if (action->action_timer.s == 0x16) {
            spawn_growing_rotating_flash(action, transform, sprite);
        }
        ticks_left = action->action_timer.u - 1;
        action->action_timer.u = ticks_left;
        if ((s32)(ticks_left << 16) > 0 &&
            !(sprite->flags & 0xE000)) {
            return;
        }
        action->action_state_flags |= 0x80;
        action->action_phase.u++;
        return;

    case 3:
        if (D_8008346C == 0) {
            action->action_timer.u = 0;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }

        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, sprite->tile_x, sprite->tile_y);

        kind = actor->unk_48;
        switch (kind) {
        case 0xD:
            current_anim = sprite->frameTable;
            anim_table = troll_frame_set_1;
            if (current_anim != anim_table) {
                (sprite->frameTable) = anim_table;
                select_sprite_entry(sprite,
                    *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (u32)anim_table), 0);
            }

            control = (S_8017472C_6 *)&g_dungeon_status;
            break;
        case 0xE:
            current_anim = sprite->frameTable;
            anim_table = troll_frame_set_2;
            if (current_anim != anim_table) {
                (sprite->frameTable) = anim_table;
                select_sprite_entry(sprite,
                    *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (u32)anim_table), 0);
            }

            control = (S_8017472C_6 *)&g_dungeon_status;
            break;
        case 0xF:
            current_anim = sprite->frameTable;
            anim_table = troll_frame_set_3;
            if (current_anim != anim_table) {
                (sprite->frameTable) = anim_table;
                select_sprite_entry(sprite,
                    *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (u32)anim_table), 0);
            }

            control = (S_8017472C_6 *)&g_dungeon_status;
            break;
        default:
            current_anim = (u8 *)&g_dungeon_status;
            control = current_anim;
            break;
        }
        if (control->unk_0C != 0) {
            return;
        }
        control->unk_0A--;
        action->unk_8C.address = troll_action_dispatch_address;
        advance_status_timers(actor);
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        (*(u8 *)&actor->pending_turn_updates)--;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        break;
    default:
        break;
    }
}

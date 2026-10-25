#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "shared/sprite_frame_state.h"
extern int abs(int);

extern s32 tyrant_action_resume_address;
extern u8 tyrant_direction_frames[8];

extern void select_sprite_entry();
extern void *scan_actor_along_heading();
extern void set_record_integer_tile_center();
extern void advance_status_timers();
extern void play_sound_if_enabled();
extern s32 create_actor_spell_effect();
extern void create_two_row_object_group();

typedef struct S_801729D4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801729D4_0;   /* arg0 in advance_the_actor_animation_state_reset_movement_finishes */

typedef struct S_801729D4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801729D4_3;   /* source in advance_the_actor_animation_state_reset_movement_finishes */

typedef struct S_801729D4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_801729D4_4;   /* arg2 in advance_the_actor_animation_state_reset_movement_finishes */

/* Advance the actor animation state and reset movement when it finishes. */
void advance_the_actor_animation_state_reset_movement_finishes(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 position[3];
    u8 *animation;
    s16 reuse_target;
    s32 reuse_test;
    s32 state;
    s32 anim_kind;
    void *target_root;
    void *target_source;
    void *new_target;
    s32 target_x;
    s32 abs_x;
    s32 abs_y;
    s32 target_y;

    state = ((S_801729D4_0 *)action)->unk_9B;
    reuse_target = 0;
    switch (state) {
    case 0:
        if (actor->flags1C & ACTOR_PLAYER_SIDE) {
            anim_kind = (actor->action_flags & ACTOR_ACTION_CODE_MASK) - 1;
            switch (anim_kind) {
            case 6:
                reuse_target = 1;
                /* fall through */
            case 2:
                animation = (u8 *)actor + 0xE;
                break;
            case 5:
                reuse_target = 1;
                /* fall through */
            case 1:
                animation = (u8 *)actor + 0xB;
                break;
            case 4:
                reuse_target = 1;
                /* fall through */
            case 0:
                animation = (u8 *)actor + 8;
                break;
            case 3:
            default:
                animation = 0;
                break;
            }
        } else {
            anim_kind = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (anim_kind) {
            case 3:
                animation = (u8 *)actor + 0xE;
                break;
            case 2:
                animation = (u8 *)actor + 0xB;
                break;
            case 1:
                animation = (u8 *)actor + 8;
                break;
            default:
                animation = 0;
                break;
            }
        }

        if (*animation != 0) {
            ((S_801729D4_0 *)action)->unk_98 &= 0xFF7F;
            reuse_test = reuse_target;
            if (reuse_test != 0) {
                target_root = primary_actor_record;
                actor->target = target_root;
                target_source = ((ObjectNodeHeader *)((u8 *)target_root - 0x20))->sprite;
                actor->target_tile_x = ((S_801729D4_3 *)target_source)->unk_24;
                actor->target_tile_y = ((S_801729D4_3 *)target_source)->unk_25;
            } else {
                new_target = scan_actor_along_heading(
                    actor, sprite->tile_x, sprite->tile_y,
                    actor->facing, 0x10);
                actor->target = new_target;
                abs_x = abs(actor->target_tile_x);
                abs_y = abs(actor->target_tile_y);
                actor->target_tile_x = abs_x;
                actor->target_tile_y = abs_y;
            }
            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (create_actor_spell_effect(actor, animation, reuse_target, (u8 *)action + 0x98) != 0) {
                sprite->flags &= 0xF7FF;
                play_sound_if_enabled(0x703);
                create_two_row_object_group(position, (s16)((*animation - 1) % 3));
                ((S_801729D4_0 *)action)->unk_9B++;
                return;
            }
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + (0xA6)))--;
        advance_status_timers(actor);
        (*(u8 *)&actor->pending_turn_updates)--;
        ((S_801729D4_0 *)action)->unk_8C = &tyrant_action_resume_address;
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
        ((S_801729D4_0 *)action)->unk_9B++;

        /* fall through */
    case 2:
        if ((sprite->unk_04 == 8 &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            ((S_801729D4_0 *)action)->unk_96 = 3;
            ((S_801729D4_0 *)action)->unk_98 |= 0x80;
        }
        ((S_801729D4_0 *)action)->unk_96--;
        if ((s16)((S_801729D4_0 *)action)->unk_96 <= 0) {
            ((S_801729D4_0 *)action)->unk_96 = 0;
            sprite->flags &= 0xF7FF;
        }
        if (sprite->flags & 0xE000) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            if (sprite->frameTable != tyrant_direction_frames) {
                (sprite->frameTable) = tyrant_direction_frames;
                select_sprite_entry(
                    sprite,
                    tyrant_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
            if ((g_dungeon_status.active_actor) == 0) {
                g_dungeon_status.activity_counts.parts.pending_action_count--;
                sprite->flags &= 0xF7FF;
                ((S_801729D4_0 *)action)->unk_8C = &tyrant_action_resume_address;
                advance_status_timers(actor);
                if (actor->pending_turn_updates > 0) {
                    (*(u8 *)&actor->pending_turn_updates)--;
                }
                actor->target_tile_y = 0;
                actor->target_tile_x = 0;
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
                play_sound_if_enabled(AUDIO_FADE_CD_FAST);
            }
        }

        return;
    }
}

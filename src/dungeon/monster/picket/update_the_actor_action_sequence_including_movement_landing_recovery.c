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
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "engine/cd.h"
extern int abs(int);

typedef struct S_80172C90_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x10];
    union { u16 s; s16 u; } unk_AC;   /* accessed as both */
} S_80172C90_1;   /* arg0 in update_the_actor_action_sequence_including_movement_landing_recovery */

typedef struct S_80172C90_3 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80172C90_3;   /* localOwner in update_the_actor_action_sequence_including_movement_landing_recovery */

typedef struct S_80172C90_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172C90_4;   /* localLinked in update_the_actor_action_sequence_including_movement_landing_recovery */

extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void play_sound_if_enabled(s32);
extern void create_two_effect_groups(void *, void *, void *, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void select_sprite_entry(void *, u8, s32);

extern u8 picket_action_resume_address[];
extern u8 picket_frame_set_2[];
extern u8 picket_frame_set_1[];

/* Updates the actor action sequence, including movement, landing, and recovery. */
/* Starts a targeted spell with two effect groups, animates a backward leap and landing squash, then
 * returns to its tile. */
void update_the_actor_action_sequence_including_movement_landing_recovery(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u32 dir_offset;
    u16 angle;
    u32 action_index;
    s16 *dir_x_table;
    s32 dir_x;
    s32 dir_y;
    u16 timer;
    u32 state;
    u8 *selector;
    s32 special;
    s32 tail_state; /* MATCH: the shared state store receives its value in v0. */
    u16 position[3];

    dir_x_table = dir_step_x;
    angle = ((u16)actor->facing);
    dir_offset = angle >> 8;
    dir_offset &= 0xE;
    dir_x = *(s16 *)((u8 *)dir_x_table + dir_offset);
    dir_offset += (u32)dir_step_y;
    dir_y = *(s16 *)dir_offset;
    timer = ((S_80172C90_1 *)action)->unk_96.s;
    state = ((S_80172C90_1 *)action)->unk_9B;
    ((S_80172C90_1 *)action)->unk_96.s = timer - 1;
    special = 0;
    switch (state) {

    case 0:
        ((S_80172C90_1 *)action)->unk_AC.s = ((u16)motion->z.w.i);
        if (((u32)actor->flags1C) & ACTOR_PLAYER_SIDE) {
            u16 action_kind;

            action_kind = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            action_index = action_kind - 1;
            switch (action_index) {
            case 6:
                special = 1;
            case 2:
                selector = (u8 *)actor + 0xE;
                break;
            case 5:
                special = 1;
            case 1:
                selector = (u8 *)actor + 0xB;
                break;
            case 4:
                special = 1;
            case 0:
                selector = (u8 *)actor + 8;
                break;
            case 3:
            default:
                selector = 0;
            }
        } else {
            u16 action_kind;

            action_kind = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (action_kind) {
            case 3:
                selector = (u8 *)actor + 0xE;
                break;
            case 2:
                selector = (u8 *)actor + 0xB;
                break;
            case 1:
                selector = (u8 *)actor + 8;
                break;
            default:
                selector = 0;
            }
        }

        if (*selector != 0) {
            void *owner;
            u16 use_owner;
            s32 move_result;

            ((S_80172C90_1 *)action)->unk_98 &= 0xFF7F;
            use_owner = special;
            if (use_owner) {
                owner = primary_actor_record;
                actor->target = owner;
                move_result = ((ObjectNodeHeader *)((u8 *)owner - 0x20))->sprite;
                actor->target_tile_x = ((S_80172C90_4 *)move_result)->unk_24;
                actor->target_tile_y = ((S_80172C90_4 *)move_result)->unk_25;
            } else {
                dir_offset = *selector;
                if (item_action_definitions[dir_offset].kind == 2) {
                    owner = actor->target;
                    if (owner != 0) {
                        move_result = ((ObjectNodeHeader *)((u8 *)owner - 0x20))->sprite;
                        actor->target_tile_x = ((S_80172C90_4 *)move_result)->unk_24;
                        actor->target_tile_y = ((S_80172C90_4 *)move_result)->unk_25;
                    }
                } else {
                    actor->target = scan_actor_along_heading(actor,
                        sprite->tile_x,
                        sprite->tile_y,
                        actor->facing, 16);
                    actor->target_tile_x = abs(actor->target_tile_x);
                    actor->target_tile_y = abs(actor->target_tile_y);
                }
            }

            {
                void *move_actor;

                move_actor = actor;
                position[0] = ((u16)motion->x.w.i);
                position[1] = ((u16)motion->y.w.i);
                position[2] = ((u16)motion->z.w.i);
                move_result = create_actor_spell_effect(move_actor, selector, special,
                                            (u8 *)action + 0x98);
            }
            if (!move_result) {
                return;
            }
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_effect_groups(motion, sprite, actor, 10);
            ((S_80172C90_1 *)action)->unk_90 = 0;
            ((S_80172C90_1 *)action)->unk_96.s = 2;
            ((S_80172C90_1 *)action)->unk_98 |= 8;
            {
                s32 back_x;
                s32 back_y;

                back_x = -dir_x;
                back_y = -dir_y;
                motion->velocity_x =
                    (back_x << 18) + (back_x << 19);
                motion->velocity_y =
                    (back_y << 18) + (back_y << 19);
            }
            motion->velocity_z = (s32)0xFFF30000;
            {
                tail_state = ((S_80172C90_1 *)action)->unk_9B;
                tail_state++;
                ((S_80172C90_1 *)action)->unk_9B = tail_state;
                return;
            }
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        {
            void *owner;

            owner = primary_actor_record;
            g_dungeon_status.active_actor = 0;
            ((S_80172C90_3 *)owner)->unk_A6--;
        }
        advance_status_timers(actor);
        (*(u8 *)&actor->pending_turn_updates)--;
        ((S_80172C90_1 *)action)->unk_8C = picket_action_resume_address;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        return;

    case 1:
        if (sprite->flags & 0x8000) {
            ((S_80172C90_1 *)action)->unk_9B = 16;
            ((S_80172C90_1 *)action)->unk_98 |= 0x80;
            return;
        }
        if (((S_80172C90_1 *)action)->unk_96.u <= 0) {
            motion->velocity_x = 0;
            motion->velocity_y = 0;
            motion->velocity_z = 0;
            motion->velocity_x = dir_x << 18;
            motion->velocity_y = dir_y << 18;
            motion->velocity_z = (s32)0xFFF30000;
            {
                ((S_80172C90_1 *)action)->unk_9B = ((S_80172C90_1 *)action)->unk_9B + 1;
                return;
            }
        }
        motion->velocity_x *= 2;
        motion->velocity_y *= 2;
        return;

    case 2:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x0800;
            return;
        }
        sprite->flags &= 0xF7FF;
        ((S_80172C90_1 *)action)->unk_9B++;

    case 3:
        motion->velocity_z += 0x30000;
        if (!((sprite->unk_04 == 4 && (sprite->flags & 0x1000)) ||
              (sprite->flags & 0xE000))) {
            return;
        }
        {
            motion->velocity_x = dir_x << 19;
            motion->velocity_y = dir_y << 19;
            ((S_80172C90_1 *)action)->unk_98 |= 0x80;
            ((S_80172C90_1 *)action)->unk_9B++;
            return;
        }

    case 4:
        motion->velocity_z += 0x20000;
        if (!((((u32)actor->flags1C) & ACTOR_GROUNDED) && (motion->z.w.i <= ((S_80172C90_1 *)action)->unk_AC.u))) {
            if (motion->z.w.i <= ((S_80172C90_1 *)action)->unk_AC.u) {
                return;
            }
        }
        {
            u8 *effect;

            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            ((S_80172C90_1 *)action)->unk_96.s = 4;
            sprite->scale_x = 0x1400;
            sprite->scale_y = 0x0C00;
            effect = picket_frame_set_1;
            sprite->frameTable = effect;
            select_sprite_entry(sprite,
                effect[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172C90_1 *)action)->unk_98 &= 0xFFF7;
            ((S_80172C90_1 *)action)->unk_9B++;
            return;
        }

    case 5:
    {
        s32 ticks;
        s32 ticks_squared;

        ticks = ((S_80172C90_1 *)action)->unk_96.u;
        ticks_squared = ticks * ticks;
        ticks = 0x1000 + ticks_squared * 300;
        sprite->scale_x = ticks;
        sprite->scale_y = 0x1000 - ticks_squared * 200;
    }
        if (((S_80172C90_1 *)action)->unk_96.u > 0) {
            return;
        }
        sprite->frameTable = picket_frame_set_2;
        select_sprite_entry(sprite,
            picket_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172C90_1 *)action)->unk_96.s = 10;
        ((S_80172C90_1 *)action)->unk_9B = ((S_80172C90_1 *)action)->unk_9B + 1;
        return;

    case 6:
    {
        s32 current_coord;
        {
            s32 tile_coord;

            tile_coord = sprite->tile_x;
            current_coord = motion->x.w.i;
            tile_coord = tile_coord << 6;
            current_coord -= 0x20;
            motion->velocity_x =
                (tile_coord - current_coord) << 14;
        }
        {
            s32 tile_coord;
            s32 target_coord;

            tile_coord = sprite->tile_y;
            current_coord = motion->y.w.i;
            tile_coord <<= 6;
            target_coord = tile_coord;
            current_coord -= 0x20;
            motion->velocity_y =
                (target_coord - current_coord) << 14;
        }
    }
        if (((S_80172C90_1 *)action)->unk_96.u > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        sprite->flags |= 0x6000;
        ((S_80172C90_1 *)action)->unk_9B = 16;
        return;

    case 16:
    {

        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if (*(u8 **)&sprite->frameTable != picket_frame_set_1) {
            sprite->frameTable = picket_frame_set_1;
            select_sprite_entry(sprite,
                picket_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        if (((s32)g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        sprite->flags &= 0xF7FF;
        ((S_80172C90_1 *)action)->unk_8C = picket_action_resume_address;
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            (*(u8 *)&actor->pending_turn_updates)--;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
    }
    default:
        return;
    }
}

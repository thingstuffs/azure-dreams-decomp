#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
#include "dungeon/player/object.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct {
    u32 words[3];
} __attribute__((packed)) LocalPacket;

typedef struct {
    u8 bytes[0x12];
    u8 kind;
    u8 pad;
} LocalItemInfo;

extern void select_sprite_entry(void *, s32, s32);
extern s32 rand(void);
extern void play_sound_if_enabled(s32);

extern u8 D_80171030[];
extern u8 barong_action_resume_address[];
#include "dungeon/monster/barong.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
extern u8 barong_frame_set[];
extern u8 barong_frame_set_3[];
extern LocalPacket D_801755D4;

typedef struct S_801731C8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801731C8_2;   /* linked in update_item_use_action */

typedef struct S_801731C8_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_801731C8_5;   /* object in update_item_use_action */

typedef struct S_801731C8_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801731C8_6;   /* part in update_item_use_action */

/* Updates an item-use action, its animation, and its particle effects. */
/* Starts a targeted spell, emits randomly colored particles during its animation, then restores movement
 * and status. */
void update_item_use_action(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 *item_slot;
    s16 is_special;
    s32 next_state;
    s32 state;
    void *target;

    is_special = 0;
    state = body->action_phase.u;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & ACTOR_PLAYER_SIDE) {
            switch (actor->action_flags & 0x3FFF) {
            case 7:
                is_special = 1;
                /* fallthrough */
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
                /* fallthrough */
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
                /* fallthrough */
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch (actor->action_flags & 0x3FFF) {
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            body->action_state_flags &= 0xFF7F;
            if (is_special != 0) {
                target = primary_actor_record;
                actor->target = target;
                state = (s32)(((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite);
                actor->target_tile_x = ((S_801731C8_2 *)((u8 *)state))->unk_24;
                actor->target_tile_y = ((S_801731C8_2 *)((u8 *)state))->unk_25;
            } else {
                u8 item_id;

                item_id = *item_slot;
                if (((LocalItemInfo *)item_action_definitions)[item_id].kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        state = (s32)(((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite);
                        actor->target_tile_x = ((S_801731C8_2 *)((u8 *)state))->unk_24;
                        actor->target_tile_y = ((S_801731C8_2 *)((u8 *)state))->unk_25;
                    }
                } else {
                    s32 dx;
                    s32 dy;

                    dx = (s32)scan_actor_along_heading(
                        actor, sprite->tile_x, sprite->tile_y,
                        actor->facing, 0x10);
                    actor->target = (void *)dx;
                    dx = abs(actor->target_tile_x);
                    dy = abs(actor->target_tile_y);
                    actor->target_tile_x = dx;
                    actor->target_tile_y = dy;
                }
            }

            if (create_actor_spell_effect(actor, item_slot, is_special, (u8 *)body + 0x98) == 0) {
                return;
            }
            body->action_timer.u = 0x11;
            {
                u8 *animations;
                s32 direction;

                animations = barong_frame_set_3;
                sprite->frameTable = animations;
                direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, animations[direction], 0);
            }
            next_state = body->action_phase.u + 1;
            body->action_phase.u = next_state;
            sprite->flags |= 0x800;
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        primary_actor_record->unk_A4.halves.high.u--;
        advance_status_timers(actor);
        (*((u8 *)actor + 0x6D))--;
        body->unk_8C.address = barong_action_resume_address;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x800;
            return;
        }
        body->action_phase.u++;
        play_sound_if_enabled(0x703);

    case 2:
        {
            s16 timer;

            timer = body->action_timer.u - 1;
            body->action_timer.u = timer;
            if (timer <= 0 || (sprite->flags & 0xE000)) {
                body->action_state_flags |= 0x80;
                body->action_phase.u++;
                sprite->flags |= 0x800;
                body->action_timer.u = 0xF;
            }
            if (body->action_timer.s == 8) {
                u8 *animations;
                s32 direction;

                animations = barong_frame_set;
                sprite->frameTable = animations;
                sprite->flags &= 0xF7FF;
                direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, animations[direction], 0);
            }
            if (body->action_timer.s < 2) {
                return;
            }
        }

        {
            s16 particle_count;
            u8 *particle_script;
            s32 low_color;
            s32 high_color;

            particle_count = 0;
            particle_script = D_80171030;
            low_color = 0x20;
            high_color = 0xE0;
            for (; particle_count < 1; particle_count++) {
                ObjectNodeHeader *particle;

                particle = allocate_flagged_object_node(0x212);
                if (particle == 0) {
                    continue;
                }
                {
                    S_801731C8_6 *particle_part;
                    s32 color_roll;
                    s16 color_choice;

                    ((S_801731C8_5 *)particle)->unk_22 = 8;
                    particle->update_callback = particle_script;
                    register_node(particle, project_sprite_chain);
                    particle_part = (S_801731C8_6 *)particle->sprite;
                    particle_part->unk_10 = low_color;
                    particle_part->unk_14 |= 0xC;

                    particle_part = (S_801731C8_6 *)particle->position;
                    {
                        s32 position_roll;
                        s32 position_base;

                        position_roll = rand();
                        position_base = ((u16)motion->x.w.i);
                        position_base -= 0x20;
                        particle_part->unk_02 = position_base + (position_roll & 0x3F);
                    }
                    {
                        s32 position_roll;
                        s32 position_base;

                        position_roll = rand();
                        position_base = ((u16)motion->y.w.i);
                        position_base -= 0x20;
                        particle_part->unk_06 = position_base + (position_roll & 0x3F);
                    }
                    particle_part->unk_08.at02.v =
                        ((u16)motion->z.w.i) - (rand() & 0x1F) - 0x30;

                    particle_part = (S_801731C8_6 *)particle->sprite;
                    {
                        s32 initial_color;

                        particle_part->unk_1E = 0x200;
                        particle_part->unk_1C = 0x200;
                        initial_color = 0x80;
                        particle_part->unk_0E = initial_color;
                        particle_part->unk_0D = initial_color;
                        particle_part->unk_0C = initial_color;
                    }
                    *(LocalPacket *)((u8 *)particle + 0x40) = D_801755D4;
                    particle_part->unk_08.at00.v = (u8 *)particle + 0x40;

                    color_roll = rand() & 3;
                    color_choice = color_roll;
                    if (color_choice == 0) {
                        continue;
                    }
                    particle_part->unk_12 = color_roll + 0x7DC6;
                    particle_part->unk_14 |= 0x100;
                    switch (color_choice) {
                    case 1:
                        particle_part->unk_0C = high_color;
                        particle_part->unk_0E = low_color;
                        particle_part->unk_0D = low_color;
                        break;
                    case 2:
                        particle_part->unk_0E = high_color;
                        particle_part->unk_0C = low_color;
                        particle_part->unk_0D = low_color;
                        break;
                    case 3:
                        particle_part->unk_0D = high_color;
                        particle_part->unk_0E = low_color;
                        particle_part->unk_0C = low_color;
                        break;
                    }
                }
            }
        }
        return;

    case 3:
        {
            s16 timer;

            if ((g_dungeon_status.active_actor) == 0) {
                body->action_timer.u = 0;
            }
            timer = body->action_timer.u - 1;
            body->action_timer.u = timer;
            if (timer <= 0) {
                body->action_timer.u = 0;
                sprite->flags &= 0xF7FF;
            }
            if (!(sprite->flags & 0xE000)) {
                return;
            }
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            if (*(u8 * *)&sprite->frameTable != barong_direction_frames) {
                u8 *animations;
                s32 direction;

                animations = barong_direction_frames;
                sprite->frameTable = animations;
                direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, animations[direction], 0);
                sprite->flags &= 0xF7FF;
            }
            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            body->unk_8C.address = barong_action_resume_address;
            advance_status_timers(actor);
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            (*((u8 *)actor + 0x6D))--;
            actor->action_flags &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }

    }
}

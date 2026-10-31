#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/player/object.h"
#include "engine/scene.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/item/actor_target.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct {
    u32 words[12];
} Copy48;

extern u8 D_80171020[];
#include "dungeon/monster/saber.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

extern u8 D_80174E34[];

typedef struct S_80173230_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173230_2;   /* linked in advance_item_use_and_recovery */

typedef struct S_80173230_5 {
    u8 pad_00[0x94];
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
} S_80173230_5;   /* part in advance_item_use_and_recovery */

typedef struct S_80173230_6 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80173230_6;   /* (void *)special in advance_item_use_and_recovery */

typedef struct S_80173230_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_80173230_7;   /* target in advance_item_use_and_recovery */

typedef struct S_80173230_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80173230_8;   /* base in advance_item_use_and_recovery */

/* Advances item use, its visual effect, and the actor's recovery animation. */
/* Starts a targeted spell, creates an attached sprite effect and briefly changes the actor's palette, then
 * restores idle. */
void advance_item_use_and_recovery(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 *effect_state;
    u8 * effect_handle;
    s16 special_or_effect;
    GteOffset effect_offset;
    u8 *item_slot;
    u8 *action_object;
    s32 next_state;
    u8 state;
    void *item_target;

    special_or_effect = 0;
    action_object = (u8 *)body - 0x20;
    state = body->action_phase.u;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & ACTOR_PLAYER_SIDE) {
            switch (actor->action_flags & 0x3FFF) {
            case 7:
                special_or_effect = 1;
                /* fallthrough */
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 6:
                special_or_effect = 1;
                /* fallthrough */
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 5:
                special_or_effect = 1;
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
            if ((s16)special_or_effect != 0) {
                item_target = primary_actor_record;
                actor->target = item_target;
                    effect_state = ((ObjectNodeHeader *)((u8 *)item_target - 0x20))->sprite;
                    actor->target_tile_x = ((S_80173230_2 *)effect_state)->unk_24;
                    actor->target_tile_y = ((S_80173230_2 *)effect_state)->unk_25;
            } else {
                u8 item_id = *item_slot;
                u8 *item_defs = item_action_definitions;
                if (item_defs[item_id * 20 + 0x12] == 2) {
                    item_target = actor->target;
                    if (item_target != 0) {
                    effect_state = ((ObjectNodeHeader *)((u8 *)item_target - 0x20))->sprite;
                    actor->target_tile_x = ((S_80173230_2 *)effect_state)->unk_24;
                    actor->target_tile_y = ((S_80173230_2 *)effect_state)->unk_25;
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

            if (create_actor_spell_effect(actor, item_slot, special_or_effect, (u8 *)body + 0x98) == 0) {
                return;
            }
            body->action_timer.u = 0x11;
            body->action_phase.u++;
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
        body->unk_8C.address = &saber_behavior_entry;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        body->action_phase.u++;
        play_sound_if_enabled(0x703);

    case 2:
        {
            s16 timer;

            timer = body->action_timer.u - 1;
            body->action_timer.u = timer;
            if (timer == 0xB || (sprite->flags & 0xE000)) {
                effect_handle = allocate_list_node(0x112, &scene_object_list_anchor.next);
                if (effect_handle != 0) {
                    SpriteFrameState *actor_model;
                    u8 animation_id;

                    effect_state = effect_handle + 0x20;
                    ((S_80173230_5 *)effect_state)->unk_96 = 9;
                    ((S_80173230_6 *)((void *)effect_handle))->unk_10 = D_80171020;
                    ((S_80173230_5 *)effect_state)->unk_A8 = motion;
                    ((S_80173230_5 *)effect_state)->unk_94 = (*(u16 *)((u8 *)actor + 0x2A));
                    item_slot = ((S_80173230_6 *)((void *)effect_handle))->unk_0C;
                    *(Copy48 *)item_slot = *(Copy48 *)sprite;
                    ((S_80173230_7 *)item_slot)->unk_1E = 0x1000;
                    ((S_80173230_7 *)item_slot)->unk_1C = 0x1000;
                    ((S_80173230_7 *)item_slot)->unk_0E = 0x80;
                    ((S_80173230_7 *)item_slot)->unk_0D = 0x80;
                    ((S_80173230_7 *)item_slot)->unk_0C = 0x80;
                    register_node((void *)effect_handle, project_sprite_chain);
                    animation_id = D_80174E34[0];
                    ((S_80173230_7 *)item_slot)->unk_2C = D_80174E34;
                    select_sprite_entry(item_slot, animation_id, 0);
                    ((S_80173230_7 *)item_slot)->unk_10 = 0x20;
                    ((S_80173230_7 *)item_slot)->unk_12 = 0xFF80;
                    ((S_80173230_7 *)item_slot)->unk_14 |= 0x0C;

                    actor_model = ((S_80173230_8 *)action_object)->unk_0C;
                    item_slot = ((S_80173230_6 *)((void *)effect_handle))->unk_08;
                    if (resolve_record_orientation_or_fallback(
                            actor_model->source, actor_model, &effect_offset.orientation, 1) != 0) {
                        ((S_80173230_7 *)item_slot)->unk_02 = ((u16)motion->x.w.i);
                        ((S_80173230_7 *)item_slot)->unk_06 = ((u16)motion->y.w.i);
                        ((S_80173230_7 *)item_slot)->unk_0A = ((u16)motion->z.w.i);
                        ((S_80173230_7 *)item_slot)->unk_02 += effect_offset.distance[0];
                        ((S_80173230_7 *)item_slot)->unk_06 += effect_offset.distance[1];
                        ((S_80173230_7 *)item_slot)->unk_0A += effect_offset.distance[2];
                    }
                }
            }

            if (body->action_timer.s == 0xB ||
                (sprite->flags & 0xE000)) {
                sprite->flags |= 0x800;
            }
            if (body->action_timer.s == 0 ||
                (sprite->flags & 0xE000)) {
                sprite->flags &= 0xF7FF;
            }
            if (body->action_timer.s <= 0 ||
                (sprite->flags & 0xE000)) {
                next_state = body->action_phase.u + 1;
                body->action_phase.u = next_state;
            }
        }
        return;

    case 3:
        if ((sprite->unk_04 == 3 &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0x8000)) {
            sprite->flags |= 0x800;
            body->action_timer.u = 0x14;
            body->action_state_flags |= 0x80;
            sprite->flags |= 0x100;
            body->unk_AC.halves.low.u = sprite->clut;
            sprite->clut = 0x7E80;
            body->action_phase.u++;
        }

    case 4:
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
            if (body->action_timer.s == 0x12) {
                sprite->flags &= 0xFEFF;
                sprite->clut = body->unk_AC.halves.low.u;
            }
            if (!(sprite->flags & 0xE000)) {
                return;
            }

            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->flags &= 0xFEFF;
            sprite->clut = body->unk_AC.halves.low.u;

            if (*(u8 * *)&sprite->frameTable != saber_direction_frames) {
                u8 *animations;
                s32 direction;

                animations = saber_direction_frames;
                sprite->frameTable = animations;
                direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, animations[direction], 0);
                sprite->flags &= 0xF7FF;
            }
            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            body->unk_8C.address = &saber_behavior_entry;
            advance_status_timers(actor);
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            (*((u8 *)actor + 0x6D))--;
            actor->action_flags &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }
    }
}

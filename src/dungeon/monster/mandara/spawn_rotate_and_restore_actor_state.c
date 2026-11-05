#include "shared/sprite_source.h"
#include "shared/entity.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/level.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/item/actor_target.h"
#include "dungeon/actor/state.h"
#include "dungeon/item/message.h"
#include "sdk/libc.h"

typedef struct S_80174668_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    u8 * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80174668_2;   /* arg3 in spawn_rotate_and_restore_actor_state */

typedef struct S_80174668_4 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    u32 unk_08;
    u32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_80174668_4;   /* tile in spawn_rotate_and_restore_actor_state */

typedef struct S_80174668_7 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174668_7;   /* state_object in spawn_rotate_and_restore_actor_state */

typedef struct {
    s16 x;
    s16 y;
    s16 dx;
    s16 dy;
} SpawnOffset;

typedef struct {
    s16 x;
    s16 y;
} Position2;

void spend_actor_mp(ActorRecord *entity, s32 base_reduction);
extern void draw_transformed_sprite_with_clip_rect(void *, void *, void *, s32, s32);

extern u8 rotating_particle_sprite_entries[];
extern u32 actor_update_node_cursor[];
extern u8 D_8017086C[];
extern u8 D_80170874[];

extern u8 mandara_object_callback_2[];
#include "dungeon/monster/mandara.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

/* Spawns and rotates an object, emits particles, then restores the actor state. */
/* Targets a monster ahead, rotates it amid green particles, attempts confusion, and spends Mandara's MP
 * before restoring movement. */
void spawn_rotate_and_restore_actor_state(ActorRecord *effect, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    SpawnOffset spawn = *(SpawnOffset *)D_8017086C;
    Position2 center;
    s32 state;
    u8 *spawned_object;
    S_80174668_7 *rotating_object;
    ObjectPosition *particle_pos;
    ObjectNodeHeader *effect_alloc;
    RotateAndRestoreActorStateBody *effect_data;
    u8 *direction_table;
    SpriteFrameState *tile;
    void *context;
    void *previous_context;
    s32 random;
    void *result;
    s32 height;
    s32 ticks_left;

    state = effect->action_phase.u;
    switch (state) {
    case 0:
        spawned_object = scan_actor_along_heading(actor, sprite->tile_x,
            sprite->tile_y, actor->facing, 0x10);
        actor->target = spawned_object;
        direction_table = mandara_direction_frames;
        sprite->frameTable = direction_table;
        select_sprite_entry(sprite,
            direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        if (sprite->flags & 0x8000) {
            effect->action_phase.u = 2;
            return;
        }

        effect->action_phase.u = 1;
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if (actor->target == 0) {
            return;
        }

        result = append_entity_display_text(actor, context = get_unused_text_buffer());
        previous_context = context;
        context = result;
        result = expand_text_control_codes(D_80170874, context);
        clear_byte_and_advance(result);
        display_text_with_fullwidth_adjustment(previous_context);
        play_sound_if_enabled(0x60A);

        tile = NODE_HEADER(((S_80174668_2 *)actor)->unk_60)->sprite;
        actor->target_tile_x = tile->tile_x;
        actor->target_tile_y = tile->tile_y;
        center.x = spawn.x + (spawn.dx >> 1);
        center.y = spawn.y + (spawn.dy >> 1);
        draw_transformed_sprite_with_clip_rect(effect, &spawn, &center, 1, 0);

        effect_alloc = allocate_list_node(0x201, &scene_object_list_anchor.next);
        if (effect_alloc == 0) {
            return;
        }
        register_node(effect_alloc, draw_layered_wavy_object_strips);
        effect_alloc->update_callback = advance_actor_replacement_sequence;
        effect_data = NODE_BODY(effect_alloc);
        effect_data->target_x = (sprite->tile_x << 6) + 0x20;
        effect_data->target_y = (sprite->tile_y << 6) + 0x20;
        {
            register u32 color;
            s32 countdown;
            u16 motion_param;
            color = 0x00808080;
            motion_param = motion->z.w.i;
            countdown = 0x3C;
            effect_data->color = color;
            effect_data->ticks_remaining = countdown;
            effect_data->vertical_motion = motion_param;
            effect->action_timer.s = countdown;
            return;
        }

    case 1:
        rotating_object = actor->target;
        if ((rotating_object != 0) && (effect->action_timer.s < 0x34)) {
            rotating_object->unk_2A =
                (rotating_object->unk_2A + 0x200) & 0x3FFF;
            effect_alloc = allocate_list_node(0x312, &scene_object_list_anchor.next);
            if (effect_alloc != 0) {
                register_node(effect_alloc, project_sprite_chain);
                effect_data = NODE_BODY(effect_alloc);
                tile = effect_alloc->sprite;
                effect_alloc->update_callback = mandara_object_callback_2;

                random = rand();
                {
                    s32 tile_x = actor->target_tile_x;
                    ((ObjectPosition *)(*(u8 * *)&effect_alloc->position))->x.w.i =
                        (tile_x << 6) + (random % 64);
                }
                random = rand();
                {
                    s32 tile_y = actor->target_tile_y;
                    ((ObjectPosition *)(*(u8 * *)&effect_alloc->position))->y.w.i =
                        (tile_y << 6) + (random % 64);
                }
                particle_pos = effect_alloc->position;
                height = sample_terrain_surface_height(((u16)(particle_pos->x.w.i)),
                    ((u16)(particle_pos->y.w.i)), -0x400);
                {
                    s32 height_random = rand();
                    height -= height_random % 95;
                    height -= 0x20;
                }
                ((ObjectPosition *)(*(u8 * *)&effect_alloc->position))->z.w.i = height;

                tile->scale_y = 0xC04;
                tile->scale_x = 0xC04;
                tile->tpage_abr = 0x60;
                tile->unk_00 = rotating_particle_sprite_entries;
                tile->flags |= 0x0C;
                {
                    u32 texture_word = ((u32)((SpriteSourceEntry *)rotating_particle_sprite_entries)->source);
                    tile->unk_04 = 0;
                    tile->frame_ticks = 0;
                    tile->color.word = 0x00208020;
                    ((S_80174668_4 *)tile)->unk_08 = texture_word;
                }
                effect_data->state_9A = 0;
            }
        }
        ticks_left = effect->action_timer.u - 1;
        effect->action_timer.u = ticks_left;
        if ((ticks_left << 16) > 0) {
            return;
        }
        effect->action_phase.u++;
        return;

    case 2:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        spend_actor_mp(actor, 0x800);
        {
            void *actor_to_reset;
            actor_to_reset = actor;
            effect->unk_8C.address = update_long_actor_action;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor_to_reset);
        }
        if (actor->pending_turn_updates == 0) {
            actor->action_flags &= 0x7FFF;
        } else {
            actor_update_node_cursor[0] = (u32)((u8 *)actor - 0x20);
        }

        spawned_object = ((S_80174668_2 *)actor)->unk_60;
        if (spawned_object != 0) {
            try_apply_confusion_status(spawned_object, 0x28, 0x10);
        }

        return;
    default:
        return;
    }
}

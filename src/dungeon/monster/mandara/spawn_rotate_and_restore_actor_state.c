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

typedef struct S_80174668_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174668_0;   /* arg0 in spawn_rotate_and_restore_actor_state */

typedef struct S_80174668_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    union { void * s; u8 * u; } unk_60;   /* accessed as both */
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80174668_2;   /* arg3 in spawn_rotate_and_restore_actor_state */

typedef struct S_80174668_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174668_3;   /* arg1 in spawn_rotate_and_restore_actor_state */

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

typedef struct S_80174668_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80174668_5;   /* alloc in spawn_rotate_and_restore_actor_state */

typedef struct S_80174668_6 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 pad_9B[0x7];
    s16 unk_A2;
    s16 unk_A4;
    u16 unk_A6;
    u8 pad_A8[0x4];
    u32 unk_AC;
} S_80174668_6;   /* prim in spawn_rotate_and_restore_actor_state */

typedef struct S_80174668_7 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174668_7;   /* state_object in spawn_rotate_and_restore_actor_state */
typedef struct S_80174668_12 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80174668_12;   /* ((S_80174668_5 *)alloc)->unk_08 in spawn_rotate_and_restore_actor_state */

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

extern void select_sprite_entry(void *, s32, s32);
extern s32 rand(void);
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void spend_actor_mp(void *, s32);
extern void draw_transformed_sprite_with_clip_rect(void *, void *, void *, s32, s32);
extern void try_apply_confusion_status(void *, s32, s32);

extern u8 rotating_particle_sprite_entries[];
extern u32 actor_update_node_cursor[];
extern u8 D_8017086C[];
extern u8 D_80170874[];

extern u8 mandara_object_callback_2[];
#include "dungeon/monster/mandara.h"
#include "shared/sprite_frame_state.h"

/* Spawns and rotates an object, emits particles, then restores the actor state. */
/* Targets a monster ahead, rotates it amid green particles, attempts confusion, and spends Mandara's MP
 * before restoring movement. */
void spawn_rotate_and_restore_actor_state(S_80174668_0 *effect, S_80174668_3 *motion, SpriteFrameState *sprite, void *actor)
{
    SpawnOffset spawn = *(SpawnOffset *)D_8017086C;
    Position2 center;
    s32 state;
    u8 *spawned_object;
    S_80174668_7 *rotating_object;
    ObjectPosition *particle_pos;
    ObjectNodeHeader *effect_alloc;
    u8 *direction_table;
    S_80174668_6 *effect_data;
    SpriteFrameState *tile;
    void *context;
    void *previous_context;
    s32 random;
    void *result;
    s32 height;
    s32 ticks_left;

    state = effect->unk_9B;
    switch (state) {
    case 0:
        spawned_object = scan_actor_along_heading(actor, sprite->tile_x,
            sprite->tile_y, ((S_80174668_2 *)actor)->unk_2A, 0x10);
        ((S_80174668_2 *)actor)->unk_60.s = spawned_object;
        direction_table = mandara_direction_frames;
        sprite->frameTable = direction_table;
        select_sprite_entry(sprite,
            direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174668_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (sprite->flags & 0x8000) {
            effect->unk_9B = 2;
            return;
        }

        effect->unk_9B = 1;
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        if (((S_80174668_2 *)actor)->unk_60.s == 0) {
            return;
        }

        result = append_entity_display_text(actor, context = get_unused_text_buffer());
        previous_context = context;
        context = result;
        result = expand_text_control_codes(D_80170874, context);
        clear_byte_and_advance(result);
        display_text_with_fullwidth_adjustment(previous_context);
        play_sound_if_enabled(0x60A);

        tile = ((ObjectNodeHeader *)((u8 *)((S_80174668_2 *)actor)->unk_60.u - 0x20))->sprite;
        ((S_80174668_2 *)actor)->unk_72.s = tile->tile_x;
        ((S_80174668_2 *)actor)->unk_73.s = tile->tile_y;
        center.x = spawn.x + (spawn.dx >> 1);
        center.y = spawn.y + (spawn.dy >> 1);
        draw_transformed_sprite_with_clip_rect(effect, &spawn, &center, 1, 0);

        effect_alloc = allocate_list_node(0x201, &scene_object_list_anchor.next);
        if (effect_alloc == 0) {
            return;
        }
        register_node(effect_alloc, draw_layered_wavy_object_strips);
        effect_alloc->update_callback = advance_actor_replacement_sequence;
        effect_data = (S_80174668_6 *)(((u8 *)effect_alloc) + 0x20);
        effect_data->unk_A2 = (sprite->tile_x << 6) + 0x20;
        effect_data->unk_A4 = (sprite->tile_y << 6) + 0x20;
        {
            register u32 color;
            s32 countdown;
            u16 motion_param;
            color = 0x00808080;
            motion_param = motion->unk_0A;
            countdown = 0x3C;
            effect_data->unk_AC = color;
            effect_data->unk_96 = countdown;
            effect_data->unk_A6 = motion_param;
            effect->unk_96.s = countdown;
            return;
        }

    case 1:
        rotating_object = ((S_80174668_2 *)actor)->unk_60.s;
        if ((rotating_object != 0) && (effect->unk_96.s < 0x34)) {
            rotating_object->unk_2A =
                (rotating_object->unk_2A + 0x200) & 0x3FFF;
            effect_alloc = allocate_list_node(0x312, &scene_object_list_anchor.next);
            if (effect_alloc != 0) {
                register_node(effect_alloc, project_sprite_chain);
                effect_data = (S_80174668_6 *)(((u8 *)effect_alloc) + 0x20);
                tile = effect_alloc->sprite;
                effect_alloc->update_callback = mandara_object_callback_2;

                random = rand();
                {
                    s32 tile_x = ((S_80174668_2 *)actor)->unk_72.u;
                    ((S_80174668_12 *)(*(u8 * *)&effect_alloc->position))->unk_02 =
                        (tile_x << 6) + (random % 64);
                }
                random = rand();
                {
                    s32 tile_y = ((S_80174668_2 *)actor)->unk_73.u;
                    ((S_80174668_12 *)(*(u8 * *)&effect_alloc->position))->unk_06 =
                        (tile_y << 6) + (random % 64);
                }
                particle_pos = effect_alloc->position;
                height = sample_terrain_surface_height(*(u16 *)&particle_pos->x.w.i,
                    *(u16 *)&particle_pos->y.w.i, -0x400);
                {
                    s32 height_random = rand();
                    height -= height_random % 95;
                    height -= 0x20;
                }
                ((S_80174668_12 *)(*(u8 * *)&effect_alloc->position))->unk_0A = height;

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
                effect_data->unk_9A = 0;
            }
        }
        ticks_left = effect->unk_96.u - 1;
        effect->unk_96.u = ticks_left;
        if ((ticks_left << 16) > 0) {
            return;
        }
        effect->unk_9B++;
        return;

    case 2:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        ((S_80174668_2 *)actor)->unk_73.s = 0;
        ((S_80174668_2 *)actor)->unk_72.s = 0;
        spend_actor_mp(actor, 0x800);
        {
            void *actor_to_reset;
            actor_to_reset = actor;
            effect->unk_8C = update_long_actor_action;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor_to_reset);
        }
        if (((S_80174668_2 *)actor)->unk_6D == 0) {
            ((S_80174668_2 *)actor)->unk_46 &= 0x7FFF;
        } else {
            actor_update_node_cursor[0] = (u32)((u8 *)actor - 0x20);
        }

        spawned_object = ((S_80174668_2 *)actor)->unk_60.u;
        if (spawned_object != 0) {
            try_apply_confusion_status(spawned_object, 0x28, 0x10);
        }

        return;
    default:
        return;
    }
}

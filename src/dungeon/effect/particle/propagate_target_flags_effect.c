/* Terrain-colliding sprites, shaded particles, timed display slots, and staged projectile effects. */
#include "dungeon/effect/particle/propagate_target_flags_effect.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "shared/object_node.h"
#include "modules/dungeon_native_abi.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/record_ptrs.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"

void (*const dungeon_198a800_entry)(Work *, s32, s32) = update_staged_particle_effect;
const NativeOffsets58 D_80024004 = {{{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}}};
const RectTable D_80024024 = {{{832,320,64,64},{832,384,64,64},{832,448,64,64},{896,256,64,64},{896,320,64,64},{896,384,64,64},{896,448,64,64},{832,256,64,64}}};

/* Updates a countdown-driven visual and clears its owner slot when the countdown expires. */
extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern s32 rand(void);
extern s32 func_80024124(PointRecord *, ObjectPosition *);
extern void advance_counter_and_propagate_target_flags(void *);
extern u8 D_800DEC70[];
extern u8 D_800DECF8[];
extern void draw_transformed_sprite_with_clip_rect(void *, Rect16 *, void *, s32, s32);
extern s16 D_80082E86[6];
extern Template12 D_80026990;
extern Template12 D_8002699C;
extern Template12 D_800269A8;
extern s32 get_sprite_attachment_vector(void *, void *, void *, s32);
extern void drain_audio_commands_and_service_channels(void);
extern u32 func_80069EF8(void);

/* Shifts the sprite color toward blue, adjusts its offset, and clears its owner's indexed slot when
   the timer ends. */
void apply_random_actor_value_adjustment(void *state, void *unused, void *visual) {
    s32 remaining_ratio;
    u16 ticks_left;

    ticks_left = *(u16 *)((u8 *)state + 0x2C) - 1;
    remaining_ratio = (s32)((s32)(ticks_left << 16) >> 9) /
               (s16)*(u16 *)((u8 *)state + 0x2E);
    D_800269B4 = 1;
    *(u16 *)((u8 *)state + 0x2C) = ticks_left;
    *(u8 *)((u8 *)visual + 0x0E) += 4;
    *(s8 *)((u8 *)visual + 0x0D) = (s8)remaining_ratio;
    *(s8 *)((u8 *)visual + 0x0C) = (s8)remaining_ratio;
    if (*(s16 *)((u8 *)visual + 6) >= -6) {
        *(s16 *)((u8 *)visual + 6) -= 2;
    }
    if (*(s16 *)((u8 *)state + 0x2C) <= 0) {
        s16 *owner_slot;
        s32 slot_offset;
        s32 owner_addr;

        slot_offset = *(s16 *)((u8 *)state + 0x50) * 2;
        owner_addr = *(s32 *)((u8 *)state + 0x7C);
        owner_slot = (s16 *)(slot_offset + owner_addr + 0x64);
        *owner_slot = 0;
        *(u16 *)((u8 *)state - 2) |= NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}


/* Retail 8196A924 (func_80024124): projects each linked point and queues a brightness-scaled shaded tile
 * followed by a draw-mode packet for it. */
s32 func_80024124(PointRecord *first_point, ObjectPosition *first_position)
{
    PointRecord *point = first_point;
    ObjectPosition *position = first_position;
    GameWork *render_state = &g_game_work;
    u32 addr_mask = 0x00FFFFFF;
    GpuContext *render_ctx = g_game_work.draw_buffer;
    u8 *packet_start;
    u32 tag_mask = 0xFF000000;
    Scratch80024124 *scratch =
        (Scratch80024124 *)0x1F800000;
    PointPacket *tile;
    PointPacket *draw_mode;
    GpuContext *final_render_ctx;
    s32 color_value;
    s32 draw_page;
    ObjectNodeHeader *next_node;

    packet_start = render_ctx->packetCursor;
    scratch->ot = (u32 *)&render_ctx->orderTag;
    scratch->cursor = packet_start;

    for (;;) {
        tile = (PointPacket *)scratch->cursor;
        scratch->x = (u16)position->x.w.i;
        scratch->y = (u16)position->y.w.i;
        scratch->z = (u16)position->z.w.i;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = func_80065420(scratch, &tile->data,
                                       &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            *(u32 *)&tile->r = point->color;

            color_value = (s32)tile->r * point->brightness;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->r = color_value >> 7;

            color_value = (s32)tile->g * point->brightness;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->g = color_value >> 7;

            color_value = (s32)tile->b * point->brightness;
            tile->b = (color_value / 128);

            ((GpuLinkTag *)&tile->tag)->len = 2;
            tile->code = 0x6A;
            ((GpuLinkTag *)&tile->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)tile;

            draw_mode = (PointPacket *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = func_80066460(0, 1, 0, 0);
            func_80067F20(draw_mode, 0, 0, (u16)draw_page, 0);

            ((GpuLinkTag *)&draw_mode->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)draw_mode;
        }

        next_node = ((ObjectNodeHeader *)point - 1)->chain_next;
        if (next_node != 0) {
            point = (PointRecord *)(next_node + 1);
            position = next_node->unk_08;
            continue;
        }

        break;
    }

    final_render_ctx = render_state->draw_buffer;
    final_render_ctx->packetCursor = scratch->cursor;
    return 0;
}

/* Subtracts 8 from the object counter and sets flags when it reaches zero. */
void advance_counter_and_propagate_target_flags(void *object)
{
    u8 *object_bytes = object;
    u16 counter;

    counter = *(u16 *)(object_bytes + 50);
    D_800269B4 = 1;
    counter -= 8;
    *(u16 *)(object_bytes + 50) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(object_bytes - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}


/* Retail 8196ABC4 (func_800243C4): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..15 in x/y, 0..31 in z) and the given offsets (minus half the jitter range). */
void func_800243C4(ObjectNodeHeader *parent, s32 state_14_value, s32 state_08_value, s32 state_32_value,
                   s16 x_offset, s16 y_offset, s16 z_offset) {
    ObjectNodeHeader *spawned;
    ObjectPosition *position;
    PointRecord *state;
    s32 jitter;

    /* the parent's next slot is the list head the new node links behind */
    spawned = allocate_list_node(0x211, (ObjectNodeHeader **)parent);
    if (spawned != 0) {
        spawned->unk_10 = (void *)advance_counter_and_propagate_target_flags;
        /* Retail uses unsigned high-half arithmetic; the u16 store also
         * preserves CDK combine/scheduling before the next rand call. */
        jitter = rand();
        *(u16 *)&((ObjectPosition *)spawned->unk_08)->x.w.i =
            *(u16 *)&((ObjectPosition *)parent->unk_08)->x.w.i +
            (jitter & 0xF) + (x_offset - 8);
        jitter = rand();
        *(u16 *)&((ObjectPosition *)spawned->unk_08)->y.w.i =
            *(u16 *)&((ObjectPosition *)parent->unk_08)->y.w.i +
            (jitter & 0xF) + (y_offset - 8);
        state = (PointRecord *)(spawned + 1);
        jitter = rand();
        position = spawned->unk_08;
        *(u16 *)&position->z.w.i =
            *(u16 *)&((ObjectPosition *)parent->unk_08)->z.w.i +
            (jitter & 0x1F) + (z_offset - 0x10);
        state->unk_14 = state_14_value;
        state->brightness = state_32_value;
        register_node(spawned, (s32)func_80024124);
        state->color = state_08_value;
    }
}

   /* arg1 in func_8196ACE4 */

   /* the 0x2 bytes before arg0 in func_8196ACE4, addressed as arg0[-1] */

   /* arg0 in func_8196ACE4 */

   /* page_8002 in func_8196ACE4 */

   /* page_8008 in func_8196ACE4 */

/* Update effect motion, collisions, sprite fading and growth, and expiration. */
void func_800244E4(void *effect, S_8196ACE4_0 *position, SpriteFrameState *sprite) {
    s32 height;
    s16 life_left;
    s32 brightness;
    u16 anim_tick;
    u16 scale_x;
    u16 scale_y;
    u16 collide_x;
    u16 collide_y;
    s32 collide_z;

    position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((S_8196ACE4_1 *)effect)->unk_8C);
    ((S_8196ACE4_1 *)effect)->unk_8C = (s32) (((S_8196ACE4_1 *)effect)->unk_8C + ((S_8196ACE4_1 *)effect)->unk_98);
    collide_x = position->unk_00.at02.v;
    collide_y = position->unk_04.at02.v;
    collide_z = position->unk_08.at02.v;
    {
        u8 *collision_page = (u8 *)&D_800269B4 - 0x69B4;
        ((S_8196ACE4_2 *)collision_page)->unk_69B4 = 1;
    }
    if (((s16)sample_terrain_surface_height(collide_x, collide_y, collide_z) < 0x200) && ((check_left_tile_and_center_height(position->unk_00.at02.v,
        position->unk_04.at02.v, position->unk_08.at02.v) << 0x10) != 0)) {
        position->unk_00.at00.v = (s32) (position->unk_00.at00.v - ((S_8196ACE4_1 *)effect)->unk_8C);
        ((S_8196ACE4_1 *)effect)->unk_8C = 0;
        ((S_8196ACE4_1 *)effect)->unk_98 = 0;
    }
    position->unk_04.at00.v = (s32) (position->unk_04.at00.v + ((S_8196ACE4_1 *)effect)->unk_90);
    ((S_8196ACE4_1 *)effect)->unk_90 = (s32) (((S_8196ACE4_1 *)effect)->unk_90 + ((S_8196ACE4_1 *)effect)->unk_9C);
    if (((s16)sample_terrain_surface_height(position->unk_00.at02.v, position->unk_04.at02.v, position->unk_08.at02.v) < 0x200)
        && ((check_left_tile_and_center_height(position->unk_00.at02.v, position->unk_04.at02.v, position->unk_08.at02.v) << 0x10) != 0)) {
        position->unk_04.at00.v = (s32) (position->unk_04.at00.v - ((S_8196ACE4_1 *)effect)->unk_90);
        ((S_8196ACE4_1 *)effect)->unk_90 = 0;
        ((S_8196ACE4_1 *)effect)->unk_9C = 0;
    }
    position->unk_08.at00.v = (s32) (position->unk_08.at00.v + ((S_8196ACE4_1 *)effect)->unk_94);
    {
        s32 accel_z = ((S_8196ACE4_1 *)effect)->unk_A0;
        ((S_8196ACE4_1 *)effect)->unk_94 += accel_z;
    }
    ((S_8196ACE4_1 *)effect)->unk_8C = (s32) ((((S_8196ACE4_1 *)effect)->unk_8C * 0x60) / 100);
    ((S_8196ACE4_1 *)effect)->unk_90 = (s32) ((((S_8196ACE4_1 *)effect)->unk_90 * 0x60) / 100);
    height = position->unk_08.at02.v;
    if (((s16)sample_terrain_surface_height(position->unk_00.at02.v, position->unk_04.at02.v, (s16) (position->unk_08.at02u.v - 4)) - 0x10)
        < height) {
        ((S_8196ACE4_1 *)effect)->unk_94 = 0;
        position->unk_08.at02.v = (s16) ((s16)sample_terrain_surface_height(position->unk_00.at02.v, position->unk_04.at02.v,
            (s16) ((u16) position->unk_08.at02.v - 4)) - 0x11);
        position->unk_08.at00u.v = 0;
        if (((S_8196ACE4_1 *)effect)->unk_2A == 0) {
            ((S_8196ACE4_1 *)effect)->unk_2A = 1;
            ((S_8196ACE4_1 *)effect)->unk_8C = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 2);
            ((S_8196ACE4_1 *)effect)->unk_90 = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 2);
        }
    }
    brightness = (s32) (((S_8196ACE4_1 *)effect)->unk_2C << 7) / (s16) ((S_8196ACE4_1 *)effect)->unk_2E;
    sprite->color.c.b = (s8) brightness;
    sprite->color.c.g = (s8) brightness;
    sprite->color.c.r = (s8) brightness;
    anim_tick = ((S_8196ACE4_1 *)effect)->unk_34 + 1;
    ((S_8196ACE4_1 *)effect)->unk_34 = anim_tick;
    if ((s16) anim_tick == 3) {
        advance_sprite_animation_and_textures(sprite);
        ((S_8196ACE4_1 *)effect)->unk_34 = 0U;
    }
    scale_x = sprite->scale_x + 0xC8;
    sprite->scale_x = scale_x;
    if ((u32) (scale_x & 0xFFFF) >= 0x1001U) {
        sprite->scale_x = 0x1000U;
    }
    scale_y = sprite->scale_y + 0xC8;
    sprite->scale_y = scale_y;
    if ((u32) (scale_y & 0xFFFF) >= 0x1001U) {
        sprite->scale_y = 0x1000U;
    }
    life_left = (u16) ((S_8196ACE4_1 *)effect)->unk_2C - 1;
    ((S_8196ACE4_1 *)effect)->unk_2C = life_left;
    if ((life_left << 0x10) <= 0) {
        ((S_8196ACE4_1_pre *)effect)[-1].unk_00 = (u16) (((S_8196ACE4_1_pre *)effect)[-1].unk_00 | 0x8000);
        {
            u8 *status_page = (u8 *)0x80080000;
            ((S_8196ACE4_4 *)status_page)->unk_14A0 |= 0x8000;
        }
    }
    if (sprite->flags & 0x8000) {
        ((S_8196ACE4_1_pre *)effect)[-1].unk_00 = (u16) (((S_8196ACE4_1_pre *)effect)[-1].unk_00 | 0x8000);
        {
            u8 *status_page = (u8 *)0x80080000;
            ((S_8196ACE4_4 *)status_page)->unk_14A0 |= 0x8000;
        }
    }
}

   /* arg0 in func_8196B074 */

   /* arg1 in func_8196B074 */

/* Advance motion, resolve collisions, and mark expired objects for removal. */
void advance_terrain_colliding_sprite(void *motion, void *position, s32 update_id) {
    s32 height;
    u16 remaining_ticks;

    remaining_ticks = ((S_8196B074_0 *)motion)->unk_2C;
    D_800269B4 = 1;
    ((S_8196B074_0 *)motion)->unk_2C = remaining_ticks - 1;
    advance_sprite_animation_and_textures(update_id);
    ((S_8196B074_1 *)position)->unk_00.at00.v += ((S_8196B074_0 *)motion)->unk_8C;
    ((S_8196B074_0 *)motion)->unk_8C += ((S_8196B074_0 *)motion)->unk_98;
    if ((check_left_tile_and_center_height(((S_8196B074_1 *)position)->unk_00.at02.v, ((S_8196B074_1 *)position)->unk_04.at02.v,
        ((S_8196B074_1 *)position)->unk_08.at02.v) << 16) != 0) {
        ((S_8196B074_1 *)position)->unk_00.at00.v -= ((S_8196B074_0 *)motion)->unk_8C;
        ((S_8196B074_0 *)motion)->unk_8C = 0;
        ((S_8196B074_0 *)motion)->unk_98 = 0;
    }
    ((S_8196B074_1 *)position)->unk_04.at00.v += ((S_8196B074_0 *)motion)->unk_90;
    ((S_8196B074_0 *)motion)->unk_90 += ((S_8196B074_0 *)motion)->unk_9C;
    if ((check_left_tile_and_center_height(((S_8196B074_1 *)position)->unk_00.at02.v, ((S_8196B074_1 *)position)->unk_04.at02.v,
        ((S_8196B074_1 *)position)->unk_08.at02.v) << 16) != 0) {
        ((S_8196B074_1 *)position)->unk_04.at00.v -= ((S_8196B074_0 *)motion)->unk_90;
        ((S_8196B074_0 *)motion)->unk_90 = 0;
        ((S_8196B074_0 *)motion)->unk_9C = 0;
    }
    ((S_8196B074_1 *)position)->unk_08.at00.v += ((S_8196B074_0 *)motion)->unk_94;
    ((S_8196B074_0 *)motion)->unk_94 += ((S_8196B074_0 *)motion)->unk_A0;
    height = ((S_8196B074_1 *)position)->unk_08.at02.v;
    if (((s16)sample_terrain_surface_height(((S_8196B074_1 *)position)->unk_00.at02.v, ((S_8196B074_1 *)position)->unk_04.at02.v,
                       (s16)((u16)((S_8196B074_1 *)position)->unk_08.at02u.v - 4)) - 0x10) < height) {
        ((S_8196B074_0 *)motion)->unk_94 = 0;
        ((S_8196B074_0 *)motion)->unk_90 = 0;
        ((S_8196B074_0 *)motion)->unk_8C = 0;
        ((S_8196B074_1 *)position)->unk_08.at02.v = (s16)sample_terrain_surface_height(((S_8196B074_1 *)position)->unk_00.at02.v,
            ((S_8196B074_1 *)position)->unk_04.at02.v,
                                               (s16)((u16)((S_8196B074_1 *)position)->unk_08.at02.v - 4)) - 0x11;
        ((S_8196B074_1 *)position)->unk_08.at00u.v = 0;
        ((S_8196B074_0 *)motion)->unk_2C = 0;
    }
    if ((s16)((S_8196B074_0 *)motion)->unk_2C <= 0) {
        (*(u16 *)((u8 *)motion + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Dim the effect's color and flag completion when its countdown expires. */
void draw_effect_and_restore_clip(void *effect, s32 unused, u8 *primitive) {
    u16 ticks_left = *(u16 *)((u8 *)effect + 0x2C);

    D_800269B4 = 1;
    ticks_left -= 1;
    *(u16 *)((u8 *)effect + 0x2C) = ticks_left;

    if (primitive[12] >= 65) {
        primitive[14] = 64;
        primitive[13] = 64;
        primitive[12] = 64;
    }

    if (primitive[12] != 0) {
        s32 shade = primitive[14] - 5;

        primitive[14] = shade;
        primitive[13] = shade;
        primitive[12] = shade;
    }

    if (*(s16 *)((u8 *)effect + 0x2C) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates an effect with randomized position offsets and initializes its rendering state. */
void create_randomized_paletted_sprite(s32 unused_0, s32 unused_1, s32 unused_2, s16 x, s16 y, s16 z) {
    Effect *effect;
    EffectState *state;
    SpriteFrameState *render;
    Vec3u16 *position;
    s16 size;
    s32 jitter;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        state = &effect->payload.state;
        size = (rand() & 7) + 0x20;
        state->size_x = size;
        state->size_y = size;
        effect->callback.handler = func_800244E4;
        register_node(effect, (s32)project_sprite_chain);
        render = effect->visual.render;
        render->flags |= 0xC;
        render->tpage_abr = 0x60;
        render->flags |= 2;
        render->unk_06 = 0;
        position = effect->coordinates.position;
        position->x = x;
        position->y = y;
        position->z = z;
        position->x += ((u16)view_reference_entity.x.w.i);
        position->y += ((u16)view_reference_entity.y.w.i);
        position->z += ((u16)view_reference_entity.z.w.i);
        jitter = rand() & 0x1F;
        position->x -= 0x10;
        position->x += jitter;
        jitter = rand() & 0x1F;
        position->y -= 0x10;
        position->y += jitter;
        jitter = rand() & 0x1F;
        position->z -= 0x10;
        position->z += jitter;
        state->seed = rand();
        state->scale = 0x1000;
        render = effect->visual.render;
        render->scale_x = 0xC00;
        render->scale_y = 0xC00;
        render->color.c.b = 0x80;
        render->color.c.g = 0x80;
        render->color.c.r = 0x80;
        render->clut = 0x7DCF;
        render->flags |= 0x100;
        select_record_entry_and_value(render, effect_sprite_sources, 0);
    }
}

   /* sub in func_8196B4A4 */

   /* node in func_8196B4A4 */

   /* part in func_8196B4A4 */

   /* coords in func_8196B4A4 */

   /* coord_base in func_8196B4A4 */

   /* arg0 in func_8196B4A4 */


/* Spawns a sprite effect with randomized position and motion based on the source direction. */
void create_lingering_ballistic_sprite(S_8196B4A4_5 *source, s32 unused_1, s32 unused_2, s16 offset_x, s16 offset_y,
                   s16 offset_z)
{
    LocalPoints direction_points;
    void *effect;
    S_8196B4A4_0 *motion;
    SpriteFrameState *sprite;
    S_8196B4A4_3 *position;
    LocalPoint *directions;
    LocalPoint *direction;
    s32 direction_index;
    s16 spawn_y = offset_y;
    s16 spawn_z = offset_z;

    direction_points = D_80024004.raw;
    directions = (LocalPoint *)&direction_points;
    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        motion = (u8 *)effect + 0x20;
        motion->unk_2C = 0xF;
        ((S_8196B4A4_1 *)effect)->unk_10 = advance_terrain_colliding_sprite;
        register_node(effect, (s32)project_sprite_chain);

        sprite = ((S_8196B4A4_1 *)effect)->unk_0C;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;
        sprite->angle_z = (((s16)rand()) & 7) << 9;
        sprite->unk_06 = 0;

        position = ((S_8196B4A4_1 *)effect)->unk_08;
        position->unk_02 = offset_x;
        position->unk_06 = spawn_y;
        position->unk_0A = spawn_z;
        position->unk_02 += ((u16)view_reference_entity.x.w.i);
        position->unk_06 += ((u16)view_reference_entity.y.w.i);
        position->unk_0A += ((u16)view_reference_entity.z.w.i);

        position->unk_02 += (((s16)rand()) & 0x3F) - 0x20;
        position->unk_06 += (((s16)rand()) & 0x3F) - 0x20;
        position->unk_0A += (((s16)rand()) & 0x3F) - 0x40;

        motion->unk_94 = -0x60000;
        motion->unk_A0 = 0x20000;
        direction = directions;
        direction_index = source->unk_26;
        direction += direction_index;
        motion->unk_8C = direction->x << 18;
        direction = directions;
        direction_index = source->unk_26;
        direction += direction_index;
        motion->unk_90 = direction->y << 18;

        motion->unk_8C +=
            -0x80000 + ((((s16)rand()) & 0x3FFF) << 6);
        motion->unk_90 +=
            -0x80000 + ((((s16)rand()) & 0x3FFF) << 6);
        motion->unk_94 +=
            -0x80000 + ((((s16)rand()) & 0x3FFF) << 6);

        sprite = ((S_8196B4A4_1 *)effect)->unk_0C;
        sprite->scale_x = sprite->scale_y = 0x800;
        sprite->color.c.r = sprite->color.c.g =
            sprite->color.c.b = 0x80;
        sprite->clut = 0x7DCE;
        sprite->flags |= 0x100;
        select_record_entry_and_value(sprite, D_800DEC70, 0);
    }
}

/* MECHANISM: The 0x20 byte-aligned copy object preserves the 0x58 frame and lwl/lwr stack copy;
   a held D_80083780 base plus RMW updates restores the load-delay moves and $a0 base.
   Epilogue-held arg pins and split point base/index/add produce the retail saved roles and $s6+$v0 order. */

   /* sub in func_8196B780 */

   /* node in func_8196B780 */

   /* part in func_8196B780 */

   /* coords in func_8196B780 */

   /* coord_base in func_8196B780 */

   /* arg0 in func_8196B780 */


/* Spawns an effect with randomized position and direction-based motion. */
void create_brief_ballistic_sprite(S_8196B780_5 *source, s32 unused_1, s32 unused_2, s16 x, s16 y,
                   s16 z)
{
    LocalPoints points;
    void *effect;
    S_8196B780_0 *motion;
    SpriteFrameState *sprite;
    S_8196B780_3 *position;
    LocalPoint *point_base;
    LocalPoint *point;
    s32 point_index;
    s16 offset_y = y;
    s16 offset_z = z;

    points = D_80024004.raw;
    point_base = (LocalPoint *)&points;
    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        motion = (u8 *)effect + 0x20;
        motion->unk_2C = 0x4;
        ((S_8196B780_1 *)effect)->unk_10 = advance_terrain_colliding_sprite;
        register_node(effect, (s32)project_sprite_chain);

        sprite = ((S_8196B780_1 *)effect)->unk_0C;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;
        sprite->angle_z = (((s16)rand()) & 7) << 9;
        sprite->unk_06 = 0;

        position = ((S_8196B780_1 *)effect)->unk_08;
        position->unk_02 = x;
        position->unk_06 = offset_y;
        position->unk_0A = offset_z;
        position->unk_02 += ((u16)view_reference_entity.x.w.i);
        position->unk_06 += ((u16)view_reference_entity.y.w.i);
        position->unk_0A += ((u16)view_reference_entity.z.w.i);

        position->unk_02 += (((s16)rand()) & 0x3F) - 0x20;
        position->unk_06 += (((s16)rand()) & 0x3F) - 0x20;
        position->unk_0A += (((s16)rand()) & 0x3F) - 0x40;

        motion->unk_94 = -0x60000;
        motion->unk_A0 = 0x20000;
        point = point_base;
        point_index = source->unk_26;
        point += point_index;
        motion->unk_8C = point->x << 18;
        point = point_base;
        point_index = source->unk_26;
        point += point_index;
        motion->unk_90 = point->y << 18;

        motion->unk_8C +=
            -0x80000 + ((((s16)rand()) & 0x3FFF) << 6);
        motion->unk_90 +=
            -0x80000 + ((((s16)rand()) & 0x3FFF) << 6);
        motion->unk_94 +=
            -0x80000 + ((((s16)rand()) & 0x3FFF) << 6);

        sprite = ((S_8196B780_1 *)effect)->unk_0C;
        sprite->scale_x = sprite->scale_y = 0x1000;
        sprite->color.c.r = sprite->color.c.g =
            sprite->color.c.b = 0x80;
        sprite->clut = 0x7DCE;
        sprite->flags |= 0x100;
        select_record_entry_and_value(sprite, D_800DECF8, 0);
    }
}

/* MECHANISM: The 0x20 byte-aligned copy object preserves the 0x58 frame and lwl/lwr stack copy;
   a held D_80083780 base plus RMW updates restores the load-delay moves and $a0 base.
   Epilogue-held arg pins and split point base/index/add produce the retail saved roles and $s6+$v0 order. */

   /* work in func_8196BA5C */

   /* obj in func_8196BA5C */

   /* the 0x18 bytes before D_800814A8 in func_8196BA5C, addressed as D_800814A8[-1] */


/* Creates an object in the first free rectangle slot and marks completion when the timer expires. */
void create_timed_rectangle_effect(void *owner) {
    s16 center[2];
    RectTable slot_rects;
    u8 *copy_src;
    u8 *copy_dst;
    u8 *copy_end;
    s16 slot;
    s32 rect_offset;
    Rect16 *rect;
    void *child;
    u8 *child_work;
    Display *display;
    void *source_vector;
    void *child_vector;
    u16 ticks_left;

    copy_dst = (u8 *)&slot_rects;
    copy_src = (u8 *)&D_80024024;
    if ((u32)copy_src & 3) {
        copy_end = copy_src + sizeof(RectTable);
        do {
            *(PackedBlock *)copy_dst = *(PackedBlock *)copy_src;
            copy_src += sizeof(PackedBlock);
            copy_dst += sizeof(PackedBlock);
        } while (copy_src != copy_end);
    } else {
        copy_end = copy_src + sizeof(RectTable);
        do {
            *(AlignedBlock *)copy_dst = *(AlignedBlock *)copy_src;
            copy_src += sizeof(AlignedBlock);
            copy_dst += sizeof(AlignedBlock);
        } while (copy_src != copy_end);
    }

    D_800269B4 = 1;

    slot = 0;
    while (slot < 8 && (*(s16 *)((u8 *)owner + 0x64 + (((s32)slot << 16) >> 15))) != 0) {
        slot++;
    }

    if (slot != 8) {
        (*(s16 *)((u8 *)owner + 0x64 + slot * 2)) = 1;
        rect_offset = (s32)slot << 3;
        rect = (Rect16 *)((u8 *)&slot_rects + rect_offset);
        center[0] = rect->x + ((s16)rect->w >> 1);
        center[1] = rect->y + 0x30;
        draw_transformed_sprite_with_clip_rect(primary_actor_record, rect, center, 1, 1);

        child = allocate_flagged_object_node(0x212);
        if (child != 0) {
            child_work = (u8 *)child + 0x20;
            ((S_8196BA5C_0 *)child_work)->unk_2C = 7;
            ((S_8196BA5C_0 *)child_work)->unk_2E = 7;
            ((S_8196BA5C_0 *)child_work)->unk_50 = slot;
            ((S_8196BA5C_0 *)child_work)->unk_7C = owner;
            ((S_8196BA5C_1 *)child)->unk_10 = apply_random_actor_value_adjustment;
            register_node(child, (s32)project_sprite_chain);

            display = ((S_8196BA5C_1 *)child)->unk_0C;
            display->field6 = 4;
            display->flags &= 0xFFF3;

            source_vector = ((S_8196BA5C_2_pre *)primary_actor_record)[-1].unk_00;
            child_vector = ((S_8196BA5C_1 *)child)->unk_08;
            ((s32 *)child_vector)[0] = ((s32 *)source_vector)[0];
            ((s32 *)child_vector)[1] = ((s32 *)source_vector)[1];
            ((s32 *)child_vector)[2] = ((s32 *)source_vector)[2];

            display = ((S_8196BA5C_1 *)child)->unk_0C;
            display->scaleX = 0x1000;
            display->scaleY = 0x1000;
            display->blue = 0x80;
            display->green = 0x80;
            display->red = 0x80;

            *(PackedVec3 *)((u8 *)child + 0x58) = D_80026978;
            display->vector = (u8 *)child + 0x58;
            ((S_8196BA5C_0 *)child_work)->unk_40 = (u8)rect->x - 0x40;
            ((S_8196BA5C_0 *)child_work)->unk_41 = (u8)rect->y;
        }
    }

    ticks_left = (*(u16 *)((u8 *)owner + 0x2C)) - 1;
    (*(u16 *)((u8 *)owner + 0x2C)) = ticks_left;
    if ((s16)ticks_left <= 0) {
        (*(u16 *)((u8 *)owner + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* MECHANISM: The 0x80-byte frame, sibling table/center locals, packed copies,
   held object roles, and noreturn tail shape preserve the seed's 184-word body.
   A block-local $v1 page pin lets LEAD27 sink lui 0x8002 into the tail-j slot. */

   /* work in func_8196BD3C */

   /* obj in func_8196BD3C */

   /* the 0x18 bytes before arg0 in func_8196BD3C, addressed as arg0[-1] */

/* Creates a display object at the source position with zero scale and color. */
void func_8002553C(void *source, s32 unused_position, s32 unused_render) {
    void *object;
    u8 *object_state;
    Display *display;
    void *source_pos;
    void *object_pos;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        object_state = (u8 *)object + 0x20;
        ((S_8196BD3C_0 *)object_state)->unk_2C = 0xB;
        ((S_8196BD3C_0 *)object_state)->unk_7C = source;
        ((S_8196BD3C_1 *)object)->unk_10 = create_timed_rectangle_effect;
        register_node(object, (s32)project_sprite_chain);

        display = ((S_8196BD3C_1 *)object)->unk_0C;
        display->field10 = 0x20;
        display->field6 = 0;
        display->flags |= 0xC;

        source_pos = ((S_8196BD3C_2_pre *)source)[-1].unk_00;
        object_pos = ((S_8196BD3C_1 *)object)->unk_08;
        ((s32 *)object_pos)[0] = ((s32 *)source_pos)[0];
        ((s32 *)object_pos)[1] = ((s32 *)source_pos)[1];
        ((s32 *)object_pos)[2] = ((s32 *)source_pos)[2];

        display = ((S_8196BD3C_1 *)object)->unk_0C;
        display->scaleX = 0;
        display->scaleY = 0;
        display->blue = 0;
        display->green = 0;
        display->red = 0;

        *(PackedVec3 *)((u8 *)object + 0x58) = D_80026978;
        display->vector = (u8 *)object + 0x58;
    }
}

   /* the 0x2 bytes before obj in func_8196BE48, addressed as obj[-1] */

   /* obj in func_8196BE48 */

   /* arg2 in func_8196BE48 */

/* Advance the effect animation, offset its sprite, and mark it expired when its lifetime ends. */
void update_timed(void *effect_data, s32 unused, void *sprite) {
    u8 *effect = effect_data;
    u8 *global_page = (u8 *)&D_800269B4 - 0x69B4;
    u16 frame_ticks;
    u16 frame_index;
    u8 texture_u;

    ((S_8196BE48_0 *)effect)->unk_2C = (u16)(((S_8196BE48_0 *)effect)->unk_2C - 1);
    ((S_8196BE48_1 *)sprite)->unk_1C = (u16)(((S_8196BE48_1 *)sprite)->unk_1C + 0x7C);
    ((S_8196BE48_1 *)sprite)->unk_1E = (u16)(((S_8196BE48_1 *)sprite)->unk_1E + 0x54);
    frame_ticks = ((S_8196BE48_0 *)effect)->unk_34 + 1;
    *(s16 *)(global_page + 0x69B4) = 1;
    ((S_8196BE48_0 *)effect)->unk_34 = frame_ticks;
    if ((s16)frame_ticks == 3) {
        frame_index = ((S_8196BE48_0 *)effect)->unk_50 + 1;
        ((S_8196BE48_0 *)effect)->unk_50 = frame_index;
        if ((s16)frame_index < 7) {
            ((S_8196BE48_0 *)effect)->unk_34 = 0;
            texture_u = ((S_8196BE48_0 *)effect)->unk_40 + 0x18;
            ((S_8196BE48_0 *)effect)->unk_40 = texture_u;
            if ((texture_u & 0xFF) == 0x60) {
                ((S_8196BE48_0 *)effect)->unk_40 = 0;
                ((S_8196BE48_0 *)effect)->unk_41 = (u8)(((S_8196BE48_0 *)effect)->unk_41 + 0x20);
            }
        }
    }
    if ((s16)((S_8196BE48_0 *)effect)->unk_2C <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16)(((S_8196BE48_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

   /* the 0x2 bytes before arg0 in advance_effect_animation, addressed as arg0[-1] */

   /* arg0 in advance_effect_animation */

   /* arg2 in advance_effect_animation */

/* Advance the effect animation and flag completion when its countdown expires. */
void shrink_effect_and_step_texture(void *effect, s32 unused, S_8196BF24_1 *transform) {
    u8 next_u;

    ((S_8196BF24_0 *)effect)->unk_2C.s = (s16)(((S_8196BF24_0 *)effect)->unk_2C.s - 1);
    transform->unk_1C = (u16)(transform->unk_1C - 0x300);
    transform->unk_1E = (u16)(transform->unk_1E - 0x200);
    next_u = ((S_8196BF24_0 *)effect)->unk_40 - 0x18;
    ((S_8196BF24_0 *)effect)->unk_40 = next_u;
    if ((next_u & 0xFF) == 0xE8) {
        ((S_8196BF24_0 *)effect)->unk_40 = 0x18U;
        ((S_8196BF24_0 *)effect)->unk_41 = (u8)(((S_8196BF24_0 *)effect)->unk_41 - 0x20);
    }
    if (((S_8196BF24_0 *)effect)->unk_2C.u <= 0) {
        ((S_8196BF24_0_pre *)effect)[-1].unk_00 = (u16)(((S_8196BF24_0_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

   /* arg1 in update_renders */

   /* arg0 in update_renders */

   /* arg2 in update_renders */

   /* camera in update_renders */

/* Updates and renders a shrinking object with collision and lifetime checks. */
void advance_particle_emitting_projectile(void *object, void *position, void *render_state)
{
    s32 height;
    s16 scale_x;
    s16 scale_y;
    s32 collide_x;
    s32 collide_y;
    s32 collide_z;

    ((S_8196BFB0_0 *)position)->unk_00.at00.v += ((S_8196BFB0_1 *)object)->unk_8C;
    ((S_8196BFB0_1 *)object)->unk_8C += ((S_8196BFB0_1 *)object)->unk_98;
    collide_x = ((S_8196BFB0_0 *)position)->unk_00.at02.v;
    collide_y = ((S_8196BFB0_0 *)position)->unk_04.at02.v;
    collide_z = ((S_8196BFB0_0 *)position)->unk_08.at02.v;
    D_800269B4 = 1;
    if ((s16)check_left_tile_and_center_height(collide_x, collide_y, collide_z) != 0) {
        ((S_8196BFB0_0 *)position)->unk_00.at00.v -= ((S_8196BFB0_1 *)object)->unk_8C;
        ((S_8196BFB0_1 *)object)->unk_8C = 0;
        ((S_8196BFB0_1 *)object)->unk_98 = 0;
    }

    ((S_8196BFB0_0 *)position)->unk_04.at00.v += ((S_8196BFB0_1 *)object)->unk_90;
    ((S_8196BFB0_1 *)object)->unk_90 += ((S_8196BFB0_1 *)object)->unk_9C;
    if ((s16)check_left_tile_and_center_height(((S_8196BFB0_0 *)position)->unk_00.at02.v,
                           ((S_8196BFB0_0 *)position)->unk_04.at02.v,
                           ((S_8196BFB0_0 *)position)->unk_08.at02.v) != 0) {
        ((S_8196BFB0_0 *)position)->unk_04.at00.v -= ((S_8196BFB0_1 *)object)->unk_90;
        ((S_8196BFB0_1 *)object)->unk_90 = 0;
        ((S_8196BFB0_1 *)object)->unk_9C = 0;
    }

    ((S_8196BFB0_0 *)position)->unk_08.at00.v += ((S_8196BFB0_1 *)object)->unk_94;
    ((S_8196BFB0_1 *)object)->unk_94 += ((S_8196BFB0_1 *)object)->unk_A0;

    height = ((S_8196BFB0_0 *)position)->unk_08.at02.v;
    if ((s16)(s16)sample_terrain_surface_height(((S_8196BFB0_0 *)position)->unk_00.at02.v,
                           ((S_8196BFB0_0 *)position)->unk_04.at02.v,
                           (s16)(((S_8196BFB0_0 *)position)->unk_08.at02u.v - 4)) - 0x10 < height) {
        ((S_8196BFB0_1 *)object)->unk_94 = 0;
        ((S_8196BFB0_1 *)object)->unk_90 = 0;
        ((S_8196BFB0_1 *)object)->unk_8C = 0;
        ((S_8196BFB0_0 *)position)->unk_08.at02.v =
            (s16)sample_terrain_surface_height(((S_8196BFB0_0 *)position)->unk_00.at02.v,
                          ((S_8196BFB0_0 *)position)->unk_04.at02.v,
                          (s16)(((S_8196BFB0_0 *)position)->unk_08.at02p.v - 4)) - 0x11;
        ((S_8196BFB0_0 *)position)->unk_08.at00u.v = 0;
        ((S_8196BFB0_1 *)object)->unk_2C = 0;
    }

    if (((S_8196BFB0_1 *)object)->unk_50++ >= 3) {
        scale_x = ((S_8196BFB0_2 *)render_state)->unk_1C.u;
        scale_y = ((S_8196BFB0_2 *)render_state)->unk_1E.u;
        scale_x = scale_x - 0x100;
        if (scale_x < 0) {
            scale_x = 0;
        }
        scale_y = scale_y - 0x100;
        if (scale_y < 0) {
            scale_y = 0;
        }
        ((S_8196BFB0_2 *)render_state)->unk_1C.s = scale_x;
        ((S_8196BFB0_2 *)render_state)->unk_1E.s = scale_y;
    }

    create_randomized_paletted_sprite(object, position, render_state,
                  (s16)(((S_8196BFB0_0 *)position)->unk_00.at02.v - ((u16)view_reference_entity.x.w.i)),
                  (s16)(((S_8196BFB0_0 *)position)->unk_04.at02.v - ((u16)view_reference_entity.y.w.i)),
                  (s16)(((S_8196BFB0_0 *)position)->unk_08.at02p.v - ((u16)view_reference_entity.z.w.i)));

    if (--((S_8196BFB0_1 *)object)->unk_2C <= 0) {
        (*(u16 *)((u8 *)object + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

    if (((S_8196BFB0_2 *)render_state)->unk_14 & 0x8000) {
        (*(u16 *)((u8 *)object + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

   /* arg1 in func_8196C280 */

   /* arg0 in func_8196C280 */

   /* arg2 in func_8196C280 */

/* Move the effect with collision checks, shrink its sprite, and expire it when finished. */
void shrink_particle_emitting_projectile(void *effect, void *position, void *sprite) {
    u16 age;
    u16 reduced_scale_x;
    u16 reduced_scale_y;
    u16 life_left;
    u16 scale_x;
    u16 next_scale_y;

    ((S_8196C280_0 *)position)->unk_00.at00.v += ((S_8196C280_1 *)effect)->unk_8C;
    ((S_8196C280_1 *)effect)->unk_8C += ((S_8196C280_1 *)effect)->unk_98;
    {
        u16 check_x;
        u16 check_y;
        s32 check_z;

        check_x = ((S_8196C280_0 *)position)->unk_00.at02.v;
        check_y = ((S_8196C280_0 *)position)->unk_04.at02.v;
        check_z = ((S_8196C280_0 *)position)->unk_08.at02.v;
        D_800269B4 = 1;
        if ((check_left_tile_and_center_height(check_x, check_y, check_z) << 0x10) != 0) {
            ((S_8196C280_0 *)position)->unk_00.at00.v -= ((S_8196C280_1 *)effect)->unk_8C;
            ((S_8196C280_1 *)effect)->unk_8C = 0;
            ((S_8196C280_1 *)effect)->unk_98 = 0;
        }
    }
    ((S_8196C280_0 *)position)->unk_04.at00.v += ((S_8196C280_1 *)effect)->unk_90;
    ((S_8196C280_1 *)effect)->unk_90 += ((S_8196C280_1 *)effect)->unk_9C;
    if ((check_left_tile_and_center_height(((S_8196C280_0 *)position)->unk_00.at02.v, ((S_8196C280_0 *)position)->unk_04.at02.v,
        ((S_8196C280_0 *)position)->unk_08.at02.v) << 0x10) != 0) {
        ((S_8196C280_0 *)position)->unk_04.at00.v -= ((S_8196C280_1 *)effect)->unk_90;
        ((S_8196C280_1 *)effect)->unk_90 = 0;
        ((S_8196C280_1 *)effect)->unk_9C = 0;
    }
    ((S_8196C280_0 *)position)->unk_08.at00.v += ((S_8196C280_1 *)effect)->unk_94;
    ((S_8196C280_1 *)effect)->unk_94 += ((S_8196C280_1 *)effect)->unk_A0;
    {
        s32 height;

        height = ((S_8196C280_0 *)position)->unk_08.at02.v;
        if (((s16)sample_terrain_surface_height(((S_8196C280_0 *)position)->unk_00.at02.v, ((S_8196C280_0 *)position)->unk_04.at02.v,
            (s16)(((S_8196C280_0 *)position)->unk_08.at02u.v - 4)) - 0x10) < height) {
            ((S_8196C280_1 *)effect)->unk_94 = 0;
            ((S_8196C280_1 *)effect)->unk_90 = 0;
            ((S_8196C280_1 *)effect)->unk_8C = 0;
            ((S_8196C280_0 *)position)->unk_08.at02.v = (s16)sample_terrain_surface_height(((S_8196C280_0 *)position)->unk_00.at02.v,
                ((S_8196C280_0 *)position)->unk_04.at02.v, (s16)(((S_8196C280_0 *)position)->unk_08.at02u.v - 4))
            - 0x11;
            ((S_8196C280_0 *)position)->unk_08.at00u.v = 0;
            ((S_8196C280_1 *)effect)->unk_2C = 0;
        }
    }
    age = ((S_8196C280_1 *)effect)->unk_50;
    ((S_8196C280_1 *)effect)->unk_50 = age + 1;
    if ((s16)age >= 3) {
        scale_x = ((S_8196C280_2 *)sprite)->unk_1C;
        next_scale_y = ((S_8196C280_2 *)sprite)->unk_1E;
        reduced_scale_x = scale_x - 0x100;
        scale_x = reduced_scale_x;
        if ((s16)reduced_scale_x < 0) {
            scale_x = 0;
        }
        reduced_scale_y = next_scale_y - 0x100;
        next_scale_y = reduced_scale_y;
        if ((s16)reduced_scale_y < 0) {
            next_scale_y = 0;
        }
        if (((next_scale_y << 0x10) == 0) || ((scale_x << 0x10) == 0)) {
            ((S_8196C280_1 *)effect)->unk_2C = 0;
        }
        ((S_8196C280_2 *)sprite)->unk_1C = scale_x;
        ((S_8196C280_2 *)sprite)->unk_1E = next_scale_y;
    }
    create_randomized_paletted_sprite(effect, position, sprite,
        (s16)(((S_8196C280_0 *)position)->unk_00.at02.v - ((u16)view_reference_entity.x.w.i)),
        (s16)(((S_8196C280_0 *)position)->unk_04.at02.v - ((u16)view_reference_entity.y.w.i)),
        (s16)(((S_8196C280_0 *)position)->unk_08.at02u.v - ((u16)view_reference_entity.z.w.i)));
    life_left = ((S_8196C280_1 *)effect)->unk_2C - 1;
    ((S_8196C280_1 *)effect)->unk_2C = life_left;
    if ((life_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    if (((S_8196C280_2 *)sprite)->unk_14 & 0x8000) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}



/* Update the staged particle effect and clear its actor state when it finishes. */
void update_staged_particle_effect(Work *work, s32 position_arg, s32 sprite_arg)
{
    OffsetTable offsets;
    Effect *effect;
    Sprite *sprite;
    Motion *motion;
    register s32 particle_index;
    Position *pos;
    DungeonState *dungeon;
    DungeonState *dungeon_2;
    u8 *effect_page;
    u8 *active_page;
    void *object;
    s32 next_state;
    u16 direction_index;
    u16 dungeon_count;
    u8 object_kind;
    s16 init_timer;
    s32 spawn_timer;
    register s32 state;
    register u32 random;
    u16 local_y;

    offsets = D_80024004.signed_pairs;
    work->counter++;
    state = work->state;
    switch (state) {
    case 0:
        dungeon = *(DungeonState **)((u8 *)(&primary_actor_record));
        init_timer = 33;
        effect_page = (u8 *)0x80020000;
        *(s32 *)&dungeon->pad0[0xF4] = 0;
        *(s16 *)&dungeon->pad0[0x96] = init_timer;
        D_80082E86[0] = 6;
        next_state = (u16)work->state + 1;
        D_800269B4 = 1;
        work->state = next_state;
    case 1:
        object = work->object;
        if ((*(u16 *)object & 0x80) == 0) {
            return;
        }
        active_page = (u8 *)0x80080000;
        dungeon_2 = *(DungeonState **)(active_page + 0x14A8);
        work->timer = 45;
        dungeon_count = *(u16 *)&dungeon_2->pad0[0xA6];
        dungeon_count--;
        *(u16 *)&dungeon_2->pad0[0xA6] = dungeon_count;
        object_kind = work->kind;
        dungeon_2->pad0[0xA8] = object_kind;
        dungeon = *(DungeonState **)(active_page + 0x14A8);
        direction_index = ((*(u16 *)&dungeon->pad0[0x2A]) >> 9) & 7;
        work->state++;
        work->counter = 0;
        work->table_index = direction_index;
        func_8002553C(work, position_arg, sprite_arg);
        play_sound_if_enabled(0x300);
        drain_audio_commands_and_service_channels();
        return;

    case 2:
        if (work->timer < 39) {
            if (get_sprite_attachment_vector((((SearchContext *)&reference_tile_object))->field8, ((SearchContext *)&reference_tile_object), &work->x, 0)) {
                if (work->timer == 38) {
                    effect = allocate_flagged_object_node(0x212);
                    if (effect != 0) {
                        *(s16 *)&effect->payload.motion.pad0[0x2C] = 33;
                        effect->callback.update = update_timed;
                        register_node(effect, (s32)project_sprite_chain);
                        sprite = effect->visual.sprite;
                        sprite->unk10 = 32;
                        sprite->flags |= 0xC;
                        sprite->unk6 = -4;
                        pos = effect->coordinates.pos;
                        pos->x = work->x;
                        local_y = work->y;
                        pos->y = local_y;
                        pos->z = work->z;
                        pos->x += (((Position *)&view_reference_entity))->x;
                        pos->y += (((Position *)&view_reference_entity))->y;
                        pos->z += (((Position *)&view_reference_entity))->z;
                        sprite->scale_x = 0x900;
                        sprite->scale_y = 0x604;
                        sprite->b = 0x80;
                        sprite->g = 0x80;
                        sprite->r = 0x80;
                        *(Template12 *)&effect->payload.motion.pad0[0x38] = D_80026990;
                        sprite->image = &effect->payload.motion.pad0[0x38];
                    }
                }

                if (work->timer < 6) {
                    effect = allocate_flagged_object_node(0x212);
                    if (effect != 0) {
                        *(s16 *)&effect->payload.motion.pad0[0x2C] = 1;
                        effect->callback.update = draw_effect_and_restore_clip;
                        register_node(effect, (s32)project_sprite_chain);
                        sprite = effect->visual.sprite;
                        sprite->unk10 = 32;
                        sprite->flags |= 0xC;
                        sprite->unk6 = -4;
                        pos = effect->coordinates.pos;
                        pos->x = work->x;
                        local_y = work->y;
                        pos->y = local_y;
                        pos->z = work->z;
                        pos->x += (((Position *)&view_reference_entity))->x;
                        pos->y += (((Position *)&view_reference_entity))->y;
                        pos->z += (((Position *)&view_reference_entity))->z;
                        sprite->scale_x = 0x1800;
                        sprite->scale_y = 0x1000;
                        sprite->b = 0x80;
                        sprite->g = 0x80;
                        sprite->r = 0x80;
                        *(Template12 *)&effect->payload.motion.pad0[0x38] = D_8002699C;
                        sprite->image = &effect->payload.motion.pad0[0x38];
                    }
                }

                if (work->timer < 7) {
                    for (particle_index = 0; particle_index < 2; particle_index++) {
                        create_randomized_paletted_sprite(work, position_arg, sprite_arg, work->x, work->y, work->z);
                    }
                }
                if (work->timer < 3) {
                    particle_index = 0;
                    work->mid_x = (work->x + work->old_x) / 2;
                    work->mid_y = (work->y + work->old_y) / 2;
                    work->mid_z = (work->z + work->old_z) / 2;
                    for (; particle_index < 2; particle_index++) {
                        create_randomized_paletted_sprite(work, position_arg, sprite_arg,
                            work->mid_x, work->mid_y, work->mid_z);
                    }
                }
                work->old_x = work->x;
                work->old_y = work->y;
                work->old_z = work->z;
            }
        }
        work->timer--;
        if (work->timer > 0) {
            return;
        }
        work->timer = 16;
        work->state++;
        return;

    case 3:
        if (primary_actor_record->target != 0) {
            if (work->timer >= 13) {
                if (get_sprite_attachment_vector((((SearchContext *)&reference_tile_object))->field8, ((SearchContext *)&reference_tile_object), &work->x,
                    0)) {
                    for (particle_index = 0; particle_index < 4; particle_index++) {
                        create_lingering_ballistic_sprite(work, position_arg, sprite_arg, work->x, work->y, work->z);
                    }
                    for (particle_index = 0; particle_index < 4; particle_index++) {
                        create_brief_ballistic_sprite(work, position_arg, sprite_arg, work->x, work->y, work->z);
                    }
                    spawn_timer = work->timer;
                    if (spawn_timer == 16) {
                        effect = allocate_flagged_object_node(0x212);
                        if (effect != 0) {
                            motion = &effect->payload.motion;
                            *(s16 *)&motion->pad0[0x2C] = 30;
                            *(s16 *)&motion->pad0[0x2E] = 30;
                            effect->callback.update = advance_particle_emitting_projectile;
                            register_node(effect, (s32)project_sprite_chain);
                            sprite = effect->visual.sprite;
                            sprite->unk10 = 32;
                            sprite->flags |= 0xC;
                            motion->vel_z = (s32)0xFFF20000;
                            motion->accel_z = 0x00020000;
                            motion->vel_x = (s32)offsets.p[work->table_index].x << 19;
                            motion->vel_y = (u16)offsets.p[work->table_index].y << 19;
                            random = func_80069EF8();
                            motion->vel_x += (s32)0xFFFC0000 + ((random & 0x1FFF) << 6);
                            random = func_80069EF8();
                            motion->vel_y += (s32)0xFFFC0000 + ((random & 0x1FFF) << 6);
                            random = func_80069EF8();
                            motion->vel_z += (s32)0xFFFC0000 + ((random & 0x1FFF) << 6);
                            pos = effect->coordinates.pos;
                            pos->x = work->x;
                            local_y = work->y;
                            pos->y = local_y;
                            pos->z = work->z - 16;
                            pos->x += (((Position *)&view_reference_entity))->x;
                            pos->y += (((Position *)&view_reference_entity))->y;
                            pos->z += (((Position *)&view_reference_entity))->z;
                            sprite->scale_y = 0x1000;
                            sprite->scale_x = 0x1000;
                            sprite->b = 0x80;
                            sprite->g = 0x80;
                            sprite->r = 0x80;
                            *(Template12 *)&effect->payload.motion.pad0[0x38] = D_800269A8;
                            sprite->image = &effect->payload.motion.pad0[0x38];
                        }
                        if (work->timer == spawn_timer) {
                            effect = allocate_flagged_object_node(0x212);
                            if (effect != 0) {
                                motion = &effect->payload.motion;
                                *(s16 *)&motion->pad0[0x2C] = 30;
                                *(s16 *)&motion->pad0[0x2E] = 30;
                                effect->callback.update = shrink_particle_emitting_projectile;
                                register_node(effect, (s32)project_sprite_chain);
                                sprite = effect->visual.sprite;
                                sprite->unk10 = 32;
                                sprite->flags |= 0xC;
                                motion->vel_z = (s32)0xFFF20000;
                                motion->accel_z = 0x00020000;
                                motion->vel_x = (s32)offsets.p[work->table_index].x << 18;
                                motion->vel_y = (u16)offsets.p[work->table_index].y << 18;
                                random = func_80069EF8();
                                motion->vel_x += (s32)0xFFF80000 + ((random & 0x3FFF) << 6);
                                random = func_80069EF8();
                                motion->vel_y += (s32)0xFFF80000 + ((random & 0x3FFF) << 6);
                                random = func_80069EF8();
                                motion->vel_z += (s32)0xFFF80000 + ((random & 0x3FFF) << 6);
                                pos = effect->coordinates.pos;
                                pos->x = work->x;
                                local_y = work->y;
                                pos->y = local_y;
                                pos->z = work->z - 16;
                                pos->x += (((Position *)&view_reference_entity))->x;
                                pos->y += (((Position *)&view_reference_entity))->y;
                                pos->z += (((Position *)&view_reference_entity))->z;
                                sprite->scale_y = 0x1000;
                                sprite->scale_x = 0x1000;
                                sprite->b = 0x80;
                                sprite->g = 0x80;
                                sprite->r = 0x80;
                                *(Template12 *)&effect->payload.motion.pad0[0x38] = D_800269A8;
                                sprite->image = &effect->payload.motion.pad0[0x38];
                            }
                        }
                    }
                }
            }
        } else {
            if (work->timer == 16) {
                effect = allocate_flagged_object_node(0x212);
                if (effect != 0) {
                    motion = &effect->payload.motion;
                    *(s16 *)&motion->pad0[0x2C] = 7;
                    *(s16 *)&motion->pad0[0x2E] = 7;
                    effect->callback.update = shrink_effect_and_step_texture;
                    register_node(effect, (s32)project_sprite_chain);
                    sprite = effect->visual.sprite;
                    sprite->unk10 = 32;
                    sprite->flags |= 0xC;
                    pos = effect->coordinates.pos;
                    pos->x = work->x;
                    local_y = work->y;
                    pos->y = local_y;
                    pos->z = work->z;
                    pos->x += (((Position *)&view_reference_entity))->x;
                    pos->y += (((Position *)&view_reference_entity))->y;
                    pos->z += (((Position *)&view_reference_entity))->z;
                    sprite->scale_x = 0x1800;
                    sprite->scale_y = 0x1000;
                    sprite->b = 0x80;
                    sprite->g = 0x80;
                    sprite->r = 0x80;
                    *(Template12 *)&effect->payload.motion.pad0[0x38] = D_8002699C;
                    sprite->image = &effect->payload.motion.pad0[0x38];
                }
            }
            if (work->timer >= 13) {
                for (particle_index = 0; particle_index < 2; particle_index++) {
                    create_randomized_paletted_sprite(work, position_arg, sprite_arg,
                        work->x, work->y, (s16)(work->z - 8));
                }
            }
        }

        if ((reference_tile_object.sprite_flags & 0x8000) == 0) {
            work->timer--;
            if (work->timer >= 0) {
                return;
            }
        }
        work->state = 4;
        return;

    case 4:
        if (D_800269B4 == 0) {
            g_dungeon_status.active_actor = 0;
            reference_tile_object.unk_006 = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((u16 *)work)[-1] |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        D_800269B4 = 0;
    }
}

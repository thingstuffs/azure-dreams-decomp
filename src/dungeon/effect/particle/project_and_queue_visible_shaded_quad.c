#include "shared/object_node_flags.h"
#include "shared/audio_commands.h"
/* Visible shaded quad and point rendering, jittered sprites, and timed emission sequences. */
#include "dungeon/effect/particle/project_and_queue_visible_shaded_quad.h"
#include "shared/dungeon_effect_views.h"
#include "shared/sprite_frame_state.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/memory.h"
#include "slus.h"
#include "dungeon/system.h"

void (* const dungeon_1990800_entry)(FadingSpriteSequenceBody *, void *, void *) = advance_effect_sequence;
/* cfail-repair: tf7-phase1-cache-v3 */
#include "dungeon/effect/particle.h"
#include "shared/game_work.h"
typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef struct S_func_81970800_1 {
    u8 pad_00[0x24];
    u32 *unk_24;
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_func_81970800_1;

typedef struct S_func_81970800_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_func_81970800_2;

typedef struct S_func_81970800_3 {
    u8 pad_00[0x8];
    u8 *unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_func_81970800_3;

typedef struct S_func_81970800_4 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u8 pad_1C[0x30];
    u16 unk_4C;
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
} S_func_81970800_4;

typedef struct S_func_81970800_5 {
    union {
        u32 unk_00;
        struct {
            u8 pad_00[3];
            u8 unk_03;
        } unk_03;
    } unk_00;
    union {
        u32 unk_04;
        struct {
            u8 pad_04[3];
            u8 unk_07;
        } unk_07;
    } unk_04;
    u16 unk_08;
    u16 unk_0A;
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u32 unk_14;
    u16 unk_18;
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
} S_func_81970800_5;

typedef struct S_func_81970800_6 {
    u8 pad_00[0xB0];
    u32 unk_B0;
    u8 pad_B4[0x81C];
    u8 *unk_8D0;
} S_func_81970800_6;

/* Project and enqueue a shaded quad if its depth and screen bounds are visible. */
void project_and_queue_visible_shaded_quad(S_func_81970800_4 *quad, S_func_81970800_2 *position, S_func_81970800_3 *object, s16 depth_bias)
{
    S_func_81970800_1 *scratch = (S_func_81970800_1 *)0x1F800000;
    S_func_81970800_5 *packet;
    u8 *texture;
    s32 depth;
    u16 draw_flags;
    u8 tex_flags;
    u8 **render_context_ref = (u8 **)((u8 *)(&g_game_work));
    MATRIX matrix;

    scratch->unk_24 = (u32 *)(*(u8 **)&g_game_work.draw_buffer + 0xB0);
    scratch->unk_88 = position->unk_02;
    scratch->unk_8C = position->unk_06;
    scratch->unk_90 = position->unk_0A;
    object->unk_14 |= 0x8000;

    PushMatrix();

    scratch->unk_3C = 0x2000;
    scratch->unk_38 = 0x2000;
    scratch->unk_34 = 0x2000;
    scratch->unk_A4 = object->unk_16;
    scratch->unk_A8 = object->unk_1A;
    scratch->unk_A6 = object->unk_18;
    RotMatrix(&scratch->unk_A4, (u8 *)scratch + 0x74);
    ReadRotMatrix(&matrix);
    CompMatrix(&matrix, (u8 *)scratch + 0x74, (u8 *)scratch + 0x54);
    ScaleMatrix((u8 *)scratch + 0x54, &scratch->unk_34);
    SetTransMatrix((u8 *)scratch + 0x54);
    SetRotMatrix((u8 *)scratch + 0x54);

    texture = object->unk_08;
    scratch->unk_28 = object->unk_14;

    packet = (S_func_81970800_5 *)((S_func_81970800_6 *)g_game_work.draw_buffer)->unk_8D0;
    ((S_func_81970800_6 *)g_game_work.draw_buffer)->unk_8D0 = (u8 *)packet + 0xC;
    SetDrawMode(packet, 0, 0, GetTPage(0, 0, 0, 0) & 0xFFFF, 0);
    (packet->unk_00.unk_00) = (packet->unk_00.unk_00 & 0xFF000000) |
        (((S_func_81970800_6 *)g_game_work.draw_buffer)->unk_B0 & 0x00FFFFFF);
    (*(u32 *)((u8 *)g_game_work.draw_buffer + 0xB0)) =
        (((S_func_81970800_6 *)g_game_work.draw_buffer)->unk_B0 & 0xFF000000) |
        ((u32)packet & 0x00FFFFFF);

    {
        S_func_81970800_6 *render_context;

        render_context = g_game_work.draw_buffer;
        packet = (S_func_81970800_5 *)render_context->unk_8D0;
        render_context->unk_8D0 = (u8 *)packet + 0x24;
    }

    scratch->unk_B0 = quad->unk_4C;
    scratch->unk_B8 = quad->unk_52;
    scratch->unk_C0 = quad->unk_58;
    scratch->unk_C8 = quad->unk_5E;
    scratch->unk_B2 = quad->unk_4E;
    scratch->unk_BA = quad->unk_54;
    scratch->unk_C2 = quad->unk_5A;
    scratch->unk_CA = quad->unk_60;
    scratch->unk_B4 = quad->unk_50;
    scratch->unk_BC = quad->unk_56;
    scratch->unk_C4 = quad->unk_5C;
    scratch->unk_CC = quad->unk_62;

    depth = RotAverage4(&scratch->unk_B0, &scratch->unk_B8,
                          &scratch->unk_C0, &scratch->unk_C8,
                          &packet->unk_08, &packet->unk_10,
                          &packet->unk_18, &packet->unk_20,
                          (u8 *)scratch + 0xD0, (u8 *)scratch + 0xD4) - depth_bias - 6;
    scratch->unk_100 = depth;

    if ((u32)depth < 0x1E0) {
        if ((((u16)(packet->unk_08 + 0x20) < 0x181) &&
             ((u16)(packet->unk_0A + 0x20) < 0x121)) |
            (((u16)(packet->unk_10 + 0x20) < 0x181) &&
             ((u16)(packet->unk_12 + 0x20) < 0x121)) |
            (((u16)(packet->unk_18 + 0x20) < 0x181) &&
             ((u16)(packet->unk_1A + 0x20) < 0x121)) |
            (((u16)(packet->unk_20 + 0x20) < 0x181) &&
             ((u16)(packet->unk_22 + 0x20) < 0x121))) {
            object->unk_14 &= 0x7FFF;
            tex_flags = texture[1];
            object->unk_0F = tex_flags;
            draw_flags = scratch->unk_28;
            if (draw_flags & 8) {
                object->unk_0F = (draw_flags & 4) ?
                    (tex_flags | 2) : (tex_flags & 0xFD);
            }

            packet->unk_04.unk_04 = quad->unk_0C;
            packet->unk_0C = quad->unk_10;
            packet->unk_14 = quad->unk_14;
            packet->unk_1C = quad->unk_18;
            packet->unk_00.unk_03.unk_03 = 8;
            packet->unk_04.unk_07.unk_07 = 0x3A;

            packet->unk_00.unk_00 = (packet->unk_00.unk_00 & 0xFF000000) |
                (scratch->unk_24[scratch->unk_100] & 0x00FFFFFF);
            (*(u32 *)((u8 *)scratch->unk_24 + scratch->unk_100 * 4)) =
                (scratch->unk_24[scratch->unk_100] & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);

            packet = (S_func_81970800_5 *)((S_func_81970800_6 *)(*render_context_ref))->unk_8D0;
            ((S_func_81970800_6 *)(*render_context_ref))->unk_8D0 = (u8 *)packet + 0xC;
            SetDrawMode(packet, 0, 0, GetTPage(0, 1, 0, 0) & 0xFFFF, 0);
            packet->unk_00.unk_00 = (packet->unk_00.unk_00 & 0xFF000000) |
                (scratch->unk_24[scratch->unk_100] & 0x00FFFFFF);
            scratch->unk_24[scratch->unk_100] =
                (scratch->unk_24[scratch->unk_100] & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    PopMatrix();
}

/* Selector 59, retail file [0x1990D44, 0x1990D98); complete callable clone. */
#include "dungeon/effect/particle.h"
#include "shared/object_node.h"

/* Draw each linked record with zero depth bias; the next record is chained through the previous header's
 * unk_18 link, and its node supplies the transform and object pointers. */
s32 draw_linked_records_zero_depth_bias(void *record, void *transform, void *object) {
    ObjectNodeHeader *node;

    for (;;) {
        project_and_queue_visible_shaded_quad(record, transform, object, 0);
        node = NODE_HEADER(record)->chain_next;
        if (node == 0) {
            return 0;
        }
        record = node + 1;
        transform = node->position;
        object = node->sprite;
    }
}

#include "dungeon/effect/particle.h"
#include "shared/dungeon_effect_views.h"
#include "shared/entity.h"
/* Selector 59, retail file [0x1990D98, 0x1990FE8); complete callable clone. */
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "shared/object_node.h"

/* Position the point is projected from: three 4-byte slots, only the second halfword of each is used. */

/* The effect point's record (the object header precedes it). */

/* GPU scratchpad (0x1F800000) workspace used while projecting. */
typedef struct Bank1990800_1990d98_Scratch80024598 {
    u16 x;
    u16 y;
    u16 z;
    u8 pad_06[0x12];
    u8 *cursor;         /* next free packet */
    u8 pad_1C[4];
    u32 *ot;            /* ordering table */
    u8 pad_24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad_98[0x28];
    u32 index;          /* ordering table slot */
} Bank1990800_1990d98_Scratch80024598;

/*
 * Projects a colored point and links its drawing packets into the ordering table.
 *
 * Shaded point primitive (code 0x6A, 3 words).
 */
s32 project_scaled_colored_point(RisingPointEffectBody *record, ObjectPosition *position)
{
    GpuContext **state_ptr;
    Bank1990800_1990d98_Scratch80024598 *scratch;
    GpuContext *render_state;
    PointPacket *packet;
    PointPacket *mode_packet;
    ObjectNodeHeader *node;
    u8 blue;
    u32 depth_index;

    render_state = g_game_work.draw_buffer;
    state_ptr = (GpuContext **)&g_game_work;
    scratch = (Bank1990800_1990d98_Scratch80024598 *)0x1F800000;
    scratch->cursor = render_state->packetCursor;
    scratch->ot = (u32 *)&render_state->orderTag;
    do {
        packet = (PointPacket *)scratch->cursor;
        scratch->x = (u16)position->x.w.i;
        scratch->y = (u16)position->y.w.i;
        scratch->z = (u16)position->z.w.i;
        scratch->cursor = (u8 *)packet + 0xC;

        depth_index = RotTransPers(scratch, (u8 *)packet + 8, &scratch->xy, &scratch->depth);
        scratch->index = depth_index;
        if (depth_index < 0x1E0U) {
            *(u32 *)&packet->r = record->color;
            packet->r = (packet->r * record->scale) / record->scale_max;
            packet->g = (packet->g * record->scale) / record->scale_max;
            blue = (packet->b * record->scale) / record->scale_max;
            ((u8 *)packet)[3] = 2;
            packet->code = 0x6A;
            packet->b = blue;

            ((GpuLinkTag *)&packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)packet & 0x00FFFFFF);

            mode_packet = (PointPacket *)scratch->cursor;
            scratch->cursor = (u8 *)mode_packet + 0xC;
            SetDrawMode(mode_packet, 0, 0, GetTPage(0, 1, 0, 0) & 0xFFFF, 0);

            ((GpuLinkTag *)&mode_packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)mode_packet & 0x00FFFFFF);
        }

        node = NODE_HEADER(record)->chain_next;
        record = NODE_BODY(node);
        if (node == 0) {
            break;
        }
        position = node->position;
    } while (1);
    (*state_ptr)->packetCursor = scratch->cursor;
    return 0;
}

#include "dungeon/effect/particle/project_and_queue_visible_shaded_quad.h"
/* Selector 59, retail file [0x1990FE8, 0x19910A8); complete callable clone. */
#include "dungeon/effect/particle.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "modules/dungeon_native_abi.h"

/* Adjust height conditionally and set flags when the countdown reaches zero or below. */
void advance_rising_quad_countdown(RisingPointEffectBody *state, ObjectPosition *position)
{
    s16 countdown;

    fading_quad_effect_updated = 1;
    if (position->z.w.i <
        (s16)sample_terrain_surface_height((u16)position->x.w.i, (u16)position->y.w.i, position->z.w.i + 2)) {
        position->z.v += state->height_step;
    }

    countdown = (u16)state->scale - 4;
    state->scale = countdown;
    if ((countdown << 16) <= 0) {
        NODE_HEADER(state)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "shared/entity.h"
/* Selector 59, retail file [0x19910A8, 0x19911E0); complete callable clone. */
#include "dungeon/effect/particle.h"
#include "modules/dungeon_native_abi.h"

#ifndef NULL
#define NULL 0
#endif

/* Position block (three 4-byte slots, only the second halfword of each is used). */

extern s32 rand();

/* Spawn and initialize an effect at a randomly offset position relative to the source. */
void spawn_random_offset_effect_record(
    ObjectNodeHeader *source,
    s32 property_34,
    s32 property_28,
    s16 property_52,
    s16 x_offset,
    s16 y_offset,
    s16 z_offset)
{
    ObjectNodeHeader *effect;
    RisingPointEffectBody *record;
    u16 jitter;
    u16 effect_pos;

    effect = allocate_list_node(0x211, &source->next);
    if (effect != NULL) {
        effect->update_callback = advance_rising_quad_countdown;
        jitter = rand() & 0x1F;
        effect_pos = (u16)source->position->x.w.i + jitter;
        effect_pos += x_offset - 0x10;
        effect->position->x.w.i = effect_pos;

        jitter = rand() & 0x1F;
        effect_pos = (u16)source->position->y.w.i + jitter;
        effect_pos += y_offset - 0x10;
        effect->position->y.w.i = effect_pos;

        jitter = rand() & 0x1F;
        record = NODE_BODY(effect);
        effect_pos = (u16)source->position->z.w.i + jitter;
        effect_pos += z_offset - 0x10;
        effect->position->z.w.i = effect_pos;
        record->unk_14 = property_34;
        record->scale = property_52;
        record->scale_max = property_52;
        register_node(effect, project_scaled_colored_point);
        record->height_step = rand() + 0x10000;
        record->color = property_28;
    }
}

#include "dungeon/effect/particle.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"

/* Decrement the timer, update scale and position, and flag completion at zero. */
void follow_origin_and_fade_sprite(OriginFollowingFadeSpriteBody *state_arg, MovingPosition *position, SpriteFrameState *sprite) {
    OriginFollowingFadeSpriteBody *state = state_arg;
    s32 scale_factor;
    u16 ticks_left;
    MovingPosition *base_position;

    ticks_left = state->ticks_remaining - 1;
    scale_factor = (s32) ((s32) (ticks_left << 16) >> 9) / (s16) state->fade_divisor;
    fading_quad_effect_updated = 1;
    state->ticks_remaining = ticks_left;
    sprite->color.c.b = (u8) scale_factor;
    sprite->color.c.g = (u8) scale_factor;
    sprite->color.c.r = (u8) scale_factor;

    base_position = state->base_position;
    position->x = state->offset_x;
    position->y = state->offset_y;
    position->z = state->offset_z;
    position->x = (u16) (position->x + base_position->x);
    position->y = (u16) (position->y + base_position->y);
    position->z = (u16) (position->z + base_position->z);

    if ((s16)state->ticks_remaining <= 0) {
        NODE_HEADER(state)->flags |= NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}

#include "dungeon/effect/particle.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad[0x38];
    s16 timer;
    s16 divisor;
    u16 phase;
} QuarterColorFadeBody;

typedef struct {
    u8 pad0[8];
    s32 value;
    u8 padC[8];
    s32 delta;
} Motion;

/* Advance a timed effect, update its intensity and motion, and flag completion. */
void fade_effect_color_by_quarter(QuarterColorFadeBody *effect, Motion *motion, SpriteFrameState *render_data)
{
    s32 intensity;
    u16 phase;

    fading_quad_effect_updated = 1;
    effect->timer--;
    phase = effect->phase + 1;
    effect->phase = phase;
    if ((s16)phase == 2) {
        effect->phase = 0;
        advance_sprite_animation_and_textures(render_data);
    }
    intensity = (effect->timer << 7) / effect->divisor;
    render_data->color.c.b = intensity;
    render_data->color.c.g = intensity;
    render_data->color.c.r = intensity;
    motion->value += motion->delta;
    if (effect->timer <= 0) {
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "dungeon/effect/particle.h"
#include "shared/object_flags.h"

typedef struct S_81971398_0 {
    u8 pad_00[0x38];
    union { u16 s; s16 u; } unk_38;   /* accessed as both */
    s16 unk_3A;
} S_81971398_0;   /* base in func_80024B98 */

typedef struct S_81971398_1 {
    u8 pad_00[0x5FF4];
    s16 unk_5FF4;
} S_81971398_1;   /* page in func_80024B98 */

typedef struct S_81971398_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
} S_81971398_2;   /* p in func_80024B98 */

/* Advance the fade, scale four vertex colors, and flag completion when the timer expires. */
void fade_timed_quad_vertices(void *fade_data)
{
    S_81971398_0 *fade;
    s32 vertex_index;
    S_81971398_2 *vertex;
    u8 *global_page;
    u16 ticks_left;

    fade = fade_data;
    vertex_index = 0;
    global_page = (u8 *)&fading_quad_effect_updated - 0x5FF4;
    ticks_left = fade->unk_38.s;
    ((S_81971398_1 *)global_page)->unk_5FF4 = 1;
    ticks_left--;
    fade->unk_38.s = ticks_left;
    for (; vertex_index < 4; vertex_index++) {
        vertex = (S_81971398_2 *)((u32 *)fade + vertex_index);
        vertex->unk_0C =
            vertex->unk_1C * fade->unk_38.u /
            fade->unk_3A;
        vertex->unk_0D =
            vertex->unk_1D * fade->unk_38.u /
            fade->unk_3A;
        vertex->unk_0E =
            vertex->unk_1E * fade->unk_38.u /
            fade->unk_3A;
    }
    if (fade->unk_38.u <= 0) {
        (*(u16 *)((u8 *)fade + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "dungeon/effect/particle.h"
#include "shared/object_flags.h"

/* Advance an effect's fade and mark it finished when its countdown expires. */
void render_linked_jittered_effect_strips(void *effect, s32 unused, void *packet)
{
    s32 intensity;
    u16 ticks_left;

    ticks_left = *(u16 *)((u8 *)effect + 0x38) - 1;
    intensity = ((s32)(ticks_left << 16) >> 9) /
            *(s16 *)((u8 *)effect + 0x3A);
    fading_quad_effect_updated = 1;
    *(u16 *)((u8 *)effect + 0x38) = ticks_left;
    *(s8 *)((u8 *)packet + 0x0E) = intensity;
    *(s8 *)((u8 *)packet + 0x0D) = intensity;
    *(s8 *)((u8 *)packet + 0x0C) = intensity;
    *((u8 *)effect + 0x84) -= 1;
    *(u16 *)((u8 *)packet + 0x1A) += *(u16 *)((u8 *)effect + 0x44);
    if (*(s16 *)((u8 *)effect + 0x38) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "dungeon/effect/particle.h"
#include "shared/object_flags.h"

#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U8_AT(p, off) (*(u8 *)((u8 *)(p) + (off)))

/* Advances a timed visual update and sets completion flags when the countdown expires. */
void advance_timed_visual(void *effect, s32 unused, void *visual)
{
    u8 *effect_bytes;
    u16 countdown;
    s32 step_index;
    u8 *status_page;
    u8 *visual_bytes;
    u8 *flags_page;
    u16 field_value;

    effect_bytes = effect;
    visual_bytes = visual;
    status_page = (u8 *)&fading_quad_effect_updated - 0x5FF4;
    countdown = U16_AT(effect_bytes, 0x38);
    *(s16 *)(status_page + 0x5FF4) = 1;
    countdown--;
    U16_AT(effect_bytes, 0x38) = countdown;
    step_index = (u32)(s16)countdown;
    if ((u32)step_index < 20U) {
        switch (step_index) {
        case 0: case 9: case 10: case 19:
            field_value = 0x20;
            break;
        case 1: case 8: case 11: case 18:
            field_value = 0x35;
            break;
        case 2: case 7: case 12: case 17:
            field_value = 0x50;
            break;
        case 3: case 6: case 13: case 16:
            field_value = 0x65;
            break;
        case 4: case 5: case 14: case 15:
            field_value = 0x80;
            break;
        }
        U8_AT(visual_bytes, 0x0E) = field_value;
        U8_AT(visual_bytes, 0x0D) = field_value;
        U8_AT(visual_bytes, 0x0C) = field_value;
    }
    field_value = U16_AT(visual_bytes, 0x1A) + 400;
    U16_AT(visual_bytes, 0x1A) = field_value;
    if (S16_AT(effect_bytes, 0x38) > 0) {
        return;
    }
    flags_page = (u8 *)0x80080000;
    field_value = U16_AT((u8 *)effect_bytes - 2, 0) | 0x8000;
    U16_AT((u8 *)effect_bytes - 2, 0) = field_value;
    *(u32 *)(flags_page + 0x14A0) |= 0x8000;
}

#include "dungeon/effect/particle.h"
#include "shared/slus_callbacks.h"

struct Dst;
struct Elem;

typedef struct Bank1990800_19915d4_Sprite Bank1990800_19915d4_Sprite;
typedef struct Bank1990800_19915d4_Object Bank1990800_19915d4_Object;

struct Bank1990800_19915d4_Sprite {
    u8 pad0[12];
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    u16 flags10;
    s16 angle;
    u16 flags14;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
};

struct Bank1990800_19915d4_Object {
    u8 pad0[8];
    u16 *dst;
    Bank1990800_19915d4_Sprite *sprite;
    u8 *callback;
    u8 pad14[0x44];
    s16 unk58;
    s16 unk5A;
};

s32 rand();
extern u8 fading_sprite_entries[];

/* Creates a sprite object with randomized offsets from the source position. */
void create_fading_jittered_sprite(u16 *source, ObjectPosition *unused_1, SpriteFrameState *unused_2, s16 base_x, s16 base_y, s16 base_z) {
    s32 random_value;
    SpriteFrameState *sprite;
    SpriteFrameState *render_sprite;
    u16 *position;
    ObjectNodeHeader *object;
    QuarterColorFadeBody *object_data;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        object_data = NODE_BODY(object);
        object_data->timer = 0x14;
        object_data->divisor = 0x14;
        object->update_callback = (u8 *)fade_effect_color_by_quarter;
        register_node(object, project_sprite_chain);
        sprite = object->sprite;
        sprite->tpage_abr = 0x20;
        sprite->depth_bias = 0;
        sprite->flags |= 0xC;
        position = *(u16 * *)&object->position;
        position[1] = base_x;
        position[3] = base_y;
        position[5] = base_z;
        position[1] += source[62];
        position[3] += source[63];
        position[5] += source[64];
        random_value = rand(sprite);
        {
            s32 x = position[1];
            x -= 7;
            x += random_value & 0xF;
            position[1] = (u16)x;
        }
        random_value = rand();
        {
            s32 y = position[3];
            y -= 7;
            y += random_value & 0xF;
            position[3] = (u16)y;
        }
        random_value = rand();
        ((ObjectPosition *)position)->velocity_z = 0x20000;
        {
            s32 z = position[5];
            z -= 7;
            z += random_value & 0xF;
            position[5] = (u16)z;
        }
        render_sprite = object->sprite;
        render_sprite->scale_y = 0x1000;
        render_sprite->scale_x = 0x1000;
        render_sprite->color.c.b = 0x80;
        render_sprite->color.c.g = 0x80;
        render_sprite->color.c.r = 0x80;
        render_sprite->clut = 0x7DCE;
        render_sprite->flags |= 0x100;
        select_record_entry_and_value(render_sprite, fading_sprite_entries, 0);
    }
}

#include "dungeon/effect/particle.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

s32 rand();
extern M2C_UNK D_80025FE8;

typedef struct {
    s32 y;
    s32 z;
} OffsetYZ;

/* Creates an effect at a randomized offset from the origin and initializes its rendering data. */
void create_origin_following_fade_sprite(void *unused_0, void *origin_data, SpriteFrameState *unused_2, s32 offset_x, OffsetYZ offset_yz) {
    u16 jittered_x;
    void *effect_arg;
    u16 coord;
    s32 random_value;
    SpriteFrameState *render_data;
    OriginFollowingFadeSpriteBody *effect_state;
    ObjectNodeHeader *effect;
    MovingPosition *origin = origin_data;
    s32 initial_y = offset_yz.y;
    s32 initial_z = offset_yz.z;
    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        effect_arg = effect;
        effect_state = NODE_BODY(effect);
        effect_state->ticks_remaining = 0x1E;
        effect_state->fade_divisor = 0x1E;
        effect_state->offset_x = offset_x;
        effect_state->offset_y = (u16) initial_y;
        effect_state->offset_z = (u16) initial_z;
        effect_state->base_position = origin;
        effect->update_callback = follow_origin_and_fade_sprite;
        register_node(effect_arg, project_sprite_chain);
        render_data = effect->sprite;
        render_data->tpage_abr = 0x20;
        render_data->depth_bias = 6;
        render_data->flags = (u16) (render_data->flags | 0xC);
        offset_x = (s32)effect->position;
        random_value = rand();
        coord = effect_state->offset_x;
        coord -= 0x10;
        effect_state->offset_x = coord + (random_value & 0x1F);
        random_value = rand();
        coord = effect_state->offset_y;
        coord -= 0x10;
        effect_state->offset_y = coord + (random_value & 0x1F);
        random_value = rand();
        coord = effect_state->offset_z;
        jittered_x = effect_state->offset_x;
        coord -= 0x10;
        effect_state->offset_z = coord + (random_value & 0x1F);
        ((MovingPosition *)offset_x)->x = jittered_x;
        ((MovingPosition *)offset_x)->y = (u16) effect_state->offset_y;
        ((MovingPosition *)offset_x)->z = (u16) effect_state->offset_z;
        ((MovingPosition *)offset_x)->x = (u16) (((MovingPosition *)offset_x)->x + origin->x);
        ((MovingPosition *)offset_x)->y = (u16) (((MovingPosition *)offset_x)->y + origin->y);
        ((MovingPosition *)offset_x)->z = (u16) (((MovingPosition *)offset_x)->z + origin->z);
        render_data = effect->sprite;
        render_data->scale_y = 0x800;
        render_data->scale_x = 0x800;
        render_data->color.c.b = 0x80;
        render_data->color.c.g = 0x80;
        render_data->color.c.r = 0x80;
        memcpy((u8 *) effect + 0xA2,  &D_80025FE8, 12);
        render_data->source = (((void *)effect) + 0xA2);
    }
}

#include "shared/entity_height_offsets.h"
#include "dungeon/effect/particle.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"




   /* gbase in advance_effect_sequence */

typedef struct S_8197192C_4 {
    u16 unk_00;
} S_8197192C_4;   /* D_80025FF4 in advance_effect_sequence */

typedef struct S_8197192C_7 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u8 pad_2C[0xC];
    u16 unk_38;
    u16 unk_3A;
    u8 pad_3C[0x10];
    u16 unk_4C;
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
} S_8197192C_7;   /* work in advance_effect_sequence */

   /* part in advance_effect_sequence */

typedef struct S_8197192C_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x40];
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
} S_8197192C_9;   /* dst in advance_effect_sequence */

typedef struct S_8197192C_11 {
    u8 pad_00[0x4C];
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
} S_8197192C_11;   /* dst2 in advance_effect_sequence */

typedef struct S_8197192C_12 {
    u8 pad_00[0x2E94];
    u16 unk_2E94;
} S_8197192C_12;   /* status_page in advance_effect_sequence */



typedef struct {
    u8 bytes[12];
} Data12;

/* These data objects are present in the retail image but are not in the
 * current symbol catalog.  Keep the bindings narrow: they are not local
 * definitions, only names for the linked overlay data. */

extern Data12 D_80025FD0;
extern Data12 visible_quad_payload_template;

extern s32 rand(void);

/* Advance the effect sequence, spawning sprites and particles along its sampled path. */
void advance_effect_sequence(FadingSpriteSequenceBody *effect, void *owner, void *context_arg)
{
    ObjectPosition *position;
    S_8197192C_7 *effect_data_m;
    ObjectNodeHeader *effect_obj;
    u32 state;
    MovingPosition *state_2;
    void *context;
    u32 light_color;
    u32 light_color_2;
    u32 dark_color;
    ActorRecord *player;
    ActorRecord *player_2;
    u16 coord_z;
    u16 heading;

    effect->unk_38 = effect->unk_38 + 1;
    state = (s16)effect->spell.phase;
    context = context_arg;
    switch (state) {
    case 0:
        player = primary_actor_record;
        ((PlayerRecord *)player)->unk_F4 = 0;
        player->action_timer = 20;
        reference_tile_object.depth_bias = 6;
        state_2 = (MovingPosition *)(&view_reference_entity);
        effect->spell.phase = effect->spell.phase + 1;
        effect->unk_7C = state_2->x;
        effect->unk_7E = state_2->y;
        coord_z = state_2->z;
        ((S_8197192C_4 *)&fading_quad_effect_updated)->unk_00 = 1;
        effect->unk_80 = coord_z;
    case 1:
        if ((*effect->spell.context & 0x80) == 0) {
            return;
        }
        player_2 = primary_actor_record;
        effect->unk_2C = 33;
        player_2->unk_A4.halves.high.u = player_2->unk_A4.halves.high.u - 1;
        (*(u8 *)&player_2->unk_A8) = effect->spell.spell_id;
        player = primary_actor_record;
        heading = ((u16)player->facing);
        effect->spell.phase = effect->spell.phase + 1;
        effect->unk_38 = 0;
        effect->unk_34 = (heading >> 9) & 7;
        return;

    case 2:
    {
        effect->unk_2C = effect->unk_2C - 1;
        if ((s16)effect->unk_2C <= 0) {
            effect->unk_2C = 16;
            effect->spell.phase = effect->spell.phase + 1;
            return;
        }
        if ((s16)effect->unk_2C == 26) {
            if (read_sound_mode_blocking_status(4) != 2) {
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            } else {
                play_sound_if_enabled(AUDIO_RESUME_CD);
            }
        }

    }

        {
            s32 step;
            if ((u16)(effect->unk_2C - 5) < 19) {
                TileObject *map_base = &reference_tile_object;
                if (get_sprite_attachment_vector(
                    *(void **)&map_base->sprite_source, map_base,
                    (u8 *)effect + 0x2E, 0) != 0) {
                    step = 0;
                    do {
                        spawn_random_offset_effect_record((u8 *)(*(void **)&((EntityRec *)((void **)(&primary_actor_record)))->x) - 0x20, 0,
                                      0xE04040, (rand() & 0x3F) | 0x40,
                                      (s16)effect->unk_2E,
                                      (s16)effect->unk_30,
                                      (s16)effect->unk_32);
                        step++;
                    } while (step < 2);
                }
            }

            if ((s16)effect->unk_2C == 24) {
                TileObject *map_base = &reference_tile_object;
                if (get_sprite_attachment_vector(*(void **)&map_base->sprite_source, map_base,
                                  (u8 *)effect + 0x2E, 0) != 0) {
                    SpriteFrameState *sprite;
                    ObjectPosition *world_pos;

                    effect_obj = allocate_flagged_object_node(0x212);
                    if (effect_obj != 0) {
                        effect_data_m = NODE_BODY(effect_obj);
                        effect_data_m->unk_38 = 20;
                        effect_data_m->unk_3A = 20;
                        effect_obj->update_callback = (void *)advance_timed_visual;
                        register_node(effect_obj, project_sprite_chain);
                        sprite = effect_obj->sprite;
                        world_pos = &view_reference_entity;
                        sprite->tpage_abr = 0x60;
                        sprite->flags = sprite->flags | 0x0C;
                        position = effect_obj->position;
                        position->x.w.i = effect->unk_2E +
                                              ((u16)world_pos->x.w.i);
                        position->y.w.i = effect->unk_30 +
                                              ((u16)world_pos->y.w.i);
                        position->z.w.i = (u16)effect->unk_32 +
                                               ((u16)world_pos->z.w.i);
                        sprite = effect_obj->sprite;
                        sprite->scale_y = 0x1000;
                        sprite->scale_x = 0x1000;
                        sprite->color.c.b = 0x20;
                        sprite->color.c.g = 0x20;
                        sprite->color.c.r = 0x20;
                        *(Data12 *)((u8 *)effect_obj + 0xA2) = D_80025FD0;
                        sprite->source = (u8 *)effect_obj + 0xA2;
                    }
                }
            }
        }

        {
            s32 segment;
            s32 point_index;
            s32 step;
            ObjectPosition *world_pos;
            S_8197192C_9 *outer_point;
            if ((s16)effect->unk_2C >= 10) {
                return;
            }
            if ((s16)effect->unk_2C >= 6) {
                return;
            }
            if ((s16)effect->unk_2C == 3) {
                return;
            }
            segment = ((s16)effect->unk_2C == 4);
            if ((s16)effect->unk_2C == 2) {
                segment = 2;
            }
            if ((s16)effect->unk_2C == 1) {
                segment = 3;
            }
            {
                TileObject *map_base = &reference_tile_object;
                if (get_sprite_attachment_vector(*(void **)&map_base->sprite_source, map_base,
                                  (u8 *)effect + 0x2E, 0) != 0) {
                if ((s16)effect->unk_2C == 1) {
                    effect->unk_32 = -12;
                }
            point_index = segment << 1;
            {
                outer_point = (S_8197192C_9 *)((u8 *)effect + ((point_index + segment) << 2));
                point_index++;
                {
                    u32 shifted_x;
                    s32 origin_x;
                    s32 half_x;
                    shifted_x = effect->unk_2E;
                    origin_x = effect->unk_7C;
                    shifted_x <<= 16;
                    half_x = (s32)shifted_x >> 16;
                    half_x += shifted_x >> 31;
                    world_pos = &view_reference_entity;
                    half_x >>= 1;
                    outer_point->unk_4C = (s16)(half_x +
                        (world_pos->x.w.i - origin_x) / 2);
                }
                outer_point->unk_4E = (s16)(((s16)effect->unk_30) / 2 +
                    (world_pos->y.w.i - effect->unk_7E) / 2);
                outer_point->unk_50 = (s16)(((s16)effect->unk_32) / 2 +
                    (world_pos->z.w.i - effect->unk_80) / 2);
            }

            {
                S_8197192C_11 *inner_point = (S_8197192C_11 *)((u8 *)effect + (((point_index << 1) + point_index) << 1));
                inner_point->unk_4C = (s16)(((s16)effect->unk_2E) / 4 +
                    (world_pos->x.w.i - effect->unk_7C) / 2);
                inner_point->unk_4E = (s16)(((s16)effect->unk_30) / 4 +
                    (world_pos->y.w.i - effect->unk_7E) / 2);
                inner_point->unk_50 = (s16)(((s16)effect->unk_32) / 4 +
                    (world_pos->z.w.i - effect->unk_80) / 2);
            }
                }
            }

            if ((s16)effect->unk_2C == 4) {
                S_8197192C_7 *effect_data;
                effect_obj = allocate_flagged_object_node(0x212);
                effect_data = NODE_BODY(effect_obj);
                if (effect_obj != 0) {

                    SpriteFrameState *sprite;
                    void *init_data;
                    light_color_2 = 0x00E0E0E0;
                    dark_color = 0x00804020;
                    init_data = (void *)draw_linked_records_zero_depth_bias;
                    effect_data->unk_1C = light_color_2;
                    effect_data->unk_24 = dark_color;
                    effect_data->unk_28 = dark_color;
                    effect_data->unk_20 = light_color_2;
                    effect_data->unk_38 = 20;
                    effect_data->unk_3A = 20;
                    effect_data->unk_0C = effect_data->unk_1C;
                    effect_data->unk_10 = effect_data->unk_20;
                    effect_data->unk_14 = effect_data->unk_24;
                    effect_data->unk_18 = effect_data->unk_28;
                    effect_obj->update_callback = (void *)fade_timed_quad_vertices;
                    register_node(effect_obj, init_data);
                    sprite = effect_obj->sprite;
                    sprite->tpage_abr = 0x20;
                    sprite->flags = sprite->flags | 0x0C;
                    effect_data->unk_4C = (u16)effect->unk_58;
                    effect_data->unk_4E = (u16)effect->unk_5A;
                    effect_data->unk_50 = (u16)effect->unk_5C;
                    effect_data->unk_52 = (u16)effect->unk_4C;
                    effect_data->unk_54 = (u16)effect->unk_4E;
                    effect_data->unk_56 = (u16)effect->unk_50;
                    effect_data->unk_58 = effect->unk_5E;
                    effect_data->unk_5A = effect->unk_60;
                    effect_data->unk_5C = effect->unk_62;
                    effect_data->unk_5E = effect->unk_52;
                    effect_data->unk_60 = effect->unk_54;
                    effect_data->unk_62 = effect->unk_56;
                    position = effect_obj->position;
                    position->x.w.i = (u16)effect->unk_7C;
                    position->y.w.i = (u16)effect->unk_7E;
                    position->z.w.i = (u16)effect->unk_80;
                    sprite = effect_obj->sprite;
                    sprite->scale_y = 0x1000;
                    sprite->scale_x = 0x1000;
                    sprite->color.c.b = 0x80;
                    sprite->color.c.g = 0x80;
                    sprite->color.c.r = 0x80;
                    *(Data12 *)((u8 *)effect_obj + 0xA2) = visible_quad_payload_template;
                    sprite->source = (u8 *)effect_obj + 0xA2;
                }
            }
            if ((s16)effect->unk_2C == 2) {
                S_8197192C_7 *effect_data;
                effect_obj = allocate_flagged_object_node(0x212);
                effect_data = NODE_BODY(effect_obj);
                if (effect_obj != 0) {

                    SpriteFrameState *sprite;
                    void *init_data;
                    light_color = 0x00E0E0E0;
                    dark_color = 0x00804020;
                    init_data = (void *)draw_linked_records_zero_depth_bias;
                    effect_data->unk_1C = light_color;
                    effect_data->unk_24 = dark_color;
                    effect_data->unk_28 = dark_color;
                    effect_data->unk_20 = light_color;
                    effect_data->unk_38 = 20;
                    effect_data->unk_3A = 20;
                    effect_data->unk_0C = effect_data->unk_1C;
                    effect_data->unk_10 = effect_data->unk_20;
                    effect_data->unk_14 = effect_data->unk_24;
                    effect_data->unk_18 = effect_data->unk_28;
                    effect_obj->update_callback = (void *)fade_timed_quad_vertices;
                    register_node(effect_obj, init_data);
                    sprite = effect_obj->sprite;
                    sprite->tpage_abr = 0x20;
                    sprite->flags = sprite->flags | 0x0C;
                    effect_data->unk_4C = (u16)effect->unk_64;
                    effect_data->unk_4E = (u16)effect->unk_66;
                    effect_data->unk_50 = (u16)effect->unk_68;
                    effect_data->unk_52 = (u16)effect->unk_58;
                    effect_data->unk_54 = (u16)effect->unk_5A;
                    effect_data->unk_56 = (u16)effect->unk_5C;
                    effect_data->unk_58 = effect->unk_6A;
                    effect_data->unk_5A = effect->unk_6C;
                    effect_data->unk_5C = effect->unk_6E;
                    effect_data->unk_5E = effect->unk_5E;
                    effect_data->unk_60 = effect->unk_60;
                    effect_data->unk_62 = effect->unk_62;
                    position = effect_obj->position;
                    position->x.w.i = (u16)effect->unk_7C;
                    position->y.w.i = (u16)effect->unk_7E;
                    position->z.w.i = (u16)effect->unk_80;
                    sprite = effect_obj->sprite;
                    sprite->scale_y = 0x1000;
                    sprite->scale_x = 0x1000;
                    sprite->color.c.b = 0x80;
                    sprite->color.c.g = 0x80;
                    sprite->color.c.r = 0x80;
                    *(Data12 *)((u8 *)effect_obj + 0xA2) = visible_quad_payload_template;
                    sprite->source = (u8 *)effect_obj + 0xA2;
                }
            }
            if ((s16)effect->unk_2C == 1) {
                effect_obj = allocate_flagged_object_node(0x212);
                if (effect_obj != 0) {
                    SpriteFrameState *sprite;
                    void *init_data;
                    effect_data_m = NODE_BODY(effect_obj);
                    light_color = 0x00E0E0E0;
                    dark_color = 0x00804020;
                    init_data = (void *)draw_linked_records_zero_depth_bias;
                    effect_data_m->unk_1C = light_color;
                    effect_data_m->unk_24 = dark_color;
                    effect_data_m->unk_28 = dark_color;
                    effect_data_m->unk_20 = light_color;
                    effect_data_m->unk_38 = 20;
                    effect_data_m->unk_3A = 20;
                    effect_data_m->unk_0C = effect_data_m->unk_1C;
                    effect_data_m->unk_10 = effect_data_m->unk_20;
                    effect_data_m->unk_14 = effect_data_m->unk_24;
                    effect_data_m->unk_18 = effect_data_m->unk_28;
                    effect_obj->update_callback = (void *)fade_timed_quad_vertices;
                    register_node(effect_obj, init_data);
                    sprite = effect_obj->sprite;
                    sprite->tpage_abr = 0x20;
                    sprite->flags = sprite->flags | 0x0C;
                    effect_data_m->unk_4C = (u16)effect->unk_70;
                    effect_data_m->unk_4E = (u16)effect->unk_72;
                    effect_data_m->unk_50 = (u16)effect->unk_74;
                    effect_data_m->unk_52 = (u16)effect->unk_64;
                    effect_data_m->unk_54 = (u16)effect->unk_66;
                    effect_data_m->unk_56 = (u16)effect->unk_68;
                    effect_data_m->unk_58 = effect->unk_76;
                    effect_data_m->unk_5A = effect->unk_78;
                    effect_data_m->unk_5C = effect->unk_7A;
                    effect_data_m->unk_5E = effect->unk_6A;
                    effect_data_m->unk_60 = effect->unk_6C;
                    effect_data_m->unk_62 = effect->unk_6E;
                    position = effect_obj->position;
                    position->x.w.i = (u16)effect->unk_7C;
                    position->y.w.i = (u16)effect->unk_7E;
                    position->z.w.i = (u16)effect->unk_80;
                    sprite = effect_obj->sprite;
                    sprite->scale_y = 0x1000;
                    sprite->scale_x = 0x1000;
                    sprite->color.c.b = 0x80;
                    sprite->color.c.g = 0x80;
                    sprite->color.c.r = 0x80;
                    *(Data12 *)((u8 *)effect_obj + 0xA2) = visible_quad_payload_template;
                    sprite->source = (u8 *)effect_obj + 0xA2;
                }
            }

            if ((s16)effect->unk_2C == 4) {
                step = 0;
                do {
                    s32 spawn_x;
                    s32 spawn_y;
                    s32 spawn_z;
                    spawn_x = (s16)(((u16)effect->unk_58 +
                              (effect->unk_4C - effect->unk_58) * step / 6)
                                  << 1);
                    spawn_y = (s16)(((u16)effect->unk_5A +
                              (effect->unk_4E - effect->unk_5A) * step / 6)
                                  << 1);
                    spawn_z = (s16)(((u16)effect->unk_5C +
                              (effect->unk_50 - effect->unk_5C) * step / 6)
                                  << 1);
                    create_fading_jittered_sprite(effect, owner, context,
                        spawn_x, spawn_y, spawn_z);
                    step++;
                } while (step < 6);
            }
            if ((s16)effect->unk_2C == 2) {
                step = 0;
                do {
                    s32 spawn_x;
                    s32 spawn_y;
                    s32 spawn_z;
                    spawn_x = (s16)(((u16)effect->unk_64 +
                              (effect->unk_58 - effect->unk_64) * step / 12)
                                  << 1);
                    spawn_y = (s16)(((u16)effect->unk_66 +
                              (effect->unk_5A - effect->unk_66) * step / 12)
                                  << 1);
                    spawn_z = (s16)(((u16)effect->unk_68 +
                              (effect->unk_5C - effect->unk_68) * step / 12)
                                  << 1);
                    create_fading_jittered_sprite(effect, owner, context,
                        spawn_x, spawn_y, spawn_z);
                    step++;
                } while (step < 12);
            }
            if ((s16)effect->unk_2C != 1) {
                return;
            }
            step = 0;
            do {
                s32 spawn_x;
                s32 spawn_y;
                s32 spawn_z;
                spawn_x = (s16)(((u16)effect->unk_70 +
                          (effect->unk_64 - effect->unk_70) * step / 2) << 1);
                spawn_y = (s16)(((u16)effect->unk_72 +
                          (effect->unk_66 - effect->unk_72) * step / 2) << 1);
                spawn_z = (s16)(((u16)effect->unk_74 +
                          (effect->unk_68 - effect->unk_74) * step / 2) << 1);
                create_fading_jittered_sprite(effect, owner, context,
                    spawn_x, spawn_y, spawn_z);
                step++;
            } while (step < 2);
            return;

        }

    case 3:
    {
        s32 angle;
        ActorRecord *source_obj;
        ObjectPosition *source_owner;
        u8 *angle_base;
        u8 *angle_table;
        u8 angle_count;
        S_8197192C_12 *status_page;
        if ((s16)effect->unk_2C != 16) {
            status_page = (S_8197192C_12 *)0x80080000;
        } else {
        source_obj = ((ActorRecord *)((*(void **)&((EntityRec *)((void **)(&primary_actor_record)))->x)))->target;
        if (source_obj != 0) {
            angle_table = entity_height_offsets;
            angle_count = angle_table[source_obj->species];
            source_owner = NODE_HEADER(source_obj)->position;
            angle = 0;
            if (angle_count != 0) {
                angle_base = angle_table;
                do {
                    {
                        create_origin_following_fade_sprite(effect, source_owner, context, 0, (OffsetYZ){0, (s16)angle});
                        angle -= 15;
                    }
                } while (-*(u8 *)((u32)source_obj->species + (u32)angle_base) < angle);
            }
        }
        status_page = (S_8197192C_12 *)0x80080000;
        }
        {
            u16 next_state = 4;
            if ((status_page->unk_2E94 & 0x8000) == 0) {
                effect->unk_2C = effect->unk_2C - 1;
                if ((s16)effect->unk_2C >= 0) {
                    return;
                }
            }
            effect->spell.phase = next_state;
            return;
        }
    }

    case 4:
    {
        u16 cleanup_count;
        if (fading_quad_effect_updated == 0) {
            cleanup_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
            g_dungeon_status.active_actor = 0;
            reference_tile_object.depth_bias = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count = cleanup_count - 1;
            NODE_HEADER(effect)->flags = NODE_HEADER(effect)->flags | 0x8000;
            object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            return;
        }
        fading_quad_effect_updated = 0;

    }

    }
}

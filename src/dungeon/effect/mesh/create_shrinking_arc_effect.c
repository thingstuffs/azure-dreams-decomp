#include "engine/node/registration.h"
#include "shared/entity.h"
#include "shared/audio_commands.h"
/* Five-point effect geometry, orbiting animation, and movement toward an attack target. */
#include "shared/game_work.h"
#include "shared/object_node.h"
#include "dungeon/effect/mesh/create_shrinking_arc_effect.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/mesh.h"
void (*const dungeon_ovl_1930844_entry)(ApproachingImpactSpellBody *state, ObjectPosition *motion, SpriteFrameState *appearance) = update_approaching_impact_effect;

/* Moves a rotating, shrinking sprite along its velocity with a sinusoidal height offset until its
   duration ends. */
void advance_shrinking_arc_effect(RandomAngleSpriteEffectBody *state, ovl_1930844_81910844_S_81910844_2 *motion, ovl_1930844_81910844_S_81910844_3 *visual) {
    s32 pos_x;
    s32 pos_y;
    s32 velocity_x;
    s32 velocity_y;
    s32 scale_step;
    u16 angle;
    u16 scale;
    s16 elapsed;
    s16 duration;
    ovl_1930844_81910844_S_81910844_1 *owner;

    owner = state->owner;
    owner->unk_14 =
        (u16) (owner->unk_14 + 1);
    state->elapsed.s =
        (u16) (state->elapsed.s + 1);
    pos_x = motion->unk_00;
    velocity_x = motion->unk_0C;
    pos_y = motion->unk_04;
    velocity_y = motion->unk_10;
    motion->unk_00 = pos_x + velocity_x;
    motion->unk_04 = pos_y + velocity_y;
    state->initial_z =
        state->initial_z + motion->unk_14;
    motion->unk_08 =
        state->initial_z -
        ((rsin((0x800 / state->duration.s) *
                        (s16) state->elapsed.s) >> 4) << 0xE);
    scale_step = 0x200 / state->duration.s;
    angle = visual->unk_1A;
    scale = visual->unk_1E;
    visual->unk_1A = angle + 0x300;
    scale = scale - scale_step;
    visual->unk_1E = scale;
    visual->unk_1C = scale;
    elapsed = state->elapsed.u;
    duration = state->duration.s;
    if (elapsed > duration) {
        ((ovl_1930844_81910844_S_81910844_0_pre *)state)[-1].unk_00 =
            ((ovl_1930844_81910844_S_81910844_0_pre *)state)[-1].unk_00 | 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a randomly rotated gray sprite with copied motion, the owner's duration, and a saved
   starting height. */
void * create_shrinking_arc_effect(ApproachingImpactSpellBody *owner, ObjectPosition *source_position)
{
    s32 random_value;
    s32 initial_z;
    s32 rounded_random;
    SpriteFrameState *sprite;
    RandomAngleSpriteEffectNode *effect;
    RandomAngleSpriteEffectBody *effect_state;
    ObjectPosition *position;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        effect_state = &effect->body;
        effect->header.update_callback = (void *)advance_shrinking_arc_effect;
        effect_state->owner = owner;
        effect_state->elapsed.u = 0;
        effect_state->duration.u = owner->unk_12;
        sprite = effect->header.sprite;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->source = D_800DE720;
        sprite->clut = 0x7E00;
        sprite->flags |= 0x100;
        rounded_random = rand();
        random_value = rounded_random;
        if (random_value < 0) {
            rounded_random = random_value + 0xFFF;
        }
        sprite->angle_z = (random_value % 4096);
        sprite->scale_y = 0x400;
        sprite->scale_x = 0x400;
        register_node(&effect->header, project_sprite_chain);
        position = effect->header.position;
        *(ovl_1930844_81910970_Copy6 *)position = *(ovl_1930844_81910970_Copy6 *)source_position;
        initial_z = position->z.v;
        effect_state->initial_z = initial_z;
        return effect;
    }
    return 0;
}

/* Projects five radial line segments between successive animation steps and queues them at their
   average depth. */
/* Keep the field views: direct owning-member rewrites change the production payload. */
void queue_radial_line_burst(ovl_1930844_81911BF4_Obj81911BF4 *effect_data, void *origin, s16 step_index, s16 scale_factor)
{
    s32 scale;
    register s32 step;
    u32 addr_mask;
    s32 angle;
    u8 *scratch;
    GameWork *render_global;
    u8 *line_packet;
    void *start_vertex;
    void *start_screen;
    void *end_vertex;
    void *end_screen;
    u8 * draw_mode_packet;
    s32 radial_x;
    s32 radial_y;
    s32 ray_index = 0;
    s32 prev_step;
    render_global = &g_game_work;
    scale = (s16) scale_factor;
    step = (s16) step_index;
    prev_step = step - 1;
    addr_mask = 0x00FFFFFF;
    angle = 0;
    scratch = (u8 *) 0x1F800000;
    *((void **) (scratch + 0x18)) = (*(u8 **)&g_game_work.draw_buffer) + 0xB0;
    do {
        void **render_ptr = (void **) render_global;
        void *render_ctx = *render_ptr;
        s32 start_step_offset;
        s32 end_step_offset;
        s32 z_delta;
        s32 z_step;
        s32 avg_depth;
        void *origin_ptr;
        u16 origin_coord;
        line_packet = *((u8 **) (((u8 *) render_ctx) + 0x8D0));
        *((u8 **) (((u8 *) render_ctx) + 0x8D0)) = line_packet + 0x14;
        *((line_packet + 3)) = 4;
        *((line_packet + 7)) = 0x52;
        *((line_packet + 4)) = effect_data->field40;
        *((line_packet + 5)) = effect_data->field41;
        *((line_packet + 6)) = effect_data->field42;
        *((line_packet + 0xC)) = effect_data->field40;
        *((line_packet + 0xD)) = effect_data->field41;
        *((line_packet + 0xE)) = effect_data->field42;
        origin_ptr = origin;
        origin_coord = *((u16 *) (((u8 *) origin_ptr) + 2));
        *((u16 *) (scratch + 0x6C)) = origin_coord;
        *((u16 *) (scratch + 0x64)) = origin_coord;
        radial_x = ((rsin(angle + (*((s16 *) (((u8 *) effect_data) + 0xA))))
            >> 4) * effect_data->scale) << 8;
        start_step_offset = radial_x / scale;
        *((s32 *) (scratch + 0x108)) = radial_x;
        *((u16 *) (scratch + 0x64)) += (start_step_offset * prev_step) >> 16;
        end_step_offset = (*((s32 *) (scratch + 0x108))) / scale;
        *((u16 *) (scratch + 0x6C)) += (end_step_offset * step) >> 16;
        origin_ptr = origin;
        origin_coord = *((u16 *) (((u8 *) origin_ptr) + 6));
        *((u16 *) (scratch + 0x6E)) = origin_coord;
        *((u16 *) (scratch + 0x66)) = origin_coord;
        start_vertex = scratch + 0x64;
        start_screen = scratch + 0xD8;
        end_vertex = scratch + 0x6C;
        end_screen = scratch + 0xDC;
        radial_y = ((rcos(angle + (*((s16 *) (((u8 *) effect_data) + 0xA))))
            >> 4) * effect_data->scale) << 8;
        start_step_offset = radial_y / scale;
        *((s32 *) (scratch + 0x10C)) = radial_y;
        *((u16 *) (scratch + 0x66)) += (start_step_offset * prev_step) >> 16;
        end_step_offset = (*((s32 *) (scratch + 0x10C))) / scale;
        render_ptr = (void **)(scratch + 0x84);
        *((u16 *) (scratch + 0x6E)) += (end_step_offset * step) >> 16;
        origin_ptr = origin;
        origin_coord = *((u16 *) (((u8 *) origin_ptr) + 0xA));
        *((u16 *) (scratch + 0x70)) = origin_coord;
        *((u16 *) (scratch + 0x68)) = origin_coord;
        z_delta = (((s32) effect_data->field14) << 16) - (*((s32 *) (((u8 *) origin_ptr) + 8)));
        *((s32 *) (scratch + 0x110)) = z_delta;
        z_step = z_delta >> scale;
        *((u16 *) (scratch + 0x68)) += (z_step << prev_step) >> 16;
        *((u16 *) (scratch + 0x70)) += (((*((s32 *) (scratch + 0x110))) >> scale) << step) >> 16;
        origin_ptr = scratch + 0x88;
        *((s32 *) (scratch + 0xF4)) = RotTransPers(start_vertex, start_screen, render_ptr, origin_ptr);
        *((s32 *) (scratch + 0xF8)) = RotTransPers(end_vertex, end_screen, render_ptr,
            origin_ptr);
        *((u16 *) (line_packet + 8)) = *((u16 *) (scratch + 0xD8));
        *((u16 *) (line_packet + 0xA)) = *((u16 *) (scratch + 0xDA));
        *((u16 *) (line_packet + 0x10)) = *((u16 *) (scratch + 0xDC));
        *((u16 *) (line_packet + 0x12)) = *((u16 *) (scratch + 0xDE));
        avg_depth = ((*((s32 *) (scratch + 0xF4))) + (*((s32 *) (scratch + 0xF8)))) / 2;
        *((s32 *) (scratch + 0xB4)) = avg_depth;
        if (((u32) avg_depth) < 0x1E0U) {
            OT_SETADDR(line_packet, OT_GETADDR((*((u32 **) (((u8 *) scratch) + 0x18))) + avg_depth, addr_mask),
                0xFF000000, addr_mask);
            *((u32 *) (((u8 *) ((*((u32 **) (scratch + 0x18))) + (*((s32 *) (scratch + 0xB4)))))
                + 0)) = ((*((u32 *) (((u8 *) ((*((u32 **) (scratch + 0x18)))
                + (*((s32 *) (scratch + 0xB4))))) + 0))) & 0xFF000000) | (((u32) line_packet) & addr_mask);
            render_ptr = (void **) render_global;
            render_ctx = *render_ptr;
            draw_mode_packet = *((u8 **) (((u8 *) render_ctx) + 0x8D0));
            *((u8 **) (((u8 *) render_ctx) + 0x8D0)) = draw_mode_packet + 0xC;
            SetDrawMode(draw_mode_packet, 0, 0, GetTPage(0, effect_data->field12, 0,
                0) & 0xFFFF, 0);
            OT_SETADDR(draw_mode_packet, OT_GETADDR((*((u32 **) (((u8 *) scratch) + 0x18)))
                + (*((s32 *) (((u8 *) scratch) + 0xB4))), addr_mask), 0xFF000000, addr_mask);
            *((u32 *) (((u8 *) ((*((u32 **) (scratch + 0x18))) + (*((s32 *) (scratch + 0xB4)))))
                + 0)) = ((*((u32 *) (((u8 *) ((*((u32 **) (scratch + 0x18)))
                + (*((s32 *) (scratch + 0xB4))))) + 0))) & 0xFF000000) | (((u32) draw_mode_packet) & addr_mask);
        }
        angle += 0x333;
        ray_index++;
    }
    while (ray_index < 5);
}

/* Builds five translucent quads between the effect's interpolated points and queues their draw modes
   by depth. */
#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"
#include "dungeon/effect/projected_quad_scratch.h"

void build_and_enqueue_five_translucent_quads_between_interpolated_points(u8 *shape, void *position, s16 scale_num, s16 scale_den)
{
    GameWork *gfx_slot= ovl_1930844_81910EC0_GFX_ROOT_SLOT;
    u8 *gfx = gfx_slot->draw_buffer;
    s32 edge = 0;
    s32 scale = scale_num;
    s32 divisor = scale_den;
    s32 interpolate = scale < divisor;
    ProjectedQuadScratch *scratch = (ProjectedQuadScratch *)0x1F800000;

    scratch->ordering_table = (u32 *)(gfx + 0xB0);
    do {
        GpuContext **gfx_pool = (GpuContext **)gfx_slot;
        u8 *start_point = shape + edge * 4;
        POLY_G4 *packet;
        DR_MODE *mode_packet;
        u8 *end_point;
        s32 coord_delta;
        u16 coord;
        u16 vertex_y;
        u32 depth;

        packet = (*gfx_pool)->packetCursor;
        (*gfx_pool)->packetCursor = packet + 1;

        ((GpuLinkTag *)&packet->tag)->len = 8;
        packet->code = 0x3A;
        packet->red0 = ovl_1930844_81910EC0_U8_AT(shape, 0x40);
        packet->green0 = ovl_1930844_81910EC0_U8_AT(shape, 0x41);
        packet->blue0 = ovl_1930844_81910EC0_U8_AT(shape, 0x42);
        packet->red1 = ovl_1930844_81910EC0_U8_AT(shape, 0x40);
        packet->green1 = ovl_1930844_81910EC0_U8_AT(shape, 0x41);
        packet->blue1 = ovl_1930844_81910EC0_U8_AT(shape, 0x42);
        packet->red2 = ovl_1930844_81910EC0_U8_AT(shape, 0x40);
        packet->green2 = ovl_1930844_81910EC0_U8_AT(shape, 0x41);
        packet->blue2 = ovl_1930844_81910EC0_U8_AT(shape, 0x42);
        packet->red3 = ovl_1930844_81910EC0_U8_AT(shape, 0x40);
        packet->green3 = ovl_1930844_81910EC0_U8_AT(shape, 0x41);
        packet->blue3 = ovl_1930844_81910EC0_U8_AT(shape, 0x42);

        end_point = shape + (((edge + 2) % 5) * 4);
        {
            u16 start_x = ovl_1930844_81910EC0_U16_AT(start_point, 0x1A);

            scratch->vertices[2].vx = start_x;
            scratch->vertices[0].vx = start_x;
        }

        coord_delta = ovl_1930844_81910EC0_S32_AT(end_point, 0x18) - ovl_1930844_81910EC0_S32_AT(start_point, 0x18);
        scratch->step_x = coord_delta;
        if (interpolate) {
            scratch->step_x = (coord_delta / divisor) * scale;
        }

        /* BYTES: retail reads the integer half of the 16.16 step with one lhu of its high halfword; the shift spelling compiles to lw and sra */
        coord = ovl_1930844_81910EC0_U16_AT(start_point, 0x1A) + ((u16 *)&scratch->step_x)[1];
        scratch->vertices[3].vx = coord;
        scratch->vertices[1].vx = coord;

        vertex_y = ovl_1930844_81910EC0_U16_AT(start_point, 0x2E);
        scratch->vertices[2].vy = vertex_y;
        scratch->vertices[0].vy = vertex_y;

        coord_delta = ovl_1930844_81910EC0_S32_AT(end_point, 0x2C) - ovl_1930844_81910EC0_S32_AT(start_point, 0x2C);
        scratch->step_y = coord_delta;
        if (interpolate) {
            scratch->step_y = (coord_delta / divisor) * scale;
        }

        /* BYTES: retail reads the integer half of the 16.16 step with one lhu of its high halfword; the shift spelling compiles to lw and sra */
        vertex_y = ovl_1930844_81910EC0_U16_AT(start_point, 0x2E) + ((u16 *)&scratch->step_y)[1];
        scratch->vertices[3].vy = vertex_y;
        scratch->vertices[1].vy = vertex_y;

        coord = ovl_1930844_81910EC0_U16_AT(position, 0xA) - ovl_1930844_81910EC0_U16_AT(shape, 0x10);
        scratch->vertices[1].vz = coord;
        scratch->vertices[0].vz = coord;

        coord = ovl_1930844_81910EC0_U16_AT(position, 0xA);
        scratch->vertices[2].vz = coord;
        scratch->vertices[3].vz = coord;

        scratch->ot_index = RotAverage4(
            &scratch->vertices[0], &scratch->vertices[1],
            &scratch->vertices[2], &scratch->vertices[3],
            (s32 *)&scratch->screen[0], (s32 *)&scratch->screen[1],
            (s32 *)&scratch->screen[2], (s32 *)&scratch->screen[3],
            &scratch->depth_cue, &scratch->gte_flag);

        packet->x0 = scratch->screen[0].x;
        packet->y0 = scratch->screen[0].y;
        packet->x1 = scratch->screen[1].x;
        packet->y1 = scratch->screen[1].y;
        packet->x2 = scratch->screen[2].x;
        packet->y2 = scratch->screen[2].y;
        packet->x3 = scratch->screen[3].x;
        packet->y3 = scratch->screen[3].y;

        depth = scratch->ot_index;
        if (depth < 0x1E0) {
            u32 addr_mask = 0x00FFFFFF;
            u32 length_mask = 0xFF000000;

            ((GpuLinkTag *)&packet->tag)->addr = ((GpuLinkTag *)&scratch->ordering_table[depth])->addr;
            *(u32 *)((u8 *)scratch->ordering_table + scratch->ot_index * 4) =
                (scratch->ordering_table[scratch->ot_index] & length_mask) |
                ((u32)packet & addr_mask);

            gfx_pool = (GpuContext **)gfx_slot;
            mode_packet = (*gfx_pool)->packetCursor;
            (*gfx_pool)->packetCursor = mode_packet + 1;
            SetDrawMode(mode_packet, 0, 0,
                (u16)GetTPage(0, ovl_1930844_81910EC0_S16_AT(shape, 0x12), 0, 0), 0);

            mode_packet->tag = (mode_packet->tag & length_mask) |
                (scratch->ordering_table[scratch->ot_index] & addr_mask);
            {
                u32 packet_depth = scratch->ot_index;

                mode_packet = (DR_MODE *)((u32)mode_packet & addr_mask);
                scratch->ordering_table[packet_depth] =
                    (scratch->ordering_table[packet_depth] & length_mask) |
                    (u32)mode_packet;
            }
        }

        edge++;
    } while (edge < 5);
}

/* Adds the radius-scaled trigonometric component to the fixed-point center coordinate. */
static __inline__ s32 radial_coordinate(s32 center, s32 trig, s16 radius)
{
    return center + (((trig >> 4) * radius) << 8);
}

typedef union { s32 value; struct { u16 low, high; } half; } PointCoord;
typedef struct { u8 prefix[0x18]; PointCoord x[5]; PointCoord y[5]; } EffectCoords;

/*
 * Builds two colored vertical quads for each of five radial targets, interpolating their moving
 * edges from adjacent saved X/Y points over the supplied duration. Projects and queues each quad
 * with its draw mode only for depths below 0x1E0.
 */
void queue_perimeter_vertical_quads(ovl_1930844_81911BF4_Obj81911BF4 *effect_in, ovl_1930844_819112CC_S_819112CC_1 *origin, s16 step_in, s16 duration_in)
{
    ovl_1930844_81911BF4_Obj81911BF4 *effect = effect_in;
    s32 step = step_in;
    s32 duration = duration_in;

    POLY_G4 *quad;
    DR_MODE *mode;
    s32 angle_x_or_mask;
    s32 angle_x_or_mask_2;
    s32 target_x;
    s32 target_y;
    s32 radial_y;
    s32 interpolate;
    SVECTOR *vertex_base;
    s16 next_end_y;
    s16 end_y;
    s16 bottom_z;
    s16 end_x;
    s16 next_end_x;
    u32 *link;
    s32 radial_x;
    s32 next_delta_y;
    s32 delta_y;
    s32 next_delta_x;
    s32 delta_x;
    s32 point_index;
    s32 twice_index;
    s32 next_index;
    u16 y_step;
    u16 next_start_y;
    u16 start_x;
    u16 start_y;
    u16 top_z;
    u16 next_start_x;
    ovl_1930844_819112CC_S_819112CC_3 *point;
    s32 row_off;
    s32 modulo_result;
    s32 ot_slot;
    s32 ot_slot2;
    ProjectedQuadScratch *scratch;
    GameWork *context_slot;
    SVECTOR *v1;
    SVECTOR *v2;
    SVECTOR *v3;
    SpriteScratchScreenPoint *sxy0;
    SpriteScratchScreenPoint *sxy1;
    SpriteScratchScreenPoint *sxy2;
    SpriteScratchScreenPoint *sxy3;
    s32 *depth;
    s32 *flag;
    ovl_1930844_819112CC_EmptyArg empty_arg;
    u8 *render_context = g_game_work.draw_buffer;

    context_slot = ovl_1930844_819112CC_GFX_ROOT_SLOT;
    point_index = 0;
    scratch = (ProjectedQuadScratch *)0x1F800000;
    interpolate = step < duration;
    vertex_base = &scratch->vertices[0];
    scratch->ordering_table = (u32 *)(render_context + 0xB0);
    for (; point_index < 5; point_index = next_index) {
        twice_index = point_index * 2;
        angle_x_or_mask_2 = (twice_index + 1) * 0x199;
        link = (u32 *)(angle_x_or_mask_2 + effect->angle);
        radial_x = rsin((s32)link);
        target_x = radial_coordinate(origin->unk_00, radial_x, effect->scale);
        row_off = rcos(angle_x_or_mask_2 + effect->angle);
        row_off >>= 4;
        radial_y = origin->unk_04 +
            ((row_off * effect->scale) << 8);
        target_y = radial_y;
        {
            GpuContext **pool = (GpuContext **)context_slot;
            quad = (*pool)->packetCursor;
            (*pool)->packetCursor = quad + 1;
        }
        ((GpuLinkTag *)&quad->tag)->len = 8;
        quad->code = 0x3A;
        quad->red0 = effect->field40;
        quad->green0 = effect->field41;
        quad->blue0 = effect->field42;
        quad->red1 = effect->field40;
        quad->green1 = effect->field41;
        quad->blue1 = effect->field42;
        quad->red2 = effect->field40;
        quad->green2 = effect->field41;
        quad->blue2 = effect->field42;
        quad->red3 = effect->field40;
        quad->green3 = effect->field41;
        quad->blue3 = effect->field42;
        start_x = ((EffectCoords *)effect)->x[point_index].half.high;
        scratch->vertices[2].vx = start_x;
        scratch->vertices[0].vx = start_x;
        delta_x = target_x - effect->x[point_index];
        scratch->step_x = delta_x;
        if (interpolate != 0) {
            scratch->step_x = (delta_x / duration) * step;
        }
        /* BYTES: retail reads the integer half of the 16.16 step with one lhu of its high halfword; the shift spelling compiles to lw and sra */
        end_x = ((EffectCoords *)effect)->x[point_index].half.high + ((u16 *)&scratch->step_x)[1];
        scratch->vertices[3].vx = end_x;
        scratch->vertices[1].vx = end_x;
        start_y = ((EffectCoords *)effect)->y[point_index].half.high;
        scratch->vertices[2].vy = start_y;
        scratch->vertices[0].vy = start_y;
        delta_y = radial_y - effect->y[point_index];
        scratch->step_y = delta_y;
        if (interpolate != 0) {
            scratch->step_y = (delta_y / duration) * step;
        }
        /* BYTES: retail reads the integer half of the 16.16 step with one lhu of its high halfword; the shift spelling compiles to lw and sra */
        end_y = ((EffectCoords *)effect)->y[point_index].half.high + ((u16 *)&scratch->step_y)[1];
        scratch->vertices[3].vy = end_y;
        scratch->vertices[1].vy = end_y;
        bottom_z = origin->unk_0A - effect->field10;
        scratch->vertices[1].vz = bottom_z;
        scratch->vertices[0].vz = bottom_z;
        top_z = origin->unk_0A;
        v1 = &scratch->vertices[1];
        v2 = &scratch->vertices[2];
        v3 = &scratch->vertices[3];
        sxy0 = &scratch->screen[0];
        sxy1 = &scratch->screen[1];
        sxy2 = &scratch->screen[2];
        sxy3 = &scratch->screen[3];
        depth = &scratch->depth_cue;
        flag = &scratch->gte_flag;
        scratch->ot_index = RotAverage4(vertex_base, v1, v2, v3,
                                   (s32 *)sxy0, (s32 *)sxy1, (s32 *)sxy2, (s32 *)sxy3,
                                   depth, (scratch->vertices[2].vz = top_z,
                                    scratch->vertices[3].vz = top_z,
                                    flag));
        quad->x0 = scratch->screen[0].x;
        quad->y0 = scratch->screen[0].y;
        quad->x1 = scratch->screen[1].x;
        quad->y1 = scratch->screen[1].y;
        quad->x2 = scratch->screen[2].x;
        quad->y2 = scratch->screen[2].y;
        quad->x3 = scratch->screen[3].x;
        quad->y3 = scratch->screen[3].y;
        link = (u32 *)scratch->ot_index;
        if ((u32)link < 0x1E0U) {
            ot_slot = (u32)link << 2;
            angle_x_or_mask = (s32)0xFF000000;
            ot_slot += (unsigned long)scratch->ordering_table;
            ((GpuLinkTag *)&quad->tag)->addr = ((GpuLinkTag *)ot_slot)->addr;
            link = (u32 *)scratch->ot_index;
            link = (u32 *)((u32)link << 2);
            link = (u32 *)((u8 *)link + (unsigned long)scratch->ordering_table);
            *link = (*link & (u32)angle_x_or_mask) | ((u32)quad & 0xFFFFFF);
            {
                GpuContext *ctx = context_slot->draw_buffer;
                mode = ctx->packetCursor;
                ctx->packetCursor = mode + 1;
            }
            SetDrawMode(mode, 0, 0,
                          GetTPage(0, effect->field12, 0, 0) & 0xFFFF,
                          0);
            ((GpuLinkTag *)&mode->tag)->addr = ((GpuLinkTag *)&scratch->ordering_table[scratch->ot_index])->addr;
            link = (u32 *)scratch->ot_index;
            link = (u32 *)((u32)link << 2);
            link = (u32 *)((u8 *)link + (unsigned long)scratch->ordering_table);
            *link = (*link & (u32)angle_x_or_mask) | ((u32)mode & 0xFFFFFF);
        }
        {
            GpuContext **pool = (GpuContext **)context_slot;
            quad = (*pool)->packetCursor;
            (*pool)->packetCursor = quad + 1;
        }
        ((GpuLinkTag *)&quad->tag)->len = 8;
        quad->code = 0x3A;
        quad->red0 = effect->field40;
        quad->green0 = effect->field41;
        next_index = point_index + 1;
        quad->blue0 = effect->field42;
        quad->red1 = effect->field40;
        quad->green1 = effect->field41;
        quad->blue1 = effect->field42;
        quad->red2 = effect->field40;
        quad->green2 = effect->field41;
        quad->blue2 = effect->field42;
        quad->red3 = effect->field40;
        quad->green3 = effect->field41;
        row_off = effect->field42;
        quad->blue3 = row_off;
        modulo_result = next_index % 5;
        row_off = modulo_result;
        point = (ovl_1930844_819112CC_S_819112CC_3 *)((u8 *)effect + row_off * 4);
        next_start_x = point->unk_18.at02.v;
        scratch->vertices[2].vx = next_start_x;
        scratch->vertices[0].vx = next_start_x;
        next_delta_x = target_x - point->unk_18.at00.v;
        scratch->step_x = next_delta_x;
        if (interpolate != 0) {
            scratch->step_x = (next_delta_x / duration) * step;
        }
        /* BYTES: retail reads the integer half of the 16.16 step with one lhu of its high halfword; the shift spelling compiles to lw and sra */
        next_end_x = point->unk_18.at02.v + ((u16 *)&scratch->step_x)[1];
        scratch->vertices[3].vx = next_end_x;
        scratch->vertices[1].vx = next_end_x;
        next_start_y = point->unk_2C.at02.v;
        scratch->vertices[2].vy = next_start_y;
        scratch->vertices[0].vy = next_start_y;
        next_delta_y = target_y - point->unk_2C.at00.v;
        scratch->step_y = next_delta_y;
        if (interpolate != 0) {
            scratch->step_y = (next_delta_y / duration) * step;
        }
        next_end_y = point->unk_2C.at02.v;
        /* BYTES: retail reads the integer half of the 16.16 step with one lhu of its high halfword; the shift spelling compiles to lw and sra */
        y_step = ((u16 *)&scratch->step_y)[1];
        scratch->ot_index = RotAverage4(vertex_base, v1, v2, v3,
                                   (s32 *)sxy0, (s32 *)sxy1, (s32 *)sxy2, (s32 *)sxy3,
                                   depth, (next_end_y += y_step,
                                    scratch->vertices[3].vy = next_end_y,
                                    scratch->vertices[1].vy = next_end_y,
                                    flag));
        quad->x0 = scratch->screen[0].x;
        quad->y0 = scratch->screen[0].y;
        quad->x1 = scratch->screen[1].x;
        quad->y1 = scratch->screen[1].y;
        quad->x2 = scratch->screen[2].x;
        quad->y2 = scratch->screen[2].y;
        quad->x3 = scratch->screen[3].x;
        quad->y3 = scratch->screen[3].y;
        link = (u32 *)scratch->ot_index;
        if ((u32)link < 0x1E0U) {
            ot_slot2 = (u32)link << 2;
            angle_x_or_mask = (s32)0xFF000000;
            ot_slot2 += (unsigned long)scratch->ordering_table;
            ((GpuLinkTag *)&quad->tag)->addr = ((GpuLinkTag *)ot_slot2)->addr;
            link = (u32 *)scratch->ot_index;
            link = (u32 *)((u32)link << 2);
            link = (u32 *)((u8 *)link + (unsigned long)scratch->ordering_table);
            *link = (*link & (u32)angle_x_or_mask) | ((u32)quad & 0xFFFFFF);
            {
                GpuContext *ctx = context_slot->draw_buffer;
                mode = ctx->packetCursor;
                ctx->packetCursor = mode + 1;
            }
            SetDrawMode(mode, 0, 0,
                          GetTPage(0, effect->field12, 0, 0) & 0xFFFF,
                          0);
            ((GpuLinkTag *)&mode->tag)->addr = ((GpuLinkTag *)&scratch->ordering_table[scratch->ot_index])->addr;
            link = (u32 *)scratch->ot_index;
            link = (u32 *)((u32)link << 2);
            link = (u32 *)((u8 *)link + (unsigned long)scratch->ordering_table);
            *link = (*link & (u32)angle_x_or_mask) | ((u32)mode & 0xFFFFFF);
        }
    }
}

/* Queues a translucent full-screen overlay with countdown-dependent color and removes the effect when
   the count ends. */
void draw_screen_overlay_fade(void *effect, void *unused, void *fade_state_arg) {
    ovl_1930844_81911A8C_S_81911A8C_4 *fade_state = fade_state_arg;
    s8 green_blue;
    s8 frames_left;
    ovl_1930844_81911A8C_S_81911A8C_3 *overlay;
    ovl_1930844_81911A8C_S_81911A8C_1 *effect_state;

    effect_state = ((ovl_1930844_81911A8C_S_81911A8C_0 *)effect)->unk_00;
    effect_state->unk_14 = (u16) (effect_state->unk_14 + 1);
    overlay = ((ovl_1930844_81911A8C_S_81911A8C_5 *)(g_game_work.draw_buffer))->unk_8D0;
    ((ovl_1930844_81911A8C_S_81911A8C_5 *)(g_game_work.draw_buffer))->unk_8D0 =
        (overlay + 1);
    overlay->unk_0C = 0x140;
    overlay->unk_0E = 0xE0;
    overlay->unk_08 = 0;
    overlay->unk_0A = 0;
    overlay->unk_04 = 0xC0;
    green_blue = -0x40 - (fade_state->unk_05 * 0xC);
    overlay->unk_06 = green_blue;
    overlay->unk_05 = green_blue;
    SetTile(overlay);
    overlay->unk_07 = (u8) (overlay->unk_07 | 2);
    AddPrim(g_game_work.draw_buffer + 0xB0, overlay);
    frames_left = (u8) fade_state->unk_05 - 1;
    fade_state->unk_05 = frames_left;
    if ((frames_left << 0x18) == 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((ovl_1930844_81911A8C_S_81911A8C_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

void create_screen_overlay_effect(s32 *initial_value) {
    ovl_1930844_81911B9C_S_81911B9C_0 *object;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        object->unk_10 = (void *)draw_screen_overlay_fade;
        ((ObjectNodeHeader *)object)->sprite->frame_ticks = 0x10;
        object->unk_20 = (s32) *initial_value;
    }
}

/* Animates five orbiting points through line, quad, spin, expansion, and fade phases before removal. */
void update_five_point_orbit_effect(ovl_1930844_81911BF4_Obj81911BF4 *effect, s32 *position)
{
    s32 point_index;
    s32 brightness;
    s32 fade;
    u16 angle_step;
    s16 angle_sum;
    s32 signed_angle;
    s32 angle_dividend;
    s32 state;

    effect->inner->field14++;
    effect->timer++;

    for (point_index = 0; point_index < 5; point_index++) {
        effect->x[point_index] = position[0] + (((rsin(point_index * 0x333 + effect->angle) >> 4) * effect->scale) << 8);
        effect->y[point_index] = position[1] + (((rcos(point_index * 0x333 + effect->angle) >> 4) * effect->scale) << 8);
    }

    state = effect->state;
    if ((u32)state >= 7U) {
        return;
    }

    switch (state) {
    case 0:
        queue_radial_line_burst(effect, position, effect->timer, effect->duration);
        if (effect->timer < effect->duration) {
            return;
        }
        position[2] = effect->field14 << 16;
        effect->timer = 0;
        effect->state++;
        return;

    case 1:
        build_and_enqueue_five_translucent_quads_between_interpolated_points(effect, position, effect->timer, effect->duration);
        if (effect->timer < effect->duration) {
            return;
        }
        effect->timer = 0;
        effect->duration = 4;
        effect->state++;
        return;

    case 2:
        build_and_enqueue_five_translucent_quads_between_interpolated_points(effect, position, 0, 0);
        queue_perimeter_vertical_quads(effect, position, effect->timer, effect->duration);
        if (effect->timer < effect->duration) {
            return;
        }
        effect->field12 = 3;
        effect->timer = 0;
        effect->duration = 0x10;
        effect->state++;
        return;

    case 3:
        effect->angle_step += 0x10;
        effect->angle += effect->angle_step;
        signed_angle = effect->angle;
        effect->field10 += 0x10;
        effect->angle = signed_angle % 0x1000;
        build_and_enqueue_five_translucent_quads_between_interpolated_points(effect, position, 0, 0);
        queue_perimeter_vertical_quads(effect, position, 0, 0);
        if (effect->timer < effect->duration) {
            return;
        }
        effect->timer = 0;
        effect->state++;
        return;

    case 4:
        angle_step = effect->angle_step;
        angle_sum = (u16)effect->angle;
        brightness = effect->field42;
        angle_step += 0x10;
        angle_sum += angle_step;
        signed_angle = (s16)angle_sum;
        angle_dividend = signed_angle;
        brightness += 0x0C;
        effect->field42 = brightness;
        effect->field41 = brightness;
        effect->angle_step = angle_step;
        effect->angle = angle_sum;
        effect->scale = (u16)effect->scale - 4;
        if (angle_dividend < 0) {
            angle_dividend += 0xFFF;
        }
        effect->angle = signed_angle - ((angle_dividend >> 12) << 12);
        build_and_enqueue_five_translucent_quads_between_interpolated_points(effect, position, 0, 0);
        queue_perimeter_vertical_quads(effect, position, 0, 0);
        if (effect->timer < effect->duration) {
            return;
        }
        create_screen_overlay_effect(effect);
        effect->timer = 0;
        effect->duration = 0x20;
        effect->state++;
        return;

    case 5:
        angle_step = effect->angle_step;
        angle_sum = (u16)effect->angle;
        fade = effect->field42;
        angle_step += 0x10;
        angle_sum += angle_step;
        signed_angle = (s16)angle_sum;
        angle_dividend = signed_angle;
        fade -= 6;
        effect->field42 = fade;
        effect->field41 = fade;
        effect->field40 = fade;
        effect->angle_step = angle_step;
        effect->angle = angle_sum;
        effect->scale = (u16)effect->scale + 0x0C;
        if (angle_dividend < 0) {
            angle_dividend += 0xFFF;
        }
        effect->angle = signed_angle - ((angle_dividend >> 12) << 12);
        build_and_enqueue_five_translucent_quads_between_interpolated_points(effect, position, 0, 0);
        effect->scale = (u16)effect->scale * 2;

        for (point_index = 0; point_index < 5; point_index++) {
            effect->x[point_index] = position[0] + (((rsin(point_index * 0x333 + effect->angle) >> 4) * effect->scale) << 9);
            effect->y[point_index] = position[1] + (((rcos(point_index * 0x333 + effect->angle) >> 4) * effect->scale) << 9);
        }

        queue_perimeter_vertical_quads(effect, position, 0, 0);
        effect->scale = ((s32)(u16)effect->scale << 16) >> 17;
        if (effect->timer < effect->duration) {
            return;
        }

        effect->timer = 0;
        effect->state++;
        return;

    case 6:
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
}

/* Creates a controller for five orbiting points with copied motion, initial counters, and the supplied
   setting. */
void *create_five_point_orbit_effect(s32 state_value, ObjectPosition *source_data, s16 initial_setting) {
    ObjectNodeHeader *obj;
    ovl_1930844_81912074_S_80025874_1 *fields;
    ObjectPosition *object_data;

    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->update_callback = (void *)update_five_point_orbit_effect;
        fields = NODE_BODY(obj);
        ((ovl_1930844_81912074_S_80025874_0 *)obj)->unk_20 = state_value;
        fields->unk_08 = 8;
        fields->unk_10 = 2;
        fields->unk_0E = 0x48;
        fields->unk_12 = 1;
        fields->unk_04 = 0;
        fields->unk_06 = 0;
        fields->unk_0A = 0;
        fields->unk_0C = 0;
        fields->unk_40 = 0xC0;
        fields->unk_42 = 0;
        fields->unk_41 = 0;
        fields->unk_14 = initial_setting;
        object_data = obj->position;
        *object_data = *source_data;
        return obj;
    }
    return 0;
}

/* Moves an effect toward an actor or terrain endpoint, starts its impact visuals, and applies a
   delayed attack. */
void update_approaching_impact_effect(ApproachingImpactSpellBody *state, ObjectPosition *motion, SpriteFrameState *appearance) {
    ovl_1930844_81912154_LocalStack stack;
    s16 floor_height;
    s32 phase;
    s32 x_distance;
    s32 y_distance;
    s32 z_distance;
    s32 z_base;
    s32 z_base2;
    s32 z_table;
    s32 z_table2;
    s32 z_velocity;
    s32 next_state;
    s32 travel_frames;
    s32 direction;
    s32 step_direction;
    s32 step_count;
    u32 origin_z;
    s16 motion_value;
    s32 axis_delta;
    s32 x_scaled;
    s32 y_velocity;
    s16 end_tile_x;
    s16 tile_x;
    s16 tile_y;
    s32 model;
    SpriteFrameState *source_sprite;
    ovl_1930844_81912154_S_80025954_8 *destination;
    ObjectNodeHeader *owner_links;
    ActorRecord *owner;
    ovl_1930844_81912154_S_80025954_7_pre *target;
    ObjectPosition *origin;
    ovl_1930844_81912154_S_80025954_9 *entity;
    SpriteFrameState *grid_source;
    s16 *y_lookup_first;
    s16 source_coord;
    s16 *step_table;
    s16 *table_origin;
    s32 height;
    u16 end_tile_y;

    phase = state->spell.phase;
    owner = state->spell.caster;
    state->unk_10 = (u16) (state->unk_10 + 1);
    switch ((u32)phase) {
    case 0:
        state->unk_10 = 0U;
        state->spell.phase++;
        state->unk_0E = (u16) (((u16) owner->facing >> 9) & 7);
        appearance->color.word = 0x808080;
    case 1:
        owner_links = NODE_HEADER(owner);
        source_sprite = owner_links->sprite;
        if (resolve_record_orientation_or_fallback(source_sprite->source, source_sprite, &stack.offset.orientation, 0) == 0
            && !(owner_links->sprite->flags & 0x8000)) {
            break;
        }
        origin = owner_links->position;
        motion->x.unsigned_parts.integer = origin->x.w.i;
        motion->y.unsigned_parts.integer = origin->y.w.i;
        origin_z = (u16)origin->z.w.i;
        motion->z.unsigned_parts.integer = origin_z;
        if (!(owner_links->sprite->flags & 0x8000)) {
            motion->x.unsigned_parts.integer = (u16) (motion->x.unsigned_parts.integer
                + stack.offset.distance[0]);
            motion->y.unsigned_parts.integer = (u16) (motion->y.unsigned_parts.integer
                + stack.offset.distance[1]);
            motion->z.unsigned_parts.integer = (u16) (motion->z.unsigned_parts.integer
                + stack.offset.distance[2]);
        } else {
            motion->z.unsigned_parts.integer = origin_z - 0x40;
        }
        if (!(*state->spell.context & 0x80)) {
            break;
        }
        target = owner->target;
        if (target != NULL) {
            step_count = 1;
            destination = target[-1].unk_00;
            x_distance = destination->unk_00.at02.v - motion->x.w.i;
            x_distance = abs(x_distance);
            stack.offset.distance[0] = x_distance;
            y_distance = destination->unk_04.at02.v - motion->y.w.i;
            y_distance = abs(y_distance);
            stack.offset.distance[1] = y_distance;
            entity = owner->target;
            z_table = entity_height_offsets[entity->unk_13] << 0x10;
            z_distance = destination->unk_08.at02.v - z_table;
            z_base = motion->z.w.i + 0x300000;
            z_distance -= z_base;
            stack.offset.distance[2] = abs(z_distance);
            state->unk_12 = x_distance;
            do {
                if ((s16) stack.offset.distance[step_count] > state->unk_12) {
                    state->unk_12 = stack.offset.distance[step_count];
                }
                step_count += 1;
            } while (step_count < 3);
            travel_frames = (s32) ((u16) state->unk_12 << 0x10) >> 0x14;
            state->unk_12 = travel_frames;
            if (travel_frames == 0) {
                state->unk_12 = 1;
            }
            motion->velocity_x = (destination->unk_00.at00.v
                - motion->x.v) / state->unk_12;
            motion->velocity_y = (destination->unk_04.at00.v
                - motion->y.v) / state->unk_12;
            entity = owner->target;
            z_table2 = entity_height_offsets[entity->unk_13] << 0x10;
            z_velocity = destination->unk_08.at00.v - z_table2;
            z_base2 = motion->z.v + 0x300000;
            z_velocity -= z_base2;
            motion->velocity_z = z_velocity / state->unk_12;
            create_shrinking_arc_effect(state, motion);
            next_state = (u16) state->spell.phase + 1;
        } else {
            table_origin = dir_step_x;
            step_count = 0;
            grid_source = owner_links->sprite;
            tile_x = grid_source->tile_x;
            tile_y = grid_source->tile_y;
            end_tile_x = tile_x;
            end_tile_y = tile_y;
            do {
                if ((check_layer_offset_height(((s16) tile_x << 6) & 0xFFC0, ((s16) tile_y << 6) & 0xFFC0,
                    owner->ground_height, (s16) (state->unk_0E << 9)) << 0x10)
                    != 0) {
                    goto grid_hit;
                }
                {
                    direction = (s16) state->unk_0E;
                    height = (u16) owner->ground_height;
                    entity = (void *)&dir_step_x[direction];
                }
                height = (s16) (height - 0x20);
                y_lookup_first = &dir_step_y[direction];
                floor_height = sample_terrain_surface_height(((((s16) tile_x + *((s16 *)entity)) << 6) + 0x20) & 0xFFE0,
                    ((((s16) tile_y + *y_lookup_first) << 6) + 0x20) & 0xFFE0, height);
                if (floor_height >= 0x201) {
                    break;
                }
                if ((s16) (floor_height - (u16) owner->ground_height) < -0x3F) {
                    break;
                }
                step_direction = (s16) state->unk_0E;
                step_count += 1;
                source_coord = tile_x + (u16) dir_step_x[step_direction];
                tile_x = source_coord;
                motion_value = tile_y + (u16) dir_step_y[step_direction];
                tile_y = motion_value;
                end_tile_y = motion_value;
                end_tile_x = source_coord;
            } while (step_count < 8);
            destination = (ovl_1930844_81912154_S_80025954_8 *)stack.motion;
            x_scaled = (u32) end_tile_x << 0x10;
            step_table = table_origin;
            x_scaled >>= 0xA;
            goto grid_coords;
        grid_hit:
            destination = (ovl_1930844_81912154_S_80025954_8 *)stack.motion;
            x_scaled = (u32) end_tile_x << 0x10;
            step_table = table_origin;
            x_scaled >>= 0xA;
        grid_coords:
            axis_delta = x_scaled;
            direction = (step_table[(s16) state->unk_0E] + 1) << 5;
            axis_delta += direction;
            destination->unk_00.at02.v = axis_delta;
            axis_delta = (u32) axis_delta << 0x10;
            model = ((s16) end_tile_y << 6) + ((dir_step_y[(s16) state->unk_0E] + 1) << 5);
            destination->unk_04.at02.v = model;
            axis_delta >>= 0x10;
            destination->unk_08.at02u.v = motion->z.unsigned_parts.integer;
            model = (u32) model << 0x10;
            axis_delta -= motion->x.w.i;
            axis_delta = __builtin_abs(axis_delta);
            stack.offset.distance[0] = axis_delta;
            model >>= 0x10;
            model -= motion->y.w.i;
            model = __builtin_abs(model);
            stack.offset.distance[1] = model;
            state->unk_12 = axis_delta;
            if ((s16) stack.offset.distance[1] > (s16) axis_delta) {
                state->unk_12 = stack.offset.distance[1];
            }
            travel_frames = (s32) ((u16) state->unk_12 << 0x10) >> 0x14;
            state->unk_12 = travel_frames;
            if (travel_frames == 0) {
                state->unk_12 = 1;
            }
            motion->velocity_x = (((ovl_1930844_81912154_S_80025954_12 *)(stack.motion))->unk_00
                - motion->x.v) / state->unk_12;
            y_velocity = (destination->unk_04.at00.v
                - motion->y.v) / state->unk_12;
            motion->velocity_z = 0;
            motion->velocity_y = y_velocity;
            create_shrinking_arc_effect(state, motion);
            next_state = 6;
        }
        goto set_state;
    case 2:
        motion->x.v = (s32) (motion->x.v
            + motion->velocity_x);
        motion->y.v = (s32) (motion->y.v
            + motion->velocity_y);
        motion->z.v = (s32) (motion->z.v
            + motion->velocity_z);
        if ((s16) state->unk_10 < state->unk_12) {
            break;
        }
        create_five_point_orbit_effect(state, motion, ((ovl_1930844_81912154_S_80025954_15 *)(owner->target))->unk_88);
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        state->unk_10 = 0U;
        state->spell.phase++;
        break;
    case 3:
        if ((s16) state->unk_10 >= 8) {
            state->unk_10 = 0U;
            state->spell.phase++;
            break;
        }
        state->unk_14 = 0;
        return;
    case 4:
        if ((s16) state->unk_10 < 0x44) {
            break;
        }
        apply_attack_power_and_element_effects(owner->target, 0x18, state->spell.variant, 1,
            (s32) (s16) (state->unk_0E << 9), owner, 1);
        state->unk_10 = 0U;
        state->spell.phase++;
        break;
    case 5:
        if (state->unk_14 == 0) {
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)state + -2)) = (u16) ((*(u16 *)((u8 *)state + -2)) | NODE_REMOVE);
            (*&object_flag_block.flags) = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        }
        break;
    case 6:
        motion->x.v = (s32) (motion->x.v
            + motion->velocity_x);
        motion->y.v = (s32) (motion->y.v
            + motion->velocity_y);
        motion->z.v = (s32) (motion->z.v
            + motion->velocity_z);
        if ((s16) state->unk_10 < state->unk_12) {
            break;
        }
        next_state = 5;
    set_state:
        state->spell.phase = next_state;
        state->unk_10 = 0U;
    }
    state->unk_14 = 0;
    return;
}

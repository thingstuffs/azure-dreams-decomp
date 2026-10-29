/* Kewne actor rendering, moving sprite effects, and projected ellipse geometry. */
#include "shared/entity.h"
#include "shared/object_node.h"
#include "modules/dungeon_ovl_9c32d4.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/kewne.h"

/* Prepares an ellipse render region, follows the linked position, emits particles, and fades out the
 * effect. */
void update_actor_render_effect_and_position(u8 *actor_data, u8 *output_data, u8 *effect_data)
{
    ovl_9c32d4_809A32D4_LocalArgs draw_region;
    ovl_9c32d4_809A32D4_Actor *actor;
    ovl_9c32d4_809A32D4_Output *output;
    u8 *initial_page;
    ovl_9c32d4_809A32D4_S_80174AD4_1 *rect_page;
    ovl_9c32d4_809A32D4_S_80174AD4_3 *region_page;
    u8 *base_page;
    u8 *packet_list;
    void *page_packet;
    ovl_9c32d4_809A32D4_S_80174AD4_2 *rect_packet;
    void *region_packet;
    u8 alternate_page;
    u8 adjust_y;
    s16 steps_left;
    s16 next_steps;
    s32 draw_y;
    s32 texture_u;
    s32 packed_size;
    s32 state;
    u8 decay_level;
    u8 rise_level;

    actor = (ovl_9c32d4_809A32D4_Actor *)actor_data;
    output = (ovl_9c32d4_809A32D4_Output *)output_data;
    initial_page = DUNGEON_INITIAL;
    base_page = upper_draw_context;
    state = actor->state;
    alternate_page = initial_page != base_page;
    packet_list = initial_page + 0xB0;

    if (state == 0) {
        page_packet = ((ovl_9c32d4_809A32D4_S_80174AD4_0 *)initial_page)->unk_8D0;
        ((ovl_9c32d4_809A32D4_S_80174AD4_0 *)initial_page)->unk_8D0 = (u8 *)page_packet + 0xC;
        SetDrawArea(page_packet, DUNGEON_FROM_PAGE);
        AddPrim(packet_list, page_packet);

        draw_y = 0x110;
        draw_region.x = 0x340;
        draw_region.y = 0x100;
        draw_region.w = 0x20;
        draw_region.h = 0x20;
        texture_u = 0x350;
        draw_region.u = texture_u;
        adjust_y = alternate_page;
        if (adjust_y != 0) {
            draw_y = 0x30;
        }
        draw_region.v = draw_y;

        emit_concentric_ellipse_quads(0x10, 0x10, 0, 0, texture_u, draw_region.v,
                      actor, (u8 *)actor + 4, packet_list, 0, 0x20);

        rect_page = DUNGEON_FROM_PAGE;
        rect_packet = rect_page->unk_8D0;
        rect_page->unk_8D0 = (u8 *)rect_packet + 0x10;
        rect_packet->unk_04 = 0x60000000;
        rect_packet->unk_03 = 3;
        rect_packet->unk_08 = draw_region.x;
        draw_y = draw_region.y;
        if (adjust_y != 0) {
            draw_y -= 0xE0;
        }
        packed_size = *(s32 *)&draw_region.w;
        rect_packet->unk_0A = draw_y;
        rect_packet->unk_0C = packed_size;
        AddPrim(packet_list, rect_packet);

        region_page = DUNGEON_FROM_PAGE;
        region_packet = region_page->unk_8D0;
        region_page->unk_8D0 = (u8 *)region_packet + 0xC;
        SetDrawArea(region_packet, (void *)&draw_region);
        AddPrim(packet_list, region_packet);
        actor->state++;
    } else if (state == 1) {
        register_node((u8 *)actor - 0x20, process_linked_mesh_states_mode_0);
        actor->state++;
    } else if (state == 3) {
        decay_level = ((ovl_9c32d4_809A32D4_S_80174AD4_4 *)effect_data)->unk_0C;
        if (decay_level != 0) {
            decay_level -= 8;
            ((ovl_9c32d4_809A32D4_S_80174AD4_4 *)effect_data)->unk_0C = decay_level;
            if (decay_level == 0) {
                (*(u16 *)((u8 *)actor + -2)) |= NODE_REMOVE;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            }
        }
    } else {
        rise_level = ((ovl_9c32d4_809A32D4_S_80174AD4_4 *)effect_data)->unk_0C;
        if (rise_level < 0xC0) {
            ((ovl_9c32d4_809A32D4_S_80174AD4_4 *)effect_data)->unk_0C = rise_level + 0x20;
        }
        if (actor->field16 != *actor->field10) {
            actor->state++;
        }
    }
    steps_left = 4;
    if (actor->state != 3) {
        output->field02 = ((ovl_9c32d4_809A32D4_S_80174AD4_5 *)(actor->field1C))->unk_02;
        output->field06 = ((ovl_9c32d4_809A32D4_S_80174AD4_5 *)(actor->field1C))->unk_06;
        output->field0A = ((ovl_9c32d4_809A32D4_S_80174AD4_5 *)(actor->field1C))->unk_0A - 0xC;
        do {
            spawn_randomized_directional_motion_object((u8 *)actor - 0x20, (((ovl_9c32d4_809A32D4_S_80174AD4_7 *)(((ovl_9c32d4_809A32D4_S_80174AD4_6 *)actor)->unk_0C))->unk_00 >> 9) & 7,
                0xFF);
            next_steps = steps_left - 1;
            steps_left = next_steps;
        } while ((next_steps << 16) > 0);
    }
}

/* Creates an ellipse effect linked to the parent's position and watches the supplied state byte for a
 * change. */
void create_parent_position_effect(EntityRec *parent, s32 effect_param, u8 *effect_data)
{
    ObjectNodeHeader *effect;
    ObjectPosition *position;
    SpriteFrameState *display;
    ovl_9c32d4_809A35A0_S_80174DA0_4 *state;
    void *parent_position;
    u16 coordinate;

    effect = allocate_list_node(0x12, parent);
    if (effect != 0) {
        effect->update_callback = update_actor_render_effect_and_position;
        position = effect->position;

        coordinate = ((ovl_9c32d4_809A35A0_S_80174DA0_5 *)((*(void * *)&parent->z)))->unk_02;
        *((u16 *)&position->velocity_x + 1) = coordinate;
        position->x.w.i = coordinate;

        coordinate = ((ovl_9c32d4_809A35A0_S_80174DA0_5 *)((*(void * *)&parent->z)))->unk_06;
        *((u16 *)&position->velocity_y + 1) = coordinate;
        position->y.w.i = coordinate;

        coordinate = ((ovl_9c32d4_809A35A0_S_80174DA0_5 *)((*(void * *)&parent->z)))->unk_0A;
        *((u16 *)&position->velocity_z + 1) = coordinate;
        position->z.w.i = coordinate;

        display = effect->sprite;
        display->source = D_80175F90;
        display->scale_y = 0x1000;
        display->scale_x = 0x1000;
        display->color.word = 0;
        display->depth_bias = 8;

        parent_position = (*(void * *)&parent->z);
        state = (u8 *)effect + 0x20;
        state->unk_0C = effect_param;
        state->unk_10 = effect_data;
        state->unk_1C = parent_position;
        state->unk_16 = *effect_data;
        ((ovl_9c32d4_809A35A0_S_80174DA0_0 *)effect)->unk_20 = 0x40;
        state->unk_04 = 0;
    }
}

/* Moves the effect along its direction while below the terrain height, reduces speed, and removes it when
 * stopped. */
void advance_directional_effect_motion(ovl_9c32d4_809A3698_MotionState *state, ovl_9c32d4_809A3698_MotionPosition *position) {
    s16 height;
    s16 speed;
    height = sample_terrain_surface_height(position->x.ovl_9c32d4_809A3698_half.high, position->y.ovl_9c32d4_809A3698_half.high, (s16)(position->z.ovl_9c32d4_809A3698_half.high + 2));
    if ((s16)position->z.ovl_9c32d4_809A3698_half.high < height) {
        position->x.word -= (dir_step_x[state->direction] * state->speed) << 11;
        position->y.word -= (dir_step_y[state->direction] * state->speed) << 11;
        position->z.word += (0xC0 - state->speed) << 10;
    }
    speed = state->speed - 8;
    state->speed = speed;
    if (speed <= 0) {
        *(u16 *)((u8 *)state - 2) |= NODE_REMOVE;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a sprite near its parent with randomized position and speed along the supplied direction. */
void spawn_randomized_directional_motion_object(ovl_9c32d4_809A37C0_MotionObject *parent, s16 direction, s32 value) {
    ovl_9c32d4_809A37C0_MotionObject *object;
    SpriteFrameState *draw;
    ovl_9c32d4_809A37C0_MotionState *state;
    object = allocate_list_node(0x212, parent);
    if (object != 0) {
        object->update = advance_directional_effect_motion;
        register_node(object, project_sprite_chain);
        object->position->x.ovl_9c32d4_809A37C0_half.high = parent->position->x.ovl_9c32d4_809A37C0_half.high + (rand() & 0x3F) - 0x20;
        object->position->y.ovl_9c32d4_809A37C0_half.high = parent->position->y.ovl_9c32d4_809A37C0_half.high + (rand() & 0x3F) - 0x20;
        object->position->z.ovl_9c32d4_809A37C0_half.high = parent->position->z.ovl_9c32d4_809A37C0_half.high + (rand() & 0x3F) - 0x20;
        draw = object->draw;
        state = &object->state;
        draw->source = D_80175F9C;
        draw->scale_x = draw->scale_y = 0x1000;
        draw->color.word = value;
        draw->depth_bias = 8;
        state->direction = direction;
        state->speed = (rand() & 0xFF) | 0x80;
    }
}

/*
 * Adds radius times the trigonometric value shifted right eight bits to the center, returning a
 * signed 16-bit coordinate.
 */
static __inline__ s16 project_ring_coordinate(s32 radius, s32 trig, u16 center)
{
    return center + ((radius * trig) >> 8);
}

/* Emit colored quads between two concentric elliptical arcs. */
void emit_concentric_ellipse_quads(u16 radius_a_x, u16 radius_a_y, u16 radius_b_x, u16 radius_b_y,
                   u16 center_x, s16 center_y, s32 *color_b_ptr, s32 *color_a_ptr,
                   s32 draw_bucket, s32 start_segment, s32 end_segment)
{
    ovl_9c32d4_809A38E4_RingRadii radii;
    union { u16 v; } segment_limit = {0};
    u16 segment;
    s32 scale_b_x;
    s32 scale_b_y;
    s32 scale_a_x;
    s32 scale_a_y;
    s32 angle;
    s32 sin_angle;
    s32 cos_angle;
    s32 prev_sin;
    s32 prev_cos;
    u8 *prim;
    u8 *submit_prim;
    u8 *next_vertex;
    u8 *vertex_data;
    ovl_9c32d4_809A38E4_GraphicsState **graphics_ptr;
    ovl_9c32d4_809A38E4_GraphicsState *graphics;
    u16 next_segment;
    s32 outer_prev_x;
    s32 outer_prev_y;
    s32 outer_next_x;
    s32 outer_next_y;
    s32 inner_prev_x;
    s32 inner_prev_y;
    s32 inner_next_x;
    s32 inner_next_y;

    s32 color_b;
    s32 color_a;

    vertex_data = (u8 *)((s16)start_segment);
    angle = (s32)vertex_data << 7;
    radii.inner_x = radius_a_x;
    graphics_ptr = &g_game_work.draw_buffer;
    graphics = *graphics_ptr;
    graphics = (ovl_9c32d4_809A38E4_GraphicsState *)((u8 *)graphics + 0x8D0);
    prim = *(u8 **)graphics;
    radii.inner_y = radius_a_y;
    radii.outer_x = radius_b_x;
    radii.outer_y = radius_b_y;
    sin_angle = rcos(angle) >> 4;
    cos_angle = rsin(angle) >> 4;
    segment_limit.v = end_segment;
    segment = start_segment;

    vertex_data = (u8 *)((s32)vertex_data < (s16)end_segment);
    if (vertex_data != 0) {
        scale_b_x = radii.outer_x;
        scale_b_y = radii.outer_y;
        scale_a_x = radii.inner_x;
        do {
            scale_a_y = radii.inner_y;
            vertex_data = prim + 0x1A;
        } while (0);
        do {
            angle += 0x80;
            prev_sin = sin_angle;
            sin_angle = rcos(angle) >> 4;
            prev_cos = cos_angle;
            cos_angle = rsin(angle);
            cos_angle = cos_angle >> 4;

            color_b = *color_b_ptr;
            (*(u32 *)((u8 *)vertex_data + -0x0A)) = color_b;
            (*(u32 *)((u8 *)vertex_data + -0x16)) = color_b;
            color_a = *color_a_ptr;
            (*(u32 *)((u8 *)vertex_data + 0x0E)) = color_a;
            (*(u32 *)((u8 *)vertex_data + 0x02)) = color_a;
            SetPolyGT4(prim);

            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_0A = 1;
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_04 = 1;
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_16 = 2;
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_10 = 2;
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_11 = 0xFB;
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_05 = 0xFB;
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_17 = 0xFB;
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_0B = 0xFB;

            outer_prev_x = project_ring_coordinate(scale_b_x, prev_sin, center_x);
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_00 = outer_prev_x;
            outer_prev_y = project_ring_coordinate(scale_b_y, prev_cos, center_y);
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_02 = outer_prev_y;
            outer_next_x = project_ring_coordinate(scale_b_x, sin_angle, center_x);
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_0C = outer_next_x;
            outer_next_y = project_ring_coordinate(scale_b_y, cos_angle, center_y);
            ((ovl_9c32d4_809A38E4_S_801750E4_0_pre *)vertex_data)[-1].unk_0E = outer_next_y;
            inner_prev_x = project_ring_coordinate(scale_a_x, prev_sin, center_x);
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_06 = inner_prev_x;
            inner_prev_y = project_ring_coordinate(scale_a_y, prev_cos, center_y);
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_08 = inner_prev_y;
            inner_next_x = project_ring_coordinate(scale_a_x, sin_angle, center_x);
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_12 = inner_next_x;
            inner_next_y = project_ring_coordinate(scale_a_y, cos_angle, center_y);
            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_14 = inner_next_y;

            ((ovl_9c32d4_809A38E4_S_801750E4_0 *)vertex_data)->unk_00 = 0x133;

            submit_prim = prim;
            AddPrim(draw_bucket, submit_prim);
            prim += sizeof(ovl_9c32d4_809A38E4_Block);
            next_vertex = vertex_data + sizeof(ovl_9c32d4_809A38E4_Block);
            next_segment = segment;
            next_segment += 1;
            vertex_data = next_vertex;
            segment = next_segment;
        } while (((s32)(u32)next_segment << 16) < ((s32)(u32)segment_limit.v << 16));
    }
    (*graphics_ptr)->next_prim = prim;
}

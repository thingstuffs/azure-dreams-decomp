#include "sdk/libc.h"
/* Death effect projection, motion, fading, and object creation. */
#include "shared/object_node.h"
#include "dungeon/monster/death.h"
#include "modules/dungeon_ovl_be1084.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"

/* Projects linked effect positions and queues their colored pixel and drawing-mode packets by depth. */
s32 build_projected_tile_packets(u8 *point_data, u16 *position)
{
    PointTileScratch *scratch = (PointTileScratch *)0x1F800000;
    void **globals = ((void * *)(&g_game_work));
    GpuContext *render_state = globals[0];
    TILE_1 *first_packet = render_state->packetCursor;
    TILE_1 *packet;
    DR_MODE *mode_packet;
    s32 depth;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->ordering_table = (u32 *)&render_state->orderTag;
    scratch->packet_cursor = first_packet;
    for (;;) {
        scratch->position.vx = position[1];
        packet = scratch->packet_cursor;
        scratch->position.vy = position[3];
        scratch->position.vz = position[5];

        scratch->packet_cursor = packet + 1;
        depth = RotTransPers(&scratch->position, (s32 *)&packet->x0,
                              &scratch->depth_cue, &scratch->gte_flag);
        scratch->ot_index = depth;

        if ((u32)depth < 480U) {
            u16 tpage;
            u8 r;
            u8 g;
            u8 b;

            /* BYTES: retail copies the tile colour word (r0, g0, b0 and code) with one lw/sw; member copies compile to four lbu/sb */
            *(u32 *)&packet->r0 = *(u32 *)(point_data + 8);
            ((GpuLinkTag *)&packet->tag)->len = 2;
            r = packet->r0;
            g = packet->g0;
            b = packet->b0;
            packet->r0 = r;
            packet->g0 = g;
            packet->b0 = b;
            packet->code = 106;

            packet->tag = (packet->tag & length_mask) |
                          (scratch->ordering_table[scratch->ot_index] & addr_mask);
            scratch->ordering_table[scratch->ot_index] =
                                    (scratch->ordering_table[scratch->ot_index] & length_mask) |
                                    ((u32)packet & addr_mask);

            mode_packet = scratch->packet_cursor;
            scratch->packet_cursor = mode_packet + 1;
            tpage = (u16)GetTPage(0, 1, 0, 0);
            SetDrawMode(mode_packet, 0, 0, tpage, 0);

            mode_packet->tag = (mode_packet->tag & length_mask) |
                          (scratch->ordering_table[scratch->ot_index] & addr_mask);
            mode_packet = (DR_MODE *)((u32)mode_packet & addr_mask);
            scratch->ordering_table[scratch->ot_index] =
                                    (scratch->ordering_table[scratch->ot_index] & length_mask) |
                                    (u32)mode_packet;
        }

        {
            u8 *next_point = *(u8 **)(point_data - 8);

            if (next_point == 0)
                break;
            point_data = next_point + 0x20;
            position = (u16 *)*(u8 **)(next_point + 8);
        }
    }

    ((GpuContext *)globals[0])->packetCursor = scratch->packet_cursor;
    return 0;
}

/* Accelerates the effect toward its target, fades its color, and expires it near the target or on timeout. */
void advance_effect_toward_target(ParentReturnEffectBody *effect, ObjectPosition *position) {
    s16 fade_level;
    s32 scaled_red;
    s32 scaled_green;
    s32 x_distance;
    s32 y_distance;
    s32 scaled_blue;

    position->x.v = (s32) (position->x.v
        + effect->velocity_x);
    position->y.v = (s32) (position->y.v
        + effect->velocity_y);
    position->z.v = (s32) (position->z.v + effect->velocity_z);
    effect->velocity_x = (s32) (effect->velocity_x + effect->acceleration_x);
    effect->velocity_y = (s32) (effect->velocity_y + effect->acceleration_y);
    effect->velocity_z = (s32) (effect->velocity_z + effect->acceleration_z);
    x_distance = abs(effect->target_x.s - position->x.w.i);
    if (x_distance < 0x10) {
        y_distance = abs(effect->target_y.s - position->y.w.i);
        if (y_distance < 0x10) {
            NODE_HEADER(effect)->flags |= NODE_REMOVE;
            object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        }
    }
    scaled_red = effect->base_color.channels.red * effect->fade_level;
    effect->color.channels.red = (s8) (scaled_red / 256);
    scaled_green = effect->base_color.channels.green * effect->fade_level;
    effect->color.channels.green = (s8) (scaled_green / 256);
    scaled_blue = effect->base_color.channels.blue * effect->fade_level;
    effect->color.channels.blue = (s8) (scaled_blue / 256);
    fade_level = (u16) effect->fade_level - 8;
    effect->fade_level = fade_level;
    effect->output_color = (s32) effect->color.packed;
    if ((fade_level << 0x10) <= 0) {
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

/* Moves the effect with halved velocity each frame, fades its color, and removes it when its timer
 * expires. */
void advance_damped_motion_and_fade_effect(FadeEffect *effect,ObjectPosition *motion) {
 s32 red,green,blue;
 s16 remaining;
 motion->x.v+=motion->velocity_x;
 motion->y.v+=motion->velocity_y;
 motion->z.v+=motion->velocity_z;
 motion->velocity_x/=2;
 motion->velocity_y/=2;
 motion->velocity_z/=2;
 red=effect->base_color.c.r*effect->remaining;
 effect->current.color.red=red/effect->total;
 green=effect->base_color.c.g*effect->remaining;
 effect->current.color.green=green/effect->total;
 blue=effect->base_color.c.b*effect->remaining;
 effect->current.color.blue=blue/effect->total;
 remaining=effect->remaining-1;
 effect->remaining=remaining;
 effect->output=effect->current.packed;
 if(remaining<=0) {
  NODE_HEADER(effect)->flags|=NODE_REMOVE;
  object_flag_block.flags|=OBJECT_REMOVE_PENDING;
 }
}

/* Creates a timed point effect offset from its owner with motion that converges toward the source
 * position. */
void create_parent_return_effect(
    void *parent_obj, s16 effect_param, s32 initial_value, s16 duration,
    s16 offset_x, s16 offset_y, s16 offset_z)
{
    ObjectPayloadView *parent = parent_obj;
    ObjectNodeHeader *effect;
    ParentReturnEffectBody *effect_data;
    s32 step_x;
    s32 step_y;
    s32 step_z;
    s32 rounded_step_x;
    s32 rounded_step_z;

    effect = allocate_list_node(0x211, parent);
    if (effect != 0) {
        effect->update_callback = advance_effect_toward_target;

        effect->position->x.w.i =
            ((MovingPosition *)(parent->unk_08))->x + offset_x;
        effect->position->y.w.i =
            ((MovingPosition *)(parent->unk_08))->y + offset_y;
        effect->position->z.w.i =
            ((MovingPosition *)(parent->unk_08))->z + offset_z - 100;

        effect_data = NODE_BODY(effect);
        effect_data->target_x.u = ((MovingPosition *)(parent->unk_08))->x;
        effect_data->target_y.u = ((MovingPosition *)(parent->unk_08))->y;
        effect_data->target_z = ((MovingPosition *)(parent->unk_08))->z;

        step_x = -(offset_x << 16) / (duration / 8);
        effect_data->velocity_x = step_x / 2;
        step_y = -(offset_y << 16) / (duration / 8);
        effect_data->velocity_y = step_y / 2;
        step_z = -(offset_z << 16) / (duration / 8);
        effect_data->velocity_z = step_z / 2;

        rounded_step_x = -(offset_x << 16) / (duration / 8);
        if (rounded_step_x < 0) {
            rounded_step_x += 3;
        }
        effect_data->acceleration_x = rounded_step_x >> 2;

        rounded_step_z = step_y;
        if (rounded_step_z < 0) {
            rounded_step_z += 3;
        }
        effect_data->acceleration_y = rounded_step_z >> 2;

        rounded_step_z = step_z;
        effect_data->acceleration_z = (rounded_step_z / 4);

        effect_data->unk_14 = effect_param;
        effect_data->fade_level = duration;
        register_node(effect, build_projected_tile_packets);
        rounded_step_x = initial_value;
        effect_data->base_color.packed = rounded_step_x;
        effect_data->output_color = initial_value;
    }

}

/* Creates a short-lived colored point effect offset from its owner with randomized velocity. */
void spawn_parent_offset_random_motion_effect(void *parent_arg, register s16 effect_param_arg, register s32 state_value_arg,
    register s32 unused_arg, register s32 offset_x_arg, register s32 offset_y_arg, register s32 offset_z_arg) {
    register ObjectPayloadView *parent = parent_arg;
    register s16 effect_param = effect_param_arg;
    register s32 state_value = state_value_arg;
    register s32 offset_x = offset_x_arg;
    register s32 offset_y = offset_y_arg;
    register s32 offset_z = offset_z_arg;
    S_80BC172C_1 *effect_data;
    ObjectNodeHeader *effect;
    u16 parent_x;

    effect = allocate_list_node(0x211, parent);
    if (effect != NULL) {
        effect->update_callback = advance_damped_motion_and_fade_effect;
        /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: dungeon/func_80BC172C). */
        do {
            parent_x = ((MovingPosition *)(parent->unk_08))->x;
            effect->position->x.w.i = (s16) (parent_x + offset_x);
            effect->position->y.w.i =
                (s16) (((MovingPosition *)(parent->unk_08))->y + offset_y);
            effect->position->z.w.i =
                (s16) ((((MovingPosition *)(parent->unk_08))->z + offset_z) - 0x64);
        } while (0);
        effect->sprite->depth_bias = 6;
        effect->position->velocity_x = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        effect->position->velocity_y = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        effect_data = NODE_BODY(effect);
        effect->position->velocity_z = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        effect_data->unk_14 = effect_param;
        effect_data->unk_32 = 5;
        effect_data->unk_34 = 5;
        register_node(effect, build_projected_tile_packets);
        ((S_80BC172C_0 *)effect)->unk_20 = state_value;
        effect_data->unk_08 = state_value;
    }
}

/* Shrinks and rotates the effect, updates its color and projected depth, and removes it when its timer
 * expires. */
void spawn_configured_overlay_object_b(void *effect_arg, MovingPosition *position, S_80BC1880_0 *render_state)
{
    S_80BC1880_1 *effect = effect_arg;
    DepthProjectionWork projection;
    s16 ticks_left;

    render_state->unk_1C -= 500;
    render_state->unk_1E -= 500;
    render_state->unk_1A += 400;

    render_state->unk_0C =
        effect->unk_02 *
        (effect->unk_1C - effect->unk_1A.s) /
        effect->unk_1C;
    render_state->unk_0D =
        effect->unk_03 *
        (effect->unk_1C - effect->unk_1A.s) /
        effect->unk_1C;
    render_state->unk_0E =
        effect->unk_04 *
        (effect->unk_1C - effect->unk_1A.s) /
        effect->unk_1C;

    projection.position.vx = position->x;
    projection.position.vy = position->y;
    projection.position.vz = position->z;
    render_state->unk_06 =
        RotTransPers(&projection.position, &projection.screen_xy, &projection.depth_cue, &projection.gte_flag) - 8;

    ticks_left = effect->unk_1A.u - 1;
    effect->unk_1A.u = ticks_left;
    if ((ticks_left << 16) <= 0) {
        ((ObjectRetirementFlags *)effect)[-1].flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

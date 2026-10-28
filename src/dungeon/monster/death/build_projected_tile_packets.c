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
    Scratch *scratch = (Scratch *)0x1F800000;
    void **globals = ((void * *)(&g_game_work));
    GpuContext *render_state = (GpuContext *)globals[0];
    Packet *first_packet = (Packet *)render_state->packetCursor;
    Packet *packet;
    Packet *mode_packet;
    s32 depth;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->table = (u8 *)render_state + 0xB0;
    scratch->current = (u8 *)first_packet;
    for (;;) {
        scratch->in0 = position[1];
        packet = (Packet *)scratch->current;
        scratch->in1 = position[3];
        scratch->in2 = position[5];

        scratch->current = (u8 *)packet + 0xC;
        depth = RotTransPers(&scratch->in0, (u8 *)packet + 8,
                              &scratch->out0, &scratch->out1);
        scratch->index = depth;

        if ((u32)depth < 480U) {
            u16 tpage;
            u8 r;
            u8 g;
            u8 b;

            packet->data.link = *(u32 *)(point_data + 8);
            packet->code = 2;
            r = packet->data.color.r;
            g = packet->data.color.g;
            b = packet->data.color.b;
            packet->data.color.r = r;
            packet->data.color.g = g;
            packet->data.color.b = b;
            packet->data.color.command = 106;

            *(u32 *)packet = (*(u32 *)packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & addr_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    ((u32)packet & addr_mask);

            mode_packet = (Packet *)scratch->current;
            scratch->current = (u8 *)mode_packet + 0xC;
            tpage = (u16)GetTPage(0, 1, 0, 0);
            SetDrawMode(mode_packet, 0, 0, tpage, 0);

            *(u32 *)mode_packet = (*(u32 *)mode_packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & addr_mask);
            mode_packet = (Packet *)((u32)mode_packet & addr_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
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

    ((GpuContext *)globals[0])->packetCursor = scratch->current;
    return 0;
}

/* Accelerates the effect toward its target, fades its color, and expires it near the target or on timeout. */
void advance_effect_toward_target(void *effect, ObjectPosition *position) {
    s16 fade_level;
    s32 scaled_red;
    s32 scaled_green;
    s32 x_distance;
    s32 y_distance;
    s32 scaled_blue;

    position->x.v = (s32) (position->x.v
        + ((S_80BC1264_1 *)effect)->unk_40);
    position->y.v = (s32) (position->y.v
        + ((S_80BC1264_1 *)effect)->unk_44);
    position->z.v = (s32) (position->z.v + ((S_80BC1264_1 *)effect)->unk_48);
    ((S_80BC1264_1 *)effect)->unk_40 = (s32) (((S_80BC1264_1 *)effect)->unk_40 + ((S_80BC1264_1 *)effect)->unk_4C);
    ((S_80BC1264_1 *)effect)->unk_44 = (s32) (((S_80BC1264_1 *)effect)->unk_44 + ((S_80BC1264_1 *)effect)->unk_50);
    ((S_80BC1264_1 *)effect)->unk_48 = (s32) (((S_80BC1264_1 *)effect)->unk_48 + ((S_80BC1264_1 *)effect)->unk_54);
    x_distance = abs(((S_80BC1264_1 *)effect)->unk_36 - position->x.w.i);
    if (x_distance < 0x10) {
        y_distance = abs(((S_80BC1264_1 *)effect)->unk_38 - position->y.w.i);
        if (y_distance < 0x10) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((ObjectRetirementFlags *)effect)[-1].flags | NODE_REMOVE);
            object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        }
    }
    scaled_red = ((S_80BC1264_1 *)effect)->unk_00 * ((S_80BC1264_1 *)effect)->unk_32;
    ((S_80BC1264_1 *)effect)->unk_04.at00.v = (s8) (scaled_red / 256);
    scaled_green = ((S_80BC1264_1 *)effect)->unk_01 * ((S_80BC1264_1 *)effect)->unk_32;
    ((S_80BC1264_1 *)effect)->unk_04.at01.v = (s8) (scaled_green / 256);
    scaled_blue = ((S_80BC1264_1 *)effect)->unk_02 * ((S_80BC1264_1 *)effect)->unk_32;
    ((S_80BC1264_1 *)effect)->unk_04.at02.v = (s8) (scaled_blue / 256);
    fade_level = (u16) ((S_80BC1264_1 *)effect)->unk_32 - 8;
    ((S_80BC1264_1 *)effect)->unk_32 = fade_level;
    ((S_80BC1264_1 *)effect)->unk_08 = (s32) ((S_80BC1264_1 *)effect)->unk_04.at00u.v;
    if ((fade_level << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((ObjectRetirementFlags *)effect)[-1].flags | NODE_REMOVE);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

/* Moves the effect with halved velocity each frame, fades its color, and removes it when its timer
 * expires. */
void advance_damped_motion_and_fade_effect(FadeEffect *effect,EffectMotion *motion) {
 s32 red,green,blue;
 s16 remaining;
 motion->x+=motion->dx;
 motion->y+=motion->dy;
 motion->z+=motion->dz;
 motion->dx/=2;
 motion->dy/=2;
 motion->dz/=2;
 red=effect->red*effect->remaining;
 effect->current.color.red=red/effect->total;
 green=effect->green*effect->remaining;
 effect->current.color.green=green/effect->total;
 blue=effect->blue*effect->remaining;
 effect->current.color.blue=blue/effect->total;
 remaining=effect->remaining-1;
 effect->remaining=remaining;
 effect->output=effect->current.packed;
 if(remaining<=0) {
  *(u16 *)((u8 *)effect-2)|=NODE_REMOVE;
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
    S_80BC1528_2 *effect_data;
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

        effect_data = (u8 *)effect + 0x20;
        effect_data->unk_36 = ((MovingPosition *)(parent->unk_08))->x;
        effect_data->unk_38 = ((MovingPosition *)(parent->unk_08))->y;
        effect_data->unk_3A = ((MovingPosition *)(parent->unk_08))->z;

        step_x = -(offset_x << 16) / (duration / 8);
        effect_data->unk_40 = step_x / 2;
        step_y = -(offset_y << 16) / (duration / 8);
        effect_data->unk_44 = step_y / 2;
        step_z = -(offset_z << 16) / (duration / 8);
        effect_data->unk_48 = step_z / 2;

        rounded_step_x = -(offset_x << 16) / (duration / 8);
        if (rounded_step_x < 0) {
            rounded_step_x += 3;
        }
        effect_data->unk_4C = rounded_step_x >> 2;

        rounded_step_z = step_y;
        if (rounded_step_z < 0) {
            rounded_step_z += 3;
        }
        effect_data->unk_50 = rounded_step_z >> 2;

        rounded_step_z = step_z;
        effect_data->unk_54 = (rounded_step_z / 4);

        effect_data->unk_14 = effect_param;
        effect_data->unk_32 = duration;
        register_node(effect, build_projected_tile_packets);
        rounded_step_x = initial_value;
        ((S_80BC1528_0 *)effect)->unk_20 = rounded_step_x;
        effect_data->unk_08 = initial_value;
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
        effect_data = ((void *)effect) + 0x20;
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
void spawn_configured_overlay_object_b(void *effect, MovingPosition *position, S_80BC1880_0 *render_state)
{
    StackWork projection;
    s16 ticks_left;

    render_state->unk_1C -= 500;
    render_state->unk_1E -= 500;
    render_state->unk_1A += 400;

    render_state->unk_0C =
        ((S_80BC1880_1 *)effect)->unk_02 *
        (((S_80BC1880_1 *)effect)->unk_1C - ((S_80BC1880_1 *)effect)->unk_1A.s) /
        ((S_80BC1880_1 *)effect)->unk_1C;
    render_state->unk_0D =
        ((S_80BC1880_1 *)effect)->unk_03 *
        (((S_80BC1880_1 *)effect)->unk_1C - ((S_80BC1880_1 *)effect)->unk_1A.s) /
        ((S_80BC1880_1 *)effect)->unk_1C;
    render_state->unk_0E =
        ((S_80BC1880_1 *)effect)->unk_04 *
        (((S_80BC1880_1 *)effect)->unk_1C - ((S_80BC1880_1 *)effect)->unk_1A.s) /
        ((S_80BC1880_1 *)effect)->unk_1C;

    projection.xyz[0] = position->x;
    projection.xyz[1] = position->y;
    projection.xyz[2] = position->z;
    render_state->unk_06 =
        RotTransPers(projection.xyz, &projection.out18, &projection.out20, &projection.out24) - 8;

    ticks_left = ((S_80BC1880_1 *)effect)->unk_1A.u - 1;
    ((S_80BC1880_1 *)effect)->unk_1A.u = ticks_left;
    if ((ticks_left << 16) <= 0) {
        ((ObjectRetirementFlags *)effect)[-1].flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

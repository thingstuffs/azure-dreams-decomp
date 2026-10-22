/* Shaded effect quad rendering and randomized radial effect creation. */
#include "dungeon/effect/sprite/project_and_queue_shaded_quad.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/sprite/project_and_queue_shaded_quad.h"

/* Transforms four colored vertices and queues a visible shaded quad with the requested depth bias. */
void project_and_queue_shaded_quad(void *quad, void *position, void *render_state, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 ot_index;
    u16 render_flags;
    u8 texture_flags;
    u8 **render_context_ptr = (u8 **)((u8 *)(&g_game_work));
    Row_81922998_MATRIX current_matrix;

    ((Row_81922998_S_80024198_0 *)scratch)->unk_24.p = *(u8 **)((u8 *)(&g_game_work)) + 0xB0;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_88 = ((Row_81922998_S_80024198_1 *)position)->unk_02;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_8C = ((Row_81922998_S_80024198_1 *)position)->unk_06;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_90 = ((Row_81922998_S_80024198_1 *)position)->unk_0A;
    ((Row_81922998_S_80024198_2 *)render_state)->unk_14 |= 0x8000;

    func_800649A0();

    ((Row_81922998_S_80024198_0 *)scratch)->unk_3C = 0x2000;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_38 = 0x2000;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_34 = 0x2000;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_A4 = ((Row_81922998_S_80024198_2 *)render_state)->unk_16;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_A8 = ((Row_81922998_S_80024198_2 *)render_state)->unk_1A;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_A6 = ((Row_81922998_S_80024198_2 *)render_state)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&current_matrix);
    func_80064840(&current_matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = (*(u8 * *)((u8 *)render_state + 8));
    ((Row_81922998_S_80024198_0 *)scratch)->unk_28 = ((Row_81922998_S_80024198_2 *)render_state)->unk_14;

    packet = ((Row_81922998_S_80024198_3 *)(g_game_work.draw_buffer))->unk_8D0;
    ((Row_81922998_S_80024198_3 *)(g_game_work.draw_buffer))->unk_8D0 = packet + 0xC;
    func_80067F20(packet, 0, 1, func_80066460(0, 0, 0, 0) & 0xFFFF, 0);
    (*(u32 *)((u8 *)packet + 0)) = (((Row_81922998_S_80024198_4 *)packet)->unk_00.at00.v & 0xFF000000) |
        (((Row_81922998_S_80024198_3 *)(g_game_work.draw_buffer))->unk_B0 & 0x00FFFFFF);
    (*(u32 *)((u8 *)(g_game_work.draw_buffer) + 0xB0)) =
        (((Row_81922998_S_80024198_3 *)(g_game_work.draw_buffer))->unk_B0 & 0xFF000000) |
        ((u32)packet & 0x00FFFFFF);

    {
        u8 *render_context;

        render_context = g_game_work.draw_buffer;
        packet = ((Row_81922998_S_80024198_5 *)render_context)->unk_8D0;
        ((Row_81922998_S_80024198_5 *)render_context)->unk_8D0 = packet + 0x24;
    }

    ((Row_81922998_S_80024198_0 *)scratch)->unk_B0 = ((Row_81922998_S_80024198_6 *)quad)->unk_20;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_B8 = ((Row_81922998_S_80024198_6 *)quad)->unk_26;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_C0 = ((Row_81922998_S_80024198_6 *)quad)->unk_2C;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_C8 = ((Row_81922998_S_80024198_6 *)quad)->unk_32;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_B2 = ((Row_81922998_S_80024198_6 *)quad)->unk_22;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_BA = ((Row_81922998_S_80024198_6 *)quad)->unk_28;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_C2 = ((Row_81922998_S_80024198_6 *)quad)->unk_2E;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_CA = ((Row_81922998_S_80024198_6 *)quad)->unk_34;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_B4 = ((Row_81922998_S_80024198_6 *)quad)->unk_24;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_BC = ((Row_81922998_S_80024198_6 *)quad)->unk_2A;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_C4 = ((Row_81922998_S_80024198_6 *)quad)->unk_30;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_CC = ((Row_81922998_S_80024198_6 *)quad)->unk_36;

    ot_index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                             scratch + 0xC0, scratch + 0xC8,
                             packet + 8, packet + 0x10,
                             packet + 0x18, packet + 0x20,
                             scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
    ((Row_81922998_S_80024198_0 *)scratch)->unk_100 = ot_index;

    if ((u32)ot_index < 0x1E0) {
        if ((((u16)(((Row_81922998_S_80024198_4 *)packet)->unk_08 + 0x20) < 0x181) &&
             ((u16)(((Row_81922998_S_80024198_4 *)packet)->unk_0A + 0x20) < 0x121)) |
            (((u16)(((Row_81922998_S_80024198_4 *)packet)->unk_10 + 0x20) < 0x181) &&
             ((u16)(((Row_81922998_S_80024198_4 *)packet)->unk_12 + 0x20) < 0x121)) |
            (((u16)(((Row_81922998_S_80024198_4 *)packet)->unk_18 + 0x20) < 0x181) &&
             ((u16)(((Row_81922998_S_80024198_4 *)packet)->unk_1A + 0x20) < 0x121)) |
            (((u16)(((Row_81922998_S_80024198_4 *)packet)->unk_20 + 0x20) < 0x181) &&
             ((u16)(((Row_81922998_S_80024198_4 *)packet)->unk_22 + 0x20) < 0x121))) {
            ((Row_81922998_S_80024198_2 *)render_state)->unk_14 &= 0x7FFF;
            texture_flags = texture[1];
            ((Row_81922998_S_80024198_2 *)render_state)->unk_0F = texture_flags;
            render_flags = ((Row_81922998_S_80024198_0 *)scratch)->unk_28;
            if (render_flags & 8) {
                ((Row_81922998_S_80024198_2 *)render_state)->unk_0F = (render_flags & 4) ?
                    (texture_flags | 2) : (texture_flags & 0xFD);
            }

            ((Row_81922998_S_80024198_4 *)packet)->unk_04.at00.v = ((Row_81922998_S_80024198_6 *)quad)->unk_00;
            ((Row_81922998_S_80024198_4 *)packet)->unk_0C = ((Row_81922998_S_80024198_6 *)quad)->unk_04;
            ((Row_81922998_S_80024198_4 *)packet)->unk_14 = ((Row_81922998_S_80024198_6 *)quad)->unk_08;
            ((Row_81922998_S_80024198_4 *)packet)->unk_1C = ((Row_81922998_S_80024198_6 *)quad)->unk_0C;
            ((Row_81922998_S_80024198_4 *)packet)->unk_00.at03.v = 8;
            ((Row_81922998_S_80024198_4 *)packet)->unk_04.at03.v = 0x3A;

            ((Row_81922998_S_80024198_4 *)packet)->unk_00.at00.v = (((Row_81922998_S_80024198_4 *)packet)->unk_00.at00.v & 0xFF000000) |
                ((*(u32 *)((u8 *)(((Row_81922998_S_80024198_0 *)scratch)->unk_24.p2)
                    + ((Row_81922998_S_80024198_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((Row_81922998_S_80024198_0 *)scratch)->unk_24.p2) + ((Row_81922998_S_80024198_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((Row_81922998_S_80024198_0 *)scratch)->unk_24.p2)
                    + ((Row_81922998_S_80024198_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);

            packet = ((Row_81922998_S_80024198_7 *)(*render_context_ptr))->unk_8D0;
            ((Row_81922998_S_80024198_7 *)(*render_context_ptr))->unk_8D0 = packet + 0xC;
            func_80067F20(packet, 0, 1, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            ((Row_81922998_S_80024198_4 *)packet)->unk_00.at00.v = (((Row_81922998_S_80024198_4 *)packet)->unk_00.at00.v & 0xFF000000) |
                ((*(u32 *)((u8 *)(((Row_81922998_S_80024198_0 *)scratch)->unk_24.p2)
                    + ((Row_81922998_S_80024198_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((Row_81922998_S_80024198_0 *)scratch)->unk_24.p2) + ((Row_81922998_S_80024198_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((Row_81922998_S_80024198_0 *)scratch)->unk_24.p2)
                    + ((Row_81922998_S_80024198_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    func_80064A40();
}

/* Draws a shaded quad for each linked effect node using that node's position and appearance. */
s32 draw_linked_shaded_quads(void *state, void *position, void *appearance) {
    Row_81922E70_GapNode *node;
    for (;;) {
        project_and_queue_shaded_quad(state, position, appearance, 0);
        node = *(Row_81922E70_GapNode **)((u8 *)state - 8);
        state = (u8 *)node + 0x20;
        if (node == 0) break;
        position = node->position;
        appearance = node->appearance;
    }
    return 0;
}

/* Fades four saved vertex colors in proportion to the remaining lifetime and removes the effect at zero. */
void fade_four_colors_to_black(Row_81922EC4_DungeonColorWork *work)
{
    s16 color_index;
    Row_81922EC4_DungeonColor *color;

    (*(s16 *)D_80025B60) = 1;
    work->remaining--;

    for (color_index = 0; color_index < 4; color_index++) {
        color = &work->color[color_index];
        color->r = (color[4].r * work->remaining) / work->duration;
        color->g = (color[4].g * work->remaining) / work->duration;
        color->b = (color[4].b * work->remaining) / work->duration;
    }

    if (work->remaining <= 0) {
        *(u16 *)((u8 *)work - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a short-lived shaded effect with random color channels and endpoints around the source radius. */
void create_randomized_radial_effect(Rec_func_800247B8_arg0 *source, Rec_func_800247B8_arg1 *origin, void *unused_sprite)
{
    s32 elevation;
    s32 planar_radius;
    s32 azimuth;
    s32 random_value;
    void *effect;
    Row_81922FB8_S_800247B8_0 *state;
    SpriteFrameState *sprite;
    Row_81922FB8_S_800247B8_4 *position;

    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        state = effect + 0x20;
        state->unk_5A = 10;
        state->unk_5C = 10;
        random_value = project_and_queue_visible_shaded_quad(8);
        state->unk_18.at00.v = 0x303030;
        if (random_value & 1) {
            state->unk_18.at00u.v = 0x90;
        }
        if (random_value & 2) {
            state->unk_18.at01.v = 0x90;
        }
        if (random_value & 4) {
            state->unk_18.at02.v = 0x90;
        }
        state->unk_10 = 0;
        state->unk_14 = 0;
        state->unk_1C = state->unk_18.at00.v;
        ((Row_81922FB8_S_800247B8_1 *)effect)->unk_20 = state->unk_10;
        state->unk_04 = state->unk_14;
        state->unk_08 = state->unk_18.at00.v;
        state->unk_0C = state->unk_1C;
        ((Row_81922FB8_S_800247B8_1 *)effect)->unk_10 = D_800246C4;
        register_node(effect, D_80024670);

        sprite = ((Row_81922FB8_S_800247B8_1 *)effect)->unk_0C;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;
        elevation = rand() & 0xFFF;
        planar_radius = (source->unk_56 * func_80064584(elevation)) >> 12;
        state->unk_24.s = (source->unk_56 * func_800644B8(elevation)) >> 12;
        azimuth = rand() & 0xFFF;
        state->unk_20.s = ((s16)planar_radius * func_80064584(azimuth)) >> 12;
        state->unk_22.s = ((s16)planar_radius * func_800644B8(azimuth)) >> 12;

        state->unk_26 = state->unk_20.u + project_and_queue_visible_shaded_quad(0x10) - 8;
        state->unk_28 = state->unk_22.u + project_and_queue_visible_shaded_quad(0x10) - 8;
        random_value = project_and_queue_visible_shaded_quad(0x10);
        state->unk_36 = 0;
        state->unk_34 = 0;
        state->unk_32 = 0;
        state->unk_30 = 0;
        state->unk_2E = 0;
        state->unk_2C = 0;
        state->unk_2A = state->unk_24.u + random_value - 8;

        position = ((Row_81922FB8_S_800247B8_1 *)effect)->unk_08;
        position->unk_02 = origin->unk_02;
        position->unk_06 = origin->unk_06;
        position->unk_0A = origin->unk_0A;

        sprite = ((Row_81922FB8_S_800247B8_1 *)effect)->unk_0C;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
    }
}

/* Rotates, grows, and shrinks a sprite, updates its visibility flag, and removes it when the countdown
   ends. */
void update_effect_values_and_expire(void *object, s32 unused, Row_819231FC_S_800249FC_0 *effect) {
    s32 ticks_left;
    s16 next_ticks;
    s16 check_result;
    u16 flags;
    u16 paired_value;

    effect->unk_1A += 0x2BC;
    ticks_left = ((Row_819231FC_S_800249FC_1 *)object)->unk_5A.s;
    ((s16 *)D_80025B60)[0] = 1;

    if (ticks_left >= 0x29) {
        paired_value = effect->unk_1E + 0xC8;
        effect->unk_1E = paired_value;
        effect->unk_1C = paired_value;
    } else {
        if (ticks_left < 0x15) {
            paired_value = effect->unk_1E - 0xBE;
            effect->unk_1E = paired_value;
            effect->unk_1C = paired_value;
        }
    }

    check_result = project_and_queue_visible_shaded_quad(3);
    flags = effect->unk_14;
    if ((flags & 0x80) || check_result != 0) {
        effect->unk_14 = flags & 0xFF7F;
    } else {
        effect->unk_14 = flags | 0x80;
    }

    next_ticks = ((Row_819231FC_S_800249FC_1 *)object)->unk_5A.s - 1;
    ((Row_819231FC_S_800249FC_1 *)object)->unk_5A.s = next_ticks;
    if (next_ticks <= 0) {
        ((Row_819231FC_S_800249FC_1_pre *)object)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates an initially zero-scale gray effect at the supplied position with copied sprite data and a
   60-step counter. */
void create_positioned_render_effect(Row_819232EC_S_80024AEC_1 *source, Rec_func_800247B8_arg1 *position, void *unused_sprite) {
    Row_819232EC_S_80024AEC_3 *render_state;
    void *effect;
    Row_819232EC_S_80024AEC_0 *effect_state;
    Row_819232EC_S_80024AEC_4 *effect_position;

    effect = allocate_flagged_object_node(0x12);
    effect_state = effect + 0x20;
    if (effect != NULL) {
        effect_state->unk_5A = 0x3C;
        effect_state->unk_5C = 0x3C;
        effect_state->unk_88 = (s32) source->unk_88;
        ((Row_819232EC_S_80024AEC_2 *)effect)->unk_10 = &D_800249FC;
        register_node(effect, project_sprite_chain);
        render_state = ((Row_819232EC_S_80024AEC_2 *)effect)->unk_0C;
        render_state->unk_10 = 0x40;
        render_state->unk_06 = 0xA;
        render_state->unk_14 = (u16) (render_state->unk_14 | 0xC);
        effect_position = ((Row_819232EC_S_80024AEC_2 *)effect)->unk_08;
        effect_position->unk_02 = (u16) position->unk_02;
        effect_position->unk_06 = (u16) position->unk_06;
        effect_position->unk_0A = (u16) position->unk_0A;
        render_state = ((Row_819232EC_S_80024AEC_2 *)effect)->unk_0C;
        render_state->unk_0E = 0x50;
        render_state->unk_0D = 0x50;
        render_state->unk_0C = 0x50;
        render_state->unk_1E = 0;
        render_state->unk_1C = 0;
        *(Row_819232EC_U12 *)((u8 *)effect + 0x96) = *(Row_819232EC_U12 *)&D_80025B48;
        render_state->unk_08 = (void *) (effect + 0x96);
    }
}

/* Grows a sprite toward twice normal scale, advances animation every fourth update, and fades it to
   removal. */
void advance_radial_effect_state(void *entity_data, s32 unused, Row_8192340C_DungeonEffect *effect_data) {
    u16 ticks_left;
    u16 updated_value;
    s32 fade_level;

    ticks_left = *(u16 *)(entity_data + 0x5A);
    *(s16 *)((u8 *)&(*(Row_8192340C_DungeonActive *)D_80025B60)) = 1;
    if (!(ticks_left & 3)) {
        advance_sprite_animation_and_textures(effect_data);
    }

    updated_value = effect_data->unk_1C + 0x32;
    effect_data->unk_1C = updated_value;
    if (updated_value >= 0x2001) {
        effect_data->unk_1C = 0x2000;
    }

    updated_value = effect_data->unk_1E + 0x32;
    effect_data->unk_1E = updated_value;
    if (updated_value >= 0x2001) {
        effect_data->unk_1E = 0x2000;
    }

    updated_value = *(u16 *)(entity_data + 0x5A) - 1;
    fade_level = ((s32)(updated_value << 16) >> 9) / *(s16 *)(entity_data + 0x5C);
    *(u16 *)(entity_data + 0x5A) = updated_value;
    effect_data->unk_E = fade_level;
    effect_data->unk_D = fade_level;
    effect_data->unk_C = fade_level;

    if (*(s16 *)(entity_data + 0x5A) <= 0) {
        *(u16 *)(entity_data - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    if (effect_data->flags_14 & 0x8000) {
        *(u16 *)(entity_data - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a gray animated sprite at a random offset within 16 units of the origin and gives it a
   14-update lifetime. */
void create_random_offset_effect(void *unused, Rec_func_800247B8_arg1 *origin, void *unused_sprite)
{
    s32 flags;
    SpriteFrameState *render_control;
    SpriteFrameState *render_style;
    Row_81923534_S_80024D34_3 *position;
    void *effect;
    Row_81923534_S_80024D34_0 *effect_data;
    s32 random_value;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        effect_data = (u8 *)effect + 0x20;
        effect_data->unk_5A = 0xE;
        effect_data->unk_5C = 0xE;
        ((Row_81923534_S_80024D34_1 *)effect)->unk_10 = D_80024C0C;
        register_node(effect, project_sprite_chain);

        render_control = ((Row_81923534_S_80024D34_1 *)effect)->unk_0C;
        render_control->flags |= 0xC;
        render_control->tpage_abr = 0x60;
        render_control->flags |= 2;

        position = ((Row_81923534_S_80024D34_1 *)effect)->unk_08;
        random_value = rand();
        position->unk_02 = origin->unk_02 + ((random_value & 0x1F) - 0x10);
        random_value = rand();
        position->unk_06 = origin->unk_06 + ((random_value & 0x1F) - 0x10);
        random_value = rand();
        position->unk_0A = origin->unk_0A + ((random_value & 0x1F) - 0x10);

        render_style = ((Row_81923534_S_80024D34_1 *)effect)->unk_0C;
        render_style->scale_y = 0xC00;
        render_style->scale_x = 0xC00;
        render_style->color.c.b = 0x80;
        render_style->color.c.g = 0x80;
        render_style->color.c.r = 0x80;
        render_style->clut = 0x7DCF;
        render_style->flags = render_style->flags | 0x100;
        select_record_entry_and_value(render_style, effect_sprite_sources, 0);
    }
}

/* MECHANISM: Preserve the seed's exact 0x20 frame, s2/s1/s0 holds, and CFG.
   Unsigned byte fields keep the shared 0x80 store value as +128, matching
   retail's addiu before the three sb operations. */

/* Cycles sprite colors, moves toward a target or along a path, then spawns impact and radial bursts. */
void update_effect_cycle_and_bursts(void *effect, void *motion, void *sprite) {
    s32 delta_x;
    s16 reduced_scale;
    u8 *height_table;
    s32 travel_distance;
    s16 travel_frames;
    s16 next_burst;
    s16 next_pair;
    s16 next_triple;
    s16 next_quad;
    s16 next_trail;
    s16 impact_state;
    s16 trail_index;
    s16 burst_index;
    s16 pair_index;
    s16 triple_index;
    s16 quad_index;
    s32 velocity_y;
    s32 target_y;
    s32 velocity_z;
    s32 target_z;
    s32 current_x;
    s32 end_frame;
    s32 target_x_or_z_step;
    s32 distance_x;
    s32 completion_state;
    s32 near_target;
    u16 next_color;
    u16 start_frame;
    u16 frames_left;
    u16 impact_frame;
    u16 scale;
    u16 burst_frame;
    u16 color_cycle;
    u16 initial_state;
    u16 clamped_scale;
    u8 effect_id;
    void *target_position;

    initial_state = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u;
    (*(s16 *)D_80025B60) = 1;
    if (initial_state < 3U) {
        ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0E.s = 0x3C;
        ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0D.s = 0x3C;
        ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0C.s = 0x3C;
        color_cycle = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_72;
        next_color = color_cycle + 1;
        ((Row_8192365C_S_80024E5C_0 *)effect)->unk_72 = next_color;
        if (!(next_color & 7)) {
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_72 = (u16) (color_cycle + 2);
        }
        if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_72 & 1) {
            ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0C.u = 0x80;
        }
        if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_72 & 2) {
            ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0D.u = 0x80;
        }
        if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_72 & 4) {
            ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0E.u = 0x80;
        }
    }
    if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.s == 0) {
        start_frame = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u;
        ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = (u16) (start_frame + 1);
        if ((s16) start_frame >= 6) {
            effect_id = D_80025B38[0];
            ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_2C = D_80025B38;
            select_sprite_entry(sprite, effect_id, 0);
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = 0U;
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u = (u16) (((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u + 1);
            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at02.v = (u16) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at02.v - 0x5A);
        }
    }
    completion_state = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.s;
    if (completion_state == 1) {
        if ((check_adjacent_tile_height_clearance(((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at02.v, ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at02.v,
            (s16) ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at02.v, ((Row_8192365C_S_80024E5C_0 *)effect)->unk_88) << 0x10) == 0) {
            if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_60 != 0) {
                target_position = ((Row_8192365C_S_80024E5C_4_pre *)(((Row_8192365C_S_80024E5C_0 *)effect)->unk_88))[-1].unk_00;
                ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_06 = 8;
                if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.s == 0) {
                    delta_x = ((Row_8192365C_S_80024E5C_3 *)target_position)->unk_00.at02.v;
                    delta_x -= ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at02u.v;
                    distance_x = abs(delta_x);
                    if (distance_x < 0) {
                        distance_x += 0x3F;
                    }
                    travel_distance = abs(((Row_8192365C_S_80024E5C_3 *)target_position)->unk_04.at02.v -
                                          ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at02u.v);
                    if (travel_distance < 0) {
                        travel_distance += 0x3F;
                    }
                    travel_distance = (distance_x >> 6) + (travel_distance >> 6);
                    ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = (u16) (((s32) (travel_distance << 0x10) >> 0xF) + 0xB);
                }
                height_table = entity_height_offsets;
                travel_frames = (s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u;
                target_z = ((Row_8192365C_S_80024E5C_3 *)target_position)->unk_08
                - (((u8) *(((Row_8192365C_S_80024E5C_4 *)(((Row_8192365C_S_80024E5C_0 *)effect)->unk_88))->unk_13 + height_table) >> 1)
                    << 0x10);
                near_target = travel_frames < 0xE;
                target_x_or_z_step = ((Row_8192365C_S_80024E5C_3 *)target_position)->unk_00.at00.v;
                target_y = ((Row_8192365C_S_80024E5C_3 *)target_position)->unk_04.at00.v;
                if (near_target == 0) {
                    current_x = ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v;
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C = (s32) ((target_x_or_z_step - current_x) / (s32) (travel_frames
                        - 0xB));
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y
                        - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v) / (s32) ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u
                        - 0xB));
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14 = (target_z
                        - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v) / (((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.s - 0xB);
                } else {
                    if (travel_frames >= 0xB) {
                        current_x = ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v;
                        ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C = (s32) ((target_x_or_z_step
                            - current_x) / (s32) (travel_frames - 9));
                        ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y
                            - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v) / (s32) ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u
                            - 9));
                        ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14 = (target_z
                            - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v) / (((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.s - 9);
                    } else {
                        if (travel_frames >= 5) {
                            s32 divisor;
                            s32 z_step;
                            current_x = ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v;
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C = (s32) ((target_x_or_z_step
                                - current_x) / (s32) (travel_frames - 4));
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y
                                - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v) / (s32) ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u
                                - 4));
                            z_step = target_z - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v;
                            divisor = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.s - 4;
                            z_step /= divisor;
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14 = z_step;
                        } else {
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C = (s32) ((s32) (target_x_or_z_step
                                - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v) / travel_frames);
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y
                                - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v) / (s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u);
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14 = (s32) ((s32) (target_z
                                - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v) / (s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u);
                        }
                    }
                }
                velocity_y = ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10;
                velocity_z = ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14;
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v
                    + ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C);
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v + velocity_y);
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v + velocity_z);
                frames_left = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u - 1;
                ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = frames_left;
                if ((frames_left << 0x10) == 0) {
                    ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u = 2U;
                    ((Row_8192365C_S_80024E5C_0 *)effect)->unk_62 = 6;
                    ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = 0U;
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14 = 0;
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10 = 0;
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C = 0;
                    ((Row_8192365C_S_80024E5C_0 *)effect)->unk_56 = 0x1E;
                }
            } else {
                ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = 0xAU;
                ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5C = (u16) (((Row_8192365C_S_80024E5C_0 *)effect)->unk_5C - 1);
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v
                    + ((Row_8192365C_S_80024E5C_0 *)effect)->unk_98);
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v
                    + ((Row_8192365C_S_80024E5C_0 *)effect)->unk_9C);
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v
                    + ((Row_8192365C_S_80024E5C_0 *)effect)->unk_A0);
                if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5C <= 0) {
                    ((Row_8192365C_S_80024E5C_5 *)(((Row_8192365C_S_80024E5C_0 *)effect)->unk_8C))->unk_86 = completion_state;
                    (*(u16 *)((u8 *)effect + (-2))) = (u16) (((Row_8192365C_S_80024E5C_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
                    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                    return;
                }
            }
            if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 5) {
                trail_index = 0;
                do {
                    create_random_offset_effect(effect, motion, sprite);
                    next_trail = trail_index + 1;
                    trail_index = next_trail;
                } while (next_trail < 4);
            }
        } else {
            ((Row_8192365C_S_80024E5C_5 *)(((Row_8192365C_S_80024E5C_0 *)effect)->unk_8C))->unk_86 = completion_state;
            (*(u16 *)((u8 *)effect + (-2))) = (u16) (((Row_8192365C_S_80024E5C_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
    }
update_impact:
    impact_state = (s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u;
    if (impact_state == 2) {
        impact_frame = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u + 1;
        ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = impact_frame;
        if ((s16) impact_frame == impact_state) {
            create_positioned_render_effect(effect, motion, sprite);
            play_sound_if_enabled(0x300);
        }
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 0xA) {
            scale = ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_1C;
            if (scale != 0) {
                reduced_scale = scale - 0xC8;
                clamped_scale = reduced_scale;
                if (reduced_scale < 0) {
                    clamped_scale = 0;
                }
                ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_1C = clamped_scale;
                ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_1E = clamped_scale;
            }
        }
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 0x1E) {
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_56 = (u16) (((Row_8192365C_S_80024E5C_0 *)effect)->unk_56 + 3);
            create_randomized_radial_effect(effect, motion, sprite);
            if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 0x28) {
                create_randomized_radial_effect(effect, motion, sprite);
            }
            if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 0x2D) {
                create_randomized_radial_effect(effect, motion, sprite);
            }
        }
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 0x32) {
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u = 3U;
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = 0U;
            ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_14 = (u16) (((Row_8192365C_S_80024E5C_1 *)sprite)->unk_14 | 0x80);
        }
    }
    if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u == 3) {
        burst_frame = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u + 1;
        ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = burst_frame;
        if ((s16) burst_frame < 0x12) {
            burst_index = 0;
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_56 = (u16) (((Row_8192365C_S_80024E5C_0 *)effect)->unk_56 - 3);
            do {
                create_randomized_radial_effect(effect, motion, sprite);
                next_burst = burst_index + 1;
                burst_index = next_burst;
            } while (next_burst < 5);
        }
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u == 0x10) {
            pair_index = 0;
            do {
                create_randomized_radial_effect(effect, motion, sprite);
                next_pair = pair_index + 1;
                pair_index = next_pair;
            } while (next_pair < 2);
        }
        triple_index = 0;
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u == 0x11) {
            do {
                create_randomized_radial_effect(effect, motion, sprite);
                next_triple = triple_index + 1;
                triple_index = next_triple;
            } while (next_triple < 3);
        }
        quad_index = 0;
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u == 0x12) {
            do {
                create_randomized_radial_effect(effect, motion, sprite);
                next_quad = quad_index + 1;
                quad_index = next_quad;
            } while (next_quad < 4);
        }
        end_frame = (s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u;
        completion_state = 1;
        if (end_frame == 1) {
            create_attached_effect(effect, motion, sprite);
            end_frame = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.s;
        }
        if (end_frame >= 0x1B) {
            ((Row_8192365C_S_80024E5C_5 *)(((Row_8192365C_S_80024E5C_0 *)effect)->unk_8C))->unk_86 = completion_state;
            (*(u16 *)((u8 *)effect + (-2))) = (u16) (((Row_8192365C_S_80024E5C_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
    }
    advance_sprite_animation_and_textures(sprite);
}

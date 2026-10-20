#include "dungeon/effect/mesh/follow_brighten.h"

void (*const dungeon_ovl_18d0850_entry)(void) = (void (*)(void))update_movement_toward_child_terrain_target_animates_associated_effects;

void follow_brighten(EntityRec *entity, s32 value_id) {
    if (try_trigger_target_record_effect(entity, 4) == 0) {
        s32 base_gain;
        s16 bonus;
        s32 gain;

        base_gain = get_random_scaled_value(value_id & 0xFF) + 8;
        bonus = entity->unk_28 & 4;
        gain = base_gain;
        if (bonus) {
            bonus = (s32) (base_gain << 16) >> 18;
            gain = base_gain + bonus;
        }
        entity->unk_64 = (u16) (((u16)entity->unk_64) + gain);
        cap_pending_actor_value_delta(entity);
        base_gain = 0x8004;
        create_actor_value_popup(base_gain, entity, (s16) ((u16)entity->unk_64), 1);
        apply_clamped_actor_value_delta(entity);
    }
}

void write_fixed_palette_pixels(void *unused0, void *unused1, void *unused2) {
    s16 rect[4];
    u16 pixel;

    pixel = 0;
    rect[0] = 0x340;
    rect[1] = 0x100;
    rect[2] = 1;
    rect[3] = 1;
    func_800672D8(rect, &pixel);

    pixel = 0xFC00;
    rect[0] = 0x340;
    rect[1] = 0x180;
    rect[2] = 1;
    rect[3] = 1;
    func_800672D8(rect, &pixel);

    func_80067014(0);
}

void advance_owner_effect_counter(ovl_18d0850_818B097C_EffectOwner *owner, void *unused, ovl_18d0850_818B097C_EffectCounter *state) {
    owner->parent->flags++;
    func_800478B8(state);
    if (state->flags & 0x6000) {
        *(u16 *)((u8 *)owner - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

ovl_18d0850_818B09F8_MainObj *create_an_initialized_render_state_copy_vector(s32 object_value, ovl_18d0850_818B09F8_VecObj *source_vec) {
    ovl_18d0850_818B09F8_MainObj *obj = (ovl_18d0850_818B09F8_MainObj *)func_8003FC64(530);
    ovl_18d0850_818B09F8_SubObj *sub;
    ovl_18d0850_818B09F8_VecObj *vec;
    ovl_18d0850_818B09F8_MainObj *result;

    if (obj != 0) {
        obj->callback = (void *)advance_owner_effect_counter;
        sub = obj->sub;
        obj->source_state = object_value;
        sub->b = 128;
        sub->g = 128;
        sub->r = 128;
        func_8003DB94(sub, D_800DEC70, 0);

        sub->unk1E = 4096;
        sub->unk1C = 4096;
        sub->unk12 = 0x7E09;
        sub->unk14 |= 0x100;
        register_node(obj, project_sprite_chain);

        vec = obj->vec;
        vec->unk2 = source_vec->unk2;
        vec->unk6 = source_vec->unk6;
        vec->unkA = source_vec->unkA;

        result = obj;
        return result;
    } else {
        result = 0;
        return result;
    }
}

void advance_height_offset_and_placement(ovl_18d0850_818B0AE0_S_800242E0_0 *state, ovl_18d0850_818B0AE0_S_800242E0_2 *position, Rec_D_80082E80 *object) {
    s32 angle;
    u16 height_offset;
    ovl_18d0850_818B0AE0_S_800242E0_1 *counter;

    counter = state->unk_00;
    counter->unk_14 = (u16)(counter->unk_14 + 1);
    height_offset = state->unk_04 + state->unk_06;
    state->unk_04 = height_offset;
    if ((s16)height_offset < -0x80) {
        angle = rand() % 0x1000;
        position->unk_02 = (s16)(state->unk_08 + ((func_800644B8(angle) * 2) >> 8));
        position->unk_06 = (s16)(state->unk_0A + ((func_80064584(angle) * 2) >> 8));
        state->unk_04 = (u16)(state->unk_04 + 0x80);
        state->unk_06 = (u16)(-6 - (rand() % 5));
    }
    position->unk_0A = (s16)(state->unk_0C + state->unk_04);
    func_800478B8(object);
    if (object->unk_14.at00_u16.v & 0x6000) {
        func_8003DB94(object, D_800DEC70, 0);
    }
}

s32 create_radial_height_offset_effect(s32 owner, void *origin, s16 motion, s16 frame) {
    s32 *node_type;
    u16 position_z;
    s32 angle;
    ovl_18d0850_818B0C3C_S_8002443C_3 *sprite;
    s32 result;
    u8 *position;
    u8 *node;
    s16 frame_index = frame;
    s32 sprite_mode;

    node = func_8003FC64(0x212);
    if (node != 0) {
        node_type = (void *)advance_height_offset_and_placement;
        ((ovl_18d0850_818B0C3C_S_8002443C_0 *)node)->unk_20 = owner;
        owner = (s32)(node + 0x20);
        ((ovl_18d0850_818B0C3C_S_8002443C_0 *)node)->unk_10 = node_type;
        ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_04 = motion;
        ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_06 = (s16) (-6 - (func_80069EF8() % 5));
        ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_08 = (u16) ((ovl_18d0850_818B0C3C_S_8002443C_2 *)origin)->unk_02.s;
        ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_0A = (u16) ((ovl_18d0850_818B0C3C_S_8002443C_2 *)origin)->unk_06.s;
        node_type = (s32 *)(((ovl_18d0850_818B0C3C_S_8002443C_2 *)origin)->unk_0A.s);
        sprite_mode = 0x7E09;
        ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_0C = (u16)node_type;
        sprite = ((ovl_18d0850_818B0C3C_S_8002443C_0 *)node)->unk_0C;
        sprite->unk_0E = 0;
        sprite->unk_0D = 0;
        sprite->unk_0C = 0;
        sprite->unk_12 = (s16)sprite_mode;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        sprite->unk_10 = (u16) (sprite->unk_10 | 0x20);
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
        func_8003DB94(sprite, &D_800DEC70, (s16)frame_index % 16, (s16)frame_index);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        register_node(node, project_sprite_chain);
        position = ((ovl_18d0850_818B0C3C_S_8002443C_0 *)node)->unk_08;
        angle = func_80069EF8() % 0x1000;
        ((ovl_18d0850_818B0C3C_S_8002443C_2 *)position)->unk_02.u = (s16) (((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_08 + ((s32) (func_800644B8(angle) * 2) >> 8));
        ((ovl_18d0850_818B0C3C_S_8002443C_2 *)position)->unk_06.u = (s16) (((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_0A + ((s32) (func_80064584(angle) * 2) >> 8));
        position_z = ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_0C;
        result = (s32)node;
        ((ovl_18d0850_818B0C3C_S_8002443C_2 *)position)->unk_0A.u = (s16)position_z;
        return result;
    }
    result = 0;
    return result;
}

s32 draw_n_16_shaded_line_segments_link_them_ordering_table_depth(void *unused_0, void *origin, void *unused_2, s32 point_scale, s32 plane_z, s32 *points_addr, u8 intensity, s32 color_phase)
{
  u8 *globals_page = D_80080000;
  s32 segment = 15;
  s32 *point_base = points_addr;
  s32 initial_z = plane_z;
  s16 phase = (s16) color_phase;
  u8 *scratch;
  u8 *line_prim;
  GpuContext *initial_ctx;
  GameWork *render_state = &g_game_work;
  s32 depth;
  initial_ctx = *((GpuContext **) (globals_page + 0x3160));
  scratch = (u8 *) 0x1F800000;
  ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_70 = (u16) initial_z;
  ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_68 = (u16) initial_z;
  ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->ot = (u32 *) (((u8 *) initial_ctx) + 0xB0);
  do
  {
    s32 phase_offset = phase;
    s32 color_index = segment + phase_offset;
    s32 biased_index = color_index;
    s32 biased_index_2;
    GpuContext *ctx;
    s32 line_code;
    s32 div255_multiplier;
    union {
      s64 both;
      struct { s32 hi; u32 lo; } word;
    } wide_product;
    globals_page = (u8 *)(intensity << 16);
    div255_multiplier = (s32) 0x80808081U;
    wide_product.both = (s64) (s32)globals_page * div255_multiplier;
    ctx = ((GpuContext *)render_state->unk_000);
    line_prim = ctx->packetCursor;
    ctx->packetCursor = line_prim + 0x14;
    line_prim[3] = 4;
    line_code = 0x52;
    color_phase = (s32)globals_page >> 31;
    line_prim[7] = (u8) line_code;
    phase_offset = (wide_product.word.hi - -(s32)globals_page) >> 7;
    globals_page = (u8 *)(phase_offset - color_phase);
    {
      s32 shade_scale = (s32)globals_page;
      s32 saved_shade_scale = shade_scale;
      globals_page = (u8 *)((s32)globals_page * (*((u8 *) (((u8 *) (&D_8002588C)) + (color_index % 16)))));
      phase_offset = (s32)globals_page >> 18;
      globals_page = (u8 *)saved_shade_scale;
      initial_z = color_index + 1;
      biased_index_2 = initial_z;
      line_prim[5] = intensity;
      line_prim[4] = (s8) phase_offset;
      line_prim[6] = (s8) phase_offset;
      if (initial_z < 0)
      {
        biased_index_2 = color_index + 16;
      }
      globals_page = (u8 *)((s32)globals_page * (*((u8 *) (((u8 *) (&D_8002588C)) + (initial_z - ((biased_index_2 >> 4) << 4))))));
      line_prim[0xD] = intensity;
      phase_offset = (s32)globals_page >> 18;
      line_prim[0xC] = (s8) phase_offset;
      line_prim[0xE] = (s8) phase_offset;
    }
    {
      u8 *origin_bytes = (u8 *) origin;
      s32 point_component;
      s32 coord_offset;
      point_component = point_base[segment];
      coord_offset = point_component * (s16) point_scale;
      coord_offset >>= 8;
      ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_64 = (*((u16 *) (origin_bytes + 2))) + coord_offset;
      point_component = point_base[segment + 1];
      coord_offset = point_component * (s16) point_scale;
      coord_offset >>= 8;
      ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_6C = (*((u16 *) (origin_bytes + 2))) + coord_offset;
      point_component = point_base[segment + 0x11];
      coord_offset = point_component * (s16) point_scale;
      coord_offset >>= 8;
      ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_66 = (*((u16 *) (origin_bytes + 6))) + coord_offset;
      point_component = point_base[segment + 0x12];
      coord_offset = point_component * (s16) point_scale;
      coord_offset >>= 8;
      ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_6E = (*((u16 *) (origin_bytes + 6))) + coord_offset;
    }
    {
      u8 *start_vertex = scratch + 0x64;
      u8 *end_vertex = scratch + 0x6C;
      u8 *start_screen = scratch + 0xD8;
      u8 *end_screen = scratch + 0xDC;
      u8 *projection_aux = scratch + 0x84;
      u8 *projection_flags = scratch + 0x88;
      ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_F4 = func_80065420(start_vertex, start_screen, projection_aux, projection_flags);
      ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_F8 = func_80065420(end_vertex, end_screen, projection_aux, projection_flags);
    }
    *((u16 *) (line_prim + 8)) = ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_D8;
    *((u16 *) (line_prim + 0xA)) = ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_DA;
    *((u16 *) (line_prim + 0x10)) = ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_DC;
    *((u16 *) (line_prim + 0x12)) = ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_DE;
    {
      s32 depth_sum;
      depth_sum = ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_F4;
      depth_sum += ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_F8;
      depth = depth_sum / 2;
    }
    ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_B4 = depth;
    if (((u32) depth) < 0x1E0U)
    {
      u8 *draw_mode_prim;
      ovl_18d0850_818B0E10_addPrim(((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->ot + ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_B4, line_prim);
      draw_mode_prim = ((GpuContext *)render_state->unk_000)->packetCursor;
      ((GpuContext *)render_state->unk_000)->packetCursor = draw_mode_prim + 0xC;
      func_80067F20(draw_mode_prim, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
      ovl_18d0850_818B0E10_addPrim(((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->ot + ((ovl_18d0850_818B0E10_LineSegmentScratch *) scratch)->unk_B4, draw_mode_prim);
    }
    segment -= 1;
  }
  while (segment >= 0);
  return 0;
}

s32 build_a_trigonometric_table_processes_up_eight_height_offset_segments(ovl_18d0850_818B11B4_S_818B11B4_0 *source, ovl_18d0850_818B11B4_S_818B11B4_2 *height_ref, void *context) {
    s32 trig_table[34];
    s32 *trig_buffer;
    s32 *trig_cursor;
    s16 angle;
    s32 scaled_segment;
    s32 table_angle;
    s32 phase;
    s32 segment_count;
    s32 biased_phase;
    s32 biased_index;
    s32 table_index;
    s32 segment_index;
    s32 segment_limit;
    u16 height;
    void *height_cursor;
    void *segment_source;

    trig_buffer = trig_table;
    table_index = 0x10;
    trig_cursor = &trig_table[16];
    do {
        biased_index = table_index;
        table_angle = (table_index - ((biased_index / 16) * 0x10)) << 8;
        trig_cursor[0] = func_800644B8(table_angle) >> 4;
        trig_cursor[17] = func_80064584(table_angle) >> 4;
        trig_cursor--;
    } while (--table_index >= 0);

    segment_count = (s32)(source->unk_16 << 0x10) >> 0x12;
    segment_limit = 8;
    if (segment_count < 9) {
        segment_limit = segment_count;
    }

    segment_index = 0;
    if (segment_limit > 0) {
        height_cursor = source;
        do {
            phase = source->unk_10 - segment_index;
            biased_phase = phase;
            angle = (func_800644B8((phase - ((biased_phase / 16) * 0x10)) << 9) >> 9) + 0x20;
            func_80064584(segment_index << 9);
            segment_source = source;
            height = ((ovl_18d0850_818B11B4_S_818B11B4_1 *)height_cursor)->unk_1A;
            scaled_segment = segment_index << 0x11;
            draw_n_16_shaded_line_segments_link_them_ordering_table_depth(segment_source, height_ref, context, angle,
                         (u32)(s16)(height_ref->unk_0A - height),
                         trig_buffer, 0xFF, scaled_segment >> 0x10);
            height_cursor = (u8 *)height_cursor + 2;
            segment_index++;
        } while (segment_index < segment_limit);
    }
    return 0;
}

s32 build_a_circular_lookup_table_submit_eight_phase_shifted_entries(ovl_18d0850_818B1334_S_818B1334_1 *source, ovl_18d0850_818B1334_S_818B1334_3 *target, void *context) {
    s32 circle_values[34];
    s32 *circle_entry;
    register s32 *circle_table;
    s16 radius;
    s32 entry_angle;
    s32 circle_angle;
    s32 phase;
    s32 phase_bias;
    s32 index_bias;
    s32 circle_index;
    s32 entry_index;
    u16 angle_offset;
    void *offset_cursor;
    void *source_arg;

    circle_table = circle_values;
    circle_index = 0x10;
    circle_entry = circle_table + 16;
    do {
        index_bias = circle_index;
        circle_angle = (circle_index - ((index_bias / 16) * 0x10)) << 8;
        ((ovl_18d0850_818B1334_S_818B1334_0 *)circle_entry)->unk_00 = (s32) (func_800644B8(circle_angle) >> 4);
        ((ovl_18d0850_818B1334_S_818B1334_0 *)circle_entry)->unk_44 = (s32) (func_80064584(circle_angle) >> 4);
        circle_entry -= 1;
    } while (--circle_index >= 0);
    entry_index = 0;
    offset_cursor = source;
    do {
        phase = source->unk_10 - entry_index;
        phase_bias = phase;
        radius = (func_800644B8((phase - ((phase_bias / 16) * 0x10)) << 9) >> 9) + 0x20;
        func_80064584(entry_index << 0xA);
        source_arg = source;
        angle_offset = ((ovl_18d0850_818B1334_S_818B1334_2 *)offset_cursor)->unk_1A;
        entry_angle = entry_index << 0x11;
        draw_n_16_shaded_line_segments_link_them_ordering_table_depth(source_arg, target, context, radius, (s32) (s16) (target->unk_0A - angle_offset), circle_table, 0xFF, entry_angle >> 0x10);
        offset_cursor += 2;
        entry_index += 1;
    } while (entry_index < 8);
    return 0;
}

s32 fade_effect_sprite_to_black(ovl_18d0850_818B1484_S_818B1484_1 *effect, ovl_18d0850_818B1484_S_818B1484_3 *target, void *context) {
    void *effect_arg;
    s32 wave_table[34];
    s32 *table_ptr;
    s32 *sample_ptr;
    s16 entry_scale;
    s32 entry_arg;
    s32 sample_angle;
    s32 phase;
    s32 phase_rounded;
    s32 index_rounded;
    s32 sample_index;
    s32 entry_index;
    u16 entry_offset;
    void *entry_ptr;

    table_ptr = wave_table;
    sample_index = 0x10;
    sample_ptr = &wave_table[16];
    do {
        index_rounded = sample_index;
        sample_angle = (sample_index - ((index_rounded / 16) * 0x10)) << 8;
        ((ovl_18d0850_818B1484_S_818B1484_0 *)sample_ptr)->unk_00 = (u32) (func_800644B8(sample_angle) >> 4);
        ((ovl_18d0850_818B1484_S_818B1484_0 *)sample_ptr)->unk_44 = (s32) (func_80064584(sample_angle) >> 4);
        sample_ptr--;
    } while (--sample_index >= 0);
    entry_index = ((s32) (effect->unk_16 << 0x10) >> 0x12) + 1;
    if (entry_index < 8) {
        entry_ptr = (void *) ((entry_index << 1) + (u32) effect);
        do {
            phase = effect->unk_10 - entry_index;
            phase_rounded = phase;
            entry_scale = (func_800644B8((phase - ((phase_rounded / 16) * 0x10)) << 9) >> 9) + 0x20;
            func_80064584(entry_index << 9);
            effect_arg = effect;
            entry_offset = ((ovl_18d0850_818B1484_S_818B1484_2 *)entry_ptr)->unk_1A;
            entry_arg = entry_index << 0x11;
            draw_n_16_shaded_line_segments_link_them_ordering_table_depth(effect_arg, target, context, entry_scale,
                         (s32) (s16) (target->unk_0A - entry_offset),
                         table_ptr, 0xFF, entry_arg >> 0x10);
            entry_ptr += 2;
            entry_index += 1;
        } while (entry_index < 8);
    }
    return 0;
}

s32 dispatch_effect_state_handler(void *state_ptr, void *second_ptr, void *third_ptr)
{
    switch (((ovl_18d0850_818B15F4_Func818B15F4Arg *)state_ptr)->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
    default:
        break;
    case 4:
        build_a_trigonometric_table_processes_up_eight_height_offset_segments(state_ptr, second_ptr, third_ptr);
        break;
    case 5:
        build_a_circular_lookup_table_submit_eight_phase_shifted_entries(state_ptr, second_ptr, third_ptr);
        break;
    case 6:
        fade_effect_sprite_to_black(state_ptr, second_ptr, third_ptr);
        break;
    }
    return 0;
}

void update_movement_toward_child_terrain_target_animates_associated_effects(ovl_18d0850_818B1664_State *state_arg, ovl_18d0850_818B1664_Motion *motion_arg, ovl_18d0850_818B1664_DrawInfo *draw_info)
{
    ovl_18d0850_818B1664_WorkFrame work;
    u16 saved_y;
    ovl_18d0850_818B1664_DrawInfo *draw = draw_info;
    ovl_18d0850_818B1664_Entity *entity;
    ovl_18d0850_818B1664_EntityHeader *header;
    s32 dispatch_state;
    s32 direction;
    s32 color;
    u16 source_z;
    ovl_18d0850_818B1664_TargetInfo *target_info;
    ovl_18d0850_818B1664_Motion *step_x;
    u8 *angle_update;
    u8 *angle_clear;
    u8 *angle_build;
    u8 *effect_clear;
    ovl_18d0850_818B1664_Effect **effect_create;
    ovl_18d0850_818B1664_Effect **effect_grow;
    ovl_18d0850_818B1664_Effect **effect_shrink;
    ovl_18d0850_818B1664_Effect **effect_cleanup;
    s32 index;
    s32 next_state;
    s32 angle;
    s32 effect_angle;
    s32 effect_step;
    s32 collision_result;
    s32 terrain_height;
    s16 *target_cursor;
    s16 *distance_cursor;
    s32 target_x;
    s32 target_y;
    u16 angle_raw;
    s32 angle_signed;
    s32 angle_adjusted;
    u16 lowered_z;
    s16 *step_y;
    s32 target;
    u16 tile_x;
    u16 tile_y;
    s16 grid_x;
    s16 grid_y;
    u16 final_x;

    void *cleanup_base;

    index = 7;
    angle_update = (u8 *)state_arg + 14;
    entity = state_arg->entity;
loop_0:
    {
        angle_raw = *(u16 *)(angle_update + 26) + (u16)state_arg->angleStep;
        angle_signed = (s16)angle_raw;
        angle_adjusted = angle_signed;
        *(u16 *)(angle_update + 26) = angle_raw;
        angle_raw = angle_signed - (((angle_adjusted / 128)) << 7);
        *(u16 *)(angle_update + 26) = angle_raw;
        index--;
        angle_update -= 2;
    }
    if (index >= 0)
        goto loop_0;
    {
        s32 timer_value;

        timer_value = (u16)state_arg->timer;
        timer_value++;
        state_arg->timer = timer_value;
        timer_value = (u16)state_arg->timer2;
        dispatch_state = state_arg->state;
        timer_value++;
        state_arg->timer2 = timer_value;
    }

    switch (dispatch_state) {
    case 0:
        state_arg->timer = 0;
        state_arg->timer2 = 0;
        state_arg->angleStep = 4;
        state_arg->state++;
        index = 7;
        angle_clear = (u8 *)state_arg + 14;
        do {
            *(s16 *)(angle_clear + 26) = 0;
            index--;
            angle_clear -= 2;
        } while (index >= 0);
        index = 9;
        effect_clear = (u8 *)state_arg + 36;
        do {
            *(ovl_18d0850_818B1664_Effect **)(effect_clear + 44) = 0;
            index--;
            effect_clear -= 4;
        } while (index >= 0);
        write_fixed_palette_pixels(angle_clear, angle_update, draw_info);
        color = 0x00808080;
        direction = (entity->flags2A >> 9) & 7;
        state_arg->direction = direction;
        draw->color = color;

    case 1:
        header = (ovl_18d0850_818B1664_EntityHeader *)((u8 *)entity - 0x20);
        target_info = header->info;
        if (resolve_record_orientation_or_fallback(target_info->map, target_info, work.distance, 0) == 0) {
            if (!(header->info->flags & 0x8000)) {
                break;
            }
        }

        step_x = header->position;
        motion_arg->x.half.hi = step_x->x.half.hi;
        motion_arg->y.half.hi = step_x->y.half.hi;
        source_z = step_x->z.half.hi;
        motion_arg->z.half.hi = source_z;
        if (!(header->info->flags & 0x8000)) {
            motion_arg->x.half.hi += work.distance[0];
            motion_arg->y.half.hi += work.distance[1];
            motion_arg->z.half.hi += work.distance[2];
        } else {
            lowered_z = source_z - 64;
            motion_arg->z.half.hi = lowered_z;
        }

        if (!(state_arg->flags & 1)) {
            register_node((u8 *)state_arg - 0x20, dispatch_effect_state_handler);
            state_arg->flags |= 1;
        }
        if (!(state_arg->resource->flags & 0x80)) {
            break;
        }

        index = 0;
        if (entity->child != 0) {
            cleanup_base = (void *)(*(ovl_18d0850_818B1664_Motion **)((u8 *)entity->child - 0x18));

            color = motion_arg->x.half.hi;
            work.distance[0] = abs(((ovl_18d0850_818B1664_Motion *)cleanup_base)->x.half.hi - color);
            work.distance[1] = abs(((ovl_18d0850_818B1664_Motion *)cleanup_base)->y.half.hi - motion_arg->y.half.hi);
            if (entity->child->flags & 0x40000) {
                color = motion_arg->z.half.hi;
                color -= 16;
                work.distance[2] = abs(((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi - color);
            } else {
                work.distance[2] = abs(((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi - motion_arg->z.half.hi);
            }
            index = 1;

            state_arg->duration = work.distance[0];
            distance_cursor = &work.target.x.half.hi;
            do {
                if (distance_cursor[12] > state_arg->duration) {
                    state_arg->duration = (u16)distance_cursor[12];
                }
                index++;
                distance_cursor++;
            } while (index < 3);
            state_arg->duration >>= 5;
            if (state_arg->duration == 0) {
                state_arg->duration = 1;
            }

            motion_arg->dx.half.hi =
                (((ovl_18d0850_818B1664_Motion *)cleanup_base)->x.half.hi - motion_arg->x.half.hi) / state_arg->duration;
            motion_arg->dy.half.hi =
                (((ovl_18d0850_818B1664_Motion *)cleanup_base)->y.half.hi - motion_arg->y.half.hi) / state_arg->duration;
            if (entity->child->flags & 0x40000) {
                s32 coord;
                coord = motion_arg->z.half.hi - 16;
                motion_arg->dz.half.hi =
                    (((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi - coord) / state_arg->duration;
            } else {
                motion_arg->dz.half.hi =
                    (((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi - motion_arg->z.half.hi) /
                    state_arg->duration;
            }
            next_state = (u16)state_arg->state + 1;
            goto reset_state;
        }

        {
            ovl_18d0850_818B1664_TargetInfo *tile_info;

            tile_info = header->info;
            tile_x = tile_info->tileX;
            tile_y = tile_info->tileY;
        }
        final_x = tile_x;
        saved_y = tile_y;

        while (index < 8) {
            grid_x = (s16)tile_x;
            grid_y = (s16)tile_y;
            collision_result = check_layer_offset_height(
                (grid_x << 6) & 0xFFC0,
                (grid_y << 6) & 0xFFC0,
                entity->height,
                (s16)(state_arg->direction << 9));
            if ((s16)collision_result != 0) {
                break;
            }
            step_x = (ovl_18d0850_818B1664_Motion *)&dir_step_x[state_arg->direction];
            target = (u16)entity->height;
            target -= 32;
            target = (u32)target << 16;
            target >>= 16;
            step_y = &dir_step_y[state_arg->direction];
            terrain_height = sample_terrain_surface_height(
                ((grid_x + *(s16 *)step_x) << 6) + 32 & 0xFFE0,
                ((grid_y + *step_y) << 6) + 32 & 0xFFE0,
                target);
            if ((s16)terrain_height >= 513 ||
                (s16)(terrain_height - entity->height) < -63) {
                break;
            }
            index++;
            tile_x += dir_step_x[state_arg->direction];
            tile_y += dir_step_y[state_arg->direction];
            saved_y = tile_y;
            final_x = tile_x;
        }

        target = (s32)(&work.target);
        index = 1;
        target_cursor = &work.target.x.half.hi;
        target_x = ((final_x << 16) >> 10) + ((dir_step_x[state_arg->direction] + 1) << 5);
        ((ovl_18d0850_818B1664_Motion *)target)->x.half.hi = target_x;
        target_y = ((saved_y << 16) >> 10) + ((dir_step_y[state_arg->direction] + 1) << 5);
        ((ovl_18d0850_818B1664_Motion *)target)->y.half.hi = target_y;
        ((ovl_18d0850_818B1664_Motion *)target)->z.half.hi = motion_arg->z.half.hi + 32;
        work.distance[0] = abs(((ovl_18d0850_818B1664_Motion *)target)->x.half.hi - motion_arg->x.half.hi);
        work.distance[1] = abs(((ovl_18d0850_818B1664_Motion *)target)->y.half.hi - motion_arg->y.half.hi);
        work.distance[2] = abs(((ovl_18d0850_818B1664_Motion *)target)->z.half.hi - motion_arg->z.half.hi);

        state_arg->duration = work.distance[0];
        do {
            if (target_cursor[12] > state_arg->duration) {
                state_arg->duration = (u16)target_cursor[12];
            }
            index++;
            target_cursor++;
        } while (index < 3);
        state_arg->duration >>= 5;
        if (state_arg->duration == 0) {
            state_arg->duration = 1;
        }
        motion_arg->dx.word = (((ovl_18d0850_818B1664_Motion *)target)->x.word - motion_arg->x.word) / state_arg->duration;
        motion_arg->dy.word = (((ovl_18d0850_818B1664_Motion *)target)->y.word - motion_arg->y.word) / state_arg->duration;
        motion_arg->dz.word = (((ovl_18d0850_818B1664_Motion *)target)->z.word - motion_arg->z.word) / state_arg->duration;
        state_arg->state = 8;
        state_arg->timer = 0;
        state_arg->timer2 = 0;
        break;

    case 2:
        motion_arg->x.half.hi += motion_arg->dx.half.hi;
        motion_arg->y.half.hi += motion_arg->dy.half.hi;
        motion_arg->z.half.hi += motion_arg->dz.half.hi;
        create_an_initialized_render_state_copy_vector(state_arg, motion_arg);
        if (state_arg->timer < state_arg->duration) {
            break;
        }
        play_sound_if_enabled(0x300);
        goto increment_reset;

    case 3:
        if (state_arg->timer < 8) {
            break;
        }
        state_arg->timer = 0;
        state_arg->timer2 = 0;
        state_arg->state++;
        cleanup_base = (void *)(*(ovl_18d0850_818B1664_Motion **)((u8 *)entity->child - 0x18));
        motion_arg->x.half.hi = ((ovl_18d0850_818B1664_Motion *)cleanup_base)->x.half.hi;
        motion_arg->y.half.hi = ((ovl_18d0850_818B1664_Motion *)cleanup_base)->y.half.hi;
        if (entity->child->flags & 0x40000) {
            motion_arg->z.half.hi = ((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi + 16;
        } else {
            motion_arg->z.half.hi = ((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi;
        }

        index = 7;
        angle = 16;
        angle_build = (u8 *)state_arg + 14;
        do {
            *(s16 *)(angle_build + 26) = angle;
            angle += 16;
            index--;
            angle_build -= 2;
        } while (index > 0);
        state_arg->angles[0] = 0;

        index = 9;
        effect_create = (ovl_18d0850_818B1664_Effect **)((u8 *)state_arg + 36);
        effect_angle = (s32)0xFF1F0000;
create_loop:
        {
            effect_create[11] =
                create_radial_height_offset_effect(state_arg, motion_arg, effect_angle >> 16, index);
            effect_create--;
            effect_step = 0x190000;
            effect_angle += effect_step;
            index--;
        }
        if (index >= 0)
            goto create_loop;
        state_arg->field14 = 0;
        return;

    case 4:
    {
        ovl_18d0850_818B1664_Effect *effect;
        ovl_18d0850_818B1664_EffectInner *inner;
        s32 effect_delta;

        index = 9;
        effect_delta = 0x40404;
        effect_grow = (ovl_18d0850_818B1664_Effect **)((u8 *)state_arg + 36);
        do {
            effect = effect_grow[11];
            inner = effect->inner;
            inner->value += effect_delta;
            effect_grow--;
            index--;
        } while (index >= 0);
        if (state_arg->timer2 < 32) {
            break;
        }
        next_state = (u16)state_arg->state;
        state_arg->timer2 = 0;
        next_state++;
        state_arg->state = next_state;
        break;
    }

    case 5:
        if (state_arg->timer2 < 32) {
            break;
        }
        next_state = (u16)state_arg->state;
        state_arg->timer2 = 0;
        next_state++;
        state_arg->state = next_state;
        break;

    case 6:
    {
        ovl_18d0850_818B1664_Effect *effect;
        ovl_18d0850_818B1664_EffectInner *inner;
        ovl_18d0850_818B1664_Effect *cleanup_effect;
        s32 cleanup_flags;
        s32 global_flags;
        s32 effect_delta;

        index = 9;
        effect_delta = -0x40404;
        effect_shrink = (ovl_18d0850_818B1664_Effect **)((u8 *)state_arg + 36);
        do {
            effect = effect_shrink[11];
            inner = effect->inner;
            inner->value += effect_delta;
            effect_shrink--;
            index--;
        } while (index >= 0);
        cleanup_base = entity;
        if (state_arg->timer2 < 32) {
            break;
        }
        follow_brighten(((ovl_18d0850_818B1664_Entity *)cleanup_base)->child, state_arg->id);
        index = 9;
        cleanup_base = (void *)0x80080000;
        next_state = (u16)state_arg->state;
        state_arg->timer2 = 0;
        next_state++;
        state_arg->state = next_state;
        do {
            effect_cleanup = (ovl_18d0850_818B1664_Effect **)((u8 *)state_arg + index * 4);
            cleanup_effect = effect_cleanup[11];
            if (cleanup_effect != 0) {
                cleanup_flags = cleanup_effect->flags;
                global_flags = *(s32 *)((u8 *)cleanup_base + 0x14A0);
                cleanup_flags |= 0x8000;
                global_flags |= 0x8000;
                cleanup_effect->flags = cleanup_flags;
                *(s32 *)((u8 *)cleanup_base + 0x14A0) = global_flags;
                effect_cleanup[11] = 0;
            }
            index--;
        } while (index >= 0);
        state_arg->field14 = 0;
        return;
    }

    case 7:
        if (state_arg->field14 != 0) {
            break;
        }
        g_dungeon_status.unk_0C = 0;
        *(u16 *)((u8 *)state_arg - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        break;

    case 8:
        motion_arg->x.half.hi += motion_arg->dx.half.hi;
        motion_arg->y.half.hi += motion_arg->dy.half.hi;
        motion_arg->z.half.hi += motion_arg->dz.half.hi;
        create_an_initialized_render_state_copy_vector(state_arg, motion_arg);
        if (state_arg->timer < state_arg->duration) {
            break;
        }

increment_reset:
        next_state = (u16)state_arg->state;
        state_arg->timer = 0;
        state_arg->timer2 = 0;
        next_state++;
        state_arg->state = next_state;
        break;

    case 9:
        if (state_arg->timer < 8) {
            break;
        }
        next_state = 7;
reset_state:
        state_arg->state = next_state;
        state_arg->timer = 0;
        state_arg->timer2 = 0;

    }
    state_arg->field14 = 0;
    return;
}

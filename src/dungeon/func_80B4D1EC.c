/* Relink of matched dungeon/func_80B471EC; every changed retail word is a paired relocation. */
#define dungeonBuildAnimatedSphericalWireframe func_8016E9EC
#define dungeonUpdateTurningFadeEffectAndModel D_8016E9A8
#include "modules/dungeon_resource12_slot0.h"
extern s32 func_8016E954(void *, void *, void *);
extern s32 func_800644B8(s32);

void func_8016E9EC(void *effect, void *origin, void *tint) {
    s16 ring_angles[10];
    s32 coordinate;
    u32 scale;
    s32 y_coordinate;
    s32 state_m;
    s16 vertices[10][6][3];
    register void *object_origin;
    void *line_data;
    s16 *closing_angle;
    s16 next_angle_index;
    s16 next_meridian;
    s16 next_ring;
    s16 remaining_ticks;
    s16 opening_angle;
    s16 next_opening_ring;
    s16 next_opening_sector;
    s16 closing_angle_value;
    s16 next_closing_ring;
    s16 next_closing_sector;
    s16 prev_angle_index;
    s16 phase;
    s16 meridian;
    s16 ring_sector;
    s16 sector;
    s16 ring;
    s16 ring_index;
    s16 next_segment;
    s32 sector_offset;
    s32 segment_index;
    s32 opening_azimuth;
    s32 closing_azimuth;
    s32 opening_sector_radius;
    s32 closing_sector_radius;
    s32 vertex_base_or_offset;
    s32 radius;
    s32 vertex_offset;
    register s32 signed_ring_index;
    s32 ring_index_shifted;
    u16 closing_progress;
    u16 opening_progress;
    u16 old_phase;
    void *meridian_render;
    void *segment_start;
    void *ring_render;
    void *meridian_line;
    void *opening_vertex;
    void *closing_vertex;
    void *sector_or_ring_start;
    void *meridian_object;
    void *segment_end;
    void *ring_object;
    void *next_vertex;
    void *current_vertex;
    void *opening_angle_slot;
    void *closing_angle_slot;
    void *meridian_origin;
    void *ring_origin;
    register void *ring_data;


    object_origin = origin;
    phase = ((R12_801749EC_S_801749EC_0 *)effect)->unk_06;
    if (phase != 1) {
        if (phase < 2) {
        if (phase == 0) {
        s16 *angle_base;
        s32 angle_limit;
        scale = 0x1E;
        ring_index = 1;
        angle_base = ring_angles;
        angle_limit = 0x400;
        ring_angles[0] = (0 - ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C) + 0x400;
        do {
            opening_angle_slot = (void *)(((ring_index << 0x10) >> 0xF) + (s32)angle_base);
            opening_angle = ((R12_801749EC_S_801749EC_2_pre *)opening_angle_slot)[-1].unk_00 + 0xCC;
            ((R12_801749EC_S_801749EC_2 *)opening_angle_slot)->unk_00 = opening_angle;
            if (opening_angle >= 0x401) {
                ((R12_801749EC_S_801749EC_2 *)opening_angle_slot)->unk_00 = angle_limit;
            }
            next_angle_index = ring_index + 1;
            ring_index = next_angle_index;
        } while (next_angle_index < 0xA);
        for (ring_index = 0; ring_index < 10; ring_index++) {
            for (sector = 0; sector < 6; sector++) {
                coordinate = func_800644B8(ring_angles[ring_index]);
                radius = scale;
                state_m = radius * coordinate;
                vertices[ring_index][sector][2] = state_m >> 0xC;
                state_m = radius * func_80064584(ring_angles[ring_index]);
                opening_azimuth = sector * 682;
                opening_sector_radius = state_m >> 0xC;
                state_m = (s16) opening_sector_radius * func_80064584(opening_azimuth);
                vertices[ring_index][sector][0] = state_m >> 0xC;
                state_m = (s16) opening_sector_radius * func_800644B8(opening_azimuth);
                vertices[ring_index][sector][1] = state_m >> 0xC;
            }
        }
        opening_progress = ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C + 0x64;
        ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C = opening_progress;
        if ((s16) opening_progress >= 0x800) {
            ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C = 0x800U;
        }
        if (((R12_801749EC_S_801749EC_1 *)effect)->unk_08 < 0x16) {
            old_phase = ((R12_801749EC_S_801749EC_1 *)effect)->unk_06;
            ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C = 0U;
            ((R12_801749EC_S_801749EC_1 *)effect)->unk_06 = old_phase + 1;
        }
        }
        }
    } else {
        {
        s16 *angle_base;
        s32 angle_limit;
        scale = 0x1E;
        ring_index = 8;
        angle_base = ring_angles;
        angle_limit = -0x400;
        ring_angles[9] = (0 - ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C) + 0x400;
        do {
            closing_angle_slot = (void *)(((ring_index << 0x10) >> 0xF) + (s32)angle_base);
            closing_angle_value = ((R12_801749EC_S_801749EC_4 *)closing_angle_slot)->unk_02 - 0xCC;
            ((R12_801749EC_S_801749EC_4 *)closing_angle_slot)->unk_00 = closing_angle_value;
            if (closing_angle_value < -0x400) {
                ((R12_801749EC_S_801749EC_4 *)closing_angle_slot)->unk_00 = angle_limit;
            }
            prev_angle_index = ring_index - 1;
            ring_index = prev_angle_index;
        } while ((prev_angle_index << 0x10) != 0);
        for (ring_index = 0; ring_index < 10; ring_index++) {
            for (sector = 0; sector < 6; sector++) {
                coordinate = func_800644B8(ring_angles[ring_index]);
                radius = scale;
                state_m = radius * coordinate;
                vertices[ring_index][sector][2] = state_m >> 0xC;
                state_m = radius * func_80064584(ring_angles[ring_index]);
                closing_azimuth = sector * 682;
                closing_sector_radius = state_m >> 0xC;
                state_m = (s16) closing_sector_radius * func_80064584(closing_azimuth);
                vertices[ring_index][sector][0] = state_m >> 0xC;
                state_m = (s16) closing_sector_radius * func_800644B8(closing_azimuth);
                vertices[ring_index][sector][1] = state_m >> 0xC;
            }
        }
        closing_progress = ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C + 0x64;
        ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C = closing_progress;
        if ((s16) closing_progress >= 0x800) {
            ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C = 0x800U;
        }
        }
    }
    for (meridian = 0; meridian < 6; meridian++) {
        for (sector = 0; sector < 9; sector++) {
        meridian_object = func_8003FC64(0x212);
        if (meridian_object != NULL) {
            meridian_line = meridian_object + 0x20;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_1A = 1;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_1C = 1;
            ((R12_801749EC_S_801749EC_7 *)meridian_object)->unk_10 = ((u8 *)dungeonUpdateTurningFadeEffectAndModel);
            func_8004491C(meridian_object, &func_8016E954);
            meridian_render = ((R12_801749EC_S_801749EC_7 *)meridian_object)->unk_0C;
            ((R12_801749EC_S_801749EC_8 *)meridian_render)->unk_10 = 0x20;
            ((R12_801749EC_S_801749EC_8 *)meridian_render)->unk_14 = (u16) (((R12_801749EC_S_801749EC_8 *)meridian_render)->unk_14 | 0xC);
            meridian_origin = ((R12_801749EC_S_801749EC_7 *)meridian_object)->unk_08;
            ((R12_801749EC_S_801749EC_9 *)meridian_origin)->unk_00 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_00;
            ((R12_801749EC_S_801749EC_9 *)meridian_origin)->unk_04 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_04;
            ((R12_801749EC_S_801749EC_9 *)meridian_origin)->unk_08 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_08;
            meridian_render = ((R12_801749EC_S_801749EC_7 *)meridian_object)->unk_0C;
            (*(s16 *)((u8 *)meridian_render + 0x1E)) = 0x1000;
            (*(s16 *)((u8 *)meridian_render + 0x1C)) = 0x1000;
            ((R12_801749EC_S_801749EC_8 *)meridian_render)->unk_0C = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0C;
            ((R12_801749EC_S_801749EC_8 *)meridian_render)->unk_0D = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0D;
            ((R12_801749EC_S_801749EC_8 *)meridian_render)->unk_0E = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0E;
            segment_index = sector << 0x10;
            segment_index >>= 0x10;
            sector_offset = meridian * 6;
            segment_end = (s8 *)vertices + (sector_offset + ((segment_index + 1) * 0x24));
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_64 = (u16) ((R12_801749EC_S_801749EC_12 *)segment_end)->unk_00;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_66 = (u16) ((R12_801749EC_S_801749EC_12 *)segment_end)->unk_02;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_68 = (u16) ((R12_801749EC_S_801749EC_12 *)segment_end)->unk_04;
            segment_start = (s8 *)vertices + (sector_offset + (segment_index * 0x24));
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_6A = (u16) ((R12_801749EC_S_801749EC_13 *)segment_start)->unk_00;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_6C = (u16) ((R12_801749EC_S_801749EC_13 *)segment_start)->unk_02;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_6E = (u16) ((R12_801749EC_S_801749EC_13 *)segment_start)->unk_04;
        }
        }
    }
    for (sector = 1; sector < 9; sector++) {
        meridian = 0;
        {
            s32 signed_outer;
            s32 scaled_outer;
            signed_outer = sector;
            scaled_outer = (signed_outer << 3) + signed_outer;
            vertex_base_or_offset = scaled_outer << 2;
        }
        for (; meridian < 6; meridian++) {
            ring_object = func_8003FC64(0x212);
            if (ring_object != NULL) {
                meridian_line = ring_object + 0x20;
                ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_1A = 1;
                ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_1C = 1;
                ((R12_801749EC_S_801749EC_15 *)ring_object)->unk_10 = ((u8 *)dungeonUpdateTurningFadeEffectAndModel);
                func_8004491C(ring_object, &func_8016E954);
                ring_render = ((R12_801749EC_S_801749EC_15 *)ring_object)->unk_0C;
                {
                    u16 object_flags;
                    s32 object_width;
                    object_flags = ((R12_801749EC_S_801749EC_16 *)ring_render)->unk_14;
                    object_width = 0x20;
                    ((R12_801749EC_S_801749EC_16 *)ring_render)->unk_10 = object_width;
                    object_flags |= 0xC;
                    ((R12_801749EC_S_801749EC_16 *)ring_render)->unk_14 = object_flags;
                }
                ring_origin = ((R12_801749EC_S_801749EC_15 *)ring_object)->unk_08;
                ((R12_801749EC_S_801749EC_17 *)ring_origin)->unk_00 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_00;
                ((R12_801749EC_S_801749EC_17 *)ring_origin)->unk_04 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_04;
                ((R12_801749EC_S_801749EC_17 *)ring_origin)->unk_08 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_08;
                ring_render = ((R12_801749EC_S_801749EC_15 *)ring_object)->unk_0C;
                (*(s16 *)((u8 *)ring_render + 0x1E)) = 0x1000;
                (*(s16 *)((u8 *)ring_render + 0x1C)) = 0x1000;
                ((R12_801749EC_S_801749EC_18 *)ring_render)->unk_0C = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0C;
                ((R12_801749EC_S_801749EC_18 *)ring_render)->unk_0D = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0D;
                ((R12_801749EC_S_801749EC_18 *)ring_render)->unk_0E = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0E;
                if (meridian != 5) {
                    next_vertex = (s8 *)vertices + (((meridian + 1) * 6) + vertex_base_or_offset);
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_64 = (u16) ((R12_801749EC_S_801749EC_19 *)next_vertex)->unk_00;
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_66 = (u16) ((R12_801749EC_S_801749EC_19 *)next_vertex)->unk_02;
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_68 = (u16) ((R12_801749EC_S_801749EC_19 *)next_vertex)->unk_04;
                } else {
                    sector_or_ring_start = (s8 *)vertices + vertex_base_or_offset;
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_64 = (u16) ((R12_801749EC_S_801749EC_20 *)sector_or_ring_start)->unk_00;
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_66 = (u16) ((R12_801749EC_S_801749EC_20 *)sector_or_ring_start)->unk_02;
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_68 = (u16) ((R12_801749EC_S_801749EC_20 *)sector_or_ring_start)->unk_04;
                }
                current_vertex = (s8 *)vertices + ((meridian * 6) + vertex_base_or_offset);
                ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_6A = (u16) ((R12_801749EC_S_801749EC_21 *)current_vertex)->unk_00;
                ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_6C = (u16) ((R12_801749EC_S_801749EC_21 *)current_vertex)->unk_02;
                ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_6E = (u16) ((R12_801749EC_S_801749EC_21 *)current_vertex)->unk_04;
            }
        }
    }
    {
        remaining_ticks = (u16) ((R12_801749EC_S_801749EC_1 *)effect)->unk_08 - 1;
        ((R12_801749EC_S_801749EC_1 *)effect)->unk_08 = remaining_ticks;
        if ((remaining_ticks << 0x10) <= 0) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((R12_801749EC_S_801749EC_1_pre *)effect)[-1].unk_00 | 0x8000);
            objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
        }
        return;
    }
}

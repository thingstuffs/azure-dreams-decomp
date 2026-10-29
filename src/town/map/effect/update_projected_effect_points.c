#include "common.h"
#include "sdk/libgte.h"
#include "town/map/animation.h"
#include "town/map/effect.h"





typedef struct S_800A8CA8_0 {
    u8 pad_00[0x74];
    u16 unk_74;
    u16 unk_76;
    u8 pad_78[0x4];
    u16 unk_7C;
    u16 unk_7E;
    u16 unk_80;
    u8 pad_82[0x2];
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
    u8 pad_8A[0x3A];
    s32 unk_C4;
    u8 pad_C8[0x4C];
    s8 unk_114;
    s8 unk_115;
    s8 unk_116;
} S_800A8CA8_0;   /* arg0 in update_projected_effect_points */

typedef struct S_800A8CA8_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_800A8CA8_1;

typedef struct S_800A8CA8_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800A8CA8_2;   /* arg3 in update_projected_effect_points */

/* Updates three offset points, their projected coordinates, and phase-based intensities. */
void update_projected_effect_points(void *object, s32 phase, void *source_data, S_800A8CA8_2 *extent) {
    S_800A8CA8_1 *source;
    u32 phase_bits;
    s32 offset_phase;
    s32 double_phase;
    s32 y_offset;
    s32 x_offset;
    void *start_point;
    void *projection_scale;
    void *projection_flags;
    void *mid_point;
    void *end_point;
    u16 z_extent;

    source = source_data;
    phase_bits = (u32) phase + 0x800;
    offset_phase = (s16)(phase_bits + 0);
    double_phase = offset_phase << 1;
    ((S_800A8CA8_0 *)object)->unk_114 = (s8) ((rsin(source->unk_0E + double_phase) + 0x1000) / 128);
    ((S_800A8CA8_0 *)object)->unk_115 = (s8) ((rsin(source->unk_12 + double_phase) + 0x1000) / 128);
    ((S_800A8CA8_0 *)object)->unk_116 = (s8) ((rsin(source->unk_16 + double_phase) + 0x1000) / 128);
    start_point = object + 0x74;
    copy_low_halfword_coordinates(start_point, source_data);
    mid_point = object + 0x7C;
    copy_low_halfword_coordinates(mid_point, source_data);
    end_point = object + 0x84;
    copy_low_halfword_coordinates(end_point, source_data);
    x_offset = (rsin(offset_phase) * extent->unk_1C) / 4096;
    y_offset = (rcos(offset_phase) * extent->unk_1E) / 4096;
    projection_scale = object + 0x94;
    projection_flags = object + 0x98;
    ((S_800A8CA8_0 *)object)->unk_74 = (u16) (((S_800A8CA8_0 *)object)->unk_74 + x_offset);
    ((S_800A8CA8_0 *)object)->unk_76 = (u16) (((S_800A8CA8_0 *)object)->unk_76 + y_offset);
    ((S_800A8CA8_0 *)object)->unk_C4 = RotTransPers(start_point, object + 0xE8, projection_scale, projection_flags);
    ((S_800A8CA8_0 *)object)->unk_7C = (u16) (((S_800A8CA8_0 *)object)->unk_7C + x_offset);
    ((S_800A8CA8_0 *)object)->unk_7E = (u16) (((S_800A8CA8_0 *)object)->unk_7E + y_offset);
    z_extent = extent->unk_20;
    ((S_800A8CA8_0 *)object)->unk_80 = (u16) (((S_800A8CA8_0 *)object)->unk_80 + ((s16) z_extent / 2));
    ((S_800A8CA8_0 *)object)->unk_C4 = ((((S_800A8CA8_0 *)object)->unk_C4 + RotTransPers(mid_point, object + 0xEC,
        projection_scale, projection_flags)) / 2) - 8;
    ((S_800A8CA8_0 *)object)->unk_84 = (u16) (((S_800A8CA8_0 *)object)->unk_84 + x_offset);
    ((S_800A8CA8_0 *)object)->unk_86 = (u16) (((S_800A8CA8_0 *)object)->unk_86 + y_offset);
    ((S_800A8CA8_0 *)object)->unk_88 = (u16) (((S_800A8CA8_0 *)object)->unk_88 + extent->unk_20);
    RotTransPers(end_point, object + 0x124, projection_scale, projection_flags);
}

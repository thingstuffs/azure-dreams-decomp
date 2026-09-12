#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#ifdef NON_MATCHING
#define ASM_DEP(var) ((void)0)
#else
#define ASM_DEP(var) __asm__("" : "+r"(var))
#endif

extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_80065420();
extern s32 func_800A8C84();

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
} S_800A8CA8_0;   /* arg0 in func_800A8CA8 */

typedef struct S_800A8CA8_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_800A8CA8_1;   /* temp_src in func_800A8CA8 */

typedef struct S_800A8CA8_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800A8CA8_2;   /* arg3 in func_800A8CA8 */

/* Updates three offset points, their projected coordinates, and phase-based intensities. */
void func_800A8CA8(void *object, s32 phase, void *source_data, S_800A8CA8_2 *extent) {
    register S_800A8CA8_1 *source ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
    ASM_DEP(source);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    phase_bits = (u32) phase + 0x800;
    phase_bits <<= 16;
    offset_phase = (s32) phase_bits >> 16;
    double_phase = offset_phase << 1;
    ((S_800A8CA8_0 *)object)->unk_114 = (s8) ((func_800644B8(source->unk_0E + double_phase) + 0x1000) / 128);
    ((S_800A8CA8_0 *)object)->unk_115 = (s8) ((func_800644B8(source->unk_12 + double_phase) + 0x1000) / 128);
    ((S_800A8CA8_0 *)object)->unk_116 = (s8) ((func_800644B8(source->unk_16 + double_phase) + 0x1000) / 128);
    start_point = object + 0x74;
    func_800A8C84(start_point, source);
    mid_point = object + 0x7C;
    func_800A8C84(mid_point, source);
    end_point = object + 0x84;
    func_800A8C84(end_point, source);
    x_offset = (func_800644B8(offset_phase) * extent->unk_1C) / 4096;
    y_offset = (func_80064584(offset_phase) * extent->unk_1E) / 4096;
    projection_scale = object + 0x94;
    projection_flags = object + 0x98;
    ((S_800A8CA8_0 *)object)->unk_74 = (u16) (((S_800A8CA8_0 *)object)->unk_74 + x_offset);
    ((S_800A8CA8_0 *)object)->unk_76 = (u16) (((S_800A8CA8_0 *)object)->unk_76 + y_offset);
    ((S_800A8CA8_0 *)object)->unk_C4 = func_80065420(start_point, object + 0xE8, projection_scale, projection_flags);
    ((S_800A8CA8_0 *)object)->unk_7C = (u16) (((S_800A8CA8_0 *)object)->unk_7C + x_offset);
    ((S_800A8CA8_0 *)object)->unk_7E = (u16) (((S_800A8CA8_0 *)object)->unk_7E + y_offset);
    z_extent = extent->unk_20;
    ((S_800A8CA8_0 *)object)->unk_80 = (u16) (((S_800A8CA8_0 *)object)->unk_80 + ((s16) z_extent / 2));
    ((S_800A8CA8_0 *)object)->unk_C4 = ((((S_800A8CA8_0 *)object)->unk_C4 + func_80065420(mid_point, object + 0xEC, projection_scale, projection_flags)) / 2) - 8;
    ((S_800A8CA8_0 *)object)->unk_84 = (u16) (((S_800A8CA8_0 *)object)->unk_84 + x_offset);
    ((S_800A8CA8_0 *)object)->unk_86 = (u16) (((S_800A8CA8_0 *)object)->unk_86 + y_offset);
    ((S_800A8CA8_0 *)object)->unk_88 = (u16) (((S_800A8CA8_0 *)object)->unk_88 + extent->unk_20);
    func_80065420(end_point, object + 0x124, projection_scale, projection_flags);
}

#include "common.h"
#include "records/Rec_func_8017121C_arg1.h"
#include "records/Rec_D_800E3D7C.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8017121C_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x3C];
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    s16 unk_62;
} S_8017121C_0;   /* base in func_8017121C */

typedef struct S_8017121C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8017121C_1;   /* effect in func_8017121C */

typedef struct S_8017121C_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8017121C_2;   /* part in func_8017121C */

typedef struct S_8017121C_3 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_8017121C_3;   /* coords in func_8017121C */


typedef struct S_8017121C_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017121C_5_pre;   /* the 0x14 bytes before arg0 in func_8017121C, addressed as arg0[-1] */

typedef struct S_8017121C_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8017121C_6;   /* source in func_8017121C */


typedef struct S_8017121C_8_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_8017121C_8_pre;   /* the 0x18 bytes before owner in func_8017121C, addressed as owner[-1] */

typedef struct S_8017121C_9 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8017121C_9;   /* tracked in func_8017121C */

typedef struct S_8017121C_10 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_8017121C_10;   /* ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv in func_8017121C */



typedef struct Vec3u16 {
    u16 raw_y;
    u16 y;
    u16 z;
} Vec3u16;

extern void *func_8003FC64(s32);
extern s32 func_8003DE58(void *, void *, Vec3u16 *, s32);
extern void func_8004491C(void *, void *);

extern u8 D_800DDC40[];
extern u8 D_80170CEC[];
extern u8 D_80170D40[];
extern s16 D_80175EBC[];

/* Creates an effect and sets its movement toward a tracked target or grid position. */
void func_8017121C(void *source_handle, Rec_func_8017121C_arg1 *origin, s32 unused, Rec_D_800E3D7C *target)
{
    Vec3u16 offset;
    void *effect;
    void *init_effect;
    void *init_data;
    S_8017121C_3 *coords;
    register u8 *effect_state ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_8017121C_6 *source;
    S_8017121C_2 *part;
    S_8017121C_9 *target_coords;
    register s16 *direction_table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 coord_delta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 untracked_mask;
    u32 target_flags;
    u32 x_table_addr;
    register void *target_handle ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 effect_x;
    s16 *x_entry;
    s32 x_offset;
    s32 target_x;
    u32 y_table_addr;
    s32 target_y;
    s32 effect_y;
    s16 *y_entry;
    s32 y_offset;
    s32 y_delta;
    s32 effect_z;
    s32 grid_x_bits;
    s32 grid_axis;
    s32 grid_y;
    s32 scaled_x;
    s32 scaled_y;
    s32 centered_coord;

    effect = func_8003FC64(0x212);
    if (effect == NULL) {
        return;
    }

    init_effect = effect;
    ASM_KEEP_NV(init_effect);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    init_data = D_80170CEC;
    ASM_KEEP(init_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    effect_state = (u8 *)effect + 0x20;
    ((S_8017121C_0 *)effect_state)->unk_18 = 2;
    ((S_8017121C_0 *)effect_state)->unk_1A = 2;
    ((S_8017121C_1 *)effect)->unk_10 = D_80170D40;
    func_8004491C(init_effect, init_data);

    part = ((S_8017121C_1 *)effect)->unk_0C;
    part->unk_14 &= 0xFFF3;

    coords = ((S_8017121C_1 *)effect)->unk_08;
    coords->unk_02.s = origin->unk_02;
    coords->unk_06.s = origin->unk_06;
    coords->unk_0A.s = origin->unk_0A;

    source = ((S_8017121C_5_pre *)source_handle)[-1].unk_00;
    if (func_8003DE58(source->unk_08, source, &offset, 0) != 0) {
        coords->unk_02.s += offset.raw_y;
        coords->unk_06.s += offset.y;
        coords->unk_0A.s += offset.z;
    } else {
        coords->unk_0A.s -= 0x14;
    }

    part = ((S_8017121C_1 *)effect)->unk_0C;
    part->unk_1E = 0x1000;
    part->unk_1C = 0x1000;
    part->unk_0E = 0xA0;
    part->unk_0D = 0xA0;
    part->unk_0C = 0xA0;
    ((S_8017121C_0 *)effect_state)->unk_00 = 0xA0;
    ((S_8017121C_0 *)effect_state)->unk_01 = part->unk_0D;
    ((S_8017121C_0 *)effect_state)->unk_02 = part->unk_0E;

    if (target->unk_60.as_pv == NULL) {
        goto no_tracked;
    }
    target_flags = target->unk_14.as_u32;
    untracked_mask = 0x04000000;
    if ((target_flags & untracked_mask) == 0) {
        direction_table = D_80175EBC;
        ((S_8017121C_0 *)effect_state)->unk_60 = 0;
        ((S_8017121C_0 *)effect_state)->unk_5C = 0;
        ((S_8017121C_0 *)effect_state)->unk_58 = 0;

        x_table_addr = target->unk_2A.as_u16;
        ASM_KEEP_NV(x_table_addr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        target_handle = target->unk_60.as_pv;
        ASM_KEEP_NV(target_handle);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        effect_x = coords->unk_02.u;
        ASM_KEEP_NV(effect_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        x_table_addr = (x_table_addr >> 7) & 0x1C;
        x_table_addr += (u32)direction_table;
        x_entry = (s16 *)x_table_addr;
        target_coords = ((S_8017121C_8_pre *)target_handle)[-1].unk_00;
   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        x_offset = *x_entry;
        target_x = target_coords->unk_02;
        x_offset <<= 4;
        coord_delta = target_x - effect_x;
        coord_delta -= x_offset;
        ((S_8017121C_0 *)effect_state)->unk_5A = coord_delta / 2;

        y_table_addr = target->unk_2A.as_u16;
        ASM_KEEP_NV(y_table_addr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        target_y = target_coords->unk_06;
        ASM_KEEP_NV(target_y);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        effect_y = coords->unk_06.u;
        ASM_KEEP_NV(effect_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        y_table_addr = (y_table_addr >> 7) & 0x1C;
        y_table_addr += (u32)direction_table;
        y_entry = (s16 *)y_table_addr;
        y_offset = y_entry[1];
        ASM_KEEP_NV(y_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        y_delta = target_y - effect_y;
        y_offset <<= 4;
        y_delta -= y_offset;
        ((S_8017121C_0 *)effect_state)->unk_5E = y_delta / 2;

        effect_z = coords->unk_0A.u;
        coord_delta = target_coords->unk_0A - effect_z;
        coord_delta -= D_800DDC40[((S_8017121C_10 *)(target->unk_60.as_pv))->unk_13] >> 1;
        ((S_8017121C_0 *)effect_state)->unk_62 = coord_delta / 2;
        return;
    }

no_tracked:
    ((S_8017121C_0 *)effect_state)->unk_60 = 0;
    ((S_8017121C_0 *)effect_state)->unk_5C = 0;
    ((S_8017121C_0 *)effect_state)->unk_58 = 0;

    grid_axis = target->unk_73.as_u8;
    grid_x_bits = target->unk_72.as_u8;
    ASM_KEEP(grid_axis);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    grid_axis <<= 24;
    grid_y = grid_axis >> 24;
    grid_x_bits <<= 24;
    grid_axis = grid_x_bits >> 24;
    if (grid_x_bits < 0) {
        grid_axis = -grid_axis;
    }
    if ((s16)grid_y < 0) {
        grid_y = -grid_y;
    }
    scaled_x = grid_axis << 16;
    centered_coord = coords->unk_02.u;
    scaled_x >>= 10;
    centered_coord -= 0x20;

    coord_delta = scaled_x - centered_coord;
    ((S_8017121C_0 *)effect_state)->unk_5A = coord_delta / 2;
    ASM_KEEP(effect_state);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    scaled_y = grid_y << 16;
    centered_coord = coords->unk_06.u;
    scaled_y >>= 10;
    ((S_8017121C_0 *)effect_state)->unk_62 = 0;
    centered_coord -= 0x20;
    coord_delta = scaled_y - centered_coord;
    ((S_8017121C_0 *)effect_state)->unk_5E = coord_delta / 2;
}

/* MECHANISM: The 0x38 frame and guarded register live ranges preserve the retail prologue, held bases, and table pipelines.
   Raw u8 shift/sign-extension idioms reproduce the fallback branches without widening artifacts.
   Mutating scaled_x/scaled_y with >>= 10 lets each sra fill an lh delay and preserves the second zero-store seam. */

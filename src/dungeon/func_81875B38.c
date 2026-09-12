#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_81875B38_1 {
    u8 pad_00[0x8];
    void *unk_08;
} S_func_81875B38_1;

typedef struct S_func_81875B38_2 {
    u8 pad_00[0x8];
    void *unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_func_81875B38_2;

typedef struct S_func_81875B38_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_func_81875B38_3;

typedef struct S_func_81875B38_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_func_81875B38_4;

typedef struct S_func_81875B38_5 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0x12];
    s32 unk_48;
} S_func_81875B38_5;

extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 D_80025028;
extern s32 D_80025278;

/* Spawn and initialize an effect at a randomly offset position relative to the source. */
void func_81875B38(
    void *source,
    s32 property_34,
    s32 property_28,
    s16 property_52,
    s32 x_offset,
    s32 y_offset,
    s32 z_offset)
{
    s32 saved_x_offset = x_offset;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    S_func_81875B38_1 *source_obj = source;
    s16 saved_property_34 = property_34;
    u32 saved_property_28 = property_28;
    register s16 saved_property_52 ASM_REG("$20") = property_52;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 saved_y_offset = y_offset;
    s32 saved_z_offset = z_offset;
    S_func_81875B38_2 *effect_ptr;
    s32 x_jitter;
    s32 y_jitter;
    s32 z_jitter;
    s32 x_bias;
    s32 y_bias;
    s32 z_bias;
    s32 effect_x;
    s32 effect_y;
    s32 effect_z;
    register S_func_81875B38_2 *effect_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *effect_config;
    S_func_81875B38_4 *x_dest;
    S_func_81875B38_4 *y_dest;
    S_func_81875B38_4 *z_dest;

    effect_ptr = func_8003FD64(0x211, source_obj);
    if (effect_ptr != NULL) {
        effect_ptr->unk_10 = (s32)&D_80025278;
        x_jitter = rand() & 0x1F;
        effect_x = ((S_func_81875B38_3 *)source_obj->unk_08)->unk_02;
        x_dest = effect_ptr->unk_08;
        effect_x += x_jitter;
        x_bias = saved_x_offset - 0x10;
        effect_x += x_bias;
        x_dest->unk_02 = (s16)effect_x;

        y_jitter = rand() & 0x1F;
        effect_y = ((S_func_81875B38_3 *)source_obj->unk_08)->unk_06;
        y_dest = effect_ptr->unk_08;
        effect_y += y_jitter;
        y_bias = saved_y_offset - 0x10;
        effect_y += y_bias;
        y_dest->unk_06 = (s16)effect_y;

        z_jitter = rand();
        effect_obj = effect_ptr;
        effect_config = &D_80025028;
        ASM_USE2(effect_obj, effect_config);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        z_jitter &= 0x1F;
        effect_z = ((S_func_81875B38_3 *)source_obj->unk_08)->unk_0A;
        effect_ptr = (S_func_81875B38_2 *)((u8 *)effect_obj + 0x20);
        z_dest = effect_obj->unk_08;
        effect_z += z_jitter;
        z_bias = saved_z_offset - 0x10;
        effect_z += z_bias;
        z_dest->unk_0A = (s16)effect_z;
        ASM_KEEP(saved_x_offset);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_y_offset);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_z_offset);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ((S_func_81875B38_5 *)effect_ptr)->unk_14 = saved_property_34;
        ((S_func_81875B38_5 *)effect_ptr)->unk_32 = saved_property_52;
        ((S_func_81875B38_5 *)effect_ptr)->unk_34 = saved_property_52;
        func_8004491C(effect_obj, effect_config, z_dest);
        ASM_KEEP(saved_property_52);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_func_81875B38_5 *)effect_ptr)->unk_48 = rand() + 0x10000;
        ((S_func_81875B38_5 *)effect_ptr)->unk_08 = saved_property_28;
    }
}

/* MECHANISM: The 0x38 frame and s2/s3/s5 stack-argument roles come from guarded held locals.
   Separate random/value/destination/offset names reproduce each v0/v1/a0 coordinate live range.
   Anchoring a0/a1 before splitting the third random mask fixes the final word-47 schedule seam. */

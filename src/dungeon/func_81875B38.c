#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 D_80025028;
extern s32 D_80025278;

/* Spawn and initialize an effect at a randomly offset position relative to the source. */
void func_81875B38(
    void *source,
    s16 property_34,
    s32 property_28,
    s16 property_52,
    s32 x_offset,
    s32 y_offset,
    s32 z_offset)
{
    s32 saved_x_offset = x_offset;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *source_obj = source;
    register s16 saved_property_34 ASM_REG("$22") = property_34;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 saved_property_28 ASM_REG("$23") = property_28;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s16 saved_property_52 ASM_REG("$20") = property_52;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 saved_y_offset = y_offset;
    s32 saved_z_offset = z_offset;
    void *effect_ptr;
    s32 x_jitter;
    s32 y_jitter;
    s32 z_jitter;
    s32 x_bias;
    s32 y_bias;
    s32 z_bias;
    s32 effect_x;
    s32 effect_y;
    s32 effect_z;
    register void *effect_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *effect_config;
    void *x_dest;
    void *y_dest;
    void *z_dest;

    effect_ptr = func_8003FD64(0x211, source_obj);
    if (effect_ptr != NULL) {
        FIELD(effect_ptr, s32 *, 0x10) = (s32)&D_80025278;
        x_jitter = rand() & 0x1F;
        effect_x = FIELD(FIELD(source_obj, void **, 8), u16 *, 2);
        x_dest = FIELD(effect_ptr, void **, 8);
        effect_x += x_jitter;
        x_bias = saved_x_offset - 0x10;
        effect_x += x_bias;
        FIELD(x_dest, s16 *, 2) = (s16)effect_x;

        y_jitter = rand() & 0x1F;
        effect_y = FIELD(FIELD(source_obj, void **, 8), u16 *, 6);
        y_dest = FIELD(effect_ptr, void **, 8);
        effect_y += y_jitter;
        y_bias = saved_y_offset - 0x10;
        effect_y += y_bias;
        FIELD(y_dest, s16 *, 6) = (s16)effect_y;

        z_jitter = rand();
        effect_obj = effect_ptr;
        effect_config = &D_80025028;
        ASM_USE2(effect_obj, effect_config);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        z_jitter &= 0x1F;
        effect_z = FIELD(FIELD(source_obj, void **, 8), u16 *, 0xA);
        effect_ptr = (u8 *)effect_obj + 0x20;
        z_dest = FIELD(effect_obj, void **, 8);
        effect_z += z_jitter;
        z_bias = saved_z_offset - 0x10;
        effect_z += z_bias;
        FIELD(z_dest, s16 *, 0xA) = (s16)effect_z;
        ASM_KEEP(saved_x_offset);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_y_offset);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_z_offset);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        FIELD(effect_ptr, s16 *, 0x14) = saved_property_34;
        ASM_KEEP(saved_property_34);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        FIELD(effect_ptr, s16 *, 0x32) = saved_property_52;
        FIELD(effect_ptr, s16 *, 0x34) = saved_property_52;
        func_8004491C(effect_obj, effect_config, z_dest);
        ASM_KEEP(saved_property_52);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        FIELD(effect_ptr, s32 *, 0x48) = rand() + 0x10000;
        FIELD(effect_ptr, s32 *, 8) = saved_property_28;
        ASM_KEEP(saved_property_28);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
}

/* MECHANISM: The 0x38 frame and s2/s3/s5 stack-argument roles come from guarded held locals.
   Separate random/value/destination/offset names reproduce each v0/v1/a0 coordinate live range.
   Anchoring a0/a1 before splitting the third random mask fixes the final word-47 schedule seam. */

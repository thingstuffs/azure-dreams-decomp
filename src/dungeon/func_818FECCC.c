#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_818FECCC_0 {
    u8 pad_00[0x8];
    union { void * s; s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_818FECCC_0;   /* temp_s0 in func_818FECCC */

typedef struct S_818FECCC_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_818FECCC_1;   /* held_arg0 in func_818FECCC */

typedef struct S_818FECCC_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_818FECCC_2;   /* dest1 in func_818FECCC */

typedef struct S_818FECCC_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_818FECCC_3;   /* dest2 in func_818FECCC */

typedef struct S_818FECCC_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_818FECCC_4;   /* call_obj in func_818FECCC */

typedef struct S_818FECCC_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_818FECCC_5;   /* dest3 in func_818FECCC */

typedef struct S_818FECCC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818FECCC_6;   /* ((S_818FECCC_1 *)held_arg0)->unk_08 in func_818FECCC */



extern void *func_8003FD64(s32, void *);
extern s32 func_80069EF8(void);
extern void func_8004491C(void *, void *, void *);
extern u8 D_800241B0[];
extern u8 D_80024400[];

/* Creates an effect at randomized offsets from the source object's position. */
void func_818FECCC(
    void *source_obj,
    s16 param_34,
    s32 param_28,
    s16 param_52,
    s32 x_offset,
    s32 y_offset,
    s32 z_offset)
{
    void *source = source_obj;
    register s16 saved_param_34 ASM_REG("$21") = param_34;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 saved_param_28 ASM_REG("$23") = param_28;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 saved_param_52 ASM_REG("$22") = param_52;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 saved_y_offset = y_offset;
    s32 saved_z_offset = z_offset;
    void *effect_cursor;
    s32 x_random;
    s32 y_random;
    s32 z_random;
    s32 x_bias;
    s32 y_bias;
    s32 z_bias;
    s32 x_pos;
    s32 y_pos;
    s32 z_pos;
    u32 descriptor_page;
    register void *effect ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *effect_data;
    S_818FECCC_2 *x_dest;
    S_818FECCC_3 *y_dest;
    S_818FECCC_5 *z_dest;

    effect_cursor = func_8003FD64(0x211, source);
    if (effect_cursor != NULL) {
        descriptor_page = 0x80020000;
        ASM_KEEP(descriptor_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_818FECCC_0 *)effect_cursor)->unk_10 = descriptor_page + 0x4400;
        x_random = func_80069EF8() & 0x1F;
        x_pos = ((S_818FECCC_6 *)(((S_818FECCC_1 *)source)->unk_08))->unk_02;
        x_dest = ((S_818FECCC_0 *)effect_cursor)->unk_08.s;
        x_pos += x_random;
        x_bias = x_offset - 0x10;
        x_pos += x_bias;
        x_dest->unk_02 = (s16)x_pos;

        y_random = func_80069EF8() & 0x1F;
        y_pos = ((S_818FECCC_6 *)(((S_818FECCC_1 *)source)->unk_08))->unk_06;
        y_dest = ((S_818FECCC_0 *)effect_cursor)->unk_08.s;
        y_pos += y_random;
        y_bias = saved_y_offset - 0x10;
        y_pos += y_bias;
        y_dest->unk_06 = (s16)y_pos;

        z_random = func_80069EF8();
        effect = effect_cursor;
        effect_data = &D_800241B0;
        ASM_USE2(effect, effect_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        z_random &= 0x1F;
        z_pos = ((S_818FECCC_6 *)(((S_818FECCC_1 *)source)->unk_08))->unk_0A;
        effect_cursor = (u8 *)effect + 0x20;
        z_dest = ((S_818FECCC_4 *)effect)->unk_08;
        z_pos += z_random;
        z_bias = saved_z_offset + 0x10;
        z_pos += z_bias;
        z_dest->unk_0A = (s16)z_pos;
        ASM_KEEP(effect_cursor);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ((S_818FECCC_0 *)effect_cursor)->unk_14 = saved_param_34;
        ASM_KEEP(saved_param_34);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_818FECCC_0 *)effect_cursor)->unk_32 = saved_param_52;
        func_8004491C(effect, effect_data, z_dest);
        ASM_KEEP(saved_param_52);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_818FECCC_0 *)effect_cursor)->unk_08.u = saved_param_28;
        ASM_KEEP(saved_param_28);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
}

#include "common.h"

typedef struct S_800AEBC4_0_pre {
    s32 unk_00;
    u8 pad_04[0x1A24];
} S_800AEBC4_0_pre;   /* the 0x1A28 bytes before base0 in func_800AEBC4, addressed as base0[-1] */

typedef struct S_800AEBC4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_800AEBC4_0;   /* base0 in func_800AEBC4 */

typedef struct S_800AEBC4_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_800AEBC4_1;   /* arg2 in func_800AEBC4 */

typedef struct S_800AEBC4_2_pre {
    s32 unk_00;
    u8 pad_04[0x1A14];
} S_800AEBC4_2_pre;   /* the 0x1A18 bytes before base1 in func_800AEBC4, addressed as base1[-1] */

typedef struct S_800AEBC4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
} S_800AEBC4_2;   /* base1 in func_800AEBC4 */

typedef struct S_800AEBC4_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800AEBC4_3;   /* arg3 in func_800AEBC4 */

typedef struct S_800AEBC4_4 {
    s32 unk_00;
    union { void * s; s32 u; } unk_04;   /* accessed as both */
    void * unk_08;
} S_800AEBC4_4;   /* arg1 in func_800AEBC4 */

typedef struct S_800AEBC4_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
} S_800AEBC4_5;   /* (void *)(u32)word in func_800AEBC4 */

typedef struct S_800AEBC4_6 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
} S_800AEBC4_6;   /* tail in func_800AEBC4 */



extern s32 D_8002E5D8[4];
extern s32 D_8002E5E8[3];

/* Copies two templates into linked records and initializes position and offset vectors. */
void func_800AEBC4(void *vector_data, S_800AEBC4_4 *config, S_800AEBC4_1 *position_data, S_800AEBC4_3 *secondary_data,
                   s32 input_x, s32 input_y) {
    S_800AEBC4_6 *vectors = vector_data;
    u8 *template_base;
    u8 *data_ptr;
    s32 value;
    s32 x;
    register s32 y ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 *stack_args = __builtin_frame_address(0);

    ASM_KEEP(vectors);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
    template_base = (u8 *)D_8002E5D8 + 0x1A28;
#else
    template_base = (u8 *)0x80030000;
#endif
    ASM_KEEP(template_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    value = ((S_800AEBC4_0_pre *)template_base)[-1].unk_00;
#ifdef NON_MATCHING
    x = input_x;
#else
    x = stack_args[4];
#endif
    ASM_UNDEF(y);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
    y = input_y;
#else
    y = stack_args[5];
#endif
    ASM_KEEP(y);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    template_base -= 0x1A28;
    position_data->unk_00 = value;

    value = ((S_800AEBC4_0 *)template_base)->unk_04;
    position_data->unk_04 = value;

    value = ((S_800AEBC4_0 *)template_base)->unk_08;
    ASM_UNDEF(data_ptr);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
    data_ptr = (u8 *)D_8002E5E8 + 0x1A18;
#else
    data_ptr = (u8 *)0x80030000;
#endif
    ASM_KEEP(data_ptr);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    position_data->unk_08 = value;

    value = ((S_800AEBC4_0 *)template_base)->unk_0C;
    template_base = (u8 *)(u32)((S_800AEBC4_2_pre *)data_ptr)[-1].unk_00;
    data_ptr -= 0x1A18;
    position_data->unk_0C = value;
    secondary_data->unk_00 = (s32)(u32)template_base;

    value = ((S_800AEBC4_2 *)data_ptr)->unk_04;
    secondary_data->unk_04 = value;
    value = ((S_800AEBC4_2 *)data_ptr)->unk_08;
    secondary_data->unk_08 = value;

    config->unk_08 = secondary_data;
    ASM_UNDEF(data_ptr);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    data_ptr = secondary_data;
    ASM_KEEP(data_ptr);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    value = -0x400;
    config->unk_04.s = position_data;
    config->unk_00 = 0;
    ((S_800AEBC4_2 *)data_ptr)->unk_02 = (s16)value;

    value = config->unk_04.u;
    ((S_800AEBC4_5 *)((void *)(u32)value))->unk_08 = (s16)x;
    value = config->unk_04.u;
    ((S_800AEBC4_5 *)((void *)(u32)value))->unk_0A = (s16)y;
    value = config->unk_04.u;
    template_base = (u8 *)0x400;
    ((S_800AEBC4_5 *)((void *)(u32)value))->unk_0C = (s16)(u32)template_base;
    data_ptr = (u8 *)(u32)config->unk_04.u;
    value = 4;
    ((S_800AEBC4_2 *)data_ptr)->unk_0F = (u8)value;

    vectors->unk_0C = (s16)x;
    vectors->unk_0E = (s16)y;
    vectors->unk_10 = (s16)(u32)template_base;
    ASM_KEEP(template_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    value = -0x60;
    if (x < 0) {
        value = 0x30;
    }
    value -= x;
    vectors->unk_14 = (s16)value;
    value = -0x40 - y;
    vectors->unk_16 = (s16)value;
    value = -0x200;
    vectors->unk_18 = (s16)value;
}

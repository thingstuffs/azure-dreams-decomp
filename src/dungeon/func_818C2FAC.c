#include "common.h"

typedef unsigned long uptr;
typedef long long s64_local;
typedef union {
    s64_local all;
    struct {
        s32 hi;
        s32 lo;
    } part;
} product_pair;

#ifndef NULL
#define NULL 0
#endif


extern void func_800248C0(void) __attribute__((noreturn));
#ifndef NON_MATCHING
extern void func_800248CC(void) __attribute__((noreturn));
#else
extern void func_800248CC() __attribute__((noreturn));
#endif
extern s32 func_800249E4() __attribute__((noreturn));
extern s32 func_8003DB94();
extern void *func_8003FC64(s32);
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_80069EF8();

extern u8 D_80024710[];
extern u8 D_80045340[];
extern u8 D_800DEC70[];


typedef struct S_818C2FAC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818C2FAC_0;   /* (void *)obj in func_818C2FAC */

typedef struct S_818C2FAC_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_818C2FAC_1;   /* work in func_818C2FAC */

typedef struct S_818C2FAC_2 {
    u8 pad_00[0xC];
    volatile u8 unk_0C;
    volatile u8 unk_0D;
    volatile u8 unk_0E;
    u8 pad_0F[0x1];
    volatile u16 unk_10;
    s16 unk_12;
    volatile u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818C2FAC_2;   /* (void *)temp in func_818C2FAC */

/* Creates an effect with a selected appearance, random rotation, and a directional offset. */
s32 func_818C2FAC(void *owner, void *source_position, s32 direction)
{
    s32 variant_seed;
    s16 variant;
    s32 biased_seed;
    s32 random_value;
    s32 biased_random;
    s32 x_factor;
    s32 y_factor;
    s32 y_offset;
    s32 new_y;
    u16 render_flags;
    u16 render_mode;
    s64_local position_xy;
    product_pair product_bits;
    s32 quotient;
    s32 position_z;
    s32 position_word_3;
    s32 position_word_4;
    s32 position_word_5;
    uptr data_addr = (uptr)owner;
    uptr position_addr = (uptr)source_position;
    s32 object_type;
    register s32 offset_angle ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register uptr effect ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register uptr render_or_radius ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 render_arg_low ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    register u32 page_base_low ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 render_arg_high;
    register u32 page_base_high ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 scaled_radius;
    s32 divisor_reciprocal;
    S_818C2FAC_1 *effect_state;

    object_type = 0x212;
    ASM_KEEP_NV(object_type);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    offset_angle = direction;
    effect = (uptr)func_8003FC64(object_type);
    ASM_KEEP(position_addr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (effect != NULL) {

        ((S_818C2FAC_0 *)((void *)effect))->unk_10 = D_80024710;
        ((S_818C2FAC_0 *)((void *)effect))->unk_20 = (*(s32 *)((u8 *)((void *)data_addr) + 0));
        effect_state = (u8 *)effect + 0x20;
        effect_state->unk_04 = 0;
        effect_state->unk_06 = 0;

        render_or_radius = (uptr)((S_818C2FAC_0 *)((void *)effect))->unk_0C;
        render_flags = ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_14;
        ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_0E = 0x80;
        ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_0D = 0x80;
        ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_0C = 0x80;
        render_mode = ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_10;
        render_flags |= 0xC;
        render_mode |= 0x60;
        ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_14 = render_flags;
        render_flags |= 0x100;
        ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_10 = render_mode;
        ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_14 = render_flags;

        variant_seed = (*(s16 *)((u8 *)((void *)data_addr) + 0x12));
        biased_seed = variant_seed;
        if (variant_seed < 0) {
            biased_seed = variant_seed + 3;
        }
        variant = variant_seed - ((biased_seed >> 2) * 4);

        if (variant == 1) goto case1;
        if (variant >= 2) goto tree2;
        render_arg_low = (s32)render_or_radius;
        if (variant == 0) goto case0;
#ifndef NON_MATCHING
        ASM_KEEP(render_arg_low);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        page_base_low = 0x800E0000;
        ASM_PAGEBASE_PIN(page_base_low);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800248CC();
#else
        func_800248CC((void *)render_or_radius, 0x800E0000);
#endif
    tree2:
        if (variant == 2) goto case2;
        render_arg_high = (s32)render_or_radius;
        if (variant == 3) goto case3;
#ifndef NON_MATCHING
        ASM_KEEP(render_arg_high);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        page_base_high = 0x800E0000;
        ASM_PAGEBASE_PIN(page_base_high);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800248CC();
#else
        func_800248CC((void *)render_or_radius, 0x800E0000);
#endif
    case0:
        {
            s32 appearance_id;
            appearance_id = 0x7DCF;
            ASM_TAILSLOT_PIN(appearance_id);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800248C0();
        }
    case1:
        {
            s32 appearance_id;
            appearance_id = 0x7E00;
            ASM_TAILSLOT_PIN(appearance_id);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800248C0();
        }
    case2:
        {
            s32 appearance_id;
            appearance_id = 0x7E01;
            ASM_TAILSLOT_PIN(appearance_id);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800248C0();
        }
    case3:
        ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_12 = 0x7E02;
        ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        {
            s32 render_arg;
            u8 *render_table;
            render_arg = (s32)render_or_radius;
            render_table = D_800DEC70;
            func_8003DB94(render_arg, render_table, 0);
        }
        random_value = func_80069EF8();
        biased_random = random_value;
        if (random_value < 0) {
            biased_random = random_value + 0xFFF;
        }
        ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_1A = random_value - ((biased_random >> 12) << 12);
        ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_1E = 0x1000;
        ((S_818C2FAC_2 *)((void *)render_or_radius))->unk_1C = 0x1000;
        func_8004491C((void *)effect, D_80045340);

        data_addr = (uptr)((S_818C2FAC_0 *)((void *)effect))->unk_08;
        position_xy = (*(s64_local *)((u8 *)((void *)position_addr) + 0));
        position_z = (*(s32 *)((u8 *)((void *)position_addr) + 8));
        position_word_3 = (*(s32 *)((u8 *)((void *)position_addr) + 0xC));
        (*(s64_local *)((u8 *)((void *)data_addr) + 0)) = position_xy;
        (*(s32 *)((u8 *)((void *)data_addr) + 8)) = position_z;
        (*(s32 *)((u8 *)((void *)data_addr) + 0xC)) = position_word_3;
        position_word_4 = (*(s32 *)((u8 *)((void *)position_addr) + 0x10));
        position_word_5 = (*(s32 *)((u8 *)((void *)position_addr) + 0x14));
        (*(s32 *)((u8 *)((void *)data_addr) + 0x10)) = position_word_4;
        (*(s32 *)((u8 *)((void *)data_addr) + 0x14)) = position_word_5;

        random_value = func_80069EF8();
        divisor_reciprocal = 0x78787879;
        render_or_radius = (uptr)random_value;
        ASM_USE_NV(divisor_reciprocal);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        offset_angle = (s16)offset_angle;
        render_or_radius = (uptr)((s32)render_or_radius % 17 + 0x20);
        x_factor = func_800644B8(offset_angle) >> 4;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        render_or_radius = (uptr)(s16)(s32)render_or_radius;
        {
            s32 x_offset;
            scaled_radius = x_factor * (s32)render_or_radius;
            x_offset = scaled_radius << 8;
            (*(s32 *)((u8 *)((void *)data_addr) + 0)) += x_offset;
        }
        {
            register s32 effect_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            y_factor = func_80064584(offset_angle) >> 4;
            effect_result = (s32)effect;
            scaled_radius = y_factor * (s32)render_or_radius;
            y_offset = scaled_radius << 8;
            new_y = (*(s32 *)((u8 *)((void *)data_addr) + 4)) + y_offset;
            ASM_KEEP(effect_result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            (*(s32 *)((u8 *)((void *)data_addr) + 4)) = new_y;
            func_800249E4(y_offset);
        }

    }
    {
        s32 result;
        result = 0;
        return result;
    }
}

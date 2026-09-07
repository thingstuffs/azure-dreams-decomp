#include "common.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct Copy24 {
    s32 word[6];
} Copy24;

extern void *func_8003FD64();
extern s32 func_80069EF8();
extern void func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();

extern s32 D_80024710;
extern s32 D_80025B10;
extern s32 D_80045340;


typedef struct S_80024804_0 {
    u8 pad_00[0x8];
    Copy24 * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80024804_0;   /* obj in func_80024804 */

typedef struct S_80024804_1 {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
    u16 unk_10;
} S_80024804_1;   /* held_arg0 in func_80024804 */

typedef struct S_80024804_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024804_2;   /* part in func_80024804 */

typedef struct S_80024804_3 {
    u8 pad_00[0xE];
    union { u16 u; s16 s; } unk_0E;   /* accessed as both */
    union { u16 u; s16 s; } unk_10;   /* accessed as both */
} S_80024804_3;   /* work in func_80024804 */

/* Creates an effect with scaled parts and offsets it from the origin using the source orientation. */
void *func_80024804(void *source, Copy24 *origin, s16 size_step)
{
    register void *result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    void *source_data = source;
    Copy24 *base_position = origin;
    register s16 saved_step ASM_REG("$16") = size_step;   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *effect;
    S_80024804_2 *part;
    Copy24 *position;
    u8 *effect_state;
    register s32 scale_step ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    s32 direction_factor;
    register s32 scaled_factor ASM_REG("$16");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 random_value;
    s16 part_scale;
    s32 alloc_kind;
    void *alloc_source;
    register s32 step_word ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    alloc_kind = 0x212;
    alloc_source = (u8 *)source_data - 0x20;
    ASM_KEEP_NV(alloc_kind);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_NV(source_data);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP_NV(base_position);   /* MATCH pin: retail schedule: same instructions, different order without it */
    effect = func_8003FD64(alloc_kind, alloc_source);
    if (effect == NULL) {
        goto null_result;
    }

    ((S_80024804_0 *)effect)->unk_10 = &D_80024710;
    ((S_80024804_0 *)effect)->unk_20 = ((S_80024804_1 *)source_data)->unk_00;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    step_word = (s32)saved_step << 16;
    scale_step = step_word >> 16;
    part = ((S_80024804_0 *)effect)->unk_0C;
    part->unk_0D = -0x60 - (scale_step << 6);
    part->unk_0C = -0x60 - (scale_step << 6);
    part->unk_0E = 0xC0;
    part->unk_12 = 0x7DCF;
    part->unk_08 = &D_80025B10;

    part->unk_14 |= 0x000C;
    part->unk_10 |= 0x0020;
    part->unk_14 |= 0x0100;

    random_value = func_80069EF8();
    effect_state = (u8 *)effect + 0x20;
    part->unk_1A = random_value % 0x1000;

    part_scale = (scale_step << 8) + 0x500;
    part->unk_1E = part_scale;
    part->unk_1C = part_scale;
    func_8004491C(effect, &D_80045340);

    position = ((S_80024804_0 *)effect)->unk_08;
    *position = *base_position;

    ((S_80024804_3 *)effect_state)->unk_0E.u = ((S_80024804_1 *)source_data)->unk_0E;
    ((S_80024804_3 *)effect_state)->unk_10.u = ((S_80024804_1 *)source_data)->unk_10;

    direction_factor = func_800644B8(((S_80024804_3 *)effect_state)->unk_0E.s);
    scale_step += 2;
    position->word[0] -= (scaled_factor = direction_factor >> 4) *
        (func_800644B8(((S_80024804_3 *)effect_state)->unk_10.s) >> 4) * scale_step * 8;

    direction_factor = func_800644B8(((S_80024804_3 *)effect_state)->unk_0E.s);
    position->word[1] -= (scaled_factor = direction_factor >> 4) *
        (func_80064584(((S_80024804_3 *)effect_state)->unk_10.s) >> 4) * scale_step * 8;

    position->word[2] -=
        ((func_80064584(((S_80024804_3 *)effect_state)->unk_0E.s) >> 4) * scale_step) << 11;
    result = effect;
    goto return_result;

null_result:
    result = NULL;

return_result:
    return result;
}

#include "common.h"

typedef struct S_81984AF4_0 {
    s32 unk_00;
    union { s8 s; volatile u8 u; } unk_04;   /* accessed as both */
    u8 pad_05[0x3];
    void * unk_08;
    u8 pad_0C[0x8];
    union { volatile u16 s; u16 u; } unk_14;   /* accessed as both */
} S_81984AF4_0;   /* obj in func_81984AF4 */

typedef struct S_81984AF4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_81984AF4_1;   /* owner in func_81984AF4 */



extern void func_80026350(void) __attribute__((noreturn));
extern void func_800263B8(void) __attribute__((noreturn));

/* Resolve the current entry, apply an index step, and enforce the index bounds. */
void func_81984AF4(void *object, s16 *index_step, s32 min_index, s32 max_index) {
    s16 step;
    s32 shifted_index;
    u32 clamp_flags;
    u32 next_index;
    u8 index;
    S_81984AF4_0 *obj = object;
    s32 initial_index = obj->unk_04.s;
    S_81984AF4_1 *owner = obj->unk_08;

    obj->unk_00 =
        owner->unk_0C + (initial_index * 22);
    step = *index_step;
    if (step > 0) {
        next_index = obj->unk_04.u + 1;
        ASM_TAILSLOT_PIN_TIED(next_index);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80026350();
    }
    if (step < 0) {
        obj->unk_04.u =
            obj->unk_04.u - 1;
    }
    index = (u8)obj->unk_04.s;
    shifted_index = index << 24;
    if ((s8)index < (s16)min_index) {
        clamp_flags = obj->unk_14.s | 0x4000;
        obj->unk_04.s = min_index;
        ASM_TAILSLOT_PIN_TIED(clamp_flags);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800263B8();
    }
    if ((s8)index > (s16)max_index) {
        clamp_flags = obj->unk_14.s | 0x4000;
        obj->unk_04.s = max_index;
        ASM_TAILSLOT_PIN_TIED(clamp_flags);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800263B8();
    }
    obj->unk_14.u &= 0xBFFF;
}

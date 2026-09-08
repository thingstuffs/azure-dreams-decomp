#include "common.h"



typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800247B4(void) __attribute__((noreturn));
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64(s32);
extern M2C_UNK func_8004491C();
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern M2C_UNK D_80024330[];
extern M2C_UNK D_80045340[];
extern M2C_UNK D_800DEAE0[];

typedef struct S_8185CE28_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8185CE28_0;   /* temp_v0 in func_8185CE28 */

typedef struct S_8185CE28_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
} S_8185CE28_1;   /* temp_s1 in func_8185CE28 */

typedef struct S_8185CE28_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8185CE28_2;   /* arg1 in func_8185CE28 */

typedef struct S_8185CE28_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8185CE28_3;   /* temp_s0 in func_8185CE28 */

/* Creates an effect at an indexed radial offset from the supplied position. */
s32 func_8185CE28(s32 effect_param, S_8185CE28_2 *position, s16 effect_index)
{
    s16 phase_index;
    s32 phase_step;
    S_8185CE28_3 *component;
    S_8185CE28_1 *state;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        phase_step = effect_index * 3;
        ((S_8185CE28_0 *)effect)->unk_20 = effect_param;
        state = effect + 0x20;
        ((S_8185CE28_0 *)effect)->unk_10 = D_80024330;
        phase_index = phase_step % 8;
        state->unk_1C = phase_index << 9;
        state->unk_20 = 0x20;
        state->unk_1E = 0;
        state->unk_22 = -8;
        state->unk_24 = phase_index;
        state->unk_06 = position->unk_02;
        state->unk_0A = position->unk_06;
        state->unk_0E = position->unk_0A;
        component = ((S_8185CE28_0 *)effect)->unk_0C;
        component->unk_0E = 0x80;
        component->unk_0D = 0x80;
        component->unk_0C = 0x80;
        func_8003DB94(component, D_800DEAE0, 0);
        component->unk_1E = 0x1800;
        component->unk_1C = 0x1800;
        component->unk_12 = 0x7E0B;
        component->unk_14 |= 0xC;
        component->unk_10 |= 0x20;
        component->unk_14 |= 0x100;
        func_8004491C(effect, D_80045340);
        component = ((S_8185CE28_0 *)effect)->unk_08;
        component->unk_02 = state->unk_06 +
            ((func_800644B8(state->unk_1C) >> 4) *
             state->unk_20 >> 8);
        component->unk_06 = state->unk_0A +
            ((func_80064584(state->unk_1C) >> 4) *
             state->unk_20 >> 8);
        {
            u16 final_z = state->unk_0E;
#ifndef NON_MATCHING
            __asm__ __volatile__("" : : : "$2");
#endif
            {
                register s32 v0pin ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                v0pin = (s32)effect;
                ASM_KEEP(v0pin);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                component->unk_0A = final_z - 8;
                func_800247B4();
            }
        }
    }
    {
        register s32 zero_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        zero_v0 = 0;
        ASM_KEEP(zero_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        return zero_v0;
    }
}

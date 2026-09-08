#include "common.h"

typedef struct S_8195EB88_0_pre {
    u16 unk_00;
} S_8195EB88_0_pre;   /* the 0x2 bytes before arg0 in func_8195EB88, addressed as arg0[-1] */

typedef struct S_8195EB88_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0x30];
    u16 unk_40;
    u16 unk_42;
    union { s16 s; u16 u; } unk_44;   /* accessed as both */
    u8 pad_46[0x2];
    union { s16 s; u16 u; } unk_48;   /* accessed as both */
    s16 unk_4A;
} S_8195EB88_0;   /* arg0 in func_8195EB88 */

typedef struct S_8195EB88_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_8195EB88_1;   /* temp_s0 in func_8195EB88 */

typedef struct S_8195EB88_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195EB88_2;   /* arg1 in func_8195EB88 */

typedef struct S_8195EB88_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8195EB88_3;   /* temp_a0_2 in func_8195EB88 */

typedef struct S_8195EB88_4 {
    u8 pad_00[0xC];
    union { u8 u8; u32 u32; } unk_0C;   /* accessed as both */
} S_8195EB88_4;   /* arg2 in func_8195EB88 */

typedef struct S_8195EB88_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8195EB88_5;   /* ((S_8195EB88_0 *)arg0)->unk_0C in func_8195EB88 */



extern s32 func_8003DE58(void *, void *, void *, s32);
extern void func_80024414(void) __attribute__((noreturn));
extern s32 func_80027204(void *);
extern void func_8004491C(void *, void *);
extern void func_80024520(void) __attribute__((noreturn));

typedef struct CounterView {
    u16 value;
    u16 pad[5];
} CounterView;

typedef struct FlagsView {
    s32 value;
    s32 pad[2];
} FlagsView;

extern CounterView D_80027330;
extern u8 D_80045340[];
extern FlagsView D_800814A0;

/* Updates the effect position, brightens and fades its primitive, and marks completion. */
void func_8195EB88(void *effect, S_8195EB88_2 *position, S_8195EB88_4 *primitive)
{
    s16 phase;
    u16 phase_value;
    S_8195EB88_3 *base_position;
    S_8195EB88_1 *source_state;

    D_80027330.value = D_80027330.value + 1;
    phase = ((S_8195EB88_0 *)effect)->unk_48.s;
    phase_value = ((S_8195EB88_0 *)effect)->unk_48.u;

    if (phase == 0) {
        source_state = ((S_8195EB88_5 *)(((S_8195EB88_0 *)effect)->unk_0C))->unk_0C;
        if (((S_8195EB88_0 *)effect)->unk_4A == 0) {
            if (func_8003DE58(source_state->unk_08, source_state,
                              (u8 *)effect + 0x40, 0) != 0) {
                ((S_8195EB88_0 *)effect)->unk_4A = 1;
                func_80024414();
            }
            if (source_state->unk_14 & 0x8000) {
                ((S_8195EB88_0 *)effect)->unk_4A = 1;
                ((S_8195EB88_0 *)effect)->unk_44.s = -0x40;
            }
            if (((S_8195EB88_0 *)effect)->unk_4A == 0) {
                goto end;
            }
        }

        base_position = ((S_8195EB88_5 *)(((S_8195EB88_0 *)effect)->unk_0C))->unk_08;
        position->unk_02 =
            base_position->unk_02 + ((S_8195EB88_0 *)effect)->unk_40;
        position->unk_06 =
            base_position->unk_06 + ((S_8195EB88_0 *)effect)->unk_42;
        position->unk_0A =
            base_position->unk_0A + ((S_8195EB88_0 *)effect)->unk_44.u;
        if (func_80027204(position) != 0) {
            func_8004491C((u8 *)effect - 0x20, D_80045340);
            ((S_8195EB88_0 *)effect)->unk_48.u = ((S_8195EB88_0 *)effect)->unk_48.u + 1;
            func_80024520();
        }
    } else if (phase == 1) {
        if (primitive->unk_0C.u8 < 0xC0) {
            primitive->unk_0C.u32 += 0x202020;
            func_80024520();
        }
        ((S_8195EB88_0 *)effect)->unk_48.u = phase_value + 1;
        func_80024520();
    } else if (phase == 2) {
        primitive->unk_0C.u32 += 0xFFEFEFF0;
        if (primitive->unk_0C.u8 == 0) {
            ((S_8195EB88_0_pre *)effect)[-1].unk_00 |= 0x8000;
            D_800814A0.value |= 0x8000;
        }
    }
end:
    ;
}

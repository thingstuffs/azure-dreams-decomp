#include "common.h"


typedef void (*Callback)(void *, s32);

extern void func_800B180C(void *, s32);


typedef struct S_800B1890_0 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_800B1890_0;   /* temp_v1 in func_800B1890 */

/* Lowers the state's value toward the target, or snaps to it and switches callbacks. */
void func_800B1890(void *object) {
    S_800B1890_0 *state;
    s32 target_value;
    s32 current_value;
    u16 current_bits;
    s32 adjustment;

    state = (*(void * *)((u8 *)object + 0x3C));
    target_value = (*(s32 *)((u8 *)object + 4));
    current_value = state->unk_08.s;
    current_bits = state->unk_08.u;
    if (target_value < current_value) {
        adjustment = current_value + 4;
        adjustment = target_value - adjustment;
        adjustment >>= 2;
        state->unk_08.s = current_bits + adjustment;
    } else {
        state->unk_08.u = (*(u16 *)((u8 *)object + 4));
        (*(volatile Callback *)((u8 *)object + -0x10)) = func_800B180C;
    }

    func_800B180C(object, current_value);
}

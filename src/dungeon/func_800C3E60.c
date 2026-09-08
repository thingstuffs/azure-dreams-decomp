#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C95C0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800C95C0_0;   /* arg1 in func_800C95C0 */

typedef struct S_800C95C0_1_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_800C95C0_1_pre;   /* the 0x8 bytes before state in func_800C95C0, addressed as state[-1] */


extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800C96E8(void *, void *);

/* Updates each linked state from its input values and delta using scratchpad memory. */
s32 func_800C95C0(void *initial_state, void *input_values, s16 *initial_delta) {
    void *state = initial_state;
    s16 *delta = initial_delta;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *next_node;

    for (;;) {
        *(u16 *)(scratch + 0) = ((S_800C95C0_0 *)input_values)->unk_02;
        *(u16 *)(scratch + 2) = (*(u16 *)((u8 *)input_values + 6));
        *(u16 *)(scratch + 4) = (*(u16 *)((u8 *)input_values + 0xA));
        *(s32 *)(scratch + 0xC0) =
            func_80065420((void *)scratch, (void *)(scratch + 0xB8),
                           (void *)(scratch + 0x90), (void *)(scratch + 0x94)) -
            *(s16 *)((u8 *)delta + 6);
        func_800C96E8(state, scratch);
        next_node = ((S_800C95C0_1_pre *)state)[-1].unk_00;
        if (next_node == NULL)
            break;
        state = next_node + 0x20;
        input_values = *(u8 **)(next_node + 8);
        delta = *(u8 **)(next_node + 0xC);
    }
    return 0;
}

#include "common.h"

/* Unaligned 4-byte copy → lwl/lwr + swl/swr */
typedef struct {
    u32 v;
} __attribute__((packed)) UA32;

extern UA32 D_80028064;

s32 func_80025E54();
s32 func_80025ECC(void);
void func_80025F0C(void *arg0, s32 arg1);
void func_80025FFC(void *arg0, s32 arg1);

/* Copies the initial word into the buffer and initializes state for the selected mode. */
void func_80026128(UA32 *buffer, s32 config, s32 mode) {
    u8 *state_base;
    s16 is_mode_two;

    *buffer = D_80028064;
    state_base = (u8 *)0x80010000;
    is_mode_two = (mode == 2);
    *(s16 *)(state_base + 0x208) = is_mode_two;
    *(s16 *)(state_base + 0x20A) = is_mode_two;
    *(s32 *)(state_base + 0x224) = *(u32 *)(state_base + 0x2D5C);
    *(s32 *)(state_base + 0x230) = func_80025E54();
    *(s32 *)(state_base + 0x228) = func_80025ECC();
    func_80025F0C(buffer, config);
    func_80025FFC(buffer, config);
}

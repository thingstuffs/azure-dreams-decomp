#include "common.h"

typedef struct {
    u8 pad0[0x24];
    s32 unk24;
    s32 unk28;
} S_80050EA8_sub;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[0x0C];
    S_80050EA8_sub unk20;
} S_80050EA8;

extern void func_80044A50(S_80050EA8 *a0);
extern void func_8004FE78(void *a0);

/* Move a pending value into a slot, run the two update helpers, then
 * clear the second helper's input field. */
void func_80050EA8(S_80050EA8 *a0)
{
    s32 v0 = a0->unk10;
    S_80050EA8_sub *sub = &a0->unk20;

    if (v0 != 0) {
        sub->unk24 = v0;
        a0->unk10 = 0;
    }
    func_80044A50(a0);
    func_8004FE78((void *)sub->unk28);
    sub->unk28 = 0;
}

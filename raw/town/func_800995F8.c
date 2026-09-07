#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} Input;

typedef struct {
    u8 pad[0x24];
    s32 unk24;
    u8 pad28[8];
    s32 unk30;
} State;

extern s16 D_8006ADD4[];
extern State D_800FE520;
extern void func_80096DC0(State *, Input *);

void func_80096D58(Input *arg0) {
    register Input *input ASM_REG("$5");
    register State *page ASM_REG("$4");
    s32 value;

    if (D_8006ADD4[0] == 12) {
        return;
    }

    input = arg0;
    ASM_KEEP(input);
    value = input->unk4;
    if (value <= 0x03FFFFFF) {
        register State *state ASM_REG("$2") = &D_800FE520;

        page = (State *)0x80100000;
        ASM_KEEP(page);
        state->unk24 = 0x0F500000;
        state->unk30 = 0x10B00000;
        func_80096DC0(page, input);
        return;
    }
    page = (State *)0x80100000;
    ASM_KEEP(page);
    page = (State *)((u8 *)page - 0x1AE0);
    page->unk24 = 0x13500000 - value;
    page->unk30 = input->unk4 + 0x0CB00000;
}

/* MECHANISM: Frameless leaf; a guarded post-guard $a1 assignment puts the input copy in the beq delay slot.
   Duplicated kept $a0=0x80100000 values hoist one page lui into the threshold-branch delay slot.
   The low arm tail-calls with that raw page; the high arm applies -0x1AE0 while pinned $v0 holds the state. */

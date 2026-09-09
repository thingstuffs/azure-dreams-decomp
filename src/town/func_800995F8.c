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

void func_80096D58(Input *arg0) {
    register Input *input ASM_REG("$5"); /* MATCH: Preserve retail's input register after removing the internal-label call. */
    State *page;
    s32 value;

    if (D_8006ADD4[0] == 12) {
        return;
    }

    input = arg0;
    ASM_KEEP(input);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    value = input->unk4;
    if (value <= 0x03FFFFFF) {
        State *state = &D_800FE520;

        page = (State *)0x80100000;
        state->unk24 = 0x0F500000;
        state->unk30 = 0x10B00000;
    } else {
        page = (State *)0x80100000;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        page = (State *)((u8 *)page - 0x1AE0);
        page->unk24 = 0x13500000 - value;
        page->unk30 = input->unk4 + 0x0CB00000;
    }
    ASM_SCHED_BARRIER(); /* MATCH: Keep both arms sharing retail's return through an internal jump. */
}

/* MECHANISM: Frameless leaf; a guarded post-guard $a1 assignment puts the input copy in the beq delay slot.
   Duplicated kept $a0=0x80100000 values hoist one page lui into the threshold-branch delay slot.
   The low arm tail-calls with that raw page; the high arm applies -0x1AE0 while pinned $v0 holds the state. */

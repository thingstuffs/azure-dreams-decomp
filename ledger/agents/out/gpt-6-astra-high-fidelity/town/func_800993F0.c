#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} State;

M2C_UNK func_80096A90();                 /* extern */
extern s16 D_8006ADD6;
extern s32 D_800FE508[4];
extern State D_800FE520;

void func_80096B50(s32 *arg0) {
    s16 temp_v1;
    register State *temp_v0 ASM_REG("$2"); /* MATCH: both arms retain the shared record base in v0. */
    s32 *var_s0;
    register s32 tail_value ASM_REG("$3"); /* MATCH: retail merges the tail value in v1. */

    var_s0 = arg0;
    D_800FE508[0] = 0x1FFFFFFF;
    D_800FE508[2] = 0x1FFFFFFF;
    D_800FE508[1] = 0;
    D_800FE508[3] = 0;
    if (*var_s0 != 0) {
        do {
            func_80096A90(D_800FE508, *var_s0);
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            var_s0++;
        } while (*var_s0 != 0);
    }
    temp_v1 = D_8006ADD6;
    if (temp_v1 == 8) {
        D_800FE520.unk0 = 0x03000000;
        ASM_SCHED_BARRIER(); /* MATCH: initialize the shared base after the first store. */
        temp_v0 = &D_800FE520;
        temp_v0->unk4 = 0x04000000;
        ASM_SCHED_BARRIER(); /* MATCH: keep the merged value in the jump delay slot. */
        tail_value = 0x02A00000;
        goto tail;
    }
    if (temp_v1 == 0xB) {
        D_800FE520.unk0 = 0;
        ASM_SCHED_BARRIER(); /* MATCH: initialize the shared base after the first store. */
        temp_v0 = &D_800FE520;
        temp_v0->unk4 = 0x04A00000;
        ASM_SCHED_BARRIER(); /* MATCH: keep the tail value after the arm stores. */
        tail_value = 0x03B00000;
    tail:
        temp_v0->unkC = tail_value;
        temp_v0->unk8 = 0;
        temp_v0->unk10 = 0x80000000;
        return;
    }
    D_800FE520.unk0 = 0x80000000;
}

/* MECHANISM: The 0x20-byte frame naturally saves s0/s1 by holding the input cursor and 0x8010 page across calls.
   Direct array/State fields recover the hi/lo bases and five-word tail record; a direct halfword read rematerializes its page.
   Post-call/pre-tail fences fix scheduling, while a v1-scoped tail pin sinks 0x02A00000 into the shared-tail jump slot. */

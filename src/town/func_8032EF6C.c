#include "common.h"

typedef void (*EntryCallback)(void *);

extern void func_8001941C(void *, void *, s32);

typedef union PackedWord {
    u32 word;
    struct {
        u16 lo;
        u16 hi;
    } half;
} PackedWord;

typedef struct DataRecord {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    PackedWord unkC;
    u32 unk10;
} DataRecord;

void *func_8001976C(void *arg0, void *arg1, s32 arg2, s32 arg3)
{
    register DataRecord *var_s0 ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u8 *var_s1 ASM_REG("$17");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 var_s2;
    u32 var_s3;
    u32 var_s4;
    u32 var_s5;
    register u32 var_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_v1;
    u32 var_a0;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    var_s0 = arg0;
    var_s1 = arg1;
    var_s2 = arg2;
    var_v1 = var_s2 >> 8;
    var_v0 = var_s2 & 0x3FFF0000;
    var_a0 = 0xC0000010;
    var_s5 = var_v0 | var_a0;
    var_v1 &= 0x3F;
    var_s4 = var_v1 << 24;
    var_s3 = (arg3 & 0xFF) << 16;
    var_a0 = (u32)var_s0;
    do {
        func_8001941C((void *)var_a0, var_s1, 5);
        var_v0 = 0xC0000000;
        if (var_s2 != 0) {
            var_s0->unk8 = var_s5;
        }
        var_v0 = var_s3 | var_v0;
        var_v0 = var_s4 | var_v0;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        var_v1 = var_s0->unkC.half.lo;
        var_v0 = var_v0 | var_v1;
        var_s0->unkC.word = var_v0;
        if (*var_s1 != 0) {
            (*(EntryCallback *)(var_s1 + 8))(var_s0);
            var_s1 += 0x14;
        } else {
            var_s0++;
            var_s1 += 0x14;
        }
        var_a0 = (u32)var_s0;
    } while (*(var_s1 - 0x13) != 0x80);
    ASM_KEEP(var_s2);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(var_s3);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(var_s4);   /* MATCH pin: retail register colouring depends on it */
    ASM_KEEP(var_s5);   /* MATCH pin: retail schedule: same instructions, different order without it */
    return var_s0;
}

/* MECHANISM: Guarded pins encode s0-s5 and v0/v1/a0; a seam fence preserves
   the second OR before the lhu, including its required load-delay nop.
   The callback arm rejoins the bottom-tested loop instead of tail-calling. */

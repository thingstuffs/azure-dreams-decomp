#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))

#ifdef NON_MATCHING
#define LOCAL_ASM_REG(reg)
#define LOCAL_ASM_KEEP(var) ((void)0)
#else
#define LOCAL_ASM_REG(reg) asm(reg)
#define LOCAL_ASM_KEEP(var) ASM_KEEP(var)
#endif

extern void func_800B09EC(void *arg0, s32 arg1);
extern void func_800B0BE8(void);

void func_800B0BD0(void *arg0) {
    register void *held LOCAL_ASM_REG("$17");
    register s32 i LOCAL_ASM_REG("$16");
    register s32 scratch LOCAL_ASM_REG("$2");
    s32 base;
    s32 value;

    held = arg0;
    i = 0;
    LOCAL_ASM_KEEP(held);
    LOCAL_ASM_KEEP(i);
    scratch = FIELD(held, s32, 0x10);
    base = scratch * 5;
    scratch = FIELD(held, s32, 0xC);
    value = base + i;
    scratch = value < scratch;
    if (scratch == 0) {
        scratch = i < 5;
        goto test;
    }
    scratch = i < 5;
    func_800B09EC(held, value);
    i++;
    scratch = i < 5;
    if (scratch == 0) {
        goto test;
    }
    func_800B0BE8();
    return;

loop:
    base = FIELD(held, s32, 0xCC);
    scratch += base;
    scratch = FIELD(scratch, s32, 0x24);
    ASM_SCHED_BARRIER();
    i++;
    *(s32 *)scratch = 0;
    scratch = i < 5;
test:
    LOCAL_ASM_KEEP(scratch);
    if (scratch != 0) {
        scratch = i * 4;
        goto loop;
    }
done:
    ASM_USE(i);
}

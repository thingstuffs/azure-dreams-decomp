#include "common.h"

typedef struct S_800B0BD0_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0xB8];
    s32 unk_CC;
} S_800B0BD0_0;   /* held in func_800B0BD0 */

typedef struct S_800B0BD0_1 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_800B0BD0_1;   /* scratch in func_800B0BD0 */



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
    scratch = ((S_800B0BD0_0 *)held)->unk_10;
    base = scratch * 5;
    scratch = ((S_800B0BD0_0 *)held)->unk_0C;
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
    base = ((S_800B0BD0_0 *)held)->unk_CC;
    scratch += base;
    scratch = ((S_800B0BD0_1 *)scratch)->unk_24;
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
}

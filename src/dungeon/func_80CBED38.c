#include "common.h"
#include "m2c_compat.h"

s32 func_800AB378(void);
s32 func_800AD9B4(s32, s32);
extern u8 D_80170F20;
extern u8 D_80173B98;

typedef struct S_80172538_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x17];
    u8 unk_A7;
} S_80172538_0;   /* object in func_80172538 */

void func_80172538(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    S_80172538_0 *object = arg0;
    s32 call_arg0 = arg2;
    s32 call_arg1 = arg3;
    void *value;

    if ((func_800AB378() != 0) &&
        ((func_800AD9B4(call_arg0, call_arg1) << 0x10) > 0)) {
        if (object->unk_A7 != 0) {
            value = &D_80173B98;
        } else {
            value = &D_80170F20;
        }
        object->unk_8C = value;
    }
    ASM_KEEP(object);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(call_arg0);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP(call_arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
}

/* MECHANISM: The true-name four-argument ABI pins arg0/arg2/arg3 to s0/s1/s2; final-use
   ASM_KEEP barriers leave the s2 copy free for the first jal delay slot.  A pointer-valued
   if/else reproduces the two global-address arms and their shared store. */

#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FC64(s32 arg0);
extern void *func_8003FD64(s32 arg0, s32 arg1);
extern void func_8004DCE0(s32 arg0);
extern void func_8004DCEC(void);
extern s32 func_800AE360(void);
extern s32 func_800AE3F8(void);
extern void func_800AE414(void *arg0);
extern s32 func_800B0214(void *arg0);
extern s32 func_800B0718(void);
extern s32 func_800B1BEC(void *arg0, s32 arg1, s32 arg2);
extern u8 D_8001029C[];

s32 func_800AE324(s32 arg0) {
    register s32 held_arg ASM_REG("$18") = arg0;
    register void *object ASM_REG("$17");
    void *state;
    void *initializer;
    register s32 count ASM_REG("$3");
    s32 result;

    if (held_arg != 0) {
        object = func_8003FD64(0, held_arg);
        ASM_TAILSLOT_PIN(object);
        return func_800AE360();
    }

    ASM_KEEP(held_arg);
    object = func_8003FC64(0);
    if (object != 0) {
        initializer = (void *)0x8001029C;
        state = (u8 *)object + 0x20;
        FIELD(state, void *, 0x20) = initializer;
        FIELD(state, s32, 0x1C) = func_800B0718();
        ASM_SCHED_BARRIER();
        count = FIELD(state, s32, 0x1C);
        ASM_KEEP(count);
        FIELD(state, s32, 0x74) = held_arg;
        if (count != 0) {
            FIELD(state, s32, 0x14) = (count - 1) / 10;
        }
        func_8004DCE0(1);
        func_8004DCEC();
        result = func_800B0214(object);
        FIELD(object, s32, 0x20) = result;
        if (result == 0) {
            goto failure;
        }
        result = func_800B1BEC(object, 0x48, -0x5C);
        FIELD(state, s32, 8) = result;
        if (result == 0) {
            goto failure;
        }
    }
cleanup:
    func_800AE3F8();
    return (s32)object;
failure:
    func_800AE414(state);
    return 0;
}

/* MECHANISM: The 0x20 frame holds selector/object/state in s2/s1/s0; the CFG uses two
   LEAD22 sibcall tails. Pinning only the post-fence count to v1 makes the call result
   store from v0 first, then copy v0 to v1, closing the word-21 code-motion residue. */

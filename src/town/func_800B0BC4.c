#include "common.h"


extern void *func_8003FC64(s32 arg0);
extern void *func_8003FD64(s32 arg0, s32 arg1);
extern void func_8004DCE0(s32 arg0);
extern void func_8004DCEC(void);
extern s32 func_800AE360(void);
extern void func_800AE414(void *arg0);
extern s32 func_800B0214(void *arg0);
extern s32 func_800B0718(void);
extern s32 func_800B1BEC(void *arg0, s32 arg1, s32 arg2);
extern u8 D_8001029C[];


typedef struct S_800AE324_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    void * unk_20;
    u8 pad_24[0x50];
    s32 unk_74;
} S_800AE324_0;   /* state in func_800AE324 */

typedef struct S_800AE324_1 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800AE324_1;   /* object in func_800AE324 */

s32 func_800AE324(s32 arg0) {
    register s32 held_arg ASM_REG("$18") = arg0;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register void *object ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    S_800AE324_0 *state;
    void *initializer;
    s32 count;
    s32 result;

    if (held_arg != 0) {
        object = func_8003FD64(0, held_arg);
        ASM_TAILSLOT_PIN(object);   /* MATCH pin: retail delay-slot contents depend on it */
        return func_800AE360();
    }

    object = func_8003FC64(0);
    if (object != 0) {
        initializer = (void *)0x8001029C;
        state = (u8 *)object + 0x20;
        state->unk_20 = initializer;
        state->unk_1C = func_800B0718();
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        count = state->unk_1C;
        ASM_KEEP(count);   /* MATCH pin: keeps a statement from moving across a call/branch */
        state->unk_74 = held_arg;
        if (count != 0) {
            state->unk_14 = (count - 1) / 10;
        }
        func_8004DCE0(1);
        func_8004DCEC();
        result = func_800B0214(object);
        ((S_800AE324_1 *)object)->unk_20 = result;
        if (result == 0) {
            goto failure;
        }
        result = func_800B1BEC(object, 0x48, -0x5C);
        state->unk_08 = result;
        if (result == 0) {
            goto failure;
        }
    }
cleanup:
    return (s32)object;
failure:
    func_800AE414(state);
    return 0;
}

/* MECHANISM: The 0x20 frame holds selector/object/state in s2/s1/s0; the CFG uses two
   LEAD22 sibcall tails. Pinning only the post-fence count to v1 makes the call result
   store from v0 first, then copy v0 to v1, closing the word-21 code-motion residue. */

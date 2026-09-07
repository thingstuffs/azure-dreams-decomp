/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

__asm__(".set D_8040C5DE_LOAD, 0x8040C5DE");
__asm__(".set D_8040C5DE_STORE, 0x8040C5DE");

extern u8 D_8040C5C0[];
extern u16 D_8040C5DE_LOAD[5];
extern u16 D_8040C5DE_STORE[5];
extern u8 D_8040086C[];
extern u8 D_80400894[];
extern void *func_8003C714(s32 arg0, void *arg1, s32 arg2);
extern s32 func_80047FD8(void *arg0);
extern void func_8007BEF0(s32 arg0);
extern void func_8007BFE0(void *arg0, s32 arg1);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_80408394(void *arg0, s32 arg1, s32 arg2);
extern void func_804084DC(void *arg0);
extern void func_804083A0(void);

/* Creates or resets the town object, initializes its state, and installs its callback. */
void *func_802F13FC(s32 init_value_a, M2C_UNK init_value_b) {
    void *object;
    u8 *state;

    object = D_8040C5C0;
    state = (u8 *)object + 0x20;
    if (func_80047FD8(object) == 0) {
        object = func_8003C714(0, D_8040C5C0, 0x19);
        if (object == NULL) {
            func_8007C040(D_8040086C, D_80400894, 0x173);
            func_8007BEF0(1);
            goto reset_object;
        }
    } else {
reset_object:
        func_804084DC(object);
        D_8040C5DE_STORE[0] = (u16) (D_8040C5DE_LOAD[0] & 0x7FFF);
        func_8007BFE0(state, 0x44);
    }
    func_80408394(state, init_value_a, init_value_b);
    *(void **)((u8 *)object + 0x10) = (void *)func_804083A0;
    return object;
}

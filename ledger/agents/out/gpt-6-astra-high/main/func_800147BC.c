#include "common.h"

extern void func_800209C4(void);
extern s32 func_800210E0(void);
extern s32 func_8002168C(void);
extern void func_80021904(void);
extern void func_80022EC4(void *arg0, void *arg1);

extern u8 D_8002789C[];
extern void *D_8002809C[];
extern s32 D_80083160[];

/* Updates the selected callback or triggers a one-time action when no callback is selected. */
void func_800277BC(void *state) {
    s32 callback_index;
    void *callback;

    if ((D_80083160[2] != 0) && (D_80083160[4] & 0x20)) {
        func_800209C4();
        *(s32 *)((u8 *)state + 0x38) = 0;
        *(void **)((u8 *)state - 0x10) = D_8002789C;
        return;
    }

    callback_index = func_8002168C();
    func_80021904();
    if (callback_index != 0) {
        *(s32 *)((u8 *)state + 0x38) = 0;
        *(s32 *)((u8 *)state + 0x30) = callback_index;
        callback = D_8002809C[callback_index];
        *(s32 *)((u8 *)state + 0x34) = callback_index;
        *(void **)((u8 *)state - 0x10) = callback;
        return;
    }

    if ((func_800210E0() == 3) && (*(s32 *)((u8 *)state + 0x38) == 0)) {
        func_80022EC4((u8 *)state - 0x20, (u8 *)state + 0x38);
        *(s32 *)((u8 *)state + 0x38) = 1;
    }
}

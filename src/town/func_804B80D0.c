#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct S_func_804B80D0_0 {
    u8 pad_00[8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_func_804B80D0_0;

typedef struct S_func_804B80D0_1 {
    u8 pad_00[2];
    u8 unk_02;
} S_func_804B80D0_1;

extern s32 func_8001611C(s32, s32);
extern s32 func_80018854(s32);
extern s32 func_800188CC(s32);
extern s32 func_8001894C(s32);
extern void *D_80016000;
extern s16 D_80018AEA;

/* Update action flags from the active entry and check whether the action is allowed. */
s32 func_800168D0(s32 object, s32 context) {
    s32 action_allowed;

    func_8001611C(object, context);
    if (func_8001894C(D_80018AEA) == 0) {
        func_80018854(0x511);
        if (((S_func_804B80D0_1 *)
             ((((S_func_804B80D0_0 *)D_80016000)->unk_08 * 8) +
              ((S_func_804B80D0_0 *)D_80016000)->unk_40))->unk_02 == 0) {
            func_800188CC(0x514);
        }
    }
    if (func_8001894C(0x514) == 0) {
        action_allowed = func_8001894C(0x11FC) == 0;
    } else {
        action_allowed = 1;
    }
    return action_allowed;
}

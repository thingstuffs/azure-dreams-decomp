#include "common.h"

extern void func_800A510C(void);
extern s32 D_80100DE0[];

/* tcame_return_plus: return the camera and clear its secondary state word. */
void func_800A5130(void) {
    s32 *camera_state = &D_80100DE0[0];

    func_800A510C();
    
    *(s32 *)((s8 *)camera_state + 4) = 0;
}

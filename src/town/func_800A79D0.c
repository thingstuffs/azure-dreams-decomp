#include "common.h"

extern void tcame_return(void);
extern s32 D_80100DE0[];

/* tcame_return_plus: return the camera and clear its secondary state word. */
void tcame_return_plus(void) {
    s32 *camera_state = &D_80100DE0[0];

    tcame_return();
    
    *(s32 *)((s8 *)camera_state + 4) = 0;
}

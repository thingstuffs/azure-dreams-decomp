#include "common.h"
#include "shared/game_work.h"

#include "common.h"

extern u8 D_80080A86;

extern s32 D_800814A0;



extern void func_80046884(void *a0, void *a1, s32 a2);
extern void func_8003BFE4(void);
extern void runActiveNodeCallbacks(void);
extern void removeMarkedActiveNodes(void);
extern void integrateActiveNodeVectors(void);
extern void func_8004D70C(void);
extern void func_800AC3EC(void);
extern void func_800AC4C4(void);
extern void dispatchRegisteredDrawCallbacks(void);
extern void appendDrawModePrimitive(void);

/* Runs node callbacks, removes flagged nodes, and updates movement and drawing state. */
void func_800400B8(void)
{
    GameWork *state = ((GameWork *)&gameWork);
    s32 mode;
    if ((D_80080A86 == 0) && (state->map.cells != 0)) {
        func_80046884(&state->view, &state->view.unk_008, 0);
        func_8003BFE4();
    }
    runActiveNodeCallbacks();
    if (D_800814A0 & 0x8000) {
        removeMarkedActiveNodes();
    }
    mode = D_80080A86;
    D_800814A0 = 0;
    if (mode == 0) {
        integrateActiveNodeVectors();
        func_8004D70C();
        if (state->map.cells != 0) {
            func_800AC3EC();
            func_800AC4C4();
        }
    }
    dispatchRegisteredDrawCallbacks();
    appendDrawModePrimitive();
}

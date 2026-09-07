#include "common.h"

extern void func_80067014(s32 arg0);
extern void func_800671A8();

// Clears a 480-wide rectangle with a height of 448 or 480.
void func_800402D8(s32 useFullHeight) {
    s16 clearRect[4];
    s16 extent;
    s32 blackComponent;

    func_80067014(0);
    extent = 0x1E0;
    clearRect[0] = 0;
    clearRect[1] = 0;
    clearRect[2] = extent;
    if (useFullHeight == 0) {
        extent = 0x1C0;
    }
    blackComponent = 0;
    clearRect[3] = extent;
    func_800671A8(clearRect, blackComponent, blackComponent, blackComponent);
    func_80067014(0);
}

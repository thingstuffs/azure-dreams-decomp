#include "common.h"

/* Entity spawn dispatcher: for type 0x38 runs two housekeeping passes first, then looks up/allocates the entity slot and dispatches to type-specific init (func_80047EEC for 0x38, func_80047FF4 otherwise). */
extern void func_800481E0(void);
extern void func_80047C00(void);
extern void *func_80047CD8(s16 a0);
extern void func_8003F320(void);
extern void func_80047EEC(s32 a0, void *a1);
extern void func_80047FF4(s32 a0, void *a1);

void func_80048088(s16 a0)
{
    void *p;

    if (a0 == 0x38) {
        func_800481E0();
        func_80047C00();
    }
    p = func_80047CD8(a0);
    if (p) {
        func_8003F320();
        if (a0 == 0x38) {
            func_80047EEC(0x38, p);
        } else {
            func_80047FF4(a0, p);
        }
    }
}

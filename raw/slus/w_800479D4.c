#include "common.h"

/* Registers two callbacks (event kind 6) with func_8003E4FC, built from
   func_80043704(a2,a0) and func_800437A4(a2,a1); a2 is a 16-bit id. */
extern void *func_80043704(s16 a0, s32 a1);
extern void *func_800437A4(s16 a0, s32 a1);
extern s32 func_8003E4FC(s32 a0, void *a1, void *a2);

void func_800479D4(s32 a0, s32 a1, s16 a2) {
    func_8003E4FC(6, func_80043704(a2, a0), 0);
    func_8003E4FC(6, func_800437A4(a2, a1), 0);
}

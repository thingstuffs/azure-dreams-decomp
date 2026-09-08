#include "common.h"

typedef void (*TownCallback)(s32, s32);

extern s8 D_80016000[];

/* Invoke the town callback with event 0x11 and value 0x200. */
void func_80018AEC(void) {
    (*(TownCallback *)((s8 *)*(void **)((s8 *)*(void **)D_80016000 + 0x20) + 0x2F8))(0x11, 0x200);
}

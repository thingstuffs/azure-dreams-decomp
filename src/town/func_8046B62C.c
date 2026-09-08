#include "common.h"

extern u8 D_80010000[];
extern s32 D_800186B4;

// Passes the table entry selected by callback 0x2D4 to callback 0x218.
void func_8001C62C(void) {
    (*(void (**)(s32))(
        *(u8 **)(*(u8 **)(D_80010000 + 0x6000) + 0x20) + 0x218))(
        *(s32 *)(((*(s32 (**)(s32))(
            *(u8 **)(*(u8 **)(D_80010000 + 0x6000) + 0x20) + 0x2D4))(0) * 4)
            + (u8 *)&D_800186B4));
}

#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern s8 D_80016000[];
extern s32 D_8001C9F4;
extern s32 func_80018BD0(s32);
extern s32 func_80018C50(s32);

typedef void (*TownCallback)(s32, s32);

/* Conditionally updates the town state pointer and invokes the town callback. */
s32 func_80016BE8(void) {
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    if (func_80018C50(0xFE8) == 0) {
        FIELD(
            FIELD(FIELD(D_80016000, void **, 0), void **, 0x1C),
            void **, 0x40) = &D_8001C9F4;
    }
    FIELD(
        FIELD(FIELD(D_80016000, void **, 0), void **, 0x20),
        TownCallback *, 0x2F8)(0x10, 0x200);
    return 0;
}

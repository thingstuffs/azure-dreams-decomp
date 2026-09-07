#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern s8 D_80016000[];
extern s32 D_80018FB4;
extern s32 func_80018BD0(s32);

s32 func_80016D74(void) {
    D_80018FB4 = FIELD(
        FIELD(FIELD(D_80016000, void **, 0), void **, 0x20),
        s32 (**)(s32), 0x54)(3);
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    FIELD(
        FIELD(FIELD(D_80016000, void **, 0), void **, 0x20),
        void (**)(s32, s32), 0x2F8)(0x10, 0x200);
    return 0;
}

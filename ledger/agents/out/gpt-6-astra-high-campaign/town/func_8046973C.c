#include "common.h"

extern void func_8001A1A0(s32, u32 *);
extern s32 D_80017AAC[];
extern s32 D_80017AB8[];
extern s32 D_80017AC4[];
extern s32 D_80017CA0[];

/* Apply three value tables to consecutive destinations and return their base. */
s32 func_8001A73C(void) {
    s32 *base_ptr = D_80017CA0;

    func_8001A1A0(base_ptr[0], D_80017AAC);
    func_8001A1A0(base_ptr[0] + 0x14, D_80017AB8);
    func_8001A1A0(base_ptr[0] + 0x28, D_80017AC4);
    return base_ptr[0];
}

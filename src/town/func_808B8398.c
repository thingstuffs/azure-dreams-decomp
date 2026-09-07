#include "common.h"

extern s32 D_00003F54[];
extern u8 D_00004154[];
extern s32 D_0000414C[];
extern s32 D_000045F8[];

s32 func_808B8398(void) {
    return D_000045F8[0] + D_0000414C[D_00004154[D_00003F54[0]]];
}

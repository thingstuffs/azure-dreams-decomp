#include "common.h"

extern s32 D_00003F54[];
extern s32 D_00004114[];
extern s8 D_00004120[];
extern s32 D_000045F8[];

s32 func_808B82AC(void) {
    return D_000045F8[0] + D_00004114[D_00004120[D_00003F54[0]]];
}

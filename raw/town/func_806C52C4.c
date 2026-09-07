#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef s32 (*Callback)(s32);

extern s8 D_80016000[];

s32 func_800162C4(void) {
    s32 temp_v1;

    FIELD(FIELD(FIELD(D_80016000, void *, 0), void *, 0x20), Callback, 0x248)(0);
    temp_v1 = FIELD(FIELD(FIELD(D_80016000, void *, 0), void *, 0x1C), s32, 4);
    return temp_v1 >= 0x3E0 ? temp_v1 < 0x3E5 : temp_v1 >= 0x3DC;
}

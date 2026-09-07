#include "common.h"

extern s32 func_800C07AC(s32);
typedef struct {
    s32 value;
    s32 pad[2];
} GlobalS32;

extern GlobalS32 D_800DF55C;
extern GlobalS32 D_800DF560;

s32 func_800C27F0(void) {
    s32 result;

    result = func_800C07AC(D_800DF55C.value - 0x20);
    D_800DF560.value = result;
    return result != 0;
}

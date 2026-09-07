#include "common.h"

#include "common.h"

extern void ClearImage(void *rect, s32 r, s32 g, s32 b);

void func_800391BC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x20) = 0;
    *(s16 *)((u8 *)arg0 + 0x22) = 0;
    ClearImage(arg0, 0, 0, 0);
}

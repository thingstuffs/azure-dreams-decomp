#include "common.h"

typedef struct {
    int val;
    int pad[2];
} S_800814A0;
extern S_800814A0 D_800814A0;

void func_7FDD3B24(void *arg0) {
    u8 *v1 = *(u8 **)((u8 *) arg0 + 4);
    s32 idx = *(s32 *)((u8 *) arg0 + 0x18);
    s16 val;

    val = (s16)(*(u16 *)(v1 + (idx * 2) + 0xE) << 0x10 >> 0x12);
    *(s16 *)((u8 *) arg0 + 0x10) = val;
    if (*(s16 *)(v1 + 0x16) & 0x8000) {
        *(u16 *)((u8 *) arg0 - 2) = *(u16 *)((u8 *) arg0 - 2) | 0x8000;
        D_800814A0.val |= 0x8000;
    }
}

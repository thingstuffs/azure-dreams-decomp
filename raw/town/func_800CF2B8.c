#include "common.h"

typedef struct {
    s8 active;
    u8 pad1[3];
    void *object;
} ObjectSlot;

extern ObjectSlot D_80082660[];
extern void func_800C4174(void *arg0, s32 arg1, s32 arg2);

void func_800CCA18(void *arg0, s32 arg1, s32 arg2) {
    s32 index;

    index = *(s32 *)((u8 *)arg0 + 0x60);
    D_80082660[index].object = (u8 *)arg0 - 0x20;
    D_80082660[*(s32 *)((u8 *)arg0 + 0x60)].active = 0;
    func_800C4174(arg0, arg1, arg2);
}

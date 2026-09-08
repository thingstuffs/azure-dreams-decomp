#include "common.h"

typedef struct {
    u8 field0;
    u8 pad1;
    u8 field2;
    u8 pad3[5];
} S_80082660;

extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern S_80082660 D_80082660[];
extern u8 D_800CB0F0[];
extern u8 D_800D68D4[];

/* Initializes an entity, sets its state to 6, and copies its table entry's byte. */
void func_800CB168(void *entity, s32 unused, s32 init_value) {
    func_800C2E84(entity, init_value, D_800D68D4);
    D_80082660[*(s32 *)((u8 *)entity + 0x60)].field0 = 0;
    *(void **)((u8 *)entity + 0x54) = D_800CB0F0;
    *(s16 *)((u8 *)entity + 0x6C) = 6;
    *(u8 *)((u8 *)entity + 0x96) = D_80082660[*(s32 *)((u8 *)entity + 0x60)].field2;
}

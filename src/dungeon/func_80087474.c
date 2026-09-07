#include "common.h"

typedef struct {
    s8 pad00[0xA];
    u16 fieldA;
} D_80083460_t;

extern void func_80048A44(void *, u8, s32, s32);
extern void func_80094E34(void);
extern s32 func_800A2B04();
extern s16 D_80083228;
extern D_80083460_t D_80083460;
extern u8 D_800DD120[];

void func_8008CBD4(void *arg0, void *arg1, void *arg2, void *arg3) {
    *(u8 **)((s8 *)arg2 + 0x2C) = D_800DD120;
    func_80048A44(arg2, D_800DD120[((D_80083228 + *(s16 *)((s8 *)arg3 + 0x2A) + 0x100) >> 9) & 7], 0, 1);
    *(u8 *)((s8 *)arg0 + 0x9A) = 8;
    *(s8 *)((s8 *)arg0 + 0x9B) = 0;
    *(s32 *)((s8 *)arg0 + 0x8C) = 0;
    func_80094E34();
    *(s32 *)((s8 *)arg3 + 0x1C) &= ~0x1638;
    *(s32 *)((s8 *)arg1 + 0x10) = 0;
    *(s32 *)((s8 *)arg1 + 0xC) = 0;
    func_800A2B04(arg1, *(u8 *)((s8 *)arg2 + 0x24), *(u8 *)((s8 *)arg2 + 0x25));
    D_80083460.fieldA += 1;
}

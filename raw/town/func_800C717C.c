#include "common.h"

typedef struct {
    s8 val;
    u8 pad[7];
} Rec8;

extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern s16 func_800C2B88(s16 arg0, s16 arg1, s32 arg2);
extern void func_800C3C5C(void);
extern Rec8 D_80082660[];

void func_800C48DC(void *arg0, s32 arg1, s32 arg2) {
    func_800C2E84(arg0, arg2, *(void **)((u8 *)*(void **)((u8 *)arg0 + 0x80) + 0x14));
    D_80082660[*(s32 *)((u8 *)arg0 + 0x60)].val = 0;
    *(void **)((u8 *)arg0 + 0x54) = (void *)func_800C3C5C;
    *(s16 *)((u8 *)arg0 + 0x72) = func_800C2B88(
        *(s16 *)((u8 *)arg0 + 0x88),
        *(s16 *)((u8 *)arg0 + 0x8A),
        arg1);
}

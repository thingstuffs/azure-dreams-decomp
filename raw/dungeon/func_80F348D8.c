#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 counter;
} State;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, u8, s32);
extern s32 func_800A2BDC(void *);
extern s32 func_800A6D30(void);
extern s16 D_80083228;
extern State D_80083460;
extern u16 D_80083462;
extern u8 D_80174AE4[];

void func_801720D8(void *arg0, void *arg1, void *arg2, void *arg3) {
    register s32 value ASM_REG("$2");

    FIELD(arg3, u8, 0x71) = (u8)(FIELD(arg3, u8, 0x71) & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2BDC(arg3) << 16) == 0)) {
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg0, s8, 0x9A) = 0x17;
        FIELD(arg0, s8, 0x9B) = 0;
        if (FIELD(arg3, s32, 0x1C) & 0x400) {
            value = FIELD(arg3, s32, 0x14);
            if (value >= 0) {
                FIELD(arg3, s32, 0x14) = (s32)(value | 0x80000000);
                FIELD(arg3, u16, 0x2A) = (u16)(FIELD(arg3, u16, 0x2A) + ((func_800A6D30() & 7) << 9));
            }
        }
        FIELD(arg0, s16, 0x96) = 0;
        D_80083460.counter = (u16)(D_80083460.counter + 1);
        FIELD(arg3, u8, 0x6D) = (u8)(FIELD(arg3, u8, 0x6D) - 1);
        FIELD(arg2, void *, 0x2C) = D_80174AE4;
        func_80047784(arg2, D_80174AE4[((D_80083228 + (s16)FIELD(arg3, u16, 0x2A) + 0x100) >> 9) & 7], 0);
    }
}

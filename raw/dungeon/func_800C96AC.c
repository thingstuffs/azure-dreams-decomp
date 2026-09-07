#include "common.h"

extern u8 D_80083460[];
extern u8 D_800CEA44[];
extern u8 D_800E3648[];

extern s32 func_8003FA44(s32 arg0, void *arg1);
extern void *func_8003FC64(s32 arg0);
extern void func_80053DA8(s32 arg0);
extern void func_800CEED8(void);

unsigned int func_800CEE0C(void *arg0, s16 arg1)
{
    s32 result;
    u8 *page;
    u8 *entry;
    register u8 *entry_base;
    u16 *state;
    void *node;
    int new_var;

    if (*((u8 *)arg0 + 0x13) != 0) {
        func_800CEED8();
        result = 1;
    } else {
#ifdef NON_MATCHING
    page = D_80083460 - 0x3460;
#else
    page = (u8 *)0x80080000;
#endif
    entry_base = D_800E3648;
    ASM_KEEP(page);
    ASM_KEEP(entry_base);
    entry = (u8 *)(((s32)(arg1 << 0x10) >> 0xE) + (u32)entry_base);
    ASM_KEEP(entry);
    state = (u16 *)(page + 0x3460);
    ASM_KEEP(state);
    if ((s16)(state[14] + *(s8 *)(entry + 2)) >= 0x21) {
        *(u8 *)(entry + 2) = 0x20 - *(u8 *)&state[14];
    }

    result = func_8003FA44(*(s8 *)(entry + 2) + 1, entry);
    new_var = result != 0;
    if (new_var) {
        node = func_8003FC64(2);
        if (node != 0) {
            *(u8 **)((u8 *)node + 0x10) = D_800CEA44;
            *(s16 *)((u8 *)node + 0x2C) = arg1;
            state[5] += 1;
            func_80053DA8(0xB1);
        }
        result = node != 0;
    } else {
        result = 0;
    }
    }

    return result;
}

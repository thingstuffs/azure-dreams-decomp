#include "common.h"

extern u8 D_80083460[];
extern u8 D_800CEA44[];
extern u8 D_800E3648[];

extern s32 func_8003FA44(s32 arg0, void *arg1);
extern void *func_8003FC64(s32 arg0);
extern void SD_Call(s32 arg0);

/* Clamp an indexed entry and create its node if processing succeeds. */
unsigned int func_800CEE0C(void *object, s16 entry_index)
{
    s32 result;
    u8 *state_page;
    u8 *entry;
    register u8 *entries;
    u16 *state;
    void *node;
    int entry_ready;

    if (*((u8 *)object + 0x13) != 0) {
        return 1;
        result = 1;
    } else {
#ifdef NON_MATCHING
        state_page = D_80083460 - 0x3460;
#else
        state_page = (u8 *)0x80080000;
#endif
        entries = D_800E3648;
        ASM_KEEP(state_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        entry = (u8 *)(((s32)(entry_index << 0x10) >> 0xE) + (u32)entries);
        state = (u16 *)(state_page + 0x3460);
        if ((s16)(state[14] + *(s8 *)(entry + 2)) >= 0x21) {
            *(u8 *)(entry + 2) = 0x20 - *(u8 *)&state[14];
        }

        result = func_8003FA44(*(s8 *)(entry + 2) + 1, entry);
        entry_ready = result != 0;
        if (entry_ready) {
            node = func_8003FC64(2);
            if (node != 0) {
                *(u8 **)((u8 *)node + 0x10) = D_800CEA44;
                *(s16 *)((u8 *)node + 0x2C) = entry_index;
                state[5] += 1;
                SD_Call(0xB1);
            }
            result = node != 0;
        } else {
            result = 0;
        }
    }

    return result;
}

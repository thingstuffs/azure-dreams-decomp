#include "common.h"

typedef struct {
    u8 pad0[6];
    s16 field_0x6;
    u8 pad8[4];
} DungeonState;

extern void func_800A08A0(s32);
extern s32 func_800A6D30(void);
extern s16 D_8008146E;
extern DungeonState D_80083460;

#ifdef NON_MATCHING
#define COMPILER_KEEP(value) ((void)0)
#else
#define COMPILER_KEEP(value) \
    __asm__ __volatile__("" : "=r"(value) : "0"(value))
#endif

void func_800A0DD8(void) {
    DungeonState *state;
    s16 counter;

    if (D_8008146E != 0) {
        state = &D_80083460;
        COMPILER_KEEP(state);
        counter = state->field_0x6 - 1;
        state->field_0x6 = counter;
        if (counter < 0) {
            state->field_0x6 = (func_800A6D30() & 0x1F) | 0x20;
            func_800A08A0(0);
        }
    }
}

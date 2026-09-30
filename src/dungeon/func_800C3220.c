#include "common.h"

typedef struct State {
    u8 pad[3];
    u8 divisor;
} State;

extern s32 func_800A48F0(State *, s32, s8);
extern s32 func_800A6D30(void);
extern s32 func_800C8484(State *);

/* Roll the state's chance and, on a hit, apply effect 4 to it. */
s32 func_800C8980(State *state, s16 value, s8 flag) {
    s32 roll;
    u16 chance;

    if (func_800C8484(state) != 0) {
        return 0;
    }
    roll = func_800A6D30() & 0xFFFF;
    if (state->divisor != 0) {
        chance = roll % state->divisor;
    } else {
        chance = 0;
    }
    if (chance < value || value == 255) {
        if ((s32)((u32)func_800A48F0(state, 4, flag) << 16) >= 0) {
            return 1;
        }
    }
    return 0;
}

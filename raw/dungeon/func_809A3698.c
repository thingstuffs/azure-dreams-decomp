#include "common.h"

/* Recovered complete gap routine; not registered or assigned to a native module. */
typedef union { s32 word; struct { u16 low, high; } half; } FixedCoord;
typedef struct { FixedCoord x, y, z; } MotionPosition;
typedef struct { u8 pad00[0x14]; s16 direction; u8 pad16[0x1C]; s16 speed; } MotionState;
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 func_800BCB04(s32 x, s32 y, s16 height);
extern s32 D_800814A0;
void func_80174E98(MotionState *state, MotionPosition *position) {
    s16 height;
    s16 speed;
    height = func_800BCB04(position->x.half.high, position->y.half.high, (s16)(position->z.half.high + 2));
    if ((s16)position->z.half.high < height) {
        position->x.word -= (D_8006CCD8[state->direction] * state->speed) << 11;
        position->y.word -= (D_8006CCE8[state->direction] * state->speed) << 11;
        position->z.word += (0xC0 - state->speed) << 10;
    }
    speed = state->speed - 8;
    state->speed = speed;
    if (speed <= 0) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

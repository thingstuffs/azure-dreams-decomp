#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad0[0xBC];
    u16 field_BC;
    u16 field_BE;
    u8 pad_C0[8];
    s16 field_C8;
} GlobalState;

typedef struct {
    s16 field_0;
    s16 field_2;
    u16 field_4;
    u16 field_6;
    s32 field_8;
    s16 field_C;
} State;

extern s32 func_80064584(s32);
extern s16 func_80065F90(s32, s32);
extern void func_800A25CC(State *);

/* Updates state from global values and triggers a refresh every 15 calls. */
void func_800A24FC(State *state) {

    state->field_8 = (func_80064584(gameWork.viewAngle) + 0x1000) / 2;
    state->field_0 = -func_80064584(gameWork.viewAngle) / 24;
    state->field_2 = func_80065F90(state->field_0, 160);
    state->field_4 = ((u16)gameWork.unk_0BC);
    state->field_6 = ((u16)gameWork.unk_0BE);

    if (--state->field_C <= 0) {
        state->field_C = 15;
        func_800A25CC(state);
    }
}
